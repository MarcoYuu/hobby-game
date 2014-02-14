#include "Main.h"
#include "Item.h"
#include "Nishi.h"
#include "Effect.h"

//----------------------------------------------------------------------
//CScoreItem�N���X(���_�A�C�e���̃N���X�j
//----------------------------------------------------------------------

bool CScoreItem::Move()
{
	// �ړ��͈́A���x
	static const float
		MaxLX=120, MaxRX=520,
		MaxTY=0, MaxBY=480;

	static const float Y_FALL =0.02f;
	++m_count;
	if(m_count<20)
	{
		X +=X_SPEED;
		Y +=Y_SPEED;
	}
	else if(!m_bsetXY)
	{
		Y +=Y_SPEED;
		Y_SPEED +=Y_FALL;
	}
	else
	{
		X +=X_SPEED;
		Y +=Y_SPEED;
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
	//�摜�̉�]�p
	roll+=6.3f;
	if(roll>360.0f)
	{
		roll-=360.0f;
	}

	return true;
}

void CScoreItem::Draw()
{
	Game->graphics->SetRenderState(ADDITION);
	Game->poligon[15]->SetColor(0x609999ff,0x609999ff,0x609999ff,0x609999ff);
	Game->poligon[15]->SetRect(X,Y,Width,Height,D3DXToRadian(roll),0.0f,0.0f,0.25f,0.25f);
	Game->graphics->Draw(Game->poligon[15],4);
}
