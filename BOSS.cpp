#include "Main.h"
#include "EnemyBullet.h"
#include "BOSS.h"
#include "Nishi.h"


//----------------------------------------------------------------------
//CBOSSクラス(全てのBOSSの基底クラス）
//----------------------------------------------------------------------

void CBOSS::base_HitorNot()
{
	++m_frame_count_laser;

	//当たり判定処理
	//ショット
	for(CTaskIter i(Game->MyBulletList);i.HasNext();)
	{
		CMyBullet *bullet =(CMyBullet*)i.Next();

		if(HitCircle(bullet))
		{
			Game->score->AddScore(10);
			vitality -=bullet->GetPower();
			i.Remove();
		}
	}
	//レーザー
	for(CTaskIter i(Game->MyLaserList);i.HasNext();)
	{
		CMyLaser *laser =(CMyLaser*)i.Next();

		if(HitCircleToLine(laser))
		{
			if(m_frame_count_laser>8)
			{
				Game->score->AddScore(10);
				m_frame_count_laser =0;
			}
			vitality -=2;
		}
	}
}


//----------------------------------------------------------------------
//CBOSS_1クラス(BOSS1クラス）
//----------------------------------------------------------------------
bool CBOSS_1::Move()
{
	//フレーム更新
	++m_frame_count;

	switch(m_life)
	{
	case 3:
		if(!Move_1())
			return true;
		break;
	case 2:
		if(!Move_2())
			return true;
		break;
	case 1:
		if(!Move_3())
			return true;
		break;
	case 0:
		if(!Move_last())
			return true;
		break;
	}

	return HitorNot();
}
bool CBOSS_1::HitorNot()
{
	base_HitorNot();

	//体力測定
	if(vitality<=0)
	{
		new CBOSSCrash(X,Y);
		Game->score->AddScore(m_score);
		m_life -=1;
		if(m_life<0)
		{
			Game->SetCreared(true);
			new CEnemyCrash(X,Y);
			new CResult1(m_stage_num,Game->GetReplay());
			return false;
		}
		vitality =max_vitality;
	}
	Game->SetBOSSHUD(m_life,vitality);

	return true;
}
void CBOSS_1::Draw()
{
	Game->poligon[17]->SetColor(0xff66ff00,0xff66ff00,0xff66ff00,0xff66ff00);
	Game->poligon[17]->SetRect(X,Y,Width,Height);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[17],3);
}
bool CBOSS_1::Move_1()
{
	// 移動範囲
	static const float
		MaxLX=250, MaxRX=410,
		MaxTY=90, MaxBY=250;

	//無敵時間
	if(frame_count1<90)
	{
		vitality =max_vitality;
		if(!have_set1)
		{
			have_set1 =true;
			X_SPEED =(rand()%100-50)/100.0f;
			Y_SPEED =(rand()%100-50)/100.0f;
		}

		++frame_count1;

		return false;
	}

	//移動
	if(m_frame_count <30)
	{
		X +=X_SPEED;
		Y +=Y_SPEED;

		// 移動範囲の制限
		if (X<MaxLX) {
			X =MaxLX;
		}else if (MaxRX<X){
			X =MaxRX;
		}
		if (Y<MaxTY){
			Y =MaxTY;
		}else if (MaxBY<Y){
			Y =MaxBY;
		}
	}
	else if(m_frame_count <85)
	{
		//ショット
		Shot_1();
	}
	else
	{
		m_frame_count =0;
		X_SPEED =(rand()%100-50)/100.0f;
		Y_SPEED =(rand()%100-50)/100.0f;
		m_roll =(float)(rand()%360);
	}
	return true;
}

bool CBOSS_1::Move_2()
{
	//中心座標
	static const float
		PX =320, PY =150, RADIUS =50;

	//無敵時間
	if(frame_count2<90)
	{
		vitality =max_vitality;
		if(!have_set2)
		{
			have_set2 =true;
			X_SPEED =(PX+RADIUS-X)/90.0f;
			Y_SPEED =(PY-Y)/90.0f;
			m_rot_angle =0;
			m_angle_spd =3.0f;
		}
		X +=X_SPEED;
		Y +=Y_SPEED;

		++frame_count2;

		return false;
	}

	//回転
	m_rot_angle +=m_angle_spd;
	if(m_rot_angle>360)
		m_rot_angle -=360.0f;

	float angle =D3DXToRadian(m_rot_angle);

	//移動
	X =PX+cos(angle)*RADIUS;
	Y =PY+sin(angle)*RADIUS;

	//ショット
	Shot_2();

	return true;
}

