#pragma once
#include "GameObj.h"

//----------------------------------------------------------------------
//CEffectクラス(エフェクトの基底クラス）
//----------------------------------------------------------------------
class CEffect :public CGameObj
{
public:
	void* operator new(size_t t) { return operator_new(t, Game->EffectList); }
	void operator delete(void* p) { operator_delete(p, Game->EffectList); }
	CEffect(float x, float y, float w, float h);
};

//----------------------------------------------------------------------
//CMyCrashクラス(自機破壊時のエフェクト）
//----------------------------------------------------------------------
class CMyCrash :public CEffect
{
private:
	int m_BombNum, m_LifeNum;
	int erase_count;
	int alpha;
	DWORD color;
public:
	CMyCrash(float x, float y, int BombNum, int LifeNum);
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CMyBombクラス(ボムのエフェクト）
//----------------------------------------------------------------------
class CMyBomb :public CEffect
{
private:
	int erase_count;
	int alpha;
	int attack;
	float delta_y;
	DWORD color;
public:
	CMyBomb(float x, float y);
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CEnemyCrashクラス(敵機破壊時のエフェクト）
//----------------------------------------------------------------------
class CEnemyCrash :public CEffect
{
private:
	int erase_count;
	int alpha;
	int R,G,B;
public:
	CEnemyCrash(float x, float y);
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CDisappearBulletクラス(敵弾消滅時のエフェクト）
//----------------------------------------------------------------------
class CDisappearBullet :public CEffect
{
private:
	DWORD color;
	int alpha;
public:
	CDisappearBullet(float x, float y);
	virtual bool Move();
	virtual void Draw();
};

//----------------------------------------------------------------------
//CBOSSCrashクラス(ボス破壊時のエフェクト）
//----------------------------------------------------------------------
class CBOSSCrash :public CEffect
{
private:
	int erase_count;
	int alpha;
	DWORD color;
public:
	CBOSSCrash(float x, float y);
	virtual bool Move();
	virtual void Draw();
};
