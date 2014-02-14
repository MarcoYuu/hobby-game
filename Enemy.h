#pragma once
#include "GameObj.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------
//CEnemy�N���X(�S�Ă̓G�̊��N���X�j
//----------------------------------------------------------------------
class CEnemy :public CGameObj
{
protected:
	int m_anime, m_anime_count;
	int m_frame_count,m_frame_count_laser;
	int vitality;
	int m_score;

	int m_LockedID;

public:
	// �R���X�g���N�^�A�ړ��A�`��
	void* operator new(size_t t) { return operator_new(t, Game->EnemyList); }
	void operator delete(void* p) { operator_delete(p, Game->EnemyList); }
	CEnemy(float x, float y, float w, float h, float r, int vitality, int score);
	virtual bool HitorNot();
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
	void SetLockID(int lockID){m_LockedID =lockID;}
	int GetLockID(){return m_LockedID;}
};
//----------------------------------------------------------------------
//CCurveMove�N���X(�Ȑ��ړ���������N���X�j
//----------------------------------------------------------------------
//�Ȑ��ړ�
class CCurveMove :public CEnemy
{
protected:
	float X_SPEED,Y_SPEED;
	float X_AXEL,Y_AXEL;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	CCurveMove(float x, float y, float x_spd, float y_spd, 
		float x_axel, float y_axel,int vital)
	:CEnemy(x,y,25,25,16,vital,1000),
	X_SPEED(x_spd),Y_SPEED(y_spd),X_AXEL(x_axel),Y_AXEL(y_axel)
	{
	}

	virtual void Shot() =0;
	bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//C2PointCurveMove�N���X(2�_�ԋȐ��ړ���������N���X�j
//----------------------------------------------------------------------
//��_�ԋȐ��ړ�
class C2PointCurveMove :public CEnemy
{
protected:
	int	m_time1,m_time2,m_shot_time;
	float X_SPEED,X_SPEED2;
	float Y_AXEL,Y_AXEL2;
	float m_x1,m_y1,m_x2,m_y2,m_x3,m_y3;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	C2PointCurveMove(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital)
	:CEnemy(x1,y1,25,25,16,vital,1200),
	m_time1(time1),m_time2(time2),m_shot_time(shot_time),
	m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2),m_x3(x3),m_y3(y3)
	{
		//X_SPEED =(x2-x1)/time1;
		//Y_AXEL =(y2-y1)/((x2-x1)*(x2-x1));

		//X_SPEED2 =(x3-x2)/time2;
		//Y_AXEL2 =(y3-y2)/((x3-x2)*(x3-x2));
	}

	//�x�W�F�Ȑ��̍��W���擾����֐�(�n�_��0�A�I�_��1�Ƃ���)
	//���߂������W�̑��΋������w��
	//���ʂ��󂯎��ϐ����|�C���^�Ŏw��
	void BezCurve(float requere_distance,float *x,float *y);


	virtual void Shot() =0;
	bool Move();
	virtual void Draw();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------
//CNormalEnemy_1�N���X(���ˏ�ɋʂ��o���G�N���X�j
//----------------------------------------------------------------------

//�Ȑ��ړ�
class CNormalEnemy_1 :public CCurveMove
{
protected:
	int shot_count,shot_count2,shotnum;
	float m_shot_speed;
	float m_roll,m_roll2;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_1(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float roll,float shot_speed,int shot_num,int count)
	:CCurveMove(x,y,x_spd,y_spd,x_axel,y_axel,vital),
	shot_count(0),shot_count2(count),m_roll(roll),m_roll2(0),
	shotnum(shot_num),m_shot_speed(shot_speed)
	{
	}

	void Shot();
};
//��_�ԋȐ��ړ�
class CNormalEnemy_1_2Point :public C2PointCurveMove
{
protected:
	int shot_count,shot_count2,shotnum;
	float m_shot_speed;
	float m_roll,m_roll2;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_1_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float roll,float shot_speed,int shot_num,int count)
	:C2PointCurveMove(x1,y1,x2,y2,x3,y3,time1,time2,shot_time,vital),
	shot_count(0),shot_count2(count),m_roll(roll),m_roll2(0),
	shotnum(shot_num),m_shot_speed(shot_speed)
	{
	}

	void Shot();
};

//----------------------------------------------------------------------
//CNormalEnemy_2�N���X(���@�_�����o���G�N���X�j
//----------------------------------------------------------------------

//�Ȑ��ړ�
class CNormalEnemy_2 :public CCurveMove
{
protected:
	int shot_count,shot_count2;
	float to_X,to_Y,m_shot_speed;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_2(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float shot_speed,int count)
	:CCurveMove(x,y,x_spd,y_spd,x_axel,y_axel,vital),
	shot_count(0),shot_count2(count),to_X(0),to_Y(0),m_shot_speed(shot_speed)
	{
	}

	void Shot();
};
//��_�ԋȐ��ړ�
class CNormalEnemy_2_2Point :public C2PointCurveMove
{
protected:
	int shot_count,shot_count2;
	float to_X,to_Y,m_shot_speed;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_2_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float shot_speed,int count)
	:C2PointCurveMove(x1,y1,x2,y2,x3,y3,time1,time2,shot_time,vital),
	shot_count(0),shot_count2(count),to_X(0),to_Y(0),m_shot_speed(shot_speed)
	{
	}

	void Shot();
};

