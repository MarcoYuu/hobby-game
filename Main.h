#include "Input.h"
#include "Graphics.h"
#include "Music.h"
#include "Sound.h"
#include "Task.h"
#include "Score.h"
#include "Script.h"
#include "FPSCounter.h"
#include <time.h>

#define IMAGE_NUM 26
#define SE_NUM 8
#define STAGE_NUM 3
#define GAME_TITLE L"NISHI-Ge ver1.16"

class CNishi;

//----------------------------------------------------------------------
//�R���t�B�O�N���X�i�ݒ��ێ�����N���X�j
//----------------------------------------------------------------------

class CConfig
{
	bool CHECK_HWVERTEX;
	bool CHECK_REFRASTERIZER;
	bool CHECK_DRAWINTERVALHALF;
	bool CHECK_CONFIRMSIZE;
	bool RADIO_FORCEFPSSIXTY;
	bool RADIO_VSYNC;
	bool RADIO_640_480;
	bool RADIO_960_720;
	bool RADIO_FULLSCREEN;
public:
	//�R���X�g���N�^
	CConfig(string file_name);
	bool GetCHECK_HWVERTEX(){return CHECK_HWVERTEX;}
	bool GetCHECK_REFRASTERIZER(){return CHECK_REFRASTERIZER;}
	bool GetCHECK_DRAWINTERVALHALF(){return CHECK_DRAWINTERVALHALF;}
	bool GetCHECK_CONFIRMSIZE(){return CHECK_CONFIRMSIZE;}
	bool GetRADIO_FORCEFPSSIXTY(){return RADIO_FORCEFPSSIXTY;}
	bool GetRADIO_VSYNC(){return RADIO_VSYNC;}
	bool GetRADIO_640_480(){return RADIO_640_480;}
	bool GetRADIO_960_720(){return RADIO_960_720;}
	bool GetRADIO_FULLSCREEN(){return RADIO_FULLSCREEN;}
};

//----------------------------------------------------------------------
//�Q�[���N���X�i�Q�[���S�̂̊Ǌ��N���X�j
//----------------------------------------------------------------------

class CGame
{
private:
	//�Q�[������
	bool execute_game;
	bool pause_game;
	bool replay_game;
	bool result_game;
	bool windowed;
	bool draw_interval;
	bool VSync;

	//���@���
	int m_leftLife;
	int m_leftBomb;
	//�{�X���
	int m_leftBOSSLife;
	int m_leftBOSSVitality;
	int m_MaxleftBOSSVitality;

	//�X�e�[�W���
	bool m_bCreared;

public:	
	//�c�[���ނ̃|�C���^
	CGraphics* graphics;
	CTexture* tex[IMAGE_NUM];
	CPoligon* poligon[IMAGE_NUM];
	CMusic* music;
	CMusic* music_boss;
	CSound* sound[SE_NUM];
	CInput* input;
	CScore* score;
	CFPSCounter* FPScounter;

	//�X�e�[�W�̃X�N���v�g�̃|�C���^
	CScript* script[STAGE_NUM];

	//�R���X�g���N�^
	CGame(HWND *hWnd,HINSTANCE hCurInst,CConfig *config,bool bWindowed);
	~CGame();

	//���ۂ̒��S�̏���
	void Init();
	virtual void Move();
	virtual void Draw();

	//����n
	void Start();
	void StartReplay();
	void ReStart();
	void Stop();

	//HUD���n
	void SetHUD(int leftLife, int leftBomb);
	void DrawHUD();

	void SetBOSSHUD(int leftLife, int vitality);
	void DrawBOSSHUD();

	void DrawFPS(float x,float y);

	//�|�[�Y
	void SetPause(bool paused){pause_game =paused;}
	//���v���C
	void SetReplay(bool replay){replay_game =replay;}
	bool GetReplay(){return replay_game;}
	//���U���g
	void SetResult(bool result){result_game =result;}
	bool GetResult(){return result_game;}
	//���̑��������
	bool GetWindowed(){return windowed;}
	bool GetDrawHalf(){return draw_interval;}
	bool GetVSync(){return VSync;}
	CNishi* GetMyShipifExist();

	//�N���A�t���O
	void SetCreared(bool creared){m_bCreared =creared;}
	bool GetCreared(){return m_bCreared;}

	//�^�X�N
	CTaskList *SceneList;
	CTaskList *StageList;
	CTaskList *EffectList;
	CTaskList *ItemList;
	CTaskList *MyShipList;
	CTaskList *MyBulletList;
	CTaskList *MyLaserList;
	CTaskList *EnemyList;
	CTaskList *EnemyBulletList;
	//CTaskList *EnemyLaserList;
	void MoveTask(CTaskList* list);
	void DrawTask(CTaskList* list);
	void DeleteAllGameChar();
};

//----------------------------------------------------------------------
//�Q�[���{�̂����O�ɐ錾
//----------------------------------------------------------------------

extern CGame* Game;

//----------------------------------------------------------------------
//���̑��̃E�B���h�E�Y�֐�
//----------------------------------------------------------------------
ATOM InitApp(HINSTANCE hInst);
BOOL InitInstance(HINSTANCE hInst, int nCmdShow, HWND *hWnd, int WindowWidth, int WindowHeight,BOOL bWindowed);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL SetUp(HWND *hWnd, HINSTANCE hCurInst, int nCmdShow);