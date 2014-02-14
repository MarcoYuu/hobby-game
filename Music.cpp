#include "Music.h"

//�R���X�g���N�^
CMusic::CMusic(HWND *hWnd, LPCTSTR file_name)
:m_hWnd(hWnd),m_hResult(0),m_lpGraph(NULL),
m_lpMediaControl(NULL),m_lpMediaEvent(NULL),m_lpMediaSeeking(NULL),
m_lpVideoWindow(NULL),m_lpBasicVideo(NULL),m_lpBasicAudio(NULL)
{
	LoadMusicFile(file_name);
}

//�f�X�g���N�^
CMusic::~CMusic(void)
{	
	UnInit();
}

//�t�@�C�����特�y��ǂݍ���
BOOL CMusic::LoadMusicFile(LPCTSTR file_name)
{
	Stop();
	UnInit();
	//�t�B���^�O���t�}�l�[�W�����쐬����
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (LPVOID *)&m_lpGraph);

	//�t�B���^�O���t���\�z����
	m_hResult = m_lpGraph->RenderFile(file_name, NULL);
	if (FAILED(m_hResult)) return FALSE;

	//���f�B�A�R���g���[���C���^�[�t�F�C�X��v������
	m_hResult = m_lpGraph->QueryInterface(IID_IMediaControl, (LPVOID *)&m_lpMediaControl);
	if (FAILED(m_hResult)) return FALSE;

	//���f�B�A�C�x���g�C���^�[�t�F�C�X��v������
	m_hResult = m_lpGraph->QueryInterface(IID_IMediaEventEx, (LPVOID *)&m_lpMediaEvent);
	if (FAILED(m_hResult)) return FALSE;

	//���f�B�A�V�[�L���O�C���^�[�t�F�C�X��v������
	m_hResult = m_lpGraph->QueryInterface(IID_IMediaSeeking, (LPVOID *)&m_lpMediaSeeking);
	if (FAILED(m_hResult)) return FALSE;

	//�r�f�I�E�B���h�E�C���^�[�t�F�C�X��v������
	m_hResult = m_lpGraph->QueryInterface(IID_IVideoWindow, (LPVOID *)&m_lpVideoWindow);
	if (FAILED(m_hResult)) return FALSE;

	//�x�[�V�b�N�r�f�I�C���^�[�t�F�C�X��v������
	m_hResult = m_lpGraph->QueryInterface(IID_IBasicVideo, (LPVOID *)&m_lpBasicVideo);
	if (FAILED(m_hResult)) return FALSE;

	//�x�[�V�b�N�I�[�f�B�I�C���^�[�t�F�C�X��v������
	m_hResult = m_lpGraph->QueryInterface(IID_IBasicAudio, (LPVOID *)&m_lpBasicAudio);
	if (FAILED(m_hResult)) return FALSE;

	//���[�v�Đ��p�̃C�x���g��ʒm
	m_lpMediaEvent->SetNotifyWindow((OAHWND)(*m_hWnd),WM_DIRECTSHOWMESSAGE,(LPARAM)this);

	return TRUE;
}

//�J������
BOOL CMusic::UnInit()
{
	//�C���^�[�t�F�C�X���J������
	RELEASE(m_lpMediaControl);
	RELEASE(m_lpMediaEvent);
	RELEASE(m_lpMediaSeeking);
	RELEASE(m_lpVideoWindow);
	RELEASE(m_lpBasicVideo);
	RELEASE(m_lpBasicAudio);

	//�t�B���^�O���t�}�l�[�W�����J������
	RELEASE(m_lpGraph);

	return TRUE;
}

//�Đ�����
BOOL CMusic::Play()
{
	//���f�B�A�R���g���[�������݂��Ȃ�
	if (!m_lpMediaControl) return FALSE;

	//�Đ�����
	if (FAILED(m_lpMediaControl->Run())) return FALSE;

	return TRUE;
}

//���[�v������ꍇ�ɂ̓v���V�[�W����WM_DIRECTSHOWMESSAGE���b�Z�[�W���ŕK���ĂԂ���
BOOL CMusic::LoopPlay()
{
	long lEventCode; 
	LONG_PTR lEvParam1,lEvParam2;
	BOOL bIsComplete = FALSE;
	do{
		//�C�x���g���擾
		m_hResult = m_lpMediaEvent->GetEvent(&lEventCode,&lEvParam1,&lEvParam2,0);
		if(m_hResult == S_OK)
		{
			//�Đ��I���ł������Ƃ��t���O�𗧂Ă�
			if(lEventCode == EC_COMPLETE) bIsComplete = TRUE;

			//�C�x���g���폜
			m_lpMediaEvent->FreeEventParams(lEventCode,lEvParam1,lEvParam2);
		}
	} while(m_hResult == S_OK);

	//�Đ��I���̂Ƃ����[�v������
	if(bIsComplete){
		Stop();
		Play();
	}

	return TRUE;
}

//�ꎞ��~
BOOL CMusic::Pause()
{
	//���f�B�A�R���g���[�������݂��Ȃ�
	if (!m_lpMediaControl) return FALSE;

	//�ꎞ��~����
	if (FAILED(m_lpMediaControl->Pause())) return FALSE;

	return TRUE;
}

//��~
BOOL CMusic::Stop()
{
	//���f�B�A�R���g���[�������݂��Ȃ�
	if (!m_lpMediaControl) return FALSE;

	//�ꎞ��~����
	if (FAILED(m_lpMediaControl->Pause())) return FALSE;

	//���f�B�A�V�[�L���O�����݂��Ȃ�
	if (!m_lpMediaSeeking) return FALSE;

	LONGLONG llSeekTime = 0; //�V�[�N�^�C��

	//�擪�ʒu�ɐݒ肷��
	if (FAILED(m_lpMediaSeeking->SetPositions(&llSeekTime,
		AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning))) return FALSE;

	return TRUE;
}
