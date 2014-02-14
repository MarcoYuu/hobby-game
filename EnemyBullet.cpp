#include "Main.h"
#include "EnemyBullet.h"
#include "Effect.h"
#include "Nishi.h"

//----------------------------------------------------------------------
//CEBullet�N���X(�e�̊��N���X�j
//----------------------------------------------------------------------

// �R���X�g���N�^
CEBullet::CEBullet(float x, float y, float w, float h, float r, float angle, float speed, DWORD color)
:CGameObj(Game->EnemyBulletList, x, y, w, h, r, 4, 4),
m_angle(D3DXToRadian(angle)),m_speed(speed),m_color(color)
{
}

//----------------------------------------------------------------------
//CEnemyBullet�N���X(�����e�N���X�j
//----------------------------------------------------------------------

CEnemyBullet::CEnemyBullet(float x, float y, float angle, float speed, float max_speed, float axel, DWORD color)
:CEBullet(x, y, 14, 14, 2, angle, speed, color),m_bSlowdown(axel<0),m_bMaxnull(max_speed==0)
{
	X_SPEED =m_speed*sin(m_angle);
	Y_SPEED =m_speed*cos(m_angle);
	X_AXEL =axel*sin(m_angle);
	Y_AXEL =axel*cos(m_angle);
	MAX_X_SPEED =max_speed*sin(m_angle);
	MAX_Y_SPEED =max_speed*cos(m_angle);
}

// �ړ�
bool CEnemyBullet::Move() {

	// �ړ��͈́A���x
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	// �ړ�
	if(m_bMaxnull)
	{
		X +=X_SPEED;
		X_SPEED +=X_AXEL;
		Y +=Y_SPEED;
		Y_SPEED +=Y_AXEL;
	}
	else if(!m_bSlowdown)
	{
		X +=X_SPEED;
		X_SPEED +=X_AXEL;
		if(abs(X_SPEED) > abs(MAX_X_SPEED))
		{
			X_SPEED =MAX_X_SPEED;
		}
		Y +=Y_SPEED;
		Y_SPEED +=Y_AXEL;
		if(abs(Y_SPEED) > abs(MAX_Y_SPEED))
		{
			Y_SPEED =MAX_Y_SPEED;
		}
	}
	else
	{
		X +=X_SPEED;
		X_SPEED +=X_AXEL;
		if(abs(X_SPEED) < abs(MAX_X_SPEED))
		{
			X_SPEED =MAX_X_SPEED;
		}
		Y +=Y_SPEED;
		Y_SPEED +=Y_AXEL;
		if(abs(Y_SPEED) < abs(MAX_Y_SPEED))
		{
			Y_SPEED =MAX_Y_SPEED;
		}
	}

	// �ړ��͈͂̐���
	if (X<MaxLX) {
		return false;
	}else if (MaxRX<X){
		return false;
	}
	if (Y<MaxTY){
		return false;
	}else if (MaxBY<Y){
		return false;
	}

	return true;
}

// �`��
void CEnemyBullet::Draw() 
{
	Game->poligon[3]->SetColor(0xffffffff,m_color,0xffffffff,m_color);
	Game->poligon[3]->SetRect(X,Y,Width,Height,0.5f,0.0f,0.75f,0.25f);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[3],2);
}

//----------------------------------------------------------------------
//CSmallEnemyBullet�N���X(�����������e�N���X�j
//----------------------------------------------------------------------

CSmallEnemyBullet::CSmallEnemyBullet(float x, float y, float angle, float speed, float axel, DWORD color)
:CEBullet(x, y, 8, 8, 1, angle, speed, color),m_roll(0)
{
	X_SPEED =m_speed*sin(m_angle);
	Y_SPEED =m_speed*cos(m_angle);
	X_AXEL =axel*sin(m_angle);
	Y_AXEL =axel*cos(m_angle);
}

// �ړ�
bool CSmallEnemyBullet::Move() {

	// �ړ��͈́A���x
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	// �ړ�
	X +=X_SPEED;
	X_SPEED +=X_AXEL;
	Y +=Y_SPEED;
	Y_SPEED +=Y_AXEL;

	// �ړ��͈͂̐���
	if (X<MaxLX) {
		return false;
	}else if (MaxRX<X){
		return false;
	}
	if (Y<MaxTY){
		return false;
	}else if (MaxBY<Y){
		return false;
	}

	m_roll +=7;
	if(m_roll>360)
		m_roll -=360;

	return true;
}

// �`��
void CSmallEnemyBullet::Draw() 
{
	Game->poligon[3]->SetColor(0xffffffff,m_color,0xffffffff,m_color);
	Game->poligon[3]->SetRect(X,Y,Width,Height,D3DXToRadian(m_roll),0.0f,0.0f,0.25f,0.25f);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[3],2);
}


//----------------------------------------------------------------------
//CAimBullet�N���X(���@�_���e�N���X�j
//----------------------------------------------------------------------

