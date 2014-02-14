#pragma once

#pragma comment (lib, "strmiids.lib")

#include <dshow.h>

#define RELEASE(p) { if(p){(p)->Release();p=NULL;} }
#define WM_DIRECTSHOWMESSAGE (WM_APP + 1)

///////////////////////////////////////////////////////////////////
//
//DirectShow�����y�Đ��֘A�̂ݒ��ȈՓI�Ɏg���N���X
//���[�v�Đ��̐��x�͂��܂�悭�Ȃ��̂ŐM�����Ă͂Ȃ�Ȃ�
//
// ���������K���X���b�h�̍ŏ���COM�̏����������邱�ƁI�I�I�I�I�I��������
//
///////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------//
//Music�N���X
//-----------------------------------------------------------------//
class CMusic
{
	IGraphBuilder *m_lpGraph;			//�t�B���^�O���t�}�l�[�W��

	IMediaControl *m_lpMediaControl;	//���f�B�A�R���g���[��
	IMediaEventEx *m_lpMediaEvent;		//���f�B�A�C�x���g
	IMediaSeeking *m_lpMediaSeeking;	//���f�B�A�V�[�L���O
	IVideoWindow  *m_lpVideoWindow;		//�r�f�I�E�B���h�E
	IBasicVideo   *m_lpBasicVideo;		//�x�[�V�b�N�r�f�I
	IBasicAudio   *m_lpBasicAudio;		//�x�[�V�b�N�I�[�f�B�I
	HRESULT m_hResult;
	HWND *m_hWnd;
public:
	//�R���X�g���N�^��f�X�g���N�^
	//COM�����������Ă���C���X�^���X�̍쐬�����邱��
	CMusic(HWND *hWnd, LPCTSTR file_name);
	virtual ~CMusic(void);

	//�t�@�C������ǂݍ���
	BOOL LoadMusicFile(LPCTSTR file_name);
	//���낢��ƊJ������
	BOOL UnInit();

	//���ꂼ��Đ��A�ꎞ��~�A��~
	//������LoopPlay��WM_DIRECTSHOWMESSAGE���b�Z�[�W����
	//�ĂԂ��Ƃɂ���ă��[�v�Đ�����B
	BOOL Play();
	BOOL Pause();
	BOOL Stop();
	BOOL LoopPlay();
};
