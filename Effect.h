#pragma once
#include "GameObj.h"

//----------------------------------------------------------------------
//CEffect�N���X(�G�t�F�N�g�̊��N���X�j
//----------------------------------------------------------------------
class CEffect :public CGameObj
{
public:
	void* operator new(size_t t) { return operator_new(t, Game->EffectList); }
	void operator delete(void* p) { operator_delete(p, Game->EffectList); }
	CEffect(float x, float y, float w, float h);
};

//----------------------------------------------------------------------
//CMyCrash�N���X(���@�j�󎞂̃G�t�F�N�g�j
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
//CMyBomb�N���X(�{���̃G�t�F�N�g�j
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
//CEnemyCrash�N���X(�G�@�j�󎞂̃G�t�F�N�g�j
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
//CDisappearBullet�N���X(�G�e���Ŏ��̃G�t�F�N�g�j
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
//CBOSSCrash�N���X(�{�X�j�󎞂̃G�t�F�N�g�j
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
