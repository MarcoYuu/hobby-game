#include "Main.h"
#include "Effect.h"
#include "Enemy.h"
#include "Stage1.h"

//----------------------------------------------------------------------
//CStage1クラス(CStage1クラス）
//----------------------------------------------------------------------
//プレイモード
bool CStage1::Move()
{
	//ポーズ判定
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();
	}

	//敵の出現ルーチン実行
	m_script->RunScript();

	//背景の描画
	m_backY +=7.0f;
	m_backY2 +=3.5f;
	if(m_backY>=608.0f)
		m_backY -=256.0f;
	if(m_backY2>=608.0f)
		m_backY2 -=256.0f;

	//入力情報の保存
	Game->input->SaveKeyStateToVariant(&input);

	return true;
}

void CStage1::Draw()
{
	//背景の描画
	Game->graphics->SetRenderState(NORMAL);
	Game->poligon[25]->SetColor(0xff555555,0xff555555,0xff555555,0xff555555);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
		Game->poligon[25]->SetRect(448,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
	}

	float temp =64.0f;
	Game->graphics->SetRenderState(ADDITION);
	Game->poligon[25]->SetColor(0xff222222,0xff222222,0xff222222,0xff222222);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
		Game->poligon[25]->SetRect(448-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
	}
	/*
	Game->poligon[25]->SetRect(192-temp,m_backY2-256,256,256);
	Game->graphics->Draw(Game->poligon[25],2);
	Game->poligon[25]->SetRect(448-temp,m_backY2-256,256,256);
	Game->graphics->Draw(Game->poligon[25],2);
	Game->poligon[25]->SetRect(192-temp,m_backY2-512,256,256);
	Game->graphics->Draw(Game->poligon[25],2);
	Game->poligon[25]->SetRect(448-temp,m_backY2-512,256,256);
	Game->graphics->Draw(Game->poligon[25],2);
	
	Game->poligon[25]->SetRect(320,m_backY,640,480);
	Game->graphics->Draw(Game->poligon[25],1);
	Game->poligon[25]->SetRect(320,m_backY-480,640,480);
	Game->graphics->Draw(Game->poligon[25],1);
	*/
}

//リプレイモード
bool CStage1_Replay::Move()
{
	//ポーズ判定
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();	
	}

	//敵の出現ルーチン実行
	m_script->RunScript();

	//背景の描画
	m_backY +=7.0f;
	m_backY2 +=3.5f;
	if(m_backY>=608.0f)
		m_backY -=256.0f;
	if(m_backY2>=608.0f)
		m_backY2 -=256.0f;

	return true;
}

void CStage1_Replay::Draw()
{
	//背景の描画
	Game->graphics->SetRenderState(NORMAL);
	Game->poligon[25]->SetColor(0xff555555,0xff555555,0xff555555,0xff555555);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
		Game->poligon[25]->SetRect(448,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
	}

	float temp =64.0f;
	Game->graphics->SetRenderState(ADDITION);
	Game->poligon[25]->SetColor(0xff222222,0xff222222,0xff222222,0xff222222);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
		Game->poligon[25]->SetRect(448-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
	}
}

//----------------------------------------------------------------------
//CStage2クラス(CStage2クラス）
//----------------------------------------------------------------------
//プレイモード
bool CStage2::Move()
{
	//ポーズ判定
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();
	}

	//敵の出現ルーチン実行
	m_script->RunScript();

	//背景の描画
	m_backY +=7.0f;
	m_backY2 +=3.5f;
	if(m_backY>=608.0f)
		m_backY -=256.0f;
	if(m_backY2>=608.0f)
		m_backY2 -=256.0f;

	//入力情報の保存
	Game->input->SaveKeyStateToVariant(&input);

	return true;
}

void CStage2::Draw()
{
	//背景の描画
	Game->graphics->SetRenderState(NORMAL);
	Game->poligon[25]->SetColor(0xffff3333,0xffff3333,0xffff3333,0xffff3333);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
		Game->poligon[25]->SetRect(448,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
	}

	float temp =64.0f;
	Game->graphics->SetRenderState(ADDITION);
	Game->poligon[25]->SetColor(0xffee2222,0xffee2222,0xffee2222,0xffee2222);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
		Game->poligon[25]->SetRect(448-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
	}
}

//リプレイモード
bool CStage2_Replay::Move()
{
	//ポーズ判定
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();	
	}

	//敵の出現ルーチン実行
	m_script->RunScript();

	//背景の描画
	m_backY +=7.0f;
	m_backY2 +=3.5f;
	if(m_backY>=608.0f)
		m_backY -=256.0f;
	if(m_backY2>=608.0f)
		m_backY2 -=256.0f;

	return true;
}

void CStage2_Replay::Draw()
{
	//背景の描画
	Game->graphics->SetRenderState(NORMAL);
	Game->poligon[25]->SetColor(0xffff5555,0xffff5555,0xffff5555,0xffff5555);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
		Game->poligon[25]->SetRect(448,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
	}

	float temp =64.0f;
	Game->graphics->SetRenderState(ADDITION);
	Game->poligon[25]->SetColor(0xffcc2222,0xffcc2222,0xffcc2222,0xffcc2222);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
		Game->poligon[25]->SetRect(448-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
	}
}

//----------------------------------------------------------------------
//CStage3クラス(CStage3クラス）
//----------------------------------------------------------------------
//プレイモード
bool CStage3::Move()
{
	//ポーズ判定
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();
	}

	//敵の出現ルーチン実行
	m_script->RunScript();

	//背景の描画
	m_backY +=7.0f;
	m_backY2 +=3.5f;
	if(m_backY>=608.0f)
		m_backY -=256.0f;
	if(m_backY2>=608.0f)
		m_backY2 -=256.0f;

	//入力情報の保存
	Game->input->SaveKeyStateToVariant(&input);

	return true;
}

void CStage3::Draw()
{
	//背景の描画
	Game->graphics->SetRenderState(NORMAL);
	Game->poligon[25]->SetColor(0xff55ff55,0xff55ff55,0xff5ff555,0xff55ff55);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
		Game->poligon[25]->SetRect(448,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
	}

	float temp =64.0f;
	Game->graphics->SetRenderState(ADDITION);
	Game->poligon[25]->SetColor(0xff22cc22,0xff22cc22,0xff22cc22,0xff22cc22);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
		Game->poligon[25]->SetRect(448-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
	}
}

//リプレイモード
bool CStage3_Replay::Move()
{
	//ポーズ判定
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();	
	}

	//敵の出現ルーチン実行
	m_script->RunScript();

	//背景の描画
	m_backY +=7.0f;
	m_backY2 +=3.5f;
	if(m_backY>=608.0f)
		m_backY -=256.0f;
	if(m_backY2>=608.0f)
		m_backY2 -=256.0f;

	return true;
}

void CStage3_Replay::Draw()
{
	//背景の描画
	Game->graphics->SetRenderState(NORMAL);
	Game->poligon[25]->SetColor(0xff55ff55,0xff55ff55,0xff55ff55,0xff55ff55);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
		Game->poligon[25]->SetRect(448,m_backY-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],1);
	}

	float temp =64.0f;
	Game->graphics->SetRenderState(ADDITION);
	Game->poligon[25]->SetColor(0xff22cc22,0xff22cc22,0xff22cc22,0xff22cc22);
	for(int i=0;i<3;++i)
	{
		Game->poligon[25]->SetRect(192-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
		Game->poligon[25]->SetRect(448-temp,m_backY2-256*i,256,256);
		Game->graphics->Draw(Game->poligon[25],2);
	}
}