#pragma once
#include "GameObj.h"

class CEnemy;

//----------------------------------------------------------------------
//Nishiクラス(自機のクラス）
//----------------------------------------------------------------------
enum NISHITYPE
{
	NISHI_NORMAL,
	NISHI_INVISI,
	NISHI_PREPARE
};

//----------------------------通常状態--------------------------------//
class CNishi : public CGameObj 
{
protected:
	int anime_count,anime;
	int shot_count,laser_count,laser_num, live_count,bomb_count;
	int m_BombNum,m_LifeNum;
	//int shot_power;
	bool prevbomb_input;
	KEYSTATE key;

public:
	// コンストラクタ、移動、描画
	void* operator new(size_t t) { return operator_new(t, Game->MyShipList); }
	void operator delete(void* p) { operator_delete(p, Game->MyShipList); }
	CNishi(float x, float y,int BombNum, int LifeNum);
	virtual bool NormalShot(int power);
	virtual bool SubShot(int power);
	virtual bool NormalLaser(int limit);
	virtual bool Move();
	virtual void Draw();
	virtual NISHITYPE GetShipState(){return NISHI_NORMAL;}
};

//----------------------------復活状態--------------------------------//
class CInvisiNishi : public CNishi
{
	DWORD color;
public:
	CInvisiNishi(float x, float y, int BombNum, int LifeNum);
	virtual bool NormalShot(int power);
	virtual bool SubShot(int power);
	virtual bool Move();
	virtual void Draw();
	virtual NISHITYPE GetShipState(){return NISHI_INVISI;}
};

//----------------------------準備状態--------------------------------//
class CPrepareNishi : public CNishi
{
	DWORD color;
public:
	CPrepareNishi(float x, float y, int BombNum, int LifeNum);
	virtual bool Move();
	virtual void Draw();
	virtual NISHITYPE GetShipState(){return NISHI_PREPARE;}
};

//----------------------------------------------------------------------
//MyBulletクラス(自機の弾クラス）
//----------------------------------------------------------------------
class CMyBullet : public CGameObj {
protected:
	//真上を0とする
	float m_angle;
	float X_SPEED,Y_SPEED;
	int m_power;
public:
	// コンストラクタ、移動、描画
	void* operator new(size_t t) { return operator_new(t, Game->MyBulletList); }
	void operator delete(void* p) { operator_delete(p, Game->MyBulletList); }
	CMyBullet(float x, float y, float angle, int power,float speed);
	CMyBullet(float x, float y, float w, float h,float r,int power);
	virtual int GetPower(){return m_power;}
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//MyLaserクラス(自機のレーザークラス）
//----------------------------------------------------------------------
class CMyLaser : public CGameObj {
protected:
	CNishi *m_nishi;
	float m_delta_x;
	float m_delta_y;
	int laser_count,laser_num;
	int m_power;
public:
	// コンストラクタ、移動、描画
	void* operator new(size_t t) { return operator_new(t, Game->MyLaserList); }
	void operator delete(void* p) { operator_delete(p, Game->MyLaserList); }
	CMyLaser(CNishi *nishi,float x, float y, float angle, int power);
	int GetPower(){return m_power;}
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//MyHomingLaserクラス(自機の弾クラス）
//----------------------------------------------------------------------
class CMyHomingLaser : public CMyBullet 
{
protected:
	//真上を0とする
	int m_power;
	int m_ID;

	float m_angle;
	float m_speed,m_axel;
	float m_roll;
	float const MAX_ANGLE;
	bool m_homing;
	DWORD m_color;

	CEnemy *m_enemy;

	float prev_X[20],prev_Y[20];
public:
	// コンストラクタ、移動、描画
	void* operator new(size_t t) { return operator_new(t, Game->MyBulletList); }
	void operator delete(void* p) { operator_delete(p, Game->MyBulletList); }
	CMyHomingLaser(CEnemy *enemy,int ID,float x, float y, float speed, float axel, float angle,float max_angle, int power,DWORD color);

	int GetPower(){return m_power;}
	virtual bool Move();
	virtual void Draw();
};
