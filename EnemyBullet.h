#pragma once
#include "GameObj.h"

//----------------------------------------------------------------------
//CEBulletクラス(弾の基底クラス）
//----------------------------------------------------------------------

class CEBullet :public CGameObj
{
protected:
	//真下を0とする
	float m_angle;
	float m_speed;
	DWORD m_color;
public:
	// コンストラクタ、移動、描画
	void* operator new(size_t t) { return operator_new(t, Game->EnemyBulletList); }
	void operator delete(void* p) { operator_delete(p, Game->EnemyBulletList); }
	CEBullet(float x, float y, float w, float h, float r, float angle, float speed,DWORD color);
};

//----------------------------------------------------------------------
//CEnemyBulletクラス(直線弾クラス）
//----------------------------------------------------------------------

class CEnemyBullet :public CEBullet
{
protected:
	float X_SPEED,Y_SPEED;
	float X_AXEL,Y_AXEL;
	float MAX_X_SPEED,MAX_Y_SPEED;
	bool m_bSlowdown,m_bMaxnull;
public:
	// コンストラクタ、移動、描画
	CEnemyBullet(float x, float y, float angle, float speed, float max_speed,float axel, DWORD color);
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CSmallEnemyBulletクラス(小さい直線弾クラス）
//----------------------------------------------------------------------

class CSmallEnemyBullet :public CEBullet
{
protected:
	float X_SPEED,Y_SPEED;
	float X_AXEL,Y_AXEL;
	float m_roll;
public:
	// コンストラクタ、移動、描画
	CSmallEnemyBullet(float x, float y, float angle, float speed, float axel, DWORD color);
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CAimBulletクラス(自機狙い弾クラス）
//----------------------------------------------------------------------

class CAimBullet :public CEBullet
{
protected:
	float X_SPEED,Y_SPEED;
	float X_AXEL,Y_AXEL;
public:
	// コンストラクタ、移動、描画
	CAimBullet(float x, float y, float to_x, float to_y, float speed, float axel, DWORD color);
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CCircleBulletクラス(円状に広がる弾クラス）
//----------------------------------------------------------------------

class CCircleBullet :public CEBullet
{
protected:
	float const m_px,m_py;							//中心座標
	float X_SPEED,Y_SPEED;						//初期半径までの速さ
	float m_rot_angle,m_angle_spd,m_angle_axel;	//回転角度と角速度
	float m_first_radius,m_radius,m_rad_spd,m_rad_axel;		//初期半径と半径増加速度
	int m_count,m_max_count;					//発射されてからのF数と存在可能F数
public:
	// コンストラクタ、移動、描画
	CCircleBullet(float x, float y, float speed,
		float rot_angle,float angle_spd, float angle_axel, 
		float radius, float rad_spd, float rad_axel, int max_count ,DWORD color)
	:CEBullet(x, y, 12, 12, 2, rot_angle, speed, color),m_px(x),m_py(y),
	m_rot_angle(rot_angle),m_angle_spd(angle_spd),m_angle_axel(angle_axel),
	m_first_radius(radius),m_radius(radius),m_rad_spd(rad_spd),m_rad_axel(rad_axel),
	m_count(0),m_max_count(max_count)
	{
		X_SPEED =m_speed*cos(m_angle);
		Y_SPEED =m_speed*sin(m_angle);
	}
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CHomingBulletクラス(ホーミング弾クラス）
//----------------------------------------------------------------------

class CHomingBullet :public CEBullet
{
protected:
	float m_speed,m_axel;
	float m_roll;
	float const MAX_ANGLE;
	bool m_homing;

	float prev_X[20],prev_Y[20];
public:
	// コンストラクタ、移動、描画
	CHomingBullet(float x, float y, float speed, float axel, float angle,float max_angle, DWORD color)
	:CEBullet(x, y, 20, 20, 5, angle, speed, color),
	MAX_ANGLE(max_angle),m_speed(speed),m_axel(axel),m_roll(0),m_homing(true)
	{
		for(int i=0;i<20;++i)
		{
			prev_X[i] =X;
			prev_Y[i] =Y;
		}
	}
	virtual bool Move();
	virtual void Draw();
};