bool CBOSS_1::Move_3()
{
	//無敵時間
	if(frame_count3<90)
	{
		vitality =max_vitality;
		if(!have_set3)
		{
			have_set3 =true;
			X_SPEED =(320-X)/90.0f;
			Y_SPEED =(150-Y)/90.0f;
			m_rot_angle =0;
			m_angle_spd =1.0f;
		}
		X +=X_SPEED;
		Y +=Y_SPEED;

		++frame_count3;

		return false;
	}

	//回転
	m_rot_angle +=m_angle_spd;
	if(m_rot_angle>360)
		m_rot_angle -=360.0f;

	//移動
	X =320+sin(D3DXToRadian(m_rot_angle))*100;

	//ショット
	Shot_3();

	return true;
}

bool CBOSS_1::Move_last()
{
	//無敵時間
	if(frame_count4<90)
	{
		vitality =max_vitality;
		if(!have_set4)
		{
			have_set4 =true;
			X_SPEED =(320-X)/90.0f;
			Y_SPEED =(220-Y)/90.0f;
			m_rot_angle =0;
			m_angle_spd =1.0f;
		}
		X +=X_SPEED;
		Y +=Y_SPEED;

		++frame_count4;

		return false;
	}
	//動かない
	Shot_last();

	return true;
}

void CBOSS_1::Shot_1()
{	
	if(shot_count>2)
	{
		Game->sound[0]->Play();
		shot_count =0;

		DWORD color =D3DCOLOR_ARGB(0xff,rand()%256,rand()%256,rand()%256);
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);

		for(int i=0;i<12;++i)
		{
			new CCircleBullet(X,Y,3.0f,(float)(360*i/12 +m_roll),-0.9f,-0.0001f,60,0.05f,0.04f,10000,0xffff9900);
			new CCircleBullet(X,Y,3.0f,(float)(360*i/12 +m_roll),0.9f,0.0001f,60,0.05f,0.04f,10000,0xffff9900);
		}
	}
	++shot_count;
}

void CBOSS_1::Shot_2()
{
	if(shot_count2>1)
	{
		shot_count2 =0;

		if(m_shot_num<3)
		{
			++m_shot_num;
			Game->sound[0]->Play();
			for(int i=0;i<m_shot_num;++i)
			{
				for(int j=0;j<12;++j)
				{
					new CEnemyBullet(X,Y,m_roll+j*360/12.0f +(i*1.0f)-((m_shot_num-1)*1.0f)/2,1.5f,30.0f,0.04f,0xff00ffff);	
				}
			}
		}
		else
		{
			m_shot_num =0;
			m_roll +=12.56f;
			if(m_roll>360)
				m_roll -=360;
		}
	}
	++shot_count2;
}

void CBOSS_1::Shot_3()
{
	static const DWORD color[7] ={
		0xff00cbff,
		0xff0800ff,
		0xffdc00ff,
		0xffff004c,
		0xffff8800,
		0xffa1ff00,
		0xff00ff33};

	if(shot_count3>10)
	{
		Game->sound[0]->Play();
		shot_count3 =0;

		for(int i=0;i<16;++i)
		{
			new CEnemyBullet(X,Y,(float)(360*i/16 +m_roll),1.0f,30.0f,0,color[color_num]);
			new CEnemyBullet(X,Y,(float)(360*i/16 -m_roll),1.0f,30.0f,0,color[color_num]);
		}

		m_roll +=3.0f;
		if(m_roll>360)
			m_roll -=360;

		if(add)
		{
			++color_num;
			if(color_num>=6)
				add =false;
		}
		else
		{
			--color_num;
			if(color_num<=0)
				add =true;
		}
	}

	++shot_count3;
}

