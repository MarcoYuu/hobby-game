
#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <fstream>
#include "Main.h"
#include "CToken.h"
#include "Nishi.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Effect.h"
#include "Scene.h"
#include "Stage1.h"

//----------------------------------------------------------------------
//�R���t�B�O�N���X�i�ݒ��ێ�����N���X�j
//----------------------------------------------------------------------
CConfig::CConfig(string file_name)
	:CHECK_HWVERTEX(false)
	,CHECK_REFRASTERIZER(false)
	,CHECK_DRAWINTERVALHALF(false)
	,CHECK_CONFIRMSIZE(false)
	,RADIO_FORCEFPSSIXTY(false)
	,RADIO_VSYNC(true)
	,RADIO_640_480(true)
	,RADIO_960_720(false)
	,RADIO_FULLSCREEN(false)
{
	using namespace std;

	string str_cfg,str_data;
	ifstream ifs(file_name.c_str());

	if(!ifs.is_open())
		return;

	int i=0;
	while(getline(ifs,str_cfg))
	{
		if(str_cfg == "")
			continue;

		CToken token(str_cfg, "=",false);
		str_data =token.next();
		str_data =token.next();

		switch(i)
		{
		case 0: CHECK_HWVERTEX			 =(0 != atoi(str_data.c_str())); break;
		case 1: CHECK_REFRASTERIZER		 =(0 != atoi(str_data.c_str())); break;
		case 2: CHECK_DRAWINTERVALHALF	 =(0 != atoi(str_data.c_str())); break;
		case 3: CHECK_CONFIRMSIZE		 =(0 != atoi(str_data.c_str())); break;
		case 4: RADIO_FORCEFPSSIXTY		 =(0 != atoi(str_data.c_str())); break;
		case 5: RADIO_VSYNC				 =(0 != atoi(str_data.c_str())); break;
		case 6: RADIO_640_480			 =(0 != atoi(str_data.c_str())); break;
		case 7: RADIO_960_720			 =(0 != atoi(str_data.c_str())); break;
		case 8: RADIO_FULLSCREEN		 =(0 != atoi(str_data.c_str())); break;
		}

		++i;
	}
	ifs.close();
}

