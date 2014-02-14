#pragma once
#include "GameObj.h"

//----------------------------------------------------------------------
//CItemクラス(全てのアイテムの基底クラス）
//----------------------------------------------------------------------
class CItem :public CGameObj
{
protected:
	float X_SPEED,Y_SPEED;
	float m_angle;
	int m_score;
	int m_count;
	bool m_bsetXY;
public:
	void* operator new(size_t t) { return operator_new(t, Game->ItemList); }
	void operator delete(void* p) { operator_delete(p, Game->ItemList); }

	CItem(float x, float y, float w, float h, float r, int score)
	:CGameObj(Game->ItemList, x, y, w, h, r, 4.0f, 4.0f),m_bsetXY(false),
	m_score(score),X_SPEED(0),Y_SPEED(0),m_angle(D3DXToRadian(rand()%3600/10.0f)),m_count(0)
	{
	}
	int GetScore()
	{
		return m_score;
	}
	void SetXYSpeed(float to_x,float to_y,float speed)
	{
		m_bsetXY =true;
		m_angle =atan2(to_y-Y,to_x-X);
		X_SPEED =speed*cos(m_angle);
		Y_SPEED =speed*sin(m_angle);
	}
};

//----------------------------------------------------------------------
//CScoreItemクラス(得点アイテムのクラス）
//----------------------------------------------------------------------
class CScoreItem :public CItem
{
	float roll;
public:
	CScoreItem(float x, float y, int score)
	:CItem(x, y, 16, 16, 10, score),roll(0)
	{
		X_SPEED =2.0f*cos(m_angle);
		Y_SPEED =2.0f*sin(m_angle);
	}

	bool Move();
	void Draw();
};
