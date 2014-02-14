#include "Sound.h"

IDirectSound8 *CSound::m_pDS8 =NULL;

CSound::CSound(HWND hWnd, LPCTSTR file_name)
:m_pDSBuffer(NULL),sound_count(0)
{
	Init(hWnd);
	LoadWave(file_name);
}

CSound::~CSound(void)
{
	UnInit();
}

BOOL CSound::Init(HWND hWnd)
{
	// DirectSoundデバイス作成
	if(NULL ==m_pDS8)
	{
		DirectSoundCreate8(NULL, &m_pDS8, NULL);
		m_pDS8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
	}

	return TRUE;
}
BOOL CSound::UnInit()
{
	for(int i=0;i <SAMETIMESOUND;++i)
	{
		RELEASE(m_pDSBufferSync[i]);
	}
	RELEASE(m_pDSBuffer);
	//RELEASE(m_pDS8);
	return TRUE;
}

BOOL CSound::OpenWave(LPCTSTR file_name, WAVEFORMATEX &waveFormatEx, char** ppData, DWORD &dataSize)
{
	if ( file_name == 0 )
		return FALSE;

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	// Waveファイルオープン
	memset( &mmioInfo, 0, sizeof(MMIOINFO) );
	hMmio = mmioOpen((LPWSTR)file_name, &mmioInfo, MMIO_READ );
	if( !hMmio )
		return FALSE; // ファイルオープン失敗

	// RIFFチャンク検索
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend( hMmio, &riffChunk, NULL, MMIO_FINDRIFF );
	if( mmRes != MMSYSERR_NOERROR ) 
	{
		mmioClose( hMmio, 0 );
		return FALSE;
	}

	// フォーマットチャンク検索
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend( hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK );
	if( mmRes != MMSYSERR_NOERROR ) 
	{
		mmioClose( hMmio, 0 );
		return FALSE;
	}
	DWORD fmsize = formatChunk.cksize;
	DWORD size = mmioRead( hMmio, (HPSTR)&waveFormatEx, fmsize );
	if( size != fmsize ) 
	{
		//mmioREADでWaveのフォーマットを読み込んで、読み込み予定サイズと実際のサイズを比較
		mmioClose( hMmio, 0 );
		return FALSE;
	}

	mmioAscend( hMmio, &formatChunk, 0 ); //一個上の階層に上がる

	// データチャンク検索
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend( hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK );
	if( mmRes != MMSYSERR_NOERROR ) 
	{
		mmioClose( hMmio, 0 );
		return FALSE;
	}

	*ppData = new char[ dataChunk.cksize ];//データのサイズ分確保
	size = mmioRead( hMmio, (HPSTR)*ppData, dataChunk.cksize );//出たそのものの読み込み
	if(size != dataChunk.cksize ) 
	{
		delete[] *ppData;
		return FALSE;
	}
	dataSize = size;

	// ハンドルクローズ
	mmioClose( hMmio, 0 );

	return TRUE;
}

BOOL CSound::LoadWave(LPCTSTR file_name)
{
	// Waveファイルオープン
	WAVEFORMATEX wFmt;
	char *pWaveData = NULL;
	DWORD waveSize = 0;
	if ( !OpenWave(file_name, wFmt, &pWaveData, waveSize ) )
		return FALSE;
	
	// セカンダリバッファ情報
	DSBUFFERDESC DSBufferDesc;
	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS;
	DSBufferDesc.dwBufferBytes = waveSize;
	DSBufferDesc.dwReserved = 0;
	DSBufferDesc.lpwfxFormat = &wFmt;
	DSBufferDesc.guid3DAlgorithm = GUID_NULL;

	//セカンダリバッファ作成
	IDirectSoundBuffer *ptmpBuf = NULL;
	m_pDS8->CreateSoundBuffer( &DSBufferDesc, &ptmpBuf, NULL );//DirectSoundBufferインタフェースが返る
	ptmpBuf->QueryInterface( IID_IDirectSoundBuffer8 ,(void**)&m_pDSBuffer);//DirectSoundBufferをDirectSoundBuffer8インタフェースに変換
	RELEASE(ptmpBuf);//DirectSoundBufferインタフェースを取得したかっただけなので開放
	ptmpBuf = NULL;
	if ( m_pDSBuffer == 0 ) {
		RELEASE(m_pDS8);
		return FALSE;
	}

	LPVOID lpvWrite = 0;
	DWORD dwLength = 0;
	if ( DS_OK == m_pDSBuffer->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER ) ) {
		memcpy( lpvWrite, pWaveData, dwLength);
		m_pDSBuffer->Unlock( lpvWrite, dwLength, NULL, 0);
	}
	delete[] pWaveData; // 元音はもういらない

	//同時再生できるように複製する
	for(int i=0;i<SAMETIMESOUND;i++)
	{
		m_pDS8->DuplicateSoundBuffer(m_pDSBuffer, &ptmpBuf);
		ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_pDSBufferSync[i]);//QueryInterfaceでver8に変換
		RELEASE(ptmpBuf);
	}

	return TRUE;
}

BOOL CSound::Play()
{
	m_pDSBufferSync[sound_count]->Play(0, 0, 0);
	++sound_count;
	if(sound_count>=SAMETIMESOUND)
		sound_count =0;
	return TRUE;
}

BOOL CSound::LoopPlay()
{
	m_pDSBufferSync[sound_count]->Play(0, 0, DSBPLAY_LOOPING);

	return TRUE;
}

BOOL CSound::Stop()
{
	for(int i=0;i<SAMETIMESOUND;++i)
	{
		m_pDSBufferSync[i]->Stop();
	}
	sound_count =0;
	return TRUE;
}

BOOL CSound::LoopStop()
{
	m_pDSBufferSync[sound_count]->Stop();
	++sound_count;
	if(sound_count >=10)
		sound_count =0;

	return TRUE;
}

