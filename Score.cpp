#include "Main.h"
#include "Score.h"
#include "CToken.h"
#include <fstream>
#include <string>
#include <sstream>   
#include <stdlib.h>

CScore::CScore()
:m_score(0),m_countingScore(0),m_highScore(30000)
{
	memset(m_cscore,0,sizeof(int)*10);
	using namespace std;
	
	//適当な文字列
	string str ="high_score=0";

	//汎用数値変数
	int inum[20];
	float fnum[20];
	memset(fnum,0,sizeof(fnum));
	memset(inum,0,sizeof(inum));

	//ファイルを開く
	ifstream file_in("./scoredata.dat",ios::in);

	//開けなかったら新しくセーブデータを作る
	if(!file_in.is_open())
	{
		file_in.close();

		ofstream file_out("./scoredata.dat",ios::out | ios::trunc);
		//超簡易暗号化
		for(int i=0;i<(int)str.length();++i)
		{
			str[i] +=100;
		}
		file_out << str << endl;
	}
	file_in.close();

	//開けたら複号化
	file_in.open("./scoredata.dat",ios::in);

	//一行取得
	getline(file_in,str);
	//複号
	for(int i=0;i<(int)str.length();++i)
	{
		str[i] -=100;
	}

	//ファイルの内容確認
	CToken token(str, "=",false);
	if(token.next() =="high_score")
	{
		m_highScore =atoi(token.next().c_str());
	}else{
		m_highScore =0;
	}
}

CScore::~CScore()
{
	//文字列ストリームでintをstringに
	stringstream s_str;
	s_str << "high_score=" <<m_highScore;
	string score = s_str.str();

	//超簡易暗号化
	for(int i=0;i<(int)score.length();++i)
	{
		score[i] +=100;
	}

	//ファイルを開く
	ofstream file_out("./scoredata.dat",ios::in);
	file_out <<score << endl;
}

void CScore::UpdateScore()
{
	unsigned int delta_score =m_score-m_countingScore;
	
	if(delta_score<=0)
	{
	}
	else if(delta_score>=1000000000)
	{
		m_countingScore +=1000000000;
	}
	else if(delta_score>=100000000)
	{
		m_countingScore +=100000000;
	}
	else if(delta_score>=10000000)
	{
		m_countingScore +=10000000;
	}
	else if(delta_score>=1000000)
	{
		m_countingScore +=1000000;
	}
	else if(delta_score>=100000)
	{
		m_countingScore +=100000;
	}
	else if(delta_score>=10000)
	{
		m_countingScore +=10000;
	}
	else if(delta_score>=1000)
	{
		m_countingScore +=1000;
	}
	else if(delta_score>=100)
	{
		m_countingScore +=100;
	}
	else if(delta_score>=10)
	{
		m_countingScore +=10;
	}
	else
	{
		m_countingScore +=1;
	}

	if(m_countingScore>m_score)
		m_countingScore =m_score;
	if(m_countingScore>m_highScore)
		m_highScore =m_countingScore;

	temp =m_countingScore;
	for(int i=9;i>=0;--i)
	{
		m_cscore[i] =(temp % 10);
		temp /=10;
	}
	temp =m_highScore;
	for(int i=9;i>=0;--i)
	{
		m_highscore[i] =(temp % 10);
		temp /=10;
	}
	/*
	int a;
	int value = 4287;

	a = (value % 10);
	value -= a;

	value → 4280
	a → 7*/
}

void CScore::DrawScore(float x, float y,
		DWORD color1,DWORD color2,DWORD color3,DWORD color4)
{
	Game->graphics->SetRenderState(NORMAL);
	Game->poligon[12]->SetColor(color1,color2,color3,color4);
	float u1(0.0f),v1(0.0f),u2(1.0f),v2(1.0f);

	//現在のスコア
	for(int i=0;i<10;++i)
	{
		switch(m_cscore[i])
		{
		case 0:
			u1 =0.0f;	v1 =0.0f;
			u2 =0.25f;	v2 =0.25f;
			break;
		case 1:
			u1 =0.25f;	v1 =0.0f;
			u2 =0.5f;	v2 =0.25f;
			break;
		case 2:
			u1 =0.5f;	v1 =0.0f;
			u2 =0.75f;	v2 =0.25f;
			break;
		case 3:
			u1 =0.75f;	v1 =0.0f;
			u2 =1.0f;	v2 =0.25f;
			break;
		case 4:
			u1 =0.0f;	v1 =0.25f;
			u2 =0.25f;	v2 =0.5f;
			break;
		case 5:
			u1 =0.25f;	v1 =0.25f;
			u2 =0.5f;	v2 =0.5f;
			break;
		case 6:
			u1 =0.5f;	v1 =0.25f;
			u2 =0.75f;	v2 =0.5f;
			break;
		case 7:
			u1 =0.75f;	v1 =0.25f;
			u2 =1.0f;	v2 =0.5f;
			break;
		case 8:
			u1 =0.0f;	v1 =0.5f;
			u2 =0.25f;	v2 =0.75f;
			break;
		case 9:
			u1 =0.25f;	v1 =0.5f;
			u2 =0.5f;	v2 =0.75f;
			break;
		default:
			break;
		}
	
		Game->poligon[12]->SetRect(x +12*(i-5)+6,y,32,32,u1,v1,u2,v2);
		Game->graphics->Draw(Game->poligon[12],1);
	}

	//ハイスコア
	for(int i=0;i<10;++i)
	{
		switch(m_highscore[i])
		{
		case 0:
			u1 =0.0f;	v1 =0.0f;
			u2 =0.25f;	v2 =0.25f;
			break;
		case 1:
			u1 =0.25f;	v1 =0.0f;
			u2 =0.5f;	v2 =0.25f;
			break;
		case 2:
			u1 =0.5f;	v1 =0.0f;
			u2 =0.75f;	v2 =0.25f;
			break;
		case 3:
			u1 =0.75f;	v1 =0.0f;
			u2 =1.0f;	v2 =0.25f;
			break;
		case 4:
			u1 =0.0f;	v1 =0.25f;
			u2 =0.25f;	v2 =0.5f;
			break;
		case 5:
			u1 =0.25f;	v1 =0.25f;
			u2 =0.5f;	v2 =0.5f;
			break;
		case 6:
			u1 =0.5f;	v1 =0.25f;
			u2 =0.75f;	v2 =0.5f;
			break;
		case 7:
			u1 =0.75f;	v1 =0.25f;
			u2 =1.0f;	v2 =0.5f;
			break;
		case 8:
			u1 =0.0f;	v1 =0.5f;
			u2 =0.25f;	v2 =0.75f;
			break;
		case 9:
			u1 =0.25f;	v1 =0.5f;
			u2 =0.5f;	v2 =0.75f;
			break;
		default:
			break;
		}
	
		Game->poligon[12]->SetRect(x +12*(i-5)+6,y+15,32,32,u1,v1,u2,v2);
		Game->graphics->Draw(Game->poligon[12],1);
	}
}

