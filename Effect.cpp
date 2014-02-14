#include "Main.h"
#include "Effect.h"
#include "Nishi.h"
#include "Enemy.h"
#include "Scene.h"
#include "Item.h"

//----------------------------------------------------------------------
//CEffectクラス(エフェクトの基底クラス）
//----------------------------------------------------------------------

CEffect::CEffect(float x, float y, float w, float h)
:CGameObj(Game->EffectList, x, y, w, h, 0, 0, 0)
{
}

//----------------------------------------------------------------------
//CMyCrashクラス(自機破壊時のエフェクト）
//----------------------------------------------------------------------

CMyCrash::CMyCrash(float x, float y, int BombNum, int LifeNum)
:CEffect(x, y, 5, 5),erase_count(0),alpha(255),m_BombNum(BombNum), m_LifeNum(LifeNum)
{
}

bool CMyCrash::Move()
{
	++erase_count;
	if(erase_count>35)
	{
		if(m_LifeNum<0)
		{
			Game->SetCreared(true);
			new CGameOver();
			return false;
		}
		new CInvisiNishi(320,360, m_BombNum, m_LifeNum);
		return false;
	}

	Width+=35;
	Height+=35;

	alpha-=15;
	if(alpha<=0)
		alpha=0;

	for (CTaskIter i(Game->EnemyBulletList); i.HasNext(); ) 
	{
		CGameObj* obj=(CGameObj*)i.Next();
		if ((obj->X-X)*(obj->X-X)+(obj->Y-Y)*(obj->Y-Y) < (Width)*(Width)/4)
		{
			Game->score->AddScore(10);
			new CDisappearBullet(obj->X,obj->Y);
			i.Remove();
		}
	}

	color =D3DCOLOR_ARGB(alpha,rand()%256,rand()%256,rand()%256);

	return true;
}
void CMyCrash::Draw()
{
	Game->poligon[4]->SetColor(color,color,color,color);
	Game->poligon[4]->SetRect(X,Y,Width,Height);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[4],3);
}

//----------------------------------------------------------------------
//CMyBombクラス(ボムのエフェクト）
//----------------------------------------------------------------------

CMyBomb::CMyBomb(float x, float y)
:CEffect(x, y, 15, 15),erase_count(0),alpha(255),attack(65),delta_y(0)
{
}

bool CMyBomb::Move()
{
	++erase_count;
	if(erase_count>100)
	{
		return false;
	}

	if(delta_y<40)
	{
		Y -=5.0f;
		delta_y++;
	}
	else
	{
		if(Width<400)
		{
			Width+=15;
			Height+=15;
		}

		alpha-=4;
		if(alpha<=0)
			alpha=0;

		//弾けし
		for (CTaskIter i(Game->EnemyBulletList); i.HasNext(); ) 
		{
			CGameObj* obj=(CGameObj*)i.Next();
			if ((obj->X-X)*(obj->X-X)+(obj->Y-Y)*(obj->Y-Y) < (Width)*(Width)/4)
			{
				Game->score->AddScore(10);
				new CDisappearBullet(obj->X,obj->Y);
				i.Remove();
			}
		}
		//ダメージ与える
		for (CTaskIter i(Game->EnemyList); i.HasNext(); ) 
		{
			CEnemy* obj=(CEnemy*)i.Next();
			if ((obj->X-X)*(obj->X-X)+(obj->Y-Y)*(obj->Y-Y) < (Width)*(Width)/4)
			{
				obj->SubtractVital(attack);
			}
		}
		//アイテム回収
		float to_X=0,to_Y=0;
		CTaskIter j(Game->MyShipList);
		if(j.HasNext())
		{
			CGameObj *temp_obj =(CGameObj*)j.Next();
			to_X =temp_obj->X;
			to_Y =temp_obj->Y;
		}
		for (CTaskIter i(Game->ItemList); i.HasNext(); ) 
		{
			CItem* obj=(CItem*)i.Next();
			obj->SetXYSpeed(to_X,to_Y,10.0f);
		}
	}

	color =D3DCOLOR_ARGB(alpha,rand()%256,rand()%256,rand()%256);

	return true;
}
void CMyBomb::Draw()
{
	Game->poligon[4]->SetColor(color,color,color,color);
	Game->poligon[4]->SetRect(X,Y,Width,Height);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[4],3);
}

//----------------------------------------------------------------------
//CEnemyCrashクラス(敵機破壊時のエフェクト）
//----------------------------------------------------------------------

CEnemyCrash::CEnemyCrash(float x, float y)
:CEffect(x, y, 5, 5),erase_count(0),alpha(255),
R(rand()%256),G(rand()%256),B(rand()%256)
{
	Game->sound[4]->Play();
}

bool CEnemyCrash::Move()
{
	/*++erase_count;
	if(erase_count>30)
	{
		return false;
	}*/

	/*if(Width<=60)
	{
		Width+=10;
		Height+=10;
	}else{
		alpha-=20;
		if(alpha<=0)
			return false;
	}*/

	if(Width<=150)
	{
		Width+=10;
		Height+=10;
	}
	alpha-=12;

	if(alpha<=0)
		return false;
	
	return true;
}
void CEnemyCrash::Draw()
{
	DWORD color =D3DCOLOR_ARGB(alpha,R,G,B);

	Game->poligon[7]->SetColor(color,color,color,color);
	Game->poligon[7]->SetRect(X,Y,Width,Height);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[7],3);
}

//----------------------------------------------------------------------
//CDisappearBulletクラス(敵弾消滅時のエフェクト）
//----------------------------------------------------------------------

CDisappearBullet::CDisappearBullet(float x, float y)
:CEffect(x, y, 15, 15),alpha(255)
{
}

bool CDisappearBullet::Move()
{
	alpha-=9;
	if(alpha<=0)
		return false;

	color =D3DCOLOR_ARGB(alpha,0xff,0xff,0xff);

	return true;
}

void CDisappearBullet::Draw()
{
	Game->poligon[8]->SetColor(color,color,color,color);
	Game->poligon[8]->SetRect(X,Y,Width,Height);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[8],5);
}

//----------------------------------------------------------------------
//CBOSSCrashクラス(BOSS破壊時のエフェクト）
//----------------------------------------------------------------------

CBOSSCrash::CBOSSCrash(float x, float y)
:CEffect(x, y, 5, 5),erase_count(0),alpha(255)
{
}

bool CBOSSCrash::Move()
{
	++erase_count;
	if(erase_count>35)
	{
		return false;
	}

	Width+=35;
	Height+=35;

	alpha-=15;
	if(alpha<=0)
		alpha=0;

	for (CTaskIter i(Game->EnemyBulletList); i.HasNext(); ) 
	{
		CGameObj* obj=(CGameObj*)i.Next();
		if ((obj->X-X)*(obj->X-X)+(obj->Y-Y)*(obj->Y-Y) < (Width)*(Width)/4)
		{
			Game->score->AddScore(10);
			new CDisappearBullet(obj->X,obj->Y);
			i.Remove();
		}
	}

	color =D3DCOLOR_ARGB(alpha,rand()%256,rand()%256,rand()%256);

	return true;
}
void CBOSSCrash::Draw()
{
	Game->poligon[4]->SetColor(color,color,color,color);
	Game->poligon[4]->SetRect(X,Y,Width,Height);
	Game->graphics->SetRenderState(ADDITION);
	Game->graphics->Draw(Game->poligon[4],3);
}
