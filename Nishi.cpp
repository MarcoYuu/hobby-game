#include "Main.h"
#include "Nishi.h"
#include "EnemyBullet.h"
#include "Enemy.h"
#include "Effect.h"
#include "Item.h"

//----------------------------------------------------------------------
//Nishiクラス(自機のクラス）
//----------------------------------------------------------------------

//----------------------------通常状態--------------------------------//

// コンストラクタ
CNishi::CNishi(float x, float y, int BombNum, int LifeNum)
:CGameObj(Game->MyShipList, x, y, 16.0f, 32.0f, 2.5f, 6.0f, 6.0f),
anime_count(0),anime(0),
shot_count(20),laser_count(20),laser_num(0), live_count(30),bomb_count(0),
m_BombNum(2),m_LifeNum(LifeNum)
{
	Game->input->GetAllState(&key);
	Game->SetHUD(m_LifeNum,m_BombNum);
}

// 移動
bool CNishi::Move() {

	// 移動範囲、速度
	static const float
		MaxLX=150+Width/2, MaxRX=490-Width/2,
		MaxTY=20+Height/2, MaxBY=460-Height/2,
		SPEED =6,LOW_SPEED =2;
	
	// キーボードの入力
	prevbomb_input =key.X;
	Game->input->GetAllState(&key);

	// 移動
	if(!key.SHIFT)
	{
		if (key.RIGHT){
			X+=SPEED;
		}else if (key.LEFT) {
			X-=SPEED;
		}
		if (key.UP){
			Y-=SPEED;
		}else if (key.DOWN){
			Y+=SPEED;
		}
	}else{
		if (key.RIGHT){
			X+=LOW_SPEED;
		}else if (key.LEFT) {
			X-=LOW_SPEED;
		}
		if (key.UP){
			Y-=LOW_SPEED;
		}else if (key.DOWN){
			Y+=LOW_SPEED;
		}
	}

	//ボムの発射
	if(!prevbomb_input && bomb_count<=0 && m_BombNum>0 && key.X)
	{
		bomb_count =100;
		--m_BombNum;
		Game->SetHUD(m_LifeNum,m_BombNum);
		new CMyBomb(X,Y);
	}
	else if(bomb_count>0)
	{
		--bomb_count;
	}

	//弾の発射
	if(!key.Z){
		shot_count =20;
		laser_count =20;
		laser_num =0;
	}
	else
	{
		if(!key.SHIFT)
		{
			laser_num =0;
			NormalShot(2);
		}else{
			NormalShot(0);
			NormalLaser(8);
		}
	}

	//当たり判定処理
	if(bomb_count<=0)
	{
		if(live_count<=0)
		{
			for(CTaskIter i(Game->EnemyBulletList);i.HasNext();)
			{
				CEBullet *bullet =(CEBullet*)i.Next();

				if(HitCircle(bullet))
				{
					Game->sound[1]->Play();
					Game->MyLaserList->DeleteTask();

					if(m_LifeNum>=0) 
					{
						--m_LifeNum;
					}
					Game->SetHUD(m_LifeNum,m_BombNum);

					new CMyCrash(X,Y, m_BombNum, m_LifeNum);
					return false;
				}
			}
			for(CTaskIter i(Game->EnemyList);i.HasNext();)
			{
				CEnemy *enemy =(CEnemy*)i.Next();

				if(HitCircle(enemy))
				{
					Game->sound[1]->Play();
					Game->MyLaserList->DeleteTask();

					if(m_LifeNum>=0) 
					{
						--m_LifeNum;
					}
					Game->SetHUD(m_LifeNum,m_BombNum);

					new CMyCrash(X,Y, m_BombNum, m_LifeNum);
					return false;
				}
			}
		}else{
			--live_count;
		}
	}

	//アイテムの取得判定
	for(CTaskIter i(Game->ItemList);i.HasNext();)
	{
		CItem *item =(CItem*)i.Next();

		if(HitCircle(item,X,Y,18))
		{
			item->SetXYSpeed(X,Y,5.0f);
		}
		if(HitCircle(item))
		{
			Game->sound[7]->Play();
			Game->score->AddScore((unsigned)item->GetScore());
			i.Remove();
		}
	}


	// 移動範囲の制限
	if (X<MaxLX) {
		X=MaxLX; 
	}else if (MaxRX<X){
		X=MaxRX;
	}
	if (Y<MaxTY){
		Y=MaxTY; 
	}else if (MaxBY<Y){
		Y=MaxBY;
	}

	++anime_count;
	if(anime_count>=10)
	{
		++anime;
		anime_count =0;
		if(anime>4)
			anime =1;
	}

	return true;
}