void CBOSS_1::Shot_last()
{	
	if(shot_count4>3)
	{
		Game->sound[0]->Play();
		shot_count4 =0;
		DWORD color =D3DCOLOR_ARGB(0xff,rand()%256,rand()%256,rand()%256);

		//米粒
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);
		for(int i=0;i<5;++i)
		{
			//枠
			new CCircleBullet(X,Y,3.0f,(float)(360*i/5 -m_roll),1.5f,0,170,0.0001f,0,200,0xffff9900);
		}
		for(int i=0;i<12;++i)
		{
			//外部へいけないように
			new CCircleBullet(X,Y,1000.0f,(float)(360*i/12 +m_roll),1.0f,0,170,1.0f,0.001f,600,0xffff3300);
			new CCircleBullet(X,Y,1000.0f,(float)(360*i/12 -m_roll),-1.0f,0,170,1.0f,0.001f,600,0xffff3300);
		}
	}
	m_roll +=0.2f;
	if(m_roll>360)
		m_roll -=360;

	++shot_count4;
}

//----------------------------------------------------------------------
//CBOSS_2クラス(BOSS2クラス）
//----------------------------------------------------------------------
bool CBOSS_2::Move()
{
	//フレーム更新
	++m_frame_count;

	switch(m_life)
	{
	case 3:
		if(!Move_1())
			return true;
		break;
	case 2:
		if(!Move_2())
			return true;
		break;
	case 1:
		if(!Move_3())
			return true;
		break;
	case 0:
		if(!Move_last())
			return true;
		break;
	}

	return HitorNot();
}
bool CBOSS_2::HitorNot()
{
	base_HitorNot();

	//体力測定
	if(vitality<=0)
	{
		new CBOSSCrash(X,Y);
		Game->score->AddScore(m_score);
		m_life -=1;
		if(m_life<0)
		{
			Game->SetCreared(true);
			new CEnemyCrash(X,Y);
			new CResult2(m_stage_num,Game->GetReplay());
			return false;
		}
		vitality =max_vitality;
	}
	Game->SetBOSSHUD(m_life,vitality);

	return true;
}
void CBOSS_2::Draw()
{
	Game->poligon[17]->SetColor(0xff66ff66,0xff66ff66,0xff66ff66,0xff66ff66);
	Game->poligon[17]->SetRect(X,Y,Width,Height);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[17],3);
}
bool CBOSS_2::Move_1()
{
	// 移動範囲
	static const float
		MaxLX=250, MaxRX=410,
		MaxTY=90, MaxBY=250;

	//無敵時間
	if(frame_count1<90)
	{
		vitality =max_vitality;
		if(!have_set1)
		{
			have_set1 =true;
			X_SPEED =(rand()%100-50)/100.0f;
			Y_SPEED =(rand()%100-50)/100.0f;
		}

		++frame_count1;

		return false;
	}

	//移動
	if(m_frame_count <30)
	{
		X +=X_SPEED;
		Y +=Y_SPEED;

		// 移動範囲の制限
		if (X<MaxLX) {
			X =MaxLX;
		}else if (MaxRX<X){
			X =MaxRX;
		}
		if (Y<MaxTY){
			Y =MaxTY;
		}else if (MaxBY<Y){
			Y =MaxBY;
		}
	}
	else if(m_frame_count <85)
	{
		//ショット
		Shot_1();
	}
	else
	{
		m_frame_count =0;
		X_SPEED =(rand()%100-50)/100.0f;
		Y_SPEED =(rand()%100-50)/100.0f;
		m_roll =(float)(rand()%360);
	}
	return true;
}

bool CBOSS_2::Move_2()
{
	//中心座標
	static const float
		PX =320, PY =150, RADIUS =50;

	//無敵時間
	if(frame_count2<90)
	{
		vitality =max_vitality;
		if(!have_set2)
		{
			have_set2 =true;
			X_SPEED =(PX+RADIUS-X)/90.0f;
			Y_SPEED =(PY-Y)/90.0f;
			m_rot_angle =0;
			m_angle_spd =3.0f;
		}
		X +=X_SPEED;
		Y +=Y_SPEED;

		++frame_count2;

		return false;
	}

	//回転
	m_rot_angle +=m_angle_spd;
	if(m_rot_angle>360)
		m_rot_angle -=360.0f;

	float angle =D3DXToRadian(m_rot_angle);

	//移動
	X =PX+cos(angle)*RADIUS;
	Y =PY+sin(angle)*RADIUS;

	//ショット
	Shot_2();

	return true;
}

