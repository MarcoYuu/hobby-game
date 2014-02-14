#include "Main.h"
#include "EnemyBullet.h"
#include "Effect.h"
#include "Nishi.h"

//----------------------------------------------------------------------
//CEBulletクラス(弾の基底クラス）
//----------------------------------------------------------------------

// コンストラクタ
CEBullet::CEBullet(float x, float y, float w, float h, float r, float angle, float speed, DWORD color)
:CGameObj(Game->EnemyBulletList, x, y, w, h, r, 4, 4),
m_angle(D3DXToRadian(angle)),m_speed(speed),m_color(color)
{
}

//----------------------------------------------------------------------
//CEnemyBulletクラス(直線弾クラス）
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

// 移動
bool CEnemyBullet::Move() {

	// 移動範囲、速度
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	// 移動
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

	// 移動範囲の制限
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

// 描画
void CEnemyBullet::Draw() 
{
	Game->poligon[3]->SetColor(0xffffffff,m_color,0xffffffff,m_color);
	Game->poligon[3]->SetRect(X,Y,Width,Height,0.5f,0.0f,0.75f,0.25f);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[3],2);
}

//----------------------------------------------------------------------
//CSmallEnemyBulletクラス(小さい直線弾クラス）
//----------------------------------------------------------------------

CSmallEnemyBullet::CSmallEnemyBullet(float x, float y, float angle, float speed, float axel, DWORD color)
:CEBullet(x, y, 8, 8, 1, angle, speed, color),m_roll(0)
{
	X_SPEED =m_speed*sin(m_angle);
	Y_SPEED =m_speed*cos(m_angle);
	X_AXEL =axel*sin(m_angle);
	Y_AXEL =axel*cos(m_angle);
}

// 移動
bool CSmallEnemyBullet::Move() {

	// 移動範囲、速度
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	// 移動
	X +=X_SPEED;
	X_SPEED +=X_AXEL;
	Y +=Y_SPEED;
	Y_SPEED +=Y_AXEL;

	// 移動範囲の制限
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

// 描画
void CSmallEnemyBullet::Draw() 
{
	Game->poligon[3]->SetColor(0xffffffff,m_color,0xffffffff,m_color);
	Game->poligon[3]->SetRect(X,Y,Width,Height,D3DXToRadian(m_roll),0.0f,0.0f,0.25f,0.25f);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[3],2);
}


//----------------------------------------------------------------------
//CAimBulletクラス(自機狙い弾クラス）
//----------------------------------------------------------------------

// コンストラクタ
CAimBullet::CAimBullet(float x, float y, float to_x, float to_y, float speed, float axel, DWORD color)
:CEBullet(x, y, 20, 20, 2, 0, speed, color)
{
	m_angle =atan2(x-to_x,y-to_y);
	X_SPEED =-m_speed*sin(m_angle);
	Y_SPEED =-m_speed*cos(m_angle);
	X_AXEL =-axel*sin(m_angle);
	Y_AXEL =-axel*cos(m_angle);
}

// 移動
bool CAimBullet::Move() {

	// 移動範囲、速度
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	// 移動
	X +=X_SPEED;
	X_SPEED +=X_AXEL;
	Y +=Y_SPEED;
	Y_SPEED +=Y_AXEL;

	// 移動範囲の制限
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

// 描画
void CAimBullet::Draw() 
{
	Game->poligon[3]->SetColor(0xffffffff,m_color,0xffffffff,m_color);
	Game->poligon[3]->SetRect(X,Y,Width,Height,-m_angle,0.75f,0.0f,1.0f,0.25f);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[3],2);
}

//----------------------------------------------------------------------
//CCircleBulletクラス(円状に広がる弾クラス）
//----------------------------------------------------------------------

bool CCircleBullet::Move()
{
	// 移動範囲
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	//時間制限
	++m_count;
	if(m_count>m_max_count)
	{
		new CDisappearBullet(X,Y);
		return false;
	}

	//初期位置まで移動
	if((X-m_px)*(X-m_px)+(Y-m_py)*(Y-m_py) <m_first_radius*m_first_radius)
	{
		// 移動
		X +=X_SPEED;
		Y +=Y_SPEED;

		return true;
	}

	//回転と半径増加
	m_rot_angle +=m_angle_spd;
	m_angle_spd +=m_angle_axel;
	if(m_rot_angle>360)
		m_rot_angle -=360.0f;
	float angle =D3DXToRadian(m_rot_angle);

	m_radius +=m_rad_spd;
	m_rad_spd +=m_rad_axel;
	
	//移動
	X =m_px+cos(angle)*m_radius;
	Y =m_py+sin(angle)*m_radius;

	// 移動範囲の制限
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
//CHomingBulletクラス(ホーミング弾クラス）
//----------------------------------------------------------------------
bool CHomingBullet::Move()
{
	// 移動範囲、速度
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;


	//西さんがいたら向きを修正
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

	//移動
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

	// 移動範囲の制限
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