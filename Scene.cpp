#include "Main.h"
#include "Effect.h"
#include "Scene.h"
#include "Stage1.h"

//----------------------------------------------------------------------
//CSceneクラス(状況を表す基底クラス）
//----------------------------------------------------------------------

CScene::CScene()
:CGameObj(Game->SceneList,320,240,640,480,0,0,0)
{
}

//----------------------------------------------------------------------
//CTitleクラス(タイトル画面クラス）
//----------------------------------------------------------------------

bool CTitle::Move()
{
	Game->SetReplay(false);

	//前フレームでの入力と今回の入力の更新
	m_PrevKey =m_Key.UP || m_Key.DOWN || m_Key.Z || m_Key.X;
	Game->input->GetAllState(&m_Key);

	if(!m_PrevKey)
	{
		if(m_Key.UP)
		{
			Game->sound[1]->Play();
			m_Menu--;
			if(m_Menu<0)
				m_Menu =MENU_NUM-1;
		}
		else if(m_Key.DOWN)
		{
			Game->sound[1]->Play();
			m_Menu++;
			if(m_Menu>MENU_NUM-1)
				m_Menu =0;
		}

		if(m_Key.Z)
		{
			Game->sound[1]->Play();
			switch(m_Menu)
			{
			case START:
				Game->Start();
				return false;
				break;
			case REPLAY:
				Game->StartReplay();
				return false;
				break;
			case EXIT:
				PostQuitMessage(0);
				break;
			default:
				break;
			}
		}
	}
	return true;
}

void CTitle::Draw()
{
	static const DWORD black =0xff000000;
	static const DWORD skelton =0x80ffffff; 

	Game->graphics->SetRenderState(NORMAL);

	//メニュー背景
	Game->poligon[11]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	Game->poligon[11]->SetRect(X,Y,Width,Height);
	Game->graphics->Draw(Game->poligon[11],1);

	//GAMESTART
	Game->poligon[9]->SetColor(m_Menu==START?black:skelton,m_Menu==START?black:skelton,
		m_Menu==START?black:skelton,m_Menu==START?black:skelton);
	Game->poligon[9]->SetRect(X,Y+50,256,47,0.0f,0.0f,1.0f,0.25f);
	Game->graphics->Draw(Game->poligon[9],1);

	//REPLAY
	Game->poligon[9]->SetColor(m_Menu==REPLAY?black:skelton,m_Menu==REPLAY?black:skelton,
		m_Menu==REPLAY?black:skelton,m_Menu==REPLAY?black:skelton);
	Game->poligon[9]->SetRect(X,Y+80,256,47,0.0f,0.5f,1.0f,0.75f);
	Game->graphics->Draw(Game->poligon[9],1);
	
	//EXIT
	Game->poligon[9]->SetColor(m_Menu==EXIT?black:skelton,m_Menu==EXIT?black:skelton,
		m_Menu==EXIT?black:skelton,m_Menu==EXIT?black:skelton);
	Game->poligon[9]->SetRect(X,Y+110,256,47,0.0f,0.25f,1.0f,0.5f);
	Game->graphics->Draw(Game->poligon[9],1);
}

//----------------------------------------------------------------------
//CPauseクラス(ポーズクラス）
//----------------------------------------------------------------------

bool CPause::Move()
{
	//前フレームでの入力と今回の入力の更新
	m_PrevKey =m_Key.UP || m_Key.DOWN || m_Key.Z || m_Key.X;
	Game->input->GetAllState(&m_Key);

	m_PrevInput =m_CurInput;
	m_CurInput =m_Key.ESCAPE;

	if(!m_PrevInput)
	{
		if(m_CurInput)
			return false;
	}

	if(!m_PrevKey)
	{
		if(m_Key.UP)
		{
			Game->sound[1]->Play();
			m_Menu--;
			if(m_Menu<0)
				m_Menu =PAUSEMENU_NUM-1;
		}
		else if(m_Key.DOWN)
		{
			Game->sound[1]->Play();
			m_Menu++;
			if(m_Menu>PAUSEMENU_NUM-1)
				m_Menu =0;
		}

		if(m_Key.Z)
		{
			Game->sound[1]->Play();
			switch(m_Menu)
			{
			case CONTINUE:
				return false;
				break;
			case EXIT_GAME:
				Game->DeleteAllGameChar();
				Game->Stop();
				new CTitle();
				return false;
				break;
			default:
				break;
			}
		}
	}

	return true;
}

void CPause::Draw()
{
	static const DWORD black =0xffffffff;
	static const DWORD skelton =0x80ffffff; 

	Game->graphics->SetRenderState(NORMAL);

	Game->poligon[13]->SetColor(m_Menu==CONTINUE?black:skelton,m_Menu==CONTINUE?black:skelton,
		m_Menu==CONTINUE?black:skelton,m_Menu==CONTINUE?black:skelton);
	Game->poligon[13]->SetRect(X,Y+50,256,64,0.0f,0.0f,1.0f,0.25f);
	Game->graphics->Draw(Game->poligon[13],1);

	Game->poligon[13]->SetColor(m_Menu==EXIT_GAME?black:skelton,m_Menu==EXIT_GAME?black:skelton,
		m_Menu==EXIT_GAME?black:skelton,m_Menu==EXIT_GAME?black:skelton);
	Game->poligon[13]->SetRect(X,Y+100,256,64,0.0f,0.25f,1.0f,0.5f);
	Game->graphics->Draw(Game->poligon[13],1);
}