//ショット
bool CNishi::NormalShot(int power)
{
	++shot_count;
	if(shot_count>=6)
	{
		shot_count =0;
		Game->sound[2]->Play();
		new CMyBullet(X-10,Y,0,10,15);
		new CMyBullet(X+10,Y,0,10,15);
		new CMyBullet(X-10,Y,160,10,15);
		new CMyBullet(X+10,Y,-160,10,15);
		SubShot(power);
	}
	return true;
}
bool CNishi::SubShot(int power)
{
	switch(power)
	{
	case 1:
		new CMyBullet(X,Y,10,10,15);
		new CMyBullet(X,Y,-10,10,15);
		break;
	case 2:
		new CMyBullet(X,Y,5,10,15);
		new CMyBullet(X,Y,-5,10,15);
		new CMyBullet(X,Y,10,10,15);
		new CMyBullet(X,Y,-10,10,15);
		break;
	case 3:
		new CMyBullet(X,Y,5,10,15);
		new CMyBullet(X,Y,-5,10,15);
		new CMyBullet(X,Y,10,10,15);
		new CMyBullet(X,Y,-10,10,15);
		new CMyBullet(X,Y,15,10,15);
		new CMyBullet(X,Y,-15,10,15);
		break;
	case 4:
		new CMyBullet(X,Y,5,10,15);
		new CMyBullet(X,Y,-5,10,15);
		new CMyBullet(X,Y,10,10,15);
		new CMyBullet(X,Y,-10,10,15);
		new CMyBullet(X,Y,15,10,15);
		new CMyBullet(X,Y,-15,10,15);
		new CMyBullet(X,Y,20,10,15);
		new CMyBullet(X,Y,-20,10,15);
		break;
	default:
		break;
	}
	return true;
}
bool CNishi::NormalLaser(int limit)
{
	++laser_count;
	if(laser_count>=6)
	{
		laser_count =0;
		Game->sound[3]->Play();

		CEnemy *enemy[7];
		int num =0;
		for(CTaskIter i(Game->EnemyList);i.HasNext();)
		{
			enemy[num] =(CEnemy*)i.Next();
			++num;
			if(num>=7)
				break;
		}
		/*for(int i=0;i<num;++i)
		{
			new CMyHomingLaser(enemy[i],1,X,Y,9.0f,0.01f,180.0f*i/num,10.0f,100,0xffffffff);
		}*/

		if(laser_num<1)
		{
			++laser_num;
			new CMyLaser(this,X-30,Y+30,0,1);
			new CMyLaser(this,X-10,Y,0,1);
			new CMyLaser(this,X+10,Y,0,1);
			new CMyLaser(this,X+30,Y+30,0,1);
		}
	}
	return true;
}

// 描画
void CNishi::Draw() 
{
	Game->poligon[1]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	Game->poligon[1]->SetRect(X,Y,Width,Height,
		1.0f*(anime-1)/4.0f,0.0f,1.0f*anime/4.0f,1.0f);
	Game->graphics->SetRenderState(NORMAL);
	Game->graphics->Draw(Game->poligon[1],1);
}

//----------------------------------------------------------------------
//CInvisiNishiクラス(自機のクラス）
//----------------------------------------------------------------------

//----------------------------復活状態--------------------------------//

//コンストラクタ
CInvisiNishi::CInvisiNishi(float x, float y, int BombNum, int LifeNum)
:CNishi(x, y, BombNum, LifeNum)
{
	live_count =90;
}

