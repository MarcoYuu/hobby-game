#pragma once
#include "GameObj.h"

//----------------------------------------------------------------------
//CEBullet�N���X(�e�̊��N���X�j
//----------------------------------------------------------------------

class CEBullet :public CGameObj
{
protected:
	//�^����0�Ƃ���
	float m_angle;
	float m_speed;
	DWORD m_color;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	void* operator new(size_t t) { return operator_new(t, Game->EnemyBulletList); }
	void operator delete(void* p) { operator_delete(p, Game->EnemyBulletList); }
	CEBullet(float x, float y, float w, float h, float r, float angle, float speed,DWORD color);
};

//----------------------------------------------------------------------
//CEnemyBullet�N���X(�����e�N���X�j
//----------------------------------------------------------------------

class CEnemyBullet :public CEBullet
{
protected:
	float X_SPEED,Y_SPEED;
	float X_AXEL,Y_AXEL;
	float MAX_X_SPEED,MAX_Y_SPEED;
	bool m_bSlowdown,m_bMaxnull;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	CEnemyBullet(float x, float y, float angle, float speed, float max_speed,float axel, DWORD color);
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CSmallEnemyBullet�N���X(�����������e�N���X�j
//----------------------------------------------------------------------

class CSmallEnemyBullet :public CEBullet
{
protected:
	float X_SPEED,Y_SPEED;
	float X_AXEL,Y_AXEL;
	float m_roll;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	CSmallEnemyBullet(float x, float y, float angle, float speed, float axel, DWORD color);
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CAimBullet�N���X(���@�_���e�N���X�j
//----------------------------------------------------------------------

class CAimBullet :public CEBullet
{
protected:
	float X_SPEED,Y_SPEED;
	float X_AXEL,Y_AXEL;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	CAimBullet(float x, float y, float to_x, float to_y, float speed, float axel, DWORD color);
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CCircleBullet�N���X(�~��ɍL����e�N���X�j
//----------------------------------------------------------------------

class CCircleBullet :public CEBullet
{
protected:
	float const m_px,m_py;							//���S���W
	float X_SPEED,Y_SPEED;						//�������a�܂ł̑���
	float m_rot_angle,m_angle_spd,m_angle_axel;	//��]�p�x�Ɗp���x
	float m_first_radius,m_radius,m_rad_spd,m_rad_axel;		//�������a�Ɣ��a�������x
	int m_count,m_max_count;					//���˂���Ă����F���Ƒ��݉\F��
public:
	// �R���X�g���N�^�A�ړ��A�`��
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
//CHomingBullet�N���X(�z�[�~���O�e�N���X�j
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
	// �R���X�g���N�^�A�ړ��A�`��
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