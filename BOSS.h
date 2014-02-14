#pragma once
#include "GameObj.h"
#include "Effect.h"
#include "Scene.h"

//----------------------------------------------------------------------
//CBOSSクラス(全てのBOSSの基底クラス）
//----------------------------------------------------------------------
class CBOSS :public CGameObj
{
protected:
	int m_anime, m_anime_count;
	int m_frame_count,m_frame_count_laser;
	int vitality,max_vitality,m_life;
	int m_score;
	int m_stage_num;
public:
	void* operator new(size_t t) { return operator_new(t, Game->EnemyList); }
	void operator delete(void* p) { operator_delete(p, Game->EnemyList); }

	CBOSS(float x, float y, float w, float h, float r, int vitality, int life,int score, int stage)
	:CGameObj(Game->EnemyList, x, y, w, h, r, 4.0f, 4.0f),m_stage_num(stage),
	m_anime(0), m_anime_count(0), m_frame_count(0), m_frame_count_laser(0),
	vitality(vitality), max_vitality(vitality),m_life(life),m_score(score)
	{
	}
	virtual ~CBOSS(void)
	{
	}

	virtual void base_HitorNot();
	int GetVitality()
	{
		return vitality;
	}
	void SetVitality(int vit)
	{
		vitality =vit;
	}
	void SubtractVital(int attack)
	{
		vitality -=attack;
	}
};

//----------------------------------------------------------------------
//CBOSS_1クラス(BOSS1クラス）
//----------------------------------------------------------------------
class CBOSS_1 :public CBOSS
{
	float X_SPEED,Y_SPEED;
	
	//第一段階
	bool have_set1; 
	int frame_count1;
	int shot_count;
	int shot_count1;
	float m_roll;
	//第二段階
	float m_rot_angle,m_angle_spd;
	bool have_set2; 
	int frame_count2,m_shot_num;
	int shot_count2;
	//第三段階
	bool have_set3; 
	int frame_count3;
	int shot_count3,color_num;
	bool add;
	//最終段階
	bool have_set4; 
	int frame_count4;
	int shot_count4;
public:
	void* operator new(size_t t) { return operator_new(t, Game->EnemyList); }
	void operator delete(void* p) { operator_delete(p, Game->EnemyList); }

	CBOSS_1(float x, float y)
	:CBOSS(x, y, 90, 90, 40, 5000, 3, 500000, 1),
	X_SPEED(0),Y_SPEED(0),
	m_rot_angle(0),m_angle_spd(0),m_roll(0),
	have_set1(false),frame_count1(0),shot_count(0),shot_count1(0),
	have_set2(false),frame_count2(0),m_shot_num(0),shot_count2(0),
	have_set3(false),frame_count3(0),shot_count3(0),color_num(0),add(true),
	have_set4(false),frame_count4(0),shot_count4(0)
	{
		Game->SetBOSSHUD(m_life,vitality);
		Game->music->Stop();
		Game->music_boss->Play();
		new CBOSSCrash(X,Y);
	}
	~CBOSS_1()
	{
		Game->SetBOSSHUD(0,0);
	}

	bool HitorNot();

	bool Move();
	void Draw();

	bool Move_1();
	bool Move_2();
	bool Move_3();
	bool Move_last();

	void Shot_1();
	void Shot_2();
	void Shot_3();
	void Shot_last();
};

//----------------------------------------------------------------------
//CBOSS_2クラス(BOSS2クラス）
//----------------------------------------------------------------------
class CBOSS_2 :public CBOSS
{
	float X_SPEED,Y_SPEED;
	
	//第一段階
	bool have_set1; 
	int frame_count1;
	int shot_count;
	int shot_count1;
	float m_roll;
	//第二段階
	float m_rot_angle,m_angle_spd;
	bool have_set2; 
	int frame_count2,m_shot_num;
	int shot_count2;
	//第三段階
	bool have_set3; 
	int frame_count3;
	int shot_count3,color_num;
	bool add;
	//最終段階
	bool have_set4; 
	int frame_count4;
	int shot_count4;
public:
	void* operator new(size_t t) { return operator_new(t, Game->EnemyList); }
	void operator delete(void* p) { operator_delete(p, Game->EnemyList); }

	CBOSS_2(float x, float y)
	:CBOSS(x, y, 90, 90, 40, 5000, 3, 500000, 2),
	X_SPEED(0),Y_SPEED(0),
	m_rot_angle(0),m_angle_spd(0),m_roll(0),
	have_set1(false),frame_count1(0),shot_count(0),shot_count1(0),
	have_set2(false),frame_count2(0),m_shot_num(0),shot_count2(0),
	have_set3(false),frame_count3(0),shot_count3(0),color_num(0),add(true),
	have_set4(false),frame_count4(0),shot_count4(0)
	{
		Game->SetBOSSHUD(m_life,vitality);
		Game->music->Stop();
		Game->music_boss->Play();
		new CBOSSCrash(X,Y);
	}
	~CBOSS_2()
	{
		Game->SetBOSSHUD(0,0);
	}

	bool HitorNot();

	bool Move();
	void Draw();

	bool Move_1();
	bool Move_2();
	bool Move_3();
	bool Move_last();

	void Shot_1();
	void Shot_2();
	void Shot_3();
	void Shot_last();
};

//----------------------------------------------------------------------
//CBOSS_3クラス(BOSS3クラス）
//----------------------------------------------------------------------
class CBOSS_3 :public CBOSS
{
	float X_SPEED,Y_SPEED;
	
	//第一段階
	bool have_set1; 
	int frame_count1;
	int shot_count;
	int shot_count1;
	float m_roll;
	//第二段階
	float m_rot_angle,m_angle_spd;
	bool have_set2; 
	int frame_count2,m_shot_num;
	int shot_count2;
	//第三段階
	bool have_set3; 
	int frame_count3;
	int shot_count3,color_num;
	bool add;
	//最終段階
	bool have_set4; 
	int frame_count4;
	int shot_count4;
public:
	void* operator new(size_t t) { return operator_new(t, Game->EnemyList); }
	void operator delete(void* p) { operator_delete(p, Game->EnemyList); }

	CBOSS_3(float x, float y)
	:CBOSS(x, y, 90, 90, 40, 5000, 3, 500000, 3),
	X_SPEED(0),Y_SPEED(0),
	m_rot_angle(0),m_angle_spd(0),m_roll(0),
	have_set1(false),frame_count1(0),shot_count(0),shot_count1(0),
	have_set2(false),frame_count2(0),m_shot_num(0),shot_count2(0),
	have_set3(false),frame_count3(0),shot_count3(0),color_num(0),add(true),
	have_set4(false),frame_count4(0),shot_count4(0)
	{
		Game->SetBOSSHUD(m_life,vitality);
		Game->music->Stop();
		Game->music_boss->Play();
		new CBOSSCrash(X,Y);
	}
	~CBOSS_3()
	{
		Game->SetBOSSHUD(0,0);
	}

	bool HitorNot();

	bool Move();
	void Draw();

	bool Move_1();
	bool Move_2();
	bool Move_3();
	bool Move_last();

	void Shot_1();
	void Shot_2();
	void Shot_3();
	void Shot_last();
};