// 移動
bool CInvisiNishi::Move() {

	// 移動範囲、速度
	static const float
		MaxLX=150+Width/2, MaxRX=490-Width/2,
		MaxTY=20+Height/2, MaxBY=460-Height/2,
		SPEED =6,LOW_SPEED =2;

	//消滅判定処理
	if(live_count<=0)
	{
		new CNishi(X,Y, m_BombNum, m_LifeNum);
		Game->MyLaserList->DeleteTask();
		return false;
	}else{
		--live_count;
	}
	
	// キーボードの入力
	KEYSTATE key;
	Game->input->GetAllState(&key);

	// 移動
	if(!key.SHIFT)
	{
		if (key.RIGHT){
			X+=SPEED;
		}else if (key.LEFT) {
			X-=SPEED;
		}
		if (key.UP){
			Y-=SPEED;
		}else if (key.DOWN){
			Y+=SPEED;
		}
	}else{
		if (key.RIGHT){
			X+=LOW_SPEED;
		}else if (key.LEFT) {
			X-=LOW_SPEED;
		}
		if (key.UP){
			Y-=LOW_SPEED;
		}else if (key.DOWN){
			Y+=LOW_SPEED;
		}
	}

	//弾の発射
	if(!key.Z){
		shot_count =20;
		laser_count =20;
		laser_num =0;
	}
	else
	{
		NormalShot(1);
	}

	//アイテムの取得判定
	for(CTaskIter i(Game->ItemList);i.HasNext();)
	{
		CItem *item =(CItem*)i.Next();

		if(HitCircle(item,X,Y,18))
		{
			item->SetXYSpeed(X,Y,5.0f);
		}
		if(HitCircle(item))
		{
			Game->sound[7]->Play();
			Game->score->AddScore((unsigned)item->GetScore());
			i.Remove();
		}
	}

	// 移動範囲の制限
	if (X<MaxLX) {
		X=MaxLX; 
	}else if (MaxRX<X){
		X=MaxRX;
	}
	if (Y<MaxTY){
		Y=MaxTY; 
	}else if (MaxBY<Y){
		Y=MaxBY;
	}
	
	color =D3DCOLOR_ARGB(0xf0,rand()%256,rand()%256,rand()%256);
	
	++anime_count;
	if(anime_count>=10)
	{
		++anime;
		anime_count =0;
		if(anime>4)
			anime =1;
	}

	return true;
}
//ショット
bool CInvisiNishi::NormalShot(int power)
{
	++shot_count;
	if(shot_count>=6)
	{
		shot_count =0;
		Game->sound[2]->Play();
		new CMyBullet(X-10,Y,0,40,15);
		new CMyBullet(X+10,Y,0,40,15);
		SubShot(power);
	}
	return true;
}
bool CInvisiNishi::SubShot(int power)
{
	switch(power)
	{
	case 1:
		new CMyBullet(X,Y,5,35,15);
		new CMyBullet(X,Y,-5,35,15);
		new CMyBullet(X,Y,10,35,15);
		new CMyBullet(X,Y,-10,35,15);
		new CMyBullet(X,Y,15,35,15);
		new CMyBullet(X,Y,-15,35,15);
		new CMyBullet(X,Y,20,35,15);
		new CMyBullet(X,Y,-20,35,15);
		break;
	default:
		break;
	}
	return true;
}
// 描画
void CInvisiNishi::Draw() 
{
	Game->poligon[1]->SetColor(color,color,color,color);
	Game->poligon[1]->SetRect(X,Y,Width,Height,
		1.0f*(anime-1)/4.0f,0.0f,1.0f*anime/4.0f,1.0f);

	Game->graphics->SetRenderState(NORMAL);
	Game->graphics->Draw(Game->poligon[1],3);
}
//----------------------------------------------------------------------
//CPrepareNishiクラス(自機のクラス）
//----------------------------------------------------------------------

//----------------------------登場状態--------------------------------//

//コンストラクタ
CPrepareNishi::CPrepareNishi(float x, float y, int BombNum, int LifeNum)
:CNishi(x, y, BombNum, LifeNum)
{
	live_count =90;
}