//----------------------------------------------------------------------
//CNormalEnemy_3�N���X(��`��ɋʂ��o���G�N���X�j
//----------------------------------------------------------------------

//�Ȑ��ړ�
class CNormalEnemy_3 :public CCurveMove
{
protected:
	int m_shot_count,m_shot_count2,
		m_shot_num,m_max_shot_num;
	float to_X,to_Y,m_shot_speed,m_angle;
	bool m_bShot;

public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_3(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float shot_speed,int max_shot_num,int count)
	:CCurveMove(x,y,x_spd,y_spd,x_axel,y_axel,vital),
	m_shot_count(0),m_shot_count2(count),m_shot_num(0),m_max_shot_num(max_shot_num),
	to_X(0),to_Y(0),m_angle(0),m_shot_speed(shot_speed),m_bShot(false)
	{
	}

	void Shot();
};
//��_�ԋȐ��ړ�
class CNormalEnemy_3_2Point :public C2PointCurveMove
{
protected:
	int m_shot_count,m_shot_count2,
		m_shot_num,m_max_shot_num;
	float to_X,to_Y,m_shot_speed,m_angle;
	bool m_bShot;

public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_3_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float shot_speed,int max_shot_num,int count)
	:C2PointCurveMove(x1,y1,x2,y2,x3,y3,time1,time2,shot_time,vital),
	m_shot_count(0),m_shot_count2(count),m_shot_num(0),m_max_shot_num(max_shot_num),
	to_X(0),to_Y(0),m_angle(0),m_shot_speed(shot_speed),m_bShot(false)
	{
	}

	void Shot();
};

//----------------------------------------------------------------------
//CNormalEnemy_4�N���X(���@�_���𕡐��o���G�N���X(��e/�����e�j)
//----------------------------------------------------------------------

//�Ȑ��ړ�
class CNormalEnemy_4 :public CCurveMove
{
protected:
	int shot_count,shot_count2;
	int m_max_shot_num;
	float m_delta_x;
	float to_X,to_Y,m_shot_speed,m_shot_axel;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_4(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float shot_speed,float shot_axel,int count,int max_shot_num,float delta_x)
	:CCurveMove(x,y,x_spd,y_spd,x_axel,y_axel,vital),
	shot_count(0),shot_count2(count),to_X(0),to_Y(0),m_shot_speed(shot_speed),
	m_max_shot_num(max_shot_num),m_delta_x(delta_x),m_shot_axel(shot_axel)
	{
	}

	void Shot();
};
//��_�ԋȐ��ړ�
class CNormalEnemy_4_2Point :public C2PointCurveMove
{
protected:
	int shot_count,shot_count2;
	int m_max_shot_num;
	float m_delta_x;
	float to_X,to_Y,m_shot_speed,m_shot_axel;
public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_4_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float shot_speed,float shot_axel,int count,int max_shot_num,float delta_x)
	:C2PointCurveMove(x1,y1,x2,y2,x3,y3,time1,time2,shot_time,vital),
	shot_count(0),shot_count2(count),to_X(0),to_Y(0),m_shot_speed(shot_speed),
	m_max_shot_num(max_shot_num),m_delta_x(delta_x),m_shot_axel(shot_axel)
	{
	}

	void Shot();
};
//----------------------------------------------------------------------
//CNormalEnemy_5�N���X(�~�`�ɐi�ޒe���o���G�N���X)
//----------------------------------------------------------------------

//�Ȑ��ړ�
class CNormalEnemy_5 :public CCurveMove
{
protected:
	int m_shot_count,m_max_shot_count;
	int m_shot_num;
	float m_line_speed;
	float m_delta_roll,m_roll;
	float m_angle_spd,m_angle_axel;
	float m_radius,m_rad_spd,m_rad_axel;
	int m_erase_count;

public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_5(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float shot_speed,float roll,float delta_roll,float angle_spd,float angle_axel,
		float radius,float rad_spd,float rad_axel,int shot_num,int erase_count,int shot_count)
	:CCurveMove(x,y,x_spd,y_spd,x_axel,y_axel,vital),
	m_shot_count(0),m_max_shot_count(shot_count),m_erase_count(erase_count),
	m_shot_num(shot_num),m_line_speed(shot_speed),m_delta_roll(delta_roll),m_roll(roll),
	m_angle_spd(angle_spd),m_angle_axel(angle_axel),m_radius(radius),m_rad_spd(rad_spd),m_rad_axel(rad_axel)
	{
	}

