#include "Main.h"
#include "Effect.h"
#include "Enemy.h"
#include "Stage1.h"

//----------------------------------------------------------------------
//CStage1�N���X(CStage1�N���X�j
//----------------------------------------------------------------------
//�v���C���[�h
bool CStage1::Move()
{
	//�|�[�Y����
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();
	}

	//�G�̏o�����[�`�����s
	m_script->RunScript();

	//�w�i�̕`��
	m_backY +=7.0f;
	m_backY2 +=3.5f;
	if(m_backY>=608.0f)
		m_backY -=256.0f;
	if(m_backY2>=608.0f)
		m_backY2 -=256.0f;

	//���͏��̕ۑ�
	Game->input->SaveKeyStateToVariant(&input);

	return true;
}

void CStage1::Draw()
{
	//�w�i�̕`��
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

//���v���C���[�h
bool CStage1_Replay::Move()
{
	//�|�[�Y����
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();	
	}

	//�G�̏o�����[�`�����s
	m_script->RunScript();

	//�w�i�̕`��
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
	//�w�i�̕`��
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
//CStage2�N���X(CStage2�N���X�j
//----------------------------------------------------------------------
//�v���C���[�h
bool CStage2::Move()
{
	//�|�[�Y����
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();
	}

	//�G�̏o�����[�`�����s
	m_script->RunScript();

	//�w�i�̕`��
	m_backY +=7.0f;
	m_backY2 +=3.5f;
	if(m_backY>=608.0f)
		m_backY -=256.0f;
	if(m_backY2>=608.0f)
		m_backY2 -=256.0f;

	//���͏��̕ۑ�
	Game->input->SaveKeyStateToVariant(&input);

	return true;
}

void CStage2::Draw()
{
	//�w�i�̕`��
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

//���v���C���[�h
bool CStage2_Replay::Move()
{
	//�|�[�Y����
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();	
	}

	//�G�̏o�����[�`�����s
	m_script->RunScript();

	//�w�i�̕`��
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
	//�w�i�̕`��
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
//CStage3�N���X(CStage3�N���X�j
//----------------------------------------------------------------------
//�v���C���[�h
bool CStage3::Move()
{
	//�|�[�Y����
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();
	}

	//�G�̏o�����[�`�����s
	m_script->RunScript();

	//�w�i�̕`��
	m_backY +=7.0f;
	m_backY2 +=3.5f;
	if(m_backY>=608.0f)
		m_backY -=256.0f;
	if(m_backY2>=608.0f)
		m_backY2 -=256.0f;

	//���͏��̕ۑ�
	Game->input->SaveKeyStateToVariant(&input);

	return true;
}

void CStage3::Draw()
{
	//�w�i�̕`��
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

//���v���C���[�h
bool CStage3_Replay::Move()
{
	//�|�[�Y����
	m_PrevInput =m_CurInput;
	m_CurInput =Game->input->GetKeyState(MY_ESCAPE);
	if(!m_PrevInput)
	{
		if(m_CurInput)
			new CPause();	
	}

	//�G�̏o�����[�`�����s
	m_script->RunScript();

	//�w�i�̕`��
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
	//�w�i�̕`��
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