// 移動
bool CPrepareNishi::Move() {

	// 移動範囲、速度
	static const float
		MaxLX=150+Width/2, MaxRX=490-Width/2,
		MaxTY=20+Height/2, MaxBY=460-Height/2,
		SPEED =6,LOW_SPEED =2;

	//消滅判定処理
	if(live_count<=0)
	{
		new CNishi(X,Y, m_BombNum, m_LifeNum);
		return false;
	}else{
		--live_count;
	}
	
	// キーボードの入力
	KEYSTATE key;
	Game->input->GetAllState(&key);

	// 移動
	if(!key.SHIFT)
	{
		if (key.RIGHT){
			X+=SPEED;
		}else if (key.LEFT) {
			X-=SPEED;
		}
		if (key.UP){
			Y-=SPEED;
		}else if (key.DOWN){
			Y+=SPEED;
		}
	}else{
		if (key.RIGHT){
			X+=LOW_SPEED;
		}else if (key.LEFT) {
			X-=LOW_SPEED;
		}
		if (key.UP){
			Y-=LOW_SPEED;
		}else if (key.DOWN){
			Y+=LOW_SPEED;
		}
	}

	//アイテムの取得判定
	for(CTaskIter i(Game->ItemList);i.HasNext();)
	{
		CItem *item =(CItem*)i.Next();

		if(HitCircle(item,X,Y,23))
		{
			item->SetXYSpeed(X,Y,5.0f);
		}
		if(HitCircle(item))
		{
			Game->sound[7]->Play();
			Game->score->AddScore((unsigned)item->GetScore());
			i.Remove();
		}
	}

	// 移動範囲の制限
	if (X<MaxLX) {
		X=MaxLX; 
	}else if (MaxRX<X){
		X=MaxRX;
	}
	if (Y<MaxTY){
		Y=MaxTY; 
	}else if (MaxBY<Y){
		Y=MaxBY;
	}
	
	color =D3DCOLOR_ARGB(0xf0,rand()%256,rand()%256,rand()%256);
	
	++anime_count;
	if(anime_count>=10)
	{
		++anime;
		anime_count =0;
		if(anime>4)
			anime =1;
	}

	return true;
}
// 描画
void CPrepareNishi::Draw()
{
	Game->poligon[1]->SetColor(color,color,color,color);
	Game->poligon[1]->SetRect(X,Y,Width,Height,
		1.0f*(anime-1)/4.0f,0.0f,1.0f*anime/4.0f,1.0f);

	Game->graphics->SetRenderState(NORMAL);
	Game->graphics->Draw(Game->poligon[1],1);
}

//----------------------------------------------------------------------
//MyBulletクラス(自機の弾クラス）
//----------------------------------------------------------------------

// コンストラクタ
CMyBullet::CMyBullet(float x, float y, float angle, int power,float speed)
:CGameObj(Game->MyBulletList, x, y, 16, 32, 6, 12, 24),
m_angle(D3DXToRadian(angle)),m_power(power)
{
	X_SPEED =speed*sin(m_angle);
	Y_SPEED =speed*cos(m_angle);
}
CMyBullet::CMyBullet(float x, float y, float w, float h,float r,int power)
:CGameObj(Game->MyBulletList, x, y, w, h, r, 0, 0),m_power(power)
{
}

// 移動
bool CMyBullet::Move() {

	// 移動範囲、速度
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	// 移動
	X +=X_SPEED; 
	Y -=Y_SPEED; 

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
void CMyBullet::Draw() 
{
	Game->poligon[18]->SetColor(0x80ffffff,0x80ffffff,0x80ffffff,0x80ffffff);
	Game->poligon[18]->SetRect(X,Y,Width,Height);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[18],1);
}

//----------------------------------------------------------------------
//MyLaserクラス(自機のレーザークラス）
//----------------------------------------------------------------------