bool CBOSS_2::Move_3()
{
	//無敵時間
	if(frame_count3<90)
	{
		vitality =max_vitality;
		if(!have_set3)
		{
			have_set3 =true;
			X_SPEED =(320-X)/90.0f;
			Y_SPEED =(150-Y)/90.0f;
			m_rot_angle =0;
			m_angle_spd =1.0f;
		}
		X +=X_SPEED;
		Y +=Y_SPEED;

		++frame_count3;

		return false;
	}

	//回転
	m_rot_angle +=m_angle_spd;
	if(m_rot_angle>360)
		m_rot_angle -=360.0f;

	//移動
	X =320+sin(D3DXToRadian(m_rot_angle))*100;

	//ショット
	Shot_3();

	return true;
}

bool CBOSS_2::Move_last()
{
	//無敵時間
	if(frame_count4<90)
	{
		vitality =max_vitality;
		if(!have_set4)
		{
			have_set4 =true;
			X_SPEED =(320-X)/90.0f;
			Y_SPEED =(220-Y)/90.0f;
			m_rot_angle =0;
			m_angle_spd =1.0f;
		}
		X +=X_SPEED;
		Y +=Y_SPEED;

		++frame_count4;

		return false;
	}
	//動かない
	Shot_last();

	return true;
}

void CBOSS_2::Shot_1()
{	
	if(shot_count>2)
	{
		Game->sound[0]->Play();
		shot_count =0;

		DWORD color =D3DCOLOR_ARGB(0xff,rand()%256,rand()%256,rand()%256);
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);

		for(int i=0;i<12;++i)
		{
			new CCircleBullet(X,Y,3.0f,(float)(360*i/12 +m_roll),-0.9f,-0.0001f,60,0.05f,0.04f,10000,0xffff9900);
			new CCircleBullet(X,Y,3.0f,(float)(360*i/12 +m_roll),0.9f,0.0001f,60,0.05f,0.04f,10000,0xffff9900);
		}
	}
	++shot_count;
}

void CBOSS_2::Shot_2()
{
	if(shot_count2>1)
	{
		shot_count2 =0;

		if(m_shot_num<3)
		{
			++m_shot_num;
			Game->sound[0]->Play();
			for(int i=0;i<m_shot_num;++i)
			{
				for(int j=0;j<12;++j)
				{
					new CEnemyBullet(X,Y,m_roll+j*360/12.0f +(i*1.0f)-((m_shot_num-1)*1.0f)/2,1.5f,30.0f,0.04f,0xff00ffff);	
				}
			}
		}
		else
		{
			m_shot_num =0;
			m_roll +=12.56f;
			if(m_roll>360)
				m_roll -=360;
		}
	}
	++shot_count2;
}

void CBOSS_2::Shot_3()
{
	static const DWORD color[7] ={
		0xff00cbff,
		0xff0800ff,
		0xffdc00ff,
		0xffff004c,
		0xffff8800,
		0xffa1ff00,
		0xff00ff33};

	if(shot_count3>10)
	{
		Game->sound[0]->Play();
		shot_count3 =0;

		for(int i=0;i<16;++i)
		{
			new CEnemyBullet(X,Y,(float)(360*i/16 +m_roll),1.0f,30.0f,0,color[color_num]);
			new CEnemyBullet(X,Y,(float)(360*i/16 -m_roll),1.0f,30.0f,0,color[color_num]);
		}

		m_roll +=3.0f;
		if(m_roll>360)
			m_roll -=360;

		if(add)
		{
			++color_num;
			if(color_num>=6)
				add =false;
		}
		else
		{
			--color_num;
			if(color_num<=0)
				add =true;
		}
	}

	++shot_count3;
}

