#pragma once

#pragma comment (lib, "dsound.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")

#include <dsound.h>
#include <mmsystem.h>

#define RELEASE(p) { if(p){(p)->Release();p=NULL;} }
#define SAMETIMESOUND 100

///////////////////////////////////////////////////////////////////
//
//DirectSoundを用いて効果音の再生を行う
//長いものも読み込めなくは無いが基本的には100数KB前後を目安に
//
//先に読み込む音数だけインスタンス作成しておくといいかもしれない
//
///////////////////////////////////////////////////////////////////

class CSound
{
	static IDirectSound8 *m_pDS8;
	IDirectSoundBuffer8 *m_pDSBuffer;
	IDirectSoundBuffer8 *m_pDSBufferSync[SAMETIMESOUND];

	int sound_count;
	
	BOOL Init(HWND hWnd);
	BOOL UnInit();
	BOOL OpenWave(LPCTSTR file_name, WAVEFORMATEX &waveFormatEx, 
		char** ppData, DWORD &dataSize);

public:
	//コンストラクタ･デストラクタ
	//実体化時に鳴らすファイルを指定
	CSound(HWND hWnd, LPCTSTR file_name);
	virtual ~CSound(void);
	
	//ファイルから読み込む(同一バッファで鳴らす音を変えるとき
	BOOL LoadWave(LPCTSTR file_name);

	//再生
	BOOL Play();
	BOOL LoopPlay();
	//停止
	BOOL Stop();
	BOOL LoopStop();
};
