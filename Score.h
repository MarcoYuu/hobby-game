#pragma once
#pragma warning(disable : 4995)

class CScore
{
	unsigned int m_score;
	unsigned int m_countingScore;
	unsigned int m_highScore;
	int m_cscore[10];
	int m_highscore[10];
	unsigned int temp;
public:
	CScore();
	virtual ~CScore();
	void ResetScore()
	{
		m_score =0;
		m_countingScore =0;
		temp =0;
	}
	void AddScore(unsigned int score)
	{
		m_score +=score;
	}
	unsigned int GetScore()
	{
		return m_score;
	}
	virtual void UpdateScore();
	virtual void DrawScore(float x, float y,
		DWORD color1=0xf0ffffff,DWORD color2=0xf0ffffff,DWORD color3=0xf0ffffff,DWORD color4=0xf0ffffff);
	virtual void DrawPresentScore(float x, float y,float w, float h,
		DWORD color1=0xf0ffffff,DWORD color2=0xf0ffffff,DWORD color3=0xf0ffffff,DWORD color4=0xf0ffffff);
	virtual void DrawHighScore(float x, float y,float w, float h,
		DWORD color1=0xf0ffffff,DWORD color2=0xf0ffffff,DWORD color3=0xf0ffffff,DWORD color4=0xf0ffffff);
};
