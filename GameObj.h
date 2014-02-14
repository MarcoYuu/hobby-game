#pragma once
#include "Task.h"

//----------------------------------------------------------------------
//とりあえずいろんな構造体
//----------------------------------------------------------------------
struct HITCIRCLE
{
	float x,y;
	float radius;
};
struct HITLINE
{
	float x1,y1;
	float x2,y2;
	float length;
	float argument;
};
struct HITRECT
{
	float rect_width, rect_height;
};
struct HITSLOPERECT
{
	float x1,y1;
	float x2,y2;
	float x3,y3;
	float x4,y4;
	float argument;
};

//----------------------------------------------------------------------
//ゲームオブジェクトクラス(あらゆるオブジェクトの基底クラス）
//----------------------------------------------------------------------
class CGameObj : public CTask 
{
public:
	float X, Y;
	float Width, Height;
	HITRECT m_hit;
	HITLINE line;
	float hit_radius;

	CGameObj(CTaskList* task_list, float x, float y, float w, float h, float r, float hit_w, float hit_h)
	:CTask(task_list), X(x), Y(y), Width(w), Height(h), hit_radius(r)
	{
		m_hit.rect_width =hit_w;
		m_hit.rect_height =hit_h;
	}

	//当たり判定処理用関数(trueで当たってる
	bool HitRect(CGameObj *obj)
	{
		return 
			X -m_hit.rect_width/2 < obj->X +obj->m_hit.rect_width/2 &&
			X +m_hit.rect_width/2 > obj->X -obj->m_hit.rect_width/2 &&
			Y -m_hit.rect_height/2 < obj->Y +obj->m_hit.rect_height/2 &&
			Y +m_hit.rect_height/2 > obj->Y -obj->m_hit.rect_height/2;
	}
	bool HitRect(CGameObj *obj, HITRECT *hit)
	{
		return 
			X -hit->rect_width/2 < obj->X +obj->m_hit.rect_width/2 &&
			X +hit->rect_width/2 > obj->X -obj->m_hit.rect_width/2 &&
			Y -hit->rect_height/2 < obj->Y +obj->m_hit.rect_height/2 &&
			Y +hit->rect_height/2 > obj->Y -obj->m_hit.rect_height/2;
	}

	bool HitCircle(CGameObj *obj)
	{
		return 
			pow(obj->X-X,2)+pow(obj->Y-Y,2) < pow(obj->hit_radius+hit_radius,2);
	}
	bool HitCircle(CGameObj *obj, float x, float y, float radius)
	{
		return 
			pow(obj->X-x,2)+pow(obj->Y-y,2) < pow(obj->hit_radius+radius,2);
	}

	bool HitCircleToLine(CGameObj *obj)
	{
		//P =(X,Y)
		//A =(obj->line.x1,obj->line.y1) 
		//B =(obj->line.x2,obj->line.y2)
		//vectorA =(X-obj->line.x1,Y-obj->line.y1) |A|=√((X-obj->line.x1)*(X-obj->line.x1)+(Y-obj->line.y1)*(Y-obj->line.y1))
		//vectorB =(X-obj->line.x2,Y-obj->line.y2) |B|=√((X-obj->line.x2)*(X-obj->line.x2)+(Y-obj->line.y2)*(Y-obj->line.y2))
		//vectorS =(obj->line.x2-obj->line.x1,obj->line.y2-obj->line.y1)
		//|S| =obj->line.length
		//|A×S| =|(X-obj->line.x1)*(obj->line.y2-obj->line.y1)-(Y-obj->line.y1)*(obj->line.x2-obj->line.x1)|
		//d =|A×S|/|S| =((X-obj->line.x1)*(obj->line.y2-obj->line.y1)-(Y-obj->line.y1)*(obj->line.x2-obj->line.x1))/obj->line.length
		//A･S =(X-obj->line.x1)*(obj->line.x2-obj->line.x1)+(Y-obj->line.y1)*(obj->line.y2-obj->line.y1)
		//B･S =(X-obj->line.x2)*(obj->line.x2-obj->line.x1)+(Y-obj->line.y2)*(obj->line.y2-obj->line.y1)
		if((hit_radius+2.0f) < abs(((X-obj->line.x1)*(obj->line.y2-obj->line.y1)-(Y-obj->line.y1)*(obj->line.x2-obj->line.x1))/obj->line.length))
		{
			return false;
		}
		else if(((X-obj->line.x1)*(obj->line.x2-obj->line.x1)+(Y-obj->line.y1)*(obj->line.y2-obj->line.y1))
				*((X-obj->line.x2)*(obj->line.x2-obj->line.x1)+(Y-obj->line.y2)*(obj->line.y2-obj->line.y1))<=0)
		{
			return true;
		}
		else if((hit_radius+2.0f)*(hit_radius+2.0f) > ((X-obj->line.x1)*(X-obj->line.x1)+(Y-obj->line.y1)*(Y-obj->line.y1)) || 
				(hit_radius+2.0f)*(hit_radius+2.0f) > ((X-obj->line.x2)*(X-obj->line.x2)+(Y-obj->line.y2)*(Y-obj->line.y2)))
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}
	/*bool HitCircleToLine(CGameObj *obj, float x, float y, float radius)
	{
	}*/
	

	//継承先でオーバーライドすること
	virtual bool Move() { return true; }
	virtual void Draw() {}
};