//----------------------------------------------------------------------
//�Q�[���N���X
//----------------------------------------------------------------------
//�R���X�g���N�^
CGame::CGame(HWND *hWnd,HINSTANCE hCurInst, CConfig *config,bool bWindowed)
	:execute_game(false)
	,pause_game(false)
	,replay_game(false)
	,result_game(false)
	,windowed(bWindowed)
	,draw_interval(config->GetCHECK_DRAWINTERVALHALF())
	,VSync(config->GetRADIO_VSYNC())
	,m_leftLife(0)
	,m_leftBomb(0)
	,m_leftBOSSLife(0)
	,m_leftBOSSVitality(0)
	,m_MaxleftBOSSVitality(0)
	,m_bCreared(false)
{
	//Com�̏�����
	CoInitialize(NULL);

	graphics =new CGraphics(*hWnd, windowed, 
		config->GetCHECK_HWVERTEX(),
		config->GetCHECK_REFRASTERIZER(),
		VSync, 
		640, 480);

	tex[0] =new CTexture(graphics, L"./Image/uma.dds");
	poligon[0] =new CPoligon(tex[0], 0, 0, 1, 1);
	tex[1] =new CTexture(graphics, L"./Image/nishisan4.dds");
	poligon[1] =new CPoligon(tex[1], 0, 0, 1, 1);
	tex[2] =new CTexture(graphics, L"./Image/mywavelaser3.dds");
	poligon[2] =new CPoligon(tex[2], 0, 0, 1, 1);
	tex[3] =new CTexture(graphics, L"./Image/enemy_bullet.dds");
	poligon[3] =new CPoligon(tex[3], 0, 0, 1, 1);
	tex[4] =new CTexture(graphics, L"./Image/my_crash.dds");
	poligon[4] =new CPoligon(tex[4], 0, 0, 1, 1);
	tex[5] =new CTexture(graphics, L"./Image/gage.dds");
	poligon[5] =new CPoligon(tex[5], 0, 0, 1, 1);
	tex[6] =new CTexture(graphics, L"./Image/scroll.dds");
	poligon[6] =new CPoligon(tex[6], 0, 0, 1, 1);
	tex[7] =new CTexture(graphics, L"./Image/enemy_crash.dds");
	poligon[7] =new CPoligon(tex[7], 0, 0, 1, 1);
	tex[8] =new CTexture(graphics, L"./Image/killed_bullet.dds");
	poligon[8] =new CPoligon(tex[8], 0, 0, 1, 1);
	tex[9] =new CTexture(graphics, L"./Image/Menutext.dds");
	poligon[9] =new CPoligon(tex[9], 0, 0, 1, 1);
	tex[10] =new CTexture(graphics, L"./Image/EXIT.dds");//���̂Ƃ���󂫃|���S��
	poligon[10] =new CPoligon(tex[10], 0, 0, 1, 1);
	tex[11] =new CTexture(graphics, L"./Image/TITLE.jpg");
	poligon[11] =new CPoligon(tex[11], 0, 0, 1, 1);
	tex[12] =new CTexture(graphics, L"./Image/number.dds");
	poligon[12] =new CPoligon(tex[12], 0, 0, 1, 1);
	tex[13] =new CTexture(graphics, L"./Image/pausetext.dds");
	poligon[13] =new CPoligon(tex[13], 0, 0, 1, 1);
	tex[14] =new CTexture(graphics, L"./Image/Gameovertext.dds");
	poligon[14] =new CPoligon(tex[14], 0, 0, 1, 1);
	tex[15] =new CTexture(graphics, L"./Image/icon.dds");
	poligon[15] =new CPoligon(tex[15], 0, 0, 1, 1);
	tex[16] =new CTexture(graphics, L"./Image/Resulttext.dds");
	poligon[16] =new CPoligon(tex[16], 0, 0, 1, 1);
	tex[17] =new CTexture(graphics, L"./Image/boss_1.dds");
	poligon[17] =new CPoligon(tex[17], 0, 0, 1, 1);
	tex[18] =new CTexture(graphics, L"./Image/nishisan.dds");
	poligon[18] =new CPoligon(tex[18], 0, 0, 1, 1);
	tex[19] =new CTexture(graphics, L"./Image/frame1.dds");
	poligon[19] =new CPoligon(tex[19], 0, 0, 1, 1);
	tex[20] =new CTexture(graphics, L"./Image/frame2.dds");
	poligon[20] =new CPoligon(tex[20], 0, 0, 1, 1);
	tex[21] =new CTexture(graphics, L"./Image/frame3.dds");
	poligon[21] =new CPoligon(tex[21], 0, 0, 1, 1);
	tex[22] =new CTexture(graphics, L"./Image/frame4.dds");
	poligon[22] =new CPoligon(tex[22], 0, 0, 1, 1);
	tex[23] =new CTexture(graphics, L"./Image/frame5.dds");
	poligon[23] =new CPoligon(tex[23], 0, 0, 1, 1);
	tex[24] =new CTexture(graphics, L"./Image/frame6.dds");
	poligon[24] =new CPoligon(tex[24], 0, 0, 1, 1);
	tex[25] =new CTexture(graphics, L"./Image/stage1_back.dds");
	poligon[25] =new CPoligon(tex[25], 0, 0, 1, 1);

	music =new CMusic(hWnd,L"./Musics/The_2nd_Theme.mp3");
	music_boss =new CMusic(hWnd,L"./Musics/FF.wav");

	sound[0] =new CSound(*hWnd, L"./Musics/enemy_shot.wav");
	sound[1] =new CSound(*hWnd, L"./Musics/death_voice.wav");
	sound[2] =new CSound(*hWnd, L"./Musics/my_shot.wav");
	sound[3] =new CSound(*hWnd, L"./Musics/my_laser.wav");
	sound[4] =new CSound(*hWnd, L"./Musics/enemy_crash.wav");
	sound[5] =new CSound(*hWnd, L"./Musics/matte.wav");
	sound[6] =new CSound(*hWnd, L"./Musics/konna.wav");
	sound[7] =new CSound(*hWnd, L"./Musics/getitem.wav");

	input =new CInput(hCurInst,*hWnd);

	script[0] =new CScript("./Script/stage1.txt");
	script[1] =new CScript("./Script/stage2.txt");
	script[2] =new CScript("./Script/stage3.txt");
	for(int i=0;i<STAGE_NUM;++i)
	{
		if(!script[i]->IsOK())
		{
			MessageBox(*hWnd,
				L"�������G���[�Ȃ̂ŏI���܂�",
				L"������",
				MB_OK | MB_ICONINFORMATION);
			DestroyWindow(*hWnd);
		}
	}

	SceneList		=new CTaskList(500, 10);
	StageList		=new CTaskList(500, 10);
	EffectList		=new CTaskList(500, 800);
	ItemList		=new CTaskList(500, 150);
	MyShipList		=new CTaskList(500, 10);
	MyBulletList	=new CTaskList(500, 100);
	MyLaserList		=new CTaskList(500, 50);
	EnemyList		=new CTaskList(500, 100);
	EnemyBulletList =new CTaskList(500, 1000);
	//EnemyLaserList	=new CTaskList(sizeof(CMyLaser), 100);

	score =new CScore();
	FPScounter =new CFPSCounter();
}

