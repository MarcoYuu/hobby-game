#include "Music.h"

//コンストラクタ
CMusic::CMusic(HWND *hWnd, LPCTSTR file_name)
:m_hWnd(hWnd),m_hResult(0),m_lpGraph(NULL),
m_lpMediaControl(NULL),m_lpMediaEvent(NULL),m_lpMediaSeeking(NULL),
m_lpVideoWindow(NULL),m_lpBasicVideo(NULL),m_lpBasicAudio(NULL)
{
	LoadMusicFile(file_name);
}

//デストラクタ
CMusic::~CMusic(void)
{	
	UnInit();
}

//ファイルから音楽を読み込む
BOOL CMusic::LoadMusicFile(LPCTSTR file_name)
{
	Stop();
	UnInit();
	//フィルタグラフマネージャを作成する
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (LPVOID *)&m_lpGraph);

	//フィルタグラフを構築する
	m_hResult = m_lpGraph->RenderFile(file_name, NULL);
	if (FAILED(m_hResult)) return FALSE;

	//メディアコントロールインターフェイスを要求する
	m_hResult = m_lpGraph->QueryInterface(IID_IMediaControl, (LPVOID *)&m_lpMediaControl);
	if (FAILED(m_hResult)) return FALSE;

	//メディアイベントインターフェイスを要求する
	m_hResult = m_lpGraph->QueryInterface(IID_IMediaEventEx, (LPVOID *)&m_lpMediaEvent);
	if (FAILED(m_hResult)) return FALSE;

	//メディアシーキングインターフェイスを要求する
	m_hResult = m_lpGraph->QueryInterface(IID_IMediaSeeking, (LPVOID *)&m_lpMediaSeeking);
	if (FAILED(m_hResult)) return FALSE;

	//ビデオウィンドウインターフェイスを要求する
	m_hResult = m_lpGraph->QueryInterface(IID_IVideoWindow, (LPVOID *)&m_lpVideoWindow);
	if (FAILED(m_hResult)) return FALSE;

	//ベーシックビデオインターフェイスを要求する
	m_hResult = m_lpGraph->QueryInterface(IID_IBasicVideo, (LPVOID *)&m_lpBasicVideo);
	if (FAILED(m_hResult)) return FALSE;

	//ベーシックオーディオインターフェイスを要求する
	m_hResult = m_lpGraph->QueryInterface(IID_IBasicAudio, (LPVOID *)&m_lpBasicAudio);
	if (FAILED(m_hResult)) return FALSE;

	//ループ再生用のイベントを通知
	m_lpMediaEvent->SetNotifyWindow((OAHWND)(*m_hWnd),WM_DIRECTSHOWMESSAGE,(LPARAM)this);

	return TRUE;
}

//開放する
BOOL CMusic::UnInit()
{
	//インターフェイスを開放する
	RELEASE(m_lpMediaControl);
	RELEASE(m_lpMediaEvent);
	RELEASE(m_lpMediaSeeking);
	RELEASE(m_lpVideoWindow);
	RELEASE(m_lpBasicVideo);
	RELEASE(m_lpBasicAudio);

	//フィルタグラフマネージャを開放する
	RELEASE(m_lpGraph);

	return TRUE;
}

//再生する
BOOL CMusic::Play()
{
	//メディアコントロールが存在しない
	if (!m_lpMediaControl) return FALSE;

	//再生する
	if (FAILED(m_lpMediaControl->Run())) return FALSE;

	return TRUE;
}

//ループさせる場合にはプロシージャのWM_DIRECTSHOWMESSAGEメッセージ下で必ず呼ぶこと
BOOL CMusic::LoopPlay()
{
	long lEventCode; 
	LONG_PTR lEvParam1,lEvParam2;
	BOOL bIsComplete = FALSE;
	do{
		//イベントを取得
		m_hResult = m_lpMediaEvent->GetEvent(&lEventCode,&lEvParam1,&lEvParam2,0);
		if(m_hResult == S_OK)
		{
			//再生終了であったときフラグを立てる
			if(lEventCode == EC_COMPLETE) bIsComplete = TRUE;

			//イベントを削除
			m_lpMediaEvent->FreeEventParams(lEventCode,lEvParam1,lEvParam2);
		}
	} while(m_hResult == S_OK);

	//再生終了のときループさせる
	if(bIsComplete){
		Stop();
		Play();
	}

	return TRUE;
}

//一時停止
BOOL CMusic::Pause()
{
	//メディアコントロールが存在しない
	if (!m_lpMediaControl) return FALSE;

	//一時停止する
	if (FAILED(m_lpMediaControl->Pause())) return FALSE;

	return TRUE;
}

//停止
BOOL CMusic::Stop()
{
	//メディアコントロールが存在しない
	if (!m_lpMediaControl) return FALSE;

	//一時停止する
	if (FAILED(m_lpMediaControl->Pause())) return FALSE;

	//メディアシーキングが存在しない
	if (!m_lpMediaSeeking) return FALSE;

	LONGLONG llSeekTime = 0; //シークタイム

	//先頭位置に設定する
	if (FAILED(m_lpMediaSeeking->SetPositions(&llSeekTime,
		AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning))) return FALSE;

	return TRUE;
}