void CBOSS_2::Shot_last()
{	
	if(shot_count4>3)
	{
		Game->sound[0]->Play();
		shot_count4 =0;
		DWORD color =D3DCOLOR_ARGB(0xff,rand()%256,rand()%256,rand()%256);

		//米粒
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);
		for(int i=0;i<5;++i)
		{
			//枠
			new CCircleBullet(X,Y,3.0f,(float)(360*i/5 -m_roll),1.5f,0,170,0.0001f,0,200,0xffff9900);
		}
		for(int i=0;i<12;++i)
		{
			//外部へいけないように
			new CCircleBullet(X,Y,1000.0f,(float)(360*i/12 +m_roll),1.0f,0,170,1.0f,0.001f,600,0xffff3300);
			new CCircleBullet(X,Y,1000.0f,(float)(360*i/12 -m_roll),-1.0f,0,170,1.0f,0.001f,600,0xffff3300);
		}
	}
	m_roll +=0.2f;
	if(m_roll>360)
		m_roll -=360;

	++shot_count4;
}
//----------------------------------------------------------------------
//CBOSS_3クラス(BOSS3クラス）
//----------------------------------------------------------------------
bool CBOSS_3::Move()
{
	//フレーム更新
	++m_frame_count;

	switch(m_life)
	{
	case 3:
		if(!Move_1())
			return true;
		break;
	case 2:
		if(!Move_2())
			return true;
		break;
	case 1:
		if(!Move_3())
			return true;
		break;
	case 0:
		if(!Move_last())
			return true;
		break;
	}

	return HitorNot();
}
bool CBOSS_3::HitorNot()
{
	base_HitorNot();

	//体力測定
	if(vitality<=0)
	{
		new CBOSSCrash(X,Y);
		Game->score->AddScore(m_score);
		m_life -=1;
		if(m_life<0)
		{
			Game->SetCreared(true);
			new CEnemyCrash(X,Y);
			new CResult3(m_stage_num,Game->GetReplay());
			return false;
		}
		vitality =max_vitality;
	}
	Game->SetBOSSHUD(m_life,vitality);

	return true;
}
void CBOSS_3::Draw()
{
	Game->poligon[17]->SetColor(0xff66ff00,0xff66ff00,0xff66ff00,0xff66ff00);
	Game->poligon[17]->SetRect(X,Y,Width,Height);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[17],3);
}
bool CBOSS_3::Move_1()
{
	// 移動範囲
	static const float
		MaxLX=250, MaxRX=410,
		MaxTY=90, MaxBY=250;

	//無敵時間
	if(frame_count1<90)
	{
		vitality =max_vitality;
		if(!have_set1)
		{
			have_set1 =true;
			X_SPEED =(rand()%100-50)/100.0f;
			Y_SPEED =(rand()%100-50)/100.0f;
		}

		++frame_count1;

		return false;
	}

	//移動
	if(m_frame_count <30)
	{
		X +=X_SPEED;
		Y +=Y_SPEED;

		// 移動範囲の制限
		if (X<MaxLX) {
			X =MaxLX;
		}else if (MaxRX<X){
			X =MaxRX;
		}
		if (Y<MaxTY){
			Y =MaxTY;
		}else if (MaxBY<Y){
			Y =MaxBY;
		}
	}
	else if(m_frame_count <85)
	{
		//ショット
		Shot_1();
	}
	else
	{
		m_frame_count =0;
		X_SPEED =(rand()%100-50)/100.0f;
		Y_SPEED =(rand()%100-50)/100.0f;
		m_roll =(float)(rand()%360);
	}
	return true;
}

bool CBOSS_3::Move_2()
{
	//中心座標
	static const float
		PX =320, PY =150, RADIUS =50;

	//無敵時間
	if(frame_count2<90)
	{
		vitality =max_vitality;
		if(!have_set2)
		{
			have_set2 =true;
			X_SPEED =(PX+RADIUS-X)/90.0f;
			Y_SPEED =(PY-Y)/90.0f;
			m_rot_angle =0;
			m_angle_spd =3.0f;
		}
		X +=X_SPEED;
		Y +=Y_SPEED;

		++frame_count2;

		return false;
	}

	//回転
	m_rot_angle +=m_angle_spd;
	if(m_rot_angle>360)
		m_rot_angle -=360.0f;

	float angle =D3DXToRadian(m_rot_angle);

	//移動
	X =PX+cos(angle)*RADIUS;
	Y =PY+sin(angle)*RADIUS;

	//ショット
	Shot_2();

	return true;
}

bool CBOSS_3::Move_3()
{
	//無敵時間
	if(frame_count3<90)
	{
		vitality =max_vitality;
		if(!have_set3)
		{
			have_set3 =true;
			X_SPEED =(320-X)/90.0f;
			Y_SPEED =(150-Y)/90.0f;
			m_rot_angle =0;
			m_angle_spd =1.0f;
		}
		X +=X_SPEED;
		Y +=Y_SPEED;

		++frame_count3;

		return false;
	}

	//回転
	m_rot_angle +=m_angle_spd;
	if(m_rot_angle>360)
		m_rot_angle -=360.0f;

	//移動
	X =320+sin(D3DXToRadian(m_rot_angle))*100;

	//ショット
	Shot_3();

	return true;
}