//�f�X�g���N�^
CGame::~CGame()
{
	int i;

	for(i =0;i<STAGE_NUM;++i)
	{
		delete script[i];
	}

	delete input;
	for(i =0;i<SE_NUM;++i)
	{
		delete sound[i];
	}
	delete music;
	for(i =0;i<IMAGE_NUM;++i)
	{
		delete poligon[i];
		delete tex[i];
	}
	delete graphics;

	delete EffectList;
	delete MyShipList;
	delete MyBulletList;
	delete MyLaserList;
	delete EnemyList;
	delete EnemyBulletList;
	//delete EnemyLaserList;
	delete ItemList;
	delete StageList;
	delete SceneList;

	delete score;
	delete FPScounter;

	//COM���J������
	CoUninitialize();
}

//������
void CGame::Init()
{
	new CTitle();
}

//���C�������̊J�n
void CGame::Start()
{
	execute_game =true;
	score->ResetScore();
	new CStage1(script[0]);
	new CPrepareNishi(320,360,3,3);
}
void CGame::StartReplay()
{
	execute_game =true;
	score->ResetScore();
	new CStage1_Replay(script[0]);
	new CPrepareNishi(320,360,3,3);
}
//���C�������̒��f�ĊJ
void CGame::ReStart()
{
	execute_game =true;
}
//���C�������̒��f
void CGame::Stop()
{
	execute_game =false;
}

//���@�����݂��Ă��邩����
CNishi* CGame::GetMyShipifExist()
{
	for (CTaskIter i(MyShipList); i.HasNext(); ) 
	{
		CNishi* nishi=(CNishi*)i.Next();
		if (nishi->GetShipState() == NISHI_NORMAL) 
			return nishi;
	}
	return NULL;
}

//��ʏ��̍X�V
void CGame::SetHUD(int leftLife, int leftBomb)
{
	m_leftLife =leftLife;
	m_leftBomb =leftBomb;
}

