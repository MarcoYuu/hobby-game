#pragma once
#include <vector>
#include "Scene.h"
#include "Script.h"

//----------------------------------------------------------------------
//CStageクラス(状況を表す基底クラス）
//----------------------------------------------------------------------
class CStage :public CGameObj
{
protected:
	CScript* m_script;
public:
	void* operator new(size_t t) { return operator_new(t, Game->StageList); }
	void operator delete(void* p) { operator_delete(p, Game->StageList); }
	CStage(CScript* script)
	:CGameObj(Game->StageList,320,240,640,480,0,0,0),m_script(script)
	{
	}
};

//----------------------------------------------------------------------
//CStage1クラス(CStage1クラス）
//----------------------------------------------------------------------
//プレイモード
class CStage1 :public CStage
{
	float m_backY,m_backY2;
	BOOL m_PrevInput,m_CurInput;
	unsigned int seed;
	
	vector<char> input;
public:
	CStage1(CScript* script)
	:CStage(script),
	m_backY(480.0f),m_backY2(480),m_PrevInput(true),m_CurInput(false)
	{
		Game->music->LoadMusicFile(L"./Musics/The_2nd_Theme.mp3");
		Game->music->Play();
		Game->SetCreared(false);
		m_script->ResetScript();
		
		srand(1);
	}
	~CStage1()
	{
		Game->music->Stop();
		if(Game->GetCreared())
		{
			Game->input->SaveKeyStateToFile(&input,"new_replay1.nishi","STAGE1",true);
		}
	}
	virtual bool Move();
	virtual void Draw();
};
//リプレイモード
class CStage1_Replay :public CStage
{
	float m_backY,m_backY2;;
	BOOL m_PrevInput,m_CurInput;
	unsigned int seed;

public:
	CStage1_Replay(CScript* script)
	:CStage(script),
	m_backY(480.0f),m_backY2(480),m_PrevInput(true),m_CurInput(false)
	{
		Game->input->SetUpKeyStateFromFile("new_replay1.nishi","STAGE1");
		Game->SetReplay(true);

		Game->music->LoadMusicFile(L"./Musics/The_2nd_Theme.mp3");
		Game->music_boss->LoadMusicFile(L"./Musics/FF.wav");
		Game->music->Play();
		m_script->ResetScript();
		
		Game->input->UpdateKeyStateFromFile();
		srand(1);
	}
	~CStage1_Replay()
	{
		Game->SetReplay(false);
		Game->music->Stop();
	}
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CStage2クラス(CStage2クラス）
//----------------------------------------------------------------------
//プレイモード
class CStage2 :public CStage
{
	float m_backY,m_backY2;
	BOOL m_PrevInput,m_CurInput;
	unsigned int seed;
	
	vector<char> input;
public:
	CStage2(CScript* script)
	:CStage(script),
	m_backY(240.0f),m_PrevInput(true),m_CurInput(false)
	{
		Game->music->LoadMusicFile(L"./Musics/The_2nd_Theme.mp3");
		Game->music->Play();
		Game->SetCreared(false);
		m_script->ResetScript();
		
		srand(1);
	}
	~CStage2()
	{
		Game->music->Stop();
		if(Game->GetCreared())
		{
			Game->input->SaveKeyStateToFile(&input,"new_replay1.nishi","STAGE2");
		}
	}
	virtual bool Move();
	virtual void Draw();
};
//リプレイモード
class CStage2_Replay :public CStage
{
	float m_backY,m_backY2;
	BOOL m_PrevInput,m_CurInput;
	unsigned int seed;

public:
	CStage2_Replay(CScript* script)
	:CStage(script),
	m_backY(240.0f),m_PrevInput(true),m_CurInput(false)
	{
		Game->input->SetUpKeyStateFromFile("new_replay1.nishi","STAGE2");
		Game->SetReplay(true);

		Game->music->LoadMusicFile(L"./Musics/The_2nd_Theme.mp3");
		Game->music_boss->LoadMusicFile(L"./Musics/FF.wav");
		Game->music->Play();
		m_script->ResetScript();
		
		Game->input->UpdateKeyStateFromFile();
		srand(1);
	}
	~CStage2_Replay()
	{
		Game->SetReplay(false);
		Game->music->Stop();
	}
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CStage3クラス(CStage3クラス）
//----------------------------------------------------------------------
//プレイモード
class CStage3 :public CStage
{
	float m_backY,m_backY2;
	BOOL m_PrevInput,m_CurInput;
	unsigned int seed;
	
	vector<char> input;
public:
	CStage3(CScript* script)
	:CStage(script),
	m_backY(240.0f),m_PrevInput(true),m_CurInput(false)
	{
		Game->music->LoadMusicFile(L"./Musics/The_2nd_Theme.mp3");
		Game->music->Play();
		Game->SetCreared(false);
		m_script->ResetScript();
		
		srand(1);
	}
	~CStage3()
	{
		Game->music->Stop();
		if(Game->GetCreared())
		{
			Game->input->SaveKeyStateToFile(&input,"new_replay1.nishi","STAGE3");
		}
	}
	virtual bool Move();
	virtual void Draw();
};
//リプレイモード
class CStage3_Replay :public CStage
{
	float m_backY,m_backY2;
	BOOL m_PrevInput,m_CurInput;
	unsigned int seed;

public:
	CStage3_Replay(CScript* script)
	:CStage(script),
	m_backY(240.0f),m_PrevInput(true),m_CurInput(false)
	{
		Game->input->SetUpKeyStateFromFile("new_replay1.nishi","STAGE3");
		Game->SetReplay(true);

		Game->music->LoadMusicFile(L"./Musics/The_2nd_Theme.mp3");
		Game->music_boss->LoadMusicFile(L"./Musics/FF.wav");
		Game->music->Play();
		m_script->ResetScript();
		
		Game->input->UpdateKeyStateFromFile();
		srand(1);
	}
	~CStage3_Replay()
	{
		Game->SetReplay(false);
		Game->music->Stop();
	}
	virtual bool Move();
	virtual void Draw();
};