bool CBOSS_3::Move_last()
{
	//無敵時間
	if(frame_count4<90)
	{
		vitality =max_vitality;
		if(!have_set4)
		{
			have_set4 =true;
			X_SPEED =(320-X)/90.0f;
			Y_SPEED =(220-Y)/90.0f;
			m_rot_angle =0;
			m_angle_spd =1.0f;
		}
		X +=X_SPEED;
		Y +=Y_SPEED;

		++frame_count4;

		return false;
	}
	//動かない
	Shot_last();

	return true;
}

void CBOSS_3::Shot_1()
{	
	if(shot_count>2)
	{
		Game->sound[0]->Play();
		shot_count =0;

		DWORD color =D3DCOLOR_ARGB(0xff,rand()%256,rand()%256,rand()%256);
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);

		for(int i=0;i<12;++i)
		{
			new CCircleBullet(X,Y,3.0f,(float)(360*i/12 +m_roll),-0.9f,-0.0001f,60,0.05f,0.04f,10000,0xffff9900);
			new CCircleBullet(X,Y,3.0f,(float)(360*i/12 +m_roll),0.9f,0.0001f,60,0.05f,0.04f,10000,0xffff9900);
		}
	}
	++shot_count;
}

void CBOSS_3::Shot_2()
{
	if(shot_count2>1)
	{
		shot_count2 =0;

		if(m_shot_num<3)
		{
			++m_shot_num;
			Game->sound[0]->Play();
			for(int i=0;i<m_shot_num;++i)
			{
				for(int j=0;j<12;++j)
				{
					new CEnemyBullet(X,Y,m_roll+j*360/12.0f +(i*1.0f)-((m_shot_num-1)*1.0f)/2,1.5f,30.0f,0.04f,0xff00ffff);	
				}
			}
		}
		else
		{
			m_shot_num =0;
			m_roll +=12.56f;
			if(m_roll>360)
				m_roll -=360;
		}
	}
	++shot_count2;
}

void CBOSS_3::Shot_3()
{
	static const DWORD color[7] ={
		0xff00cbff,
		0xff0800ff,
		0xffdc00ff,
		0xffff004c,
		0xffff8800,
		0xffa1ff00,
		0xff00ff33};

	if(shot_count3>10)
	{
		Game->sound[0]->Play();
		shot_count3 =0;

		for(int i=0;i<16;++i)
		{
			new CEnemyBullet(X,Y,(float)(360*i/16 +m_roll),1.0f,30.0f,0,color[color_num]);
			new CEnemyBullet(X,Y,(float)(360*i/16 -m_roll),1.0f,30.0f,0,color[color_num]);
		}

		m_roll +=3.0f;
		if(m_roll>360)
			m_roll -=360;

		if(add)
		{
			++color_num;
			if(color_num>=6)
				add =false;
		}
		else
		{
			--color_num;
			if(color_num<=0)
				add =true;
		}
	}

	++shot_count3;
}

void CBOSS_3::Shot_last()
{	
	if(shot_count4>3)
	{
		Game->sound[0]->Play();
		shot_count4 =0;
		DWORD color =D3DCOLOR_ARGB(0xff,rand()%256,rand()%256,rand()%256);

		//米粒
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);
		new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,1.0f,0,color);
		for(int i=0;i<5;++i)
		{
			//枠
			new CCircleBullet(X,Y,3.0f,(float)(360*i/5 -m_roll),1.5f,0,170,0.0001f,0,200,0xffff9900);
		}
		for(int i=0;i<12;++i)
		{
			//外部へいけないように
			new CCircleBullet(X,Y,1000.0f,(float)(360*i/12 +m_roll),1.0f,0,170,1.0f,0.001f,600,0xffff3300);
			new CCircleBullet(X,Y,1000.0f,(float)(360*i/12 -m_roll),-1.0f,0,170,1.0f,0.001f,600,0xffff3300);
		}
	}
	m_roll +=0.2f;
	if(m_roll>360)
		m_roll -=360;

	++shot_count4;
}