//��ʏ��̕`��
void CGame::DrawHUD()
{
	graphics->SetRenderState(NORMAL);

	//�Ƃ肠�����t���[���`��
	/*poligon[5]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	poligon[5]->SetRect(320,240,640,480);
	graphics->Draw(Game->poligon[5],1);*/
	poligon[19]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	poligon[19]->SetRect(128,128,256,256);
	graphics->Draw(Game->poligon[19],1);
	poligon[20]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	poligon[20]->SetRect(384,128,256,256);
	graphics->Draw(Game->poligon[20],1);
	poligon[21]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	poligon[21]->SetRect(640,128,256,256);
	graphics->Draw(Game->poligon[21],1);
	poligon[22]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	poligon[22]->SetRect(128,384,256,256);
	graphics->Draw(Game->poligon[22],1);
	poligon[23]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	poligon[23]->SetRect(384,384,256,256);
	graphics->Draw(Game->poligon[23],1);
	poligon[24]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	poligon[24]->SetRect(640,384,256,256);
	graphics->Draw(Game->poligon[24],1);

	//�c�@�Ǝc�{���`��
	poligon[15]->SetColor(0xffffff00,0xffff6600,0xffffff00,0xffff6600);
	for(int i=0;i<m_leftLife;++i)
	{
		poligon[15]->SetRect(520.0f+20.0f*i,145,24,24,0.0f,0.0f,0.25f,0.25f);
		graphics->Draw(poligon[15],1);
	}
	poligon[15]->SetColor(0xff6666ff,0xff6600ff,0xff6666ff,0xff6600ff);
	for(int i=0;i<m_leftBomb;++i)
	{
		poligon[15]->SetRect(520.0f+20.0f*i,210,24,24,0.25f,0.0f,0.5f,0.25f);
		graphics->Draw(poligon[15],1);
	}

	//�X�R�A�`��
	//score->DrawScore(320,30);
	//score->DrawScore(565,70);
	score->DrawPresentScore(565,70,40,40,0xffffffff,0xff000066,0xff000066,0xff000066);
	score->DrawHighScore(565,90,40,40,0xffffffff,0xff000000,0xffffffff,0xff000000);
}

//�{�X�̕\�����ݒ�֐�
void CGame::SetBOSSHUD(int leftLife, int vitality)
{
	m_leftBOSSLife =leftLife;
	m_leftBOSSVitality =vitality;

	if(m_MaxleftBOSSVitality ==0)
		m_MaxleftBOSSVitality =vitality;
}
//�{�X�̕\�����`��֐�
void CGame::DrawBOSSHUD()
{
	graphics->SetRenderState(NORMAL);

	//�c�@�Ǝc�̗͂�\��
	poligon[15]->SetColor(0xffcc9933,0xffcc0033,0xffcc9933,0xffcc0033);
	for(int i=0;i<m_leftBOSSLife;++i)
	{
		poligon[15]->SetRect(170.0f+20.0f*i,40,20,20,0.0f,0.0f,0.25f,0.25f);
		graphics->Draw(poligon[15],1);
	}
	poligon[5]->SetColor(0xffffffff,0xffffcc00,0xffffffff,0xffffcc00);
	float ber_length =320.0f*m_leftBOSSVitality/m_MaxleftBOSSVitality;
	poligon[5]->SetRect(320-(320-ber_length)/2.0f,60,ber_length,6);
	graphics->Draw(poligon[5],1);
}

//FPS�̕`��
void CGame::DrawFPS(float x,float y)
{
	static int update =0;
	static int iFPS[4]={0,0,0,0};

	//�`��^�C�v�Ƃ���ݒ�
	graphics->SetRenderState(NORMAL);
	poligon[12]->SetColor(0xf0000000,0xf0000000,0xf0000000,0xf0000000);
	float u1(0.0f),v1(0.0f),u2(1.0f),v2(1.0f);

	//FPS���擾����100�{
	double FPS =FPScounter->GetFPS();
	FPS *=100;

	//�X�V�p�x��ݒ�
	if(update>60)
	{
		update =0;
		for(int i=3;i>=0;--i)
		{
			iFPS[i] =((int)FPS % 10);
			FPS /=10;
		}
	}
	++update;

	//�`��
	for(int i=0;i<4;++i)
	{
		switch(iFPS[i])
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

		poligon[12]->SetRect(x +12*(i-2)+6,y,32,32,u1,v1,u2,v2);
		graphics->Draw(Game->poligon[12],1);
	}
	poligon[12]->SetRect(x-1,y+1,32,32,0.5f,0.5f,0.75f,0.75f);
	graphics->Draw(Game->poligon[12],1);
}

//���C���������[�v(�ړ�
void CGame::Move()
{
	replay_game ? input->UpdateKeyStateFromFile():input->UpdateKeyState();
	//input->UpdateKeyState();

	MoveTask(SceneList);

	if(!pause_game)
	{
		MoveTask(StageList);
		if(!result_game)
			MoveTask(MyShipList);
		MoveTask(MyBulletList);
		MoveTask(MyLaserList);
		MoveTask(EnemyList);
		MoveTask(EnemyBulletList);
		//MoveTask(EnemyLaserList);
		MoveTask(ItemList);
		MoveTask(EffectList);
		score->UpdateScore();
	}
}

