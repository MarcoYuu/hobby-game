#pragma once
#pragma warning(disable : 4995)


#include "CMyCommand.h"
#include <vector>
#include <string>

using namespace std;

//---------------------------------------------------------------------
//CScriptクラス（ゲームを制御するスクリプトクラス
//---------------------------------------------------------------------
class CScript
{
	vector<CMyCommand*> Command;
	int m_waitTime;
	int m_runIndex;
	bool is_ok;
public:
	CScript(string file_name);
	~CScript();
	void ResetScript();
	void RunScript();
	void PlusWait(int time)
	{
		m_waitTime +=time;
	}
	bool IsOK()
	{
		return is_ok;
	}
};