	void Shot();
};
//��_�ԋȐ��ړ�
class CNormalEnemy_5_2Point :public C2PointCurveMove
{
protected:
	int m_shot_count,m_max_shot_count;
	int m_shot_num;
	float m_line_speed;
	float m_delta_roll,m_roll;
	float m_angle_spd,m_angle_axel;
	float m_radius,m_rad_spd,m_rad_axel;
	int m_erase_count;

public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_5_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float shot_speed,float roll,float delta_roll,float angle_spd,float angle_axel,
		float radius,float rad_spd,float rad_axel,int shot_num,int erase_count,int shot_count)
	:C2PointCurveMove(x1,y1,x2,y2,x3,y3,time1,time2,shot_time,vital),
	m_shot_count(0),m_max_shot_count(shot_count),m_erase_count(erase_count),
	m_shot_num(shot_num),m_line_speed(shot_speed),m_delta_roll(delta_roll),m_roll(roll),
	m_angle_spd(angle_spd),m_angle_axel(angle_axel),m_radius(radius),m_rad_spd(rad_spd),m_rad_axel(rad_axel)
	{
	}

	void Shot();
};

//----------------------------------------------------------------------
//CNormalEnemy_6�N���X(�����̒e�𖳑���ɂ΂�T���G�N���X)
//----------------------------------------------------------------------

//�Ȑ��ړ�
class CNormalEnemy_6 :public CCurveMove
{
protected:
	int m_shot_count,m_max_shot_count;
	int m_shot_num;
	float m_speed,m_axel;

public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_6(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float speed,float axel,int shot_num,int shot_count)
	:CCurveMove(x,y,x_spd,y_spd,x_axel,y_axel,vital),
	m_shot_count(0),m_max_shot_count(shot_count),m_shot_num(shot_num),m_speed(speed),m_axel(axel)
	{
	}

	void Shot();
};
//��_�ԋȐ��ړ�
class CNormalEnemy_6_2Point :public C2PointCurveMove
{
protected:
	int m_shot_count,m_max_shot_count;
	int m_shot_num;
	float m_speed,m_axel;

public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_6_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float speed,float axel,int shot_num,int shot_count)
	:C2PointCurveMove(x1,y1,x2,y2,x3,y3,time1,time2,shot_time,vital),
	m_shot_count(0),m_max_shot_count(shot_count),m_shot_num(shot_num),m_speed(speed),m_axel(axel)
	{
	}

	void Shot();
};

//----------------------------------------------------------------------
//CNormalEnemy_7�N���X(����̕����ɒe�����G�N���X)
//----------------------------------------------------------------------
//�Ȑ��ړ�
class CNormalEnemy_7 :public CCurveMove
{
protected:
	int m_shot_count,m_max_shot_count;
	int m_shot_num,m_max_shot_num;
	float m_speed,m_max_speed,m_axel,m_angle;

public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_7(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float speed,float max_speed,float axel,float angle,int max_shot_num,int shot_count)
	:CCurveMove(x,y,x_spd,y_spd,x_axel,y_axel,vital),
	m_shot_count(0),m_max_shot_count(shot_count),m_shot_num(0),m_max_shot_num(max_shot_num),
	m_speed(speed),m_max_speed(max_speed),m_axel(axel),m_angle(angle)
	{
	}

	void Shot();
};
//��_�ԋȐ��ړ�
class CNormalEnemy_7_2Point :public C2PointCurveMove
{
protected:
	int m_shot_count,m_max_shot_count;
	int m_shot_num,m_max_shot_num;
	float m_speed,m_max_speed,m_axel,m_angle;

public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_7_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float speed,float max_speed,float axel,float angle,int max_shot_num,int shot_count)
	:C2PointCurveMove(x1,y1,x2,y2,x3,y3,time1,time2,shot_time,vital),
	m_shot_count(0),m_max_shot_count(shot_count),m_shot_num(0),m_max_shot_num(max_shot_num),
	m_speed(speed),m_max_speed(max_speed),m_axel(axel),m_angle(angle)
	{
	}

	void Shot();
};



//----------------------------------------------------------------------
//CNormalEnemy_8�N���X(�ǔ��e�G�N���X)
//----------------------------------------------------------------------

//�Ȑ��ړ�
class CNormalEnemy_8 :public CCurveMove
{
protected:
	int m_shot_count,m_max_shot_count;
	float m_speed,m_axel,m_angle,m_max_angle;

public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_8(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float speed,float axel,float angle,float max_angle,int shot_count)
	:CCurveMove(x,y,x_spd,y_spd,x_axel,y_axel,vital),
	m_shot_count(0),m_max_shot_count(shot_count),
	m_speed(speed),m_axel(axel),m_angle(angle),m_max_angle(D3DXToRadian(max_angle))
	{
	}

	void Shot();
};
//��_�ԋȐ��ړ�
class CNormalEnemy_8_2Point :public C2PointCurveMove
{
protected:
	int m_shot_count,m_max_shot_count;
	float m_speed,m_axel,m_angle,m_max_angle;

public:
	// �R���X�g���N�^�A�ړ��A�`��
	CNormalEnemy_8_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float speed,float axel,float angle,float max_angle,int shot_count)
	:C2PointCurveMove(x1,y1,x2,y2,x3,y3,time1,time2,shot_time,vital),
	m_shot_count(0),m_max_shot_count(shot_count),
	m_speed(speed),m_axel(axel),m_angle(angle),m_max_angle(D3DXToRadian(max_angle))
	{
	}

	void Shot();
};
