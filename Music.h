#pragma once

#pragma comment (lib, "strmiids.lib")

#include <dshow.h>

#define RELEASE(p) { if(p){(p)->Release();p=NULL;} }
#define WM_DIRECTSHOWMESSAGE (WM_APP + 1)

///////////////////////////////////////////////////////////////////
//
//DirectShowを音楽再生関連のみ超簡易的に使うクラス
//ループ再生の精度はあまりよくないので信頼してはならない
//
// ※※※※必ずスレッドの最初でCOMの初期化をすること！！！！！！※※※※
//
///////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------//
//Musicクラス
//-----------------------------------------------------------------//
class CMusic
{
	IGraphBuilder *m_lpGraph;			//フィルタグラフマネージャ

	IMediaControl *m_lpMediaControl;	//メディアコントロール
	IMediaEventEx *m_lpMediaEvent;		//メディアイベント
	IMediaSeeking *m_lpMediaSeeking;	//メディアシーキング
	IVideoWindow  *m_lpVideoWindow;		//ビデオウィンドウ
	IBasicVideo   *m_lpBasicVideo;		//ベーシックビデオ
	IBasicAudio   *m_lpBasicAudio;		//ベーシックオーディオ
	HRESULT m_hResult;
	HWND *m_hWnd;
public:
	//コンストラクタ･デストラクタ
	//COMを初期化してからインスタンスの作成をすること
	CMusic(HWND *hWnd, LPCTSTR file_name);
	virtual ~CMusic(void);

	//ファイルから読み込む
	BOOL LoadMusicFile(LPCTSTR file_name);
	//いろいろと開放する
	BOOL UnInit();

	//それぞれ再生、一時停止、停止
	//ただしLoopPlayはWM_DIRECTSHOWMESSAGEメッセージ下で
	//呼ぶことによってループ再生する。
	BOOL Play();
	BOOL Pause();
	BOOL Stop();
	BOOL LoopPlay();
};