//���C���������[�v(�`��
void CGame::Draw()
{
	graphics->BeginPaint();

	//�^�X�N����
	DrawTask(StageList);

	DrawTask(MyShipList);
	DrawTask(MyBulletList);
	DrawTask(MyLaserList);
	DrawTask(EnemyList);
	DrawTask(EnemyBulletList);
	DrawTask(ItemList);
	//DrawTask(EnemyLaserList);
	DrawTask(EffectList);

	//���̂ق���HUD���͂����ŕ`�悷�邱�Ƃɂ��悤
	if(execute_game)
	{
		DrawHUD();
		DrawBOSSHUD();
	}

	DrawTask(SceneList);
	DrawFPS(590,460);

	graphics->EndPaint();
	graphics->Present();
}

//���[�v�����p�ėp�֐�
void CGame::MoveTask(CTaskList* list) 
{
	for (CTaskIter i(list); i.HasNext(); ) 
	{
		CGameObj* mover=(CGameObj*)i.Next();
		if (!mover->Move()) i.Remove();
	}
}
void CGame::DrawTask(CTaskList* list) 
{
	for (CTaskIter i(list); i.HasNext(); ) 
	{
		((CGameObj*)i.Next())->Draw();
	}
}
void CGame::DeleteAllGameChar()
{
	//SceneList->DeleteTask();
	StageList->DeleteTask();
	MyShipList->DeleteTask();
	MyBulletList->DeleteTask();
	MyLaserList->DeleteTask();
	EnemyList->DeleteTask();
	EnemyBulletList->DeleteTask();
	//EnemyLaserList->DeleteTask();
	ItemList->DeleteTask();
	EffectList->DeleteTask();
}

////////////////////////////////////////////////////////////////////////
//�Q�[���{�̂̃|�C���^�I
////////////////////////////////////////////////////////////////////////

CGame* Game;

////////////////////////////////////////////////////////////////////////
//�Q�[���{�̂̃|�C���^�I
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//�������牺�̓E�B���h�E�Y�̃��C�����[�v
//��{�I�ɂ͘M��Ȃ��Ă悢
//�߂�ǂ������̂ŃN���X�ɑg�ݍ���ł��Ȃ�
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
				   LPSTR lpsCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hWnd;

	if(!SetUp(&hWnd, hCurInst, nCmdShow)) return 0;

	//�Q�[���̏�����
	Game->Init();

	//�^�C�}�[�̕���\���ő��
	timeBeginPeriod(1);

	DWORD starttime=timeGetTime(),deltatime;
	bool bDraw =true;
	//---------------------------------���C�����[�v------------------------------
	while(TRUE)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message==WM_QUIT) 
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if(!Game->GetVSync())
			{
				deltatime =timeGetTime()-starttime;
				if(deltatime >= 16)
				{
					starttime =timeGetTime();
					Game->Move();
					if(Game->GetDrawHalf())
					{
						if(bDraw)
							Game->Draw();
					}
					else
					{
						Game->Draw();
					}
					bDraw =!bDraw;
				}
				else if(deltatime+3 < 16)
				{
					Sleep(1);
				}
			}
			else
			{
				Game->Move();
				Game->Draw();
			}

			/*if(Game->input->GetKeyState(MY_ESCAPE))
			DestroyWindow(hWnd);*/
		}
		Sleep(0);
	}
	//---------------------------------���C�����[�v�I��------------------------------

	//�^�C�}�[�̕���\�����ɖ߂�
	timeEndPeriod(1);

	delete Game;

	return 0;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//�������牺�͕֋X�������֐�
//��{�I�ɂ͘M��Ȃ��Ă悢
//�߂�ǂ������̂ŃN���X�ɑg�ݍ���ł��Ȃ�
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

