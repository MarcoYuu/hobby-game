#include "Main.h"
#include "EnemyBullet.h"
#include "Enemy.h"
#include "Nishi.h"
#include "Effect.h"
#include "Item.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------
//CEnemy�N���X(�S�Ă̓G�̊��N���X�j
//----------------------------------------------------------------------
CEnemy::CEnemy(float x, float y, float w, float h, float r, int vitality, int score)
:CGameObj(Game->EnemyList, x, y, w, h, r, 4.0f, 4.0f),
m_anime(0), m_anime_count(0), m_frame_count(0), m_frame_count_laser(0),vitality(vitality), m_score(score),
m_LockedID(0)
{
}

bool CEnemy::HitorNot()
{
	bool hit =true;
	++m_frame_count_laser;

	//�����蔻�菈��
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
			vitality -=laser->GetPower();
		}
	}
	//�̗͑���
	if(vitality<=0)
	{
		Game->score->AddScore(m_score);
		new CEnemyCrash(X,Y);
		for(int j=0;j<2;++j)
		{
			new CScoreItem(X,Y,10000);
		}

		m_LockedID =0;

		return false;
	}
	return hit;
}

//----------------------------------------------------------------------
//CCurveMove�N���X(�Ȑ��ړ���������N���X�j
//----------------------------------------------------------------------
bool CCurveMove::Move()
{
	// �ړ��͈́A���x
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	//�̗͑���
	if(vitality<=0)
	{
		Game->score->AddScore(m_score);
		new CEnemyCrash(X,Y);
		return false;
	}

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

	Shot();

	return HitorNot();
}
void CCurveMove::Draw()
{
	Game->poligon[0]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	Game->poligon[0]->SetRect(X,Y,Width,Height);
	Game->graphics->SetRenderState(NORMAL);
	Game->graphics->Draw(Game->poligon[0],1);
}
//----------------------------------------------------------------------
//C2PointCurveMove�N���X(2�_�ԋȐ��ړ���������N���X�j
//----------------------------------------------------------------------
bool C2PointCurveMove::Move()
{
	// �ړ��͈́A���x
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	//�̗͑���
	if(vitality<=0)
	{
		Game->score->AddScore(m_score);
		new CEnemyCrash(X,Y);
		return false;
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

	// �ړ�
	//float x=0,y=0;
	if(m_frame_count<=m_time1)
	{
		BezCurve(0.5f*m_frame_count/m_time1,&X,&Y);
		//Y =m_y1+Y_AXEL*(X-m_x1)*(X-m_x1);
		//X +=X_SPEED;
	}
	else if(m_frame_count<=m_time1+m_shot_time)
	{
		Shot();
	}
	else if(m_frame_count<=m_time1+m_shot_time+m_time2)
	{
		BezCurve(0.5f+0.5f*(m_frame_count-m_time1-m_shot_time)/m_time1,&X,&Y);
		//Y =m_y2+Y_AXEL2*(X-m_x2)*(X-m_x2);
		//X +=X_SPEED2;
	}
	else
	{
		new CEnemyCrash(X,Y);
		return false;
	}
	++m_frame_count;
	
	return HitorNot();
}

void C2PointCurveMove::BezCurve(float requere_distance,float *x,float *y)
{
	//�Ԃ��ϐ��̏�����
	*x=0;
	*y=0;

	//�W���i�[�p�̕ϐ�
	float temp_val =(1.0f-requere_distance)*(1.0f-requere_distance);
	*x +=temp_val*m_x1;
	*y +=temp_val*m_y1;

	temp_val =2*requere_distance*(1.0f-requere_distance);
	*x +=temp_val*m_x2;
	*y +=temp_val*m_y2;

	temp_val =requere_distance*requere_distance;
	*x +=temp_val*m_x3;
	*y +=temp_val*m_y3;
}

void C2PointCurveMove::Draw()
{
	Game->poligon[0]->SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
	Game->poligon[0]->SetRect(X,Y,Width,Height);
	Game->graphics->SetRenderState(NORMAL);
	Game->graphics->Draw(Game->poligon[0],1);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------
//CNormalEnemy_1�N���X(���ˏ�ɋʂ��o���G�N���X�j
//----------------------------------------------------------------------

void CNormalEnemy_1::Shot()
{
	//�V���b�g����
	if(shot_count<=0)
	{
		shot_count =shot_count2;
		Game->sound[0]->Play();
		
		for(int i=0;i<shotnum;++i)
		{
			new CEnemyBullet(X,Y,(float)(360*i/shotnum +m_roll2),m_shot_speed,30.0f,0,0xffff000f);	
		}

		m_roll2 +=m_roll;
		if(m_roll2>360)
			m_roll2 -=360;
	}
	--shot_count;
}
void CNormalEnemy_1_2Point::Shot()
{
	//�V���b�g����
	if(shot_count<=0)
	{
		shot_count =shot_count2;
		Game->sound[0]->Play();
		
		for(int i=0;i<shotnum;++i)
		{
			new CEnemyBullet(X,Y,(float)(360*i/shotnum +m_roll2),m_shot_speed,30.0f,0,0xffff000f);	
		}

		m_roll2 +=m_roll;
		if(m_roll2>360)
			m_roll2 -=360;
	}
	--shot_count;
}


//----------------------------------------------------------------------
//CNormalEnemy_2�N���X(���@�_�����o���G�N���X�j
//----------------------------------------------------------------------

void CNormalEnemy_2::Shot()
{
	CTaskIter i(Game->MyShipList);
	if(i.HasNext())
	{
		CGameObj *obj =(CGameObj*)i.Next();
		to_X =obj->X;
		to_Y =obj->Y;
	}
	if(shot_count<=0)
	{
		shot_count =shot_count2;
		Game->sound[0]->Play();
		
		new CAimBullet(X,Y,to_X,to_Y,m_shot_speed,0,0xfff000ff);	
	}
	--shot_count;
}
void CNormalEnemy_2_2Point::Shot()
{
	CTaskIter i(Game->MyShipList);
	if(i.HasNext())
	{
		CGameObj *obj =(CGameObj*)i.Next();
		to_X =obj->X;
		to_Y =obj->Y;
	}
	if(shot_count<=0)
	{
		shot_count =shot_count2;
		Game->sound[0]->Play();
		
		new CAimBullet(X,Y,to_X,to_Y,m_shot_speed,0,0xfff000ff);	
	}
	--shot_count;
}

//----------------------------------------------------------------------
//CNormalEnemy_3�N���X(��`��ɋʂ��o���G�N���X�j
//----------------------------------------------------------------------

void CNormalEnemy_3::Shot()
{
	if(!m_bShot)
	{
		m_bShot =true;
		CTaskIter i(Game->MyShipList);
		if(i.HasNext())
		{
			CGameObj *obj =(CGameObj*)i.Next();
			to_X =obj->X;
			to_Y =obj->Y;
		}
	}
	if(!m_angle)
		m_angle =D3DXToDegree(atan2(to_X-X,to_Y-Y));

	if(m_shot_count<=0)
	{
		m_shot_count =m_shot_count2;
		
		if(m_shot_num<m_max_shot_num)
		{
			++m_shot_num;
			Game->sound[0]->Play();
			for(int i=0;i<m_shot_num;++i)
			{
				new CEnemyBullet(X,Y,m_angle+(i*5.0f)-((m_shot_num-1)*5.0f)/2,m_shot_speed,30.0f,0.05f,0xff33ff00);	
				new CEnemyBullet(X,Y,m_angle+180+(i*5.0f)-((m_shot_num-1)*5.0f)/2,m_shot_speed,30.0f,0.05f,0xff33ff00);	
			}
		}
		
	}
	--m_shot_count;
}
void CNormalEnemy_3_2Point::Shot()
{
	if(!m_bShot)
	{
		m_bShot =true;
		CTaskIter i(Game->MyShipList);
		if(i.HasNext())
		{
			CGameObj *obj =(CGameObj*)i.Next();
			to_X =obj->X;
			to_Y =obj->Y;
		}
	}
	if(!m_angle)
		m_angle =D3DXToDegree(atan2(to_X-X,to_Y-Y));

	if(m_shot_count<=0)
	{
		m_shot_count =m_shot_count2;
		
		if(m_shot_num<m_max_shot_num)
		{
			++m_shot_num;
			Game->sound[0]->Play();
			for(int i=0;i<m_shot_num;++i)
			{
				new CEnemyBullet(X,Y,m_angle+(i*5.0f)-((m_shot_num-1)*5.0f)/2,m_shot_speed,30.0f,0.05f,0xff33ff00);	
				new CEnemyBullet(X,Y,m_angle+180+(i*5.0f)-((m_shot_num-1)*5.0f)/2,m_shot_speed,30.0f,0.05f,0xff33ff00);	
			}
		}
		
	}
	--m_shot_count;
}

//----------------------------------------------------------------------
//CNormalEnemy_4�N���X(���@�_���𕡐��o���G�N���X(��e/�����e�j)
//----------------------------------------------------------------------

void CNormalEnemy_4::Shot()
{
	CTaskIter i(Game->MyShipList);
	if(i.HasNext())
	{
		CGameObj *obj =(CGameObj*)i.Next();
		to_X =obj->X;
		to_Y =obj->Y;
	}
	if(shot_count<=0)
	{
		shot_count =shot_count2;
		Game->sound[0]->Play();
		
		for(int i=0;i<m_max_shot_num;++i)
		{
			new CAimBullet(X,Y,to_X +m_delta_x*((float)(i-(m_max_shot_num-1)/2.0f)),to_Y,m_shot_speed,m_shot_axel,0xfff000ff);	
		}
	}
	--shot_count;
}
void CNormalEnemy_4_2Point::Shot()
{
	CTaskIter i(Game->MyShipList);
	if(i.HasNext())
	{
		CGameObj *obj =(CGameObj*)i.Next();
		to_X =obj->X;
		to_Y =obj->Y;
	}
	if(shot_count<=0)
	{
		shot_count =shot_count2;
		Game->sound[0]->Play();
		
		for(int i=0;i<m_max_shot_num;++i)
		{
			new CAimBullet(X,Y,to_X +m_delta_x*((float)(i-(m_max_shot_num-1)/2.0f)),to_Y,m_shot_speed,m_shot_axel,0xfff000ff);	
		}
	}
	--shot_count;
}

//----------------------------------------------------------------------
//CNormalEnemy_5�N���X(�~�`�ɐi�ޒe���o���G�N���X)
//----------------------------------------------------------------------

void CNormalEnemy_5::Shot()
{
	if(m_shot_count>m_max_shot_count)
	{
		Game->sound[0]->Play();
		m_shot_count =0;

		for(int i=0;i<m_shot_num;++i)
		{
			new CCircleBullet(X,Y,m_line_speed,(float)(360*i/m_shot_num +m_roll),
				m_angle_spd,m_angle_axel,m_radius,m_rad_spd,m_rad_axel,m_erase_count,0xffff6600);
		}
		m_roll +=m_delta_roll;
		if(m_roll>360)
			m_roll -=360;
	}
	++m_shot_count;
}
void CNormalEnemy_5_2Point::Shot()
{
	if(m_shot_count>m_max_shot_count)
	{
		Game->sound[0]->Play();
		m_shot_count =0;

		for(int i=0;i<m_shot_num;++i)
		{
			new CCircleBullet(X,Y,m_line_speed,(float)(360*i/m_shot_num +m_roll),
				m_angle_spd,m_angle_axel,m_radius,m_rad_spd,m_rad_axel,m_erase_count,0xffff6600);
		}
		m_roll +=m_delta_roll;
		if(m_roll>360)
			m_roll -=360;
	}
	++m_shot_count;
}

//----------------------------------------------------------------------
//CNormalEnemy_6�N���X(�����̒e�𖳑���ɂ΂�T���G�N���X)
//----------------------------------------------------------------------

void CNormalEnemy_6::Shot()
{
	DWORD color=0;

	if(m_shot_count>m_max_shot_count)
	{
		Game->sound[0]->Play();
		m_shot_count =0;

		for(int i=0;i<m_shot_num;++i)
		{
			color =D3DCOLOR_ARGB(0xff,rand()%256,rand()%256,rand()%256);
			new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,m_speed*(rand()%6+5)/10.0f,m_axel*(rand()%6+5)/10.0f,color);
		}
	}
	++m_shot_count;
}
void CNormalEnemy_6_2Point::Shot()
{
	DWORD color=0;

	if(m_shot_count>m_max_shot_count)
	{
		Game->sound[0]->Play();
		m_shot_count =0;

		for(int i=0;i<m_shot_num;++i)
		{
			color =D3DCOLOR_ARGB(0xff,rand()%256,rand()%256,rand()%256);
			new CSmallEnemyBullet(X,Y,(rand()%3600)/10.0f,m_speed*(rand()%6+5)/10.0f,m_axel*(rand()%6+5)/10.0f,color);
		}
	}
	++m_shot_count;
}


//----------------------------------------------------------------------
//CNormalEnemy_7�N���X(����̕����ɒe�����G�N���X)
//----------------------------------------------------------------------

void CNormalEnemy_7::Shot()
{
	if(m_shot_count>m_max_shot_count && m_shot_num<m_max_shot_num)
	{
		Game->sound[0]->Play();
		++m_shot_num;
		m_shot_count =0;

		new CEnemyBullet(X,Y,m_angle,m_speed,m_max_speed,m_axel,0xff6699cc);
	}
	++m_shot_count;
}
void CNormalEnemy_7_2Point::Shot()
{
	if(m_shot_count>m_max_shot_count && m_shot_num<m_max_shot_num)
	{
		Game->sound[0]->Play();
		++m_shot_num;
		m_shot_count =0;

		new CEnemyBullet(X,Y,m_angle,m_speed,m_max_speed,m_axel,0xff6699cc);
	}
	++m_shot_count;
}

//----------------------------------------------------------------------
//CNormalEnemy_8�N���X(�ǔ��e�G�N���X)
//----------------------------------------------------------------------

void CNormalEnemy_8::Shot()
{
	if(m_shot_count>m_max_shot_count)
	{
		m_shot_count =0;
		Game->sound[0]->Play();
		
		new CHomingBullet(X, Y, m_speed, m_axel, m_angle, m_max_angle, 0xff330033);
	}
	++m_shot_count;
}
void CNormalEnemy_8_2Point::Shot()
{
	if(m_shot_count>m_max_shot_count)
	{
		m_shot_count =0;
		Game->sound[0]->Play();
		
		new CHomingBullet(X, Y, m_speed, m_axel, m_angle, m_max_angle, 0xff330033);
	}
	++m_shot_count;
}