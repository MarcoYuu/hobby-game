#pragma once
#include "GameObj.h"

//----------------------------------------------------------------------
//CScene�N���X(�󋵂�\�����N���X�j
//----------------------------------------------------------------------
class CScene :public CGameObj
{
public:
	void* operator new(size_t t) { return operator_new(t, Game->SceneList); }
	void operator delete(void* p) { operator_delete(p, Game->SceneList); }
	CScene();
};

//----------------------------------------------------------------------
//CTitle�N���X(�^�C�g����ʃN���X�j
//----------------------------------------------------------------------
enum MENU{
	START,
	REPLAY,
	EXIT,
	
	MENU_NUM
};
class CTitle :public CScene
{
	int m_Menu;
	KEYSTATE m_Key;
	bool m_PrevKey;
public:
	CTitle()
	:m_Menu(START)
	{
		Game->music->Stop();
		Game->music_boss->Stop();
		Game->input->GetAllState(&m_Key);
	}
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CPause�N���X(�|�[�Y�N���X�j
//----------------------------------------------------------------------
enum PAUSE_MENU{
	CONTINUE,
	EXIT_GAME,
	PAUSEMENU_NUM
};
class CPause :public CScene
{
	int m_Menu;
	BOOL m_PrevInput,m_CurInput;
	KEYSTATE m_Key;
	bool m_PrevKey;
	bool replayed;
public:
	CPause()
	:m_PrevInput(true),m_CurInput(true),m_Menu(CONTINUE),replayed(Game->GetReplay())
	{
		Game->SetPause(true);
		if(replayed)
		{
			Game->SetReplay(false);
		}
		Game->input->GetAllState(&m_Key);
	}
	~CPause()
	{
		Game->SetPause(false);
		if(replayed)
		{
			Game->SetReplay(true);
			Game->input->UpdateKeyStateFromFile();
		}
	}
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CGameOver�N���X(�Q�[���I�[�o�[�N���X�j
//----------------------------------------------------------------------
class CGameOver :public CScene
{
	BOOL m_PrevInput,m_CurInput;
	int m_count;
public:
	CGameOver()
	:m_PrevInput(true),m_CurInput(true),m_count(200)
	{
		Game->sound[5]->Play();
		Game->music_boss->Stop();
		Game->music->Stop();
		Game->StageList->DeleteTask();
	}
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CResult1�N���X(���ʉ�ʃN���X�X�e�[�W1�I���j
//----------------------------------------------------------------------
class CResult1 :public CScene
{
	BOOL m_PrevInput,m_CurInput;
	bool m_replay;
	int m_count,m_draw_count;
	int m_clearStageNum;
public:
	CResult1(int stage_num,bool replay)
	:m_PrevInput(true),m_CurInput(true),m_count(200),m_clearStageNum(stage_num),m_draw_count(0),m_replay(replay)
	{
		Game->SetResult(true);
		Game->sound[6]->Play();
		Game->StageList->DeleteTask();
	}
	~CResult1()
	{
		Game->SetResult(false);
		Game->music_boss->Stop();
	}
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CResult2�N���X(���ʉ�ʃN���X�X�e�[�W2�I���j
//----------------------------------------------------------------------
class CResult2 :public CScene
{
	BOOL m_PrevInput,m_CurInput;
	bool m_replay;
	int m_count,m_draw_count;
	int m_clearStageNum;
public:
	CResult2(int stage_num,bool replay)
	:m_PrevInput(true),m_CurInput(true),m_count(200),m_clearStageNum(stage_num),m_draw_count(0),m_replay(replay)
	{
		Game->SetResult(true);
		Game->sound[6]->Play();
		Game->StageList->DeleteTask();
	}
	~CResult2()
	{
		Game->SetResult(false);
		Game->music_boss->Stop();
	}
	virtual bool Move();
	virtual void Draw();
};
//----------------------------------------------------------------------
//CResult3�N���X(���ʉ�ʃN���X�X�e�[�W3�I���j
//----------------------------------------------------------------------
class CResult3 :public CScene
{
	BOOL m_PrevInput,m_CurInput;
	bool m_replay;
	int m_count,m_draw_count;
	int m_clearStageNum;
public:
	CResult3(int stage_num,bool replay)
	:m_PrevInput(true),m_CurInput(true),m_count(200),m_clearStageNum(stage_num),m_draw_count(0),m_replay(replay)
	{
		Game->SetResult(true);
		Game->sound[6]->Play();
		Game->StageList->DeleteTask();
	}
	~CResult3()
	{
		Game->SetResult(false);
		Game->music_boss->Stop();
	}
	virtual bool Move();
	virtual void Draw();
};