//�E�B���h�E�E�N���X�̓o�^
ATOM InitApp(HINSTANCE hInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	//�v���V�[�W����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;//�C���X�^���X
	wc.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//�w�i�̓h��Ԃ��̐F
	wc.lpszMenuName = NULL;	//���j���[��
	wc.lpszClassName = L"NISHI-Ge";
	wc.hIconSm = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

//�E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow, HWND *hWnd, int WindowWidth, int WindowHeight,BOOL bWindowed)
{
	int w_width,w_height;
	if(!bWindowed)
	{
		w_width =(int)WindowWidth;
		w_height =(int)WindowHeight;
	}else{
		w_width =(int)WindowWidth 
			+GetSystemMetrics(SM_CXDLGFRAME)*2;
		w_height =(int)WindowHeight 
			+GetSystemMetrics(SM_CYDLGFRAME)*2 
			+GetSystemMetrics(SM_CYCAPTION);
	}

	*hWnd = CreateWindow(
		L"NISHI-Ge",
		GAME_TITLE, //�^�C�g���o�[�ɕ\������܂�
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, //�E�B���h�E�̎��
		CW_USEDEFAULT,	//�w���W
		CW_USEDEFAULT,	//�x���W
		w_width,	//��
		w_height,	//����
		NULL, //�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
		NULL, //���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
		hInst, //�C���X�^���X�n���h��
		NULL);
	if (!*hWnd)
		return FALSE;
	UpdateWindow(*hWnd);
	return TRUE;
}

//�Z�b�g�A�b�v
BOOL SetUp(HWND *hWnd, HINSTANCE hCurInst, int nCmdShow)
{
	CConfig config("nishisan.cfg");

	int id =0;
	if(config.GetCHECK_CONFIRMSIZE())
	{
		id =(MessageBox(NULL,
			L"�t���X�N���[���ŋN�����܂���?\n\n�͂�	�F�t���X�N���[��\n������	�F�E�B���h�E\n�L�����Z��	�F�I��",
			L"�N���m�F",
			MB_YESNOCANCEL | MB_ICONQUESTION));
	}

	if((id==0 && config.GetRADIO_FULLSCREEN()) || id==IDYES)
	{
		/*-------------------------(�t���X�N���[��)--------------------*/
		if (!InitApp(hCurInst))
			return FALSE;
		if (!InitInstance(hCurInst, nCmdShow, hWnd, 640, 480,FALSE)) 
			return FALSE;
		//�Q�[���̃C���X�^���X�쐬
		Game =new CGame(hWnd, hCurInst, &config,false);
		ShowCursor(FALSE);
	}
	else if((id==0 && config.GetRADIO_960_720()) || id == IDNO)
	{
		/*-------------------------(�E�B���h�E960*720)--------------------*/
		if (!InitApp(hCurInst))
			return FALSE;
		if (!InitInstance(hCurInst, nCmdShow, hWnd, 960, 720,TRUE)) 
			return FALSE;
		//�Q�[���̃C���X�^���X�쐬
		Game =new CGame(hWnd, hCurInst, &config,true);
		ShowCursor(TRUE);
	}
	else if(config.GetRADIO_640_480())
	{
		/*-------------------------(�E�B���h�E640*480)--------------------*/
		if (!InitApp(hCurInst))
			return FALSE;
		if (!InitInstance(hCurInst, nCmdShow, hWnd, 640, 480,TRUE)) 
			return FALSE;
		//�Q�[���̃C���X�^���X�쐬
		Game =new CGame(hWnd, hCurInst, &config,true);
		ShowCursor(TRUE);
	}
	else
	{
		return FALSE;
	}
	/*-------------------------�E�B���h�E�̕\��--------------------*/
	ShowWindow(*hWnd, nCmdShow);

	return TRUE;
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int id;
	switch (msg) {
	case WM_CLOSE:
		id = MessageBox(hWnd,
			L"�I��点���񂩁`�H",
			L"������",
			MB_YESNO | MB_ICONQUESTION);
		if (id == IDYES)
			DestroyWindow(hWnd);
		break;
	case WM_DIRECTSHOWMESSAGE:
		((CMusic*)lp)->LoopPlay();
		break;
	case WM_ERASEBKGND:
		break;
	case WM_PAINT:
		ValidateRect(hWnd,NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return 0;
}