//----------------------------------------------------------------------
//CGameOverクラス(ゲームオーバークラス）
//----------------------------------------------------------------------

bool CGameOver::Move()
{
	if(m_count>0)
	{
		Game->DeleteAllGameChar();
		--m_count;
		return true;
	}
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_Z);

	if(!m_PrevInput)
	{
		if(m_CurInput)
		{
			Game->Stop();
			new CTitle();
			return false;
		}
	}
	return true;
}

void CGameOver::Draw()
{
	Game->graphics->SetRenderState(NORMAL);

	Game->poligon[14]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	Game->poligon[14]->SetRect(X,Y,256,64,0.0f,0.0f,1.0f,0.25f);
	Game->graphics->Draw(Game->poligon[14],1);
}

//----------------------------------------------------------------------
//CResult1クラス(Stage1結果画面クラス）
//----------------------------------------------------------------------

bool CResult1::Move()
{
	++m_draw_count;
	if(m_count>0)
	{
		--m_count;
		return true;
	}
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_Z);

	if(!m_PrevInput)
	{
		if(m_CurInput)
		{
			if(m_replay)
			{
				new CStage2_Replay(Game->script[1]);
			}
			else
			{
				new CStage2(Game->script[1]);
			}
			return false;
		}
	}
	return true;
}

void CResult1::Draw()
{
	if(m_draw_count>45)
	{
		Game->graphics->SetRenderState(NORMAL);

		Game->poligon[16]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
		//Clear Stage ? !
		Game->poligon[16]->SetRect(320,120,256,64,0.0f,0.0f,1.0f,0.25f);
		Game->graphics->Draw(Game->poligon[16],1);
		float u1(0.0f),v1(0.0f),u2(1.0f),v2(1.0f);
		switch(m_clearStageNum)
		{
		case 0:
			u1 =0.0f;	v1 =0.0f;
			u2 =0.25f;	v2 =0.25f;
			break;
		case 1:
			u1 =0.25f;	v1 =0.0f;
			u2 =0.5f;	v2 =0.25f;
			break;
		case 2:
			u1 =0.5f;	v1 =0.0f;
			u2 =0.75f;	v2 =0.25f;
			break;
		case 3:
			u1 =0.75f;	v1 =0.0f;
			u2 =1.0f;	v2 =0.25f;
			break;
		case 4:
			u1 =0.0f;	v1 =0.25f;
			u2 =0.25f;	v2 =0.5f;
			break;
		case 5:
			u1 =0.25f;	v1 =0.25f;
			u2 =0.5f;	v2 =0.5f;
			break;
		case 6:
			u1 =0.5f;	v1 =0.25f;
			u2 =0.75f;	v2 =0.5f;
			break;
		case 7:
			u1 =0.75f;	v1 =0.25f;
			u2 =1.0f;	v2 =0.5f;
			break;
		case 8:
			u1 =0.0f;	v1 =0.5f;
			u2 =0.25f;	v2 =0.75f;
			break;
		case 9:
			u1 =0.25f;	v1 =0.5f;
			u2 =0.5f;	v2 =0.75f;
			break;
		default:
			break;
		}
		Game->poligon[12]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
		Game->poligon[12]->SetRect(320+72,120,64,64,u1,v1,u2,v2);
		Game->graphics->Draw(Game->poligon[12],1);

		//ThisStage's Score
		Game->poligon[16]->SetRect(320,180,256,64,0.0f,0.25f,1.0f,0.5f);
		Game->graphics->Draw(Game->poligon[16],1);
		Game->score->DrawPresentScore(320,210,64,64);

		//Your HighScore
		Game->poligon[16]->SetRect(320,260,256,64,0.0f,0.5f,1.0f,0.75f);
		Game->graphics->Draw(Game->poligon[16],1);
		Game->score->DrawHighScore(320,290,64,64);
	}
}

//----------------------------------------------------------------------
//CResult2クラス(Stage2結果画面クラス）
//----------------------------------------------------------------------

bool CResult2::Move()
{
	++m_draw_count;
	if(m_count>0)
	{
		--m_count;
		return true;
	}
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_Z);

	if(!m_PrevInput)
	{
		if(m_CurInput)
		{
			if(m_replay)
			{
				new CStage3_Replay(Game->script[2]);
			}
			else
			{
				new CStage3(Game->script[2]);
			}
			return false;
		}
	}
	return true;
}