// コンストラクタ
CMyLaser::CMyLaser(CNishi *nishi, float x, float y, float angle, int power)
:CGameObj(Game->MyLaserList, x, y-32, 8, 640, 0, 6, 640), 
m_nishi(nishi),laser_count(0),laser_num(1),m_power(power)
{
	line.length =640;
	line.argument =D3DXToRadian(angle);
	m_delta_x =x -m_nishi->X;
	m_delta_y =y -m_nishi->Y;
}

// 移動
bool CMyLaser::Move() 
{
	if(!Game->input->GetKeyState(MY_Z) || !Game->input->GetKeyState(MY_SHIFT))
		return false;

	// 移動
	if(m_nishi)
	{
		X =m_nishi->X+m_delta_x;
		Y =m_nishi->Y+m_delta_y -300; 
	}else{
		return false;
	}
	//当たり判定の移動
	//line.argument +=D3DXToRadian(1);
	float temp_x =line.length*sin(line.argument)/2.0f;
	float temp_y =line.length*cos(line.argument)/2.0f;
	line.x1 =X-temp_x;
	line.y1 =Y-temp_y;
	line.x2 =X+temp_x;
	line.y2 =Y+temp_y;
	
	return true;
}

// 描画
void CMyLaser::Draw() 
{
	Game->poligon[2]->SetColor(0xffff0000,0xffffffff,0xffffffff,0xff0000ff);
	Game->poligon[2]->SetRect(X,Y,Width,Height,-line.argument);
	Game->graphics->SetRenderState(ADDITION);

	if(laser_count<6)
	{
		++laser_count;
	}
	else if(laser_num<10)
	{
		++laser_num;
		laser_count =0;
	}
	Game->graphics->Draw(Game->poligon[2],laser_num);
}



//----------------------------------------------------------------------
//MyHomingLaserクラス(自機の弾クラス）
//----------------------------------------------------------------------

//コンストラクタ
CMyHomingLaser::CMyHomingLaser(CEnemy *enemy,int ID,float x, float y, float speed, float axel, float angle,float max_angle, int power,DWORD color)
:CMyBullet(x, y, 16, 16, 6,power),m_power(power),m_ID(ID),
MAX_ANGLE(D3DXToRadian(max_angle)),m_speed(speed),m_axel(axel),m_enemy(enemy),
m_angle(D3DXToRadian(angle)),m_roll(0),m_color(color),m_homing(true)
{
	for(int i=0;i<20;++i)
	{
		prev_X[i] =X;
		prev_Y[i] =Y;
	}
}

// 移動
bool CMyHomingLaser::Move() 
{
	// 移動範囲、速度
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	if(m_enemy->GetVitality()>0)
	{
		float temp_angle =atan2(m_enemy->Y-Y,m_enemy->X-X);
		if(abs(temp_angle-m_angle)<MAX_ANGLE)
		{
			m_angle =temp_angle;
		}
		else
		{
			if(temp_angle<m_angle-D3DX_PI)
				m_angle -=D3DX_PI*2;
			else if(temp_angle>m_angle+D3DX_PI)
				m_angle -=D3DX_PI*2;

			if(temp_angle<m_angle)
				m_angle -=MAX_ANGLE;
			else
				m_angle +=MAX_ANGLE;
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

// 描画
void CMyHomingLaser::Draw() 
{
	Game->poligon[3]->SetColor(0xffffffff,m_color,0xffffffff,m_color);
	Game->poligon[3]->SetRect(X,Y,Width,Height,D3DXToRadian(m_roll),0.5f,0.0f,0.75f,0.25f);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[3],2);
	DWORD temp_color1,temp_color2;
	for(int i=0;i<20;++i)
	{
		temp_color1 =(0xff000000|m_color)&(D3DCOLOR_ARGB(255*(20-i)/20,255,255,255));
		temp_color2 =D3DCOLOR_ARGB(10*(20-i)/20,255,255,255);
		Game->poligon[3]->SetColor(temp_color2,temp_color1,temp_color2,temp_color1);
		Game->poligon[3]->SetRect(prev_X[i],prev_Y[i],Width,Height,D3DXToRadian(m_roll),0.5f,0.0f,0.75f,0.25f);
		Game->graphics->Draw(Game->poligon[3],2);
	}
}