// �R���X�g���N�^
CAimBullet::CAimBullet(float x, float y, float to_x, float to_y, float speed, float axel, DWORD color)
:CEBullet(x, y, 20, 20, 2, 0, speed, color)
{
	m_angle =atan2(x-to_x,y-to_y);
	X_SPEED =-m_speed*sin(m_angle);
	Y_SPEED =-m_speed*cos(m_angle);
	X_AXEL =-axel*sin(m_angle);
	Y_AXEL =-axel*cos(m_angle);
}

// �ړ�
bool CAimBullet::Move() {

	// �ړ��͈́A���x
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	// �ړ�
	X +=X_SPEED;
	X_SPEED +=X_AXEL;
	Y +=Y_SPEED;
	Y_SPEED +=Y_AXEL;

	// �ړ��͈͂̐���
	if (X<MaxLX) {
		return false;
	}else if (MaxRX<X){
		return false;
	}
	if (Y<MaxTY){
		return false;
	}else if (MaxBY<Y){
		return false;
	}

	return true;
}

// �`��
void CAimBullet::Draw() 
{
	Game->poligon[3]->SetColor(0xffffffff,m_color,0xffffffff,m_color);
	Game->poligon[3]->SetRect(X,Y,Width,Height,-m_angle,0.75f,0.0f,1.0f,0.25f);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[3],2);
}

//----------------------------------------------------------------------
//CCircleBullet�N���X(�~��ɍL����e�N���X�j
//----------------------------------------------------------------------

bool CCircleBullet::Move()
{
	// �ړ��͈�
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	//���Ԑ���
	++m_count;
	if(m_count>m_max_count)
	{
		new CDisappearBullet(X,Y);
		return false;
	}

	//�����ʒu�܂ňړ�
	if((X-m_px)*(X-m_px)+(Y-m_py)*(Y-m_py) <m_first_radius*m_first_radius)
	{
		// �ړ�
		X +=X_SPEED;
		Y +=Y_SPEED;

		return true;
	}

	//��]�Ɣ��a����
	m_rot_angle +=m_angle_spd;
	m_angle_spd +=m_angle_axel;
	if(m_rot_angle>360)
		m_rot_angle -=360.0f;
	float angle =D3DXToRadian(m_rot_angle);

	m_radius +=m_rad_spd;
	m_rad_spd +=m_rad_axel;
	
	//�ړ�
	X =m_px+cos(angle)*m_radius;
	Y =m_py+sin(angle)*m_radius;

	// �ړ��͈͂̐���
	if (X<MaxLX) {
		return false;
	}else if (MaxRX<X){
		return false;
	}
	if (Y<MaxTY){
		return false;
	}else if (MaxBY<Y){
		return false;
	}

	return true;
}
void CCircleBullet::Draw()
{
	Game->poligon[3]->SetColor(0xffffffff,m_color,0xffffffff,m_color);
	Game->poligon[3]->SetRect(X,Y,Width,Height,0.5f,0.0f,0.75f,0.25f);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[3],2);
}
//----------------------------------------------------------------------
//CHomingBullet�N���X(�z�[�~���O�e�N���X�j
//----------------------------------------------------------------------
bool CHomingBullet::Move()
{
	// �ړ��͈́A���x
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;


	//�����񂪂�����������C��
	CNishi* nishi=Game->GetMyShipifExist();
	if(nishi && m_homing)
	{
		if(m_homing =(nishi->Y > Y))
		{
			float temp_angle =atan2(nishi->Y-Y,nishi->X-X);
			if(abs(temp_angle-m_angle)<MAX_ANGLE)
			{
				m_angle =temp_angle;
			}
			else
			{
				if(temp_angle>m_angle)
					m_angle +=MAX_ANGLE;
				else if(temp_angle<m_angle)
					m_angle -=MAX_ANGLE;

				/*if(m_angle>D3DX_PI*2)
					m_angle -=D3DX_PI*2;
				else if(m_angle<D3DX_PI*2)
					m_angle +=D3DX_PI*2;*/
			}
		}
	}

	//�ړ�
	X +=m_speed*cos(m_angle);
	Y +=m_speed*sin(m_angle);
	m_speed +=m_axel;

	for(int i=19;i>0;--i)
	{
		prev_X[i] =prev_X[i-1];
		prev_Y[i] =prev_Y[i-1];
	}
	prev_X[0] =X;
	prev_Y[0] =Y;

	// �ړ��͈͂̐���
	if (prev_X[19]<MaxLX) {
		return false;
	}else if (MaxRX<prev_X[19]){
		return false;
	}
	if (prev_Y[19]<MaxTY){
		return false;
	}else if (MaxBY<prev_Y[19]){
		return false;
	}

	m_roll +=17;
	if(m_roll>360)
		m_roll -=360;

	return true;
}
void CHomingBullet::Draw()
{
	Game->poligon[3]->SetColor(0xffffffff,m_color,0xffffffff,m_color);
	Game->poligon[3]->SetRect(X,Y,Width,Height,D3DXToRadian(m_roll),0.5f,0.0f,0.75f,0.25f);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[3],2);
	for(int i=0;i<20;++i)
	{
		Game->poligon[3]->SetRect(prev_X[i],prev_Y[i],Width,Height,D3DXToRadian(m_roll),0.5f,0.0f,0.75f,0.25f);
		Game->graphics->Draw(Game->poligon[3],2);
	}
}