void CResult2::Draw()
{
	if(m_draw_count>45)
	{
		Game->graphics->SetRenderState(NORMAL);

		Game->poligon[16]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
		//Clear Stage ? !
		Game->poligon[16]->SetRect(320,120,256,64,0.0f,0.0f,1.0f,0.25f);
		Game->graphics->Draw(Game->poligon[16],1);
		float u1(0.0f),v1(0.0f),u2(1.0f),v2(1.0f);
		switch(m_clearStageNum)
		{
		case 0:
			u1 =0.0f;	v1 =0.0f;
			u2 =0.25f;	v2 =0.25f;
			break;
		case 1:
			u1 =0.25f;	v1 =0.0f;
			u2 =0.5f;	v2 =0.25f;
			break;
		case 2:
			u1 =0.5f;	v1 =0.0f;
			u2 =0.75f;	v2 =0.25f;
			break;
		case 3:
			u1 =0.75f;	v1 =0.0f;
			u2 =1.0f;	v2 =0.25f;
			break;
		case 4:
			u1 =0.0f;	v1 =0.25f;
			u2 =0.25f;	v2 =0.5f;
			break;
		case 5:
			u1 =0.25f;	v1 =0.25f;
			u2 =0.5f;	v2 =0.5f;
			break;
		case 6:
			u1 =0.5f;	v1 =0.25f;
			u2 =0.75f;	v2 =0.5f;
			break;
		case 7:
			u1 =0.75f;	v1 =0.25f;
			u2 =1.0f;	v2 =0.5f;
			break;
		case 8:
			u1 =0.0f;	v1 =0.5f;
			u2 =0.25f;	v2 =0.75f;
			break;
		case 9:
			u1 =0.25f;	v1 =0.5f;
			u2 =0.5f;	v2 =0.75f;
			break;
		default:
			break;
		}
		Game->poligon[12]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
		Game->poligon[12]->SetRect(320+72,120,64,64,u1,v1,u2,v2);
		Game->graphics->Draw(Game->poligon[12],1);

		//ThisStage's Score
		Game->poligon[16]->SetRect(320,180,256,64,0.0f,0.25f,1.0f,0.5f);
		Game->graphics->Draw(Game->poligon[16],1);
		Game->score->DrawPresentScore(320,210,64,64);

		//Your HighScore
		Game->poligon[16]->SetRect(320,260,256,64,0.0f,0.5f,1.0f,0.75f);
		Game->graphics->Draw(Game->poligon[16],1);
		Game->score->DrawHighScore(320,290,64,64);
	}
}
//----------------------------------------------------------------------
//CResult3クラス(Stage3結果画面クラス）
//----------------------------------------------------------------------

bool CResult3::Move()
{
	++m_draw_count;
	if(m_count>0)
	{
		--m_count;
		return true;
	}
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_Z);

	if(!m_PrevInput)
	{
		if(m_CurInput)
		{
			Game->DeleteAllGameChar();
			Game->Stop();
			new CTitle();
			return false;
		}
	}
	return true;
}

void CResult3::Draw()
{
	if(m_draw_count>45)
	{
		Game->graphics->SetRenderState(NORMAL);

		Game->poligon[16]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
		//Clear Stage ? !
		Game->poligon[16]->SetRect(320,120,256,64,0.0f,0.0f,1.0f,0.25f);
		Game->graphics->Draw(Game->poligon[16],1);
		float u1(0.0f),v1(0.0f),u2(1.0f),v2(1.0f);
		switch(m_clearStageNum)
		{
		case 0:
			u1 =0.0f;	v1 =0.0f;
			u2 =0.25f;	v2 =0.25f;
			break;
		case 1:
			u1 =0.25f;	v1 =0.0f;
			u2 =0.5f;	v2 =0.25f;
			break;
		case 2:
			u1 =0.5f;	v1 =0.0f;
			u2 =0.75f;	v2 =0.25f;
			break;
		case 3:
			u1 =0.75f;	v1 =0.0f;
			u2 =1.0f;	v2 =0.25f;
			break;
		case 4:
			u1 =0.0f;	v1 =0.25f;
			u2 =0.25f;	v2 =0.5f;
			break;
		case 5:
			u1 =0.25f;	v1 =0.25f;
			u2 =0.5f;	v2 =0.5f;
			break;
		case 6:
			u1 =0.5f;	v1 =0.25f;
			u2 =0.75f;	v2 =0.5f;
			break;
		case 7:
			u1 =0.75f;	v1 =0.25f;
			u2 =1.0f;	v2 =0.5f;
			break;
		case 8:
			u1 =0.0f;	v1 =0.5f;
			u2 =0.25f;	v2 =0.75f;
			break;
		case 9:
			u1 =0.25f;	v1 =0.5f;
			u2 =0.5f;	v2 =0.75f;
			break;
		default:
			break;
		}
		Game->poligon[12]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
		Game->poligon[12]->SetRect(320+72,120,64,64,u1,v1,u2,v2);
		Game->graphics->Draw(Game->poligon[12],1);

		//ThisStage's Score
		Game->poligon[16]->SetRect(320,180,256,64,0.0f,0.25f,1.0f,0.5f);
		Game->graphics->Draw(Game->poligon[16],1);
		Game->score->DrawPresentScore(320,210,64,64);

		//Your HighScore
		Game->poligon[16]->SetRect(320,260,256,64,0.0f,0.5f,1.0f,0.75f);
		Game->graphics->Draw(Game->poligon[16],1);
		Game->score->DrawHighScore(320,290,64,64);
	}
}