void CScore::DrawPresentScore(float x, float y,float w, float h,
		DWORD color1,DWORD color2,DWORD color3,DWORD color4)
{
	Game->graphics->SetRenderState(NORMAL);
	Game->poligon[12]->SetColor(color1,color2,color3,color4);
	float u1(0.0f),v1(0.0f),u2(1.0f),v2(1.0f);

	//現在のスコア
	for(int i=0;i<10;++i)
	{
		switch(m_cscore[i])
		{
		case 0:
			u1 =0.0f;	v1 =0.0f;
			u2 =0.25f;	v2 =0.25f;
			break;
		case 1:
			u1 =0.25f;	v1 =0.0f;
			u2 =0.5f;	v2 =0.25f;
			break;
		case 2:
			u1 =0.5f;	v1 =0.0f;
			u2 =0.75f;	v2 =0.25f;
			break;
		case 3:
			u1 =0.75f;	v1 =0.0f;
			u2 =1.0f;	v2 =0.25f;
			break;
		case 4:
			u1 =0.0f;	v1 =0.25f;
			u2 =0.25f;	v2 =0.5f;
			break;
		case 5:
			u1 =0.25f;	v1 =0.25f;
			u2 =0.5f;	v2 =0.5f;
			break;
		case 6:
			u1 =0.5f;	v1 =0.25f;
			u2 =0.75f;	v2 =0.5f;
			break;
		case 7:
			u1 =0.75f;	v1 =0.25f;
			u2 =1.0f;	v2 =0.5f;
			break;
		case 8:
			u1 =0.0f;	v1 =0.5f;
			u2 =0.25f;	v2 =0.75f;
			break;
		case 9:
			u1 =0.25f;	v1 =0.5f;
			u2 =0.5f;	v2 =0.75f;
			break;
		default:
			break;
		}
	
		Game->poligon[12]->SetRect(x +(w*10/32)*(i-5)+6,y,w,h,u1,v1,u2,v2);
		Game->graphics->Draw(Game->poligon[12],1);
	}
}

void CScore::DrawHighScore(float x, float y,float w, float h,
		DWORD color1,DWORD color2,DWORD color3,DWORD color4)
{
	Game->graphics->SetRenderState(NORMAL);
	Game->poligon[12]->SetColor(color1,color2,color3,color4);
	float u1(0.0f),v1(0.0f),u2(1.0f),v2(1.0f);

	//ハイスコア
	for(int i=0;i<10;++i)
	{
		switch(m_highscore[i])
		{
		case 0:
			u1 =0.0f;	v1 =0.0f;
			u2 =0.25f;	v2 =0.25f;
			break;
		case 1:
			u1 =0.25f;	v1 =0.0f;
			u2 =0.5f;	v2 =0.25f;
			break;
		case 2:
			u1 =0.5f;	v1 =0.0f;
			u2 =0.75f;	v2 =0.25f;
			break;
		case 3:
			u1 =0.75f;	v1 =0.0f;
			u2 =1.0f;	v2 =0.25f;
			break;
		case 4:
			u1 =0.0f;	v1 =0.25f;
			u2 =0.25f;	v2 =0.5f;
			break;
		case 5:
			u1 =0.25f;	v1 =0.25f;
			u2 =0.5f;	v2 =0.5f;
			break;
		case 6:
			u1 =0.5f;	v1 =0.25f;
			u2 =0.75f;	v2 =0.5f;
			break;
		case 7:
			u1 =0.75f;	v1 =0.25f;
			u2 =1.0f;	v2 =0.5f;
			break;
		case 8:
			u1 =0.0f;	v1 =0.5f;
			u2 =0.25f;	v2 =0.75f;
			break;
		case 9:
			u1 =0.25f;	v1 =0.5f;
			u2 =0.5f;	v2 =0.75f;
			break;
		default:
			break;
		}
	
		Game->poligon[12]->SetRect(x +(w*10/32)*(i-5)+6,y,w,h,u1,v1,u2,v2);
		Game->graphics->Draw(Game->poligon[12],1);
	}
}
