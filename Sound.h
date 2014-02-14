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
//DirectSound��p���Č��ʉ��̍Đ����s��
//�������̂��ǂݍ��߂Ȃ��͖�������{�I�ɂ�100��KB�O���ڈ���
//
//��ɓǂݍ��މ��������C���X�^���X�쐬���Ă����Ƃ�����������Ȃ�
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
	//�R���X�g���N�^��f�X�g���N�^
	//���̉����ɖ炷�t�@�C�����w��
	CSound(HWND hWnd, LPCTSTR file_name);
	virtual ~CSound(void);
	
	//�t�@�C������ǂݍ���(����o�b�t�@�Ŗ炷����ς���Ƃ�
	BOOL LoadWave(LPCTSTR file_name);

	//�Đ�
	BOOL Play();
	BOOL LoopPlay();
	//��~
	BOOL Stop();
	BOOL LoopStop();
};
