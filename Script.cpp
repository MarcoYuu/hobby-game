#include "Script.h"
#include "CToken.h"
#include <fstream>
#include <stdlib.h>

CScript::CScript(string file_name)
:m_waitTime(0),m_runIndex(0),is_ok(true)
{
	using namespace std;

	//読み込むスクリプト行と識別子の格納変数
	string str,ID_name;
	bool skip_comment =false;

	//汎用数値変数
	int inum[20];
	float fnum[20];
	memset(fnum,0,sizeof(fnum));
	memset(inum,0,sizeof(inum));
	

	//ファイルを開く
	ifstream file_in(file_name.c_str());
	//開けなかったら終了
	if(!file_in.is_open())
	{
		is_ok =false;
		return;
	}

	//一行読み込む,ファイルの最後ならやめる
	while(getline(file_in,str))
	{
		if(str == "")
			continue;

		if(str == "*/")
			skip_comment =false;
		else if(str == "/*")
			skip_comment =true;

		if(skip_comment ==true)
			continue;

		//トークンに分ける準備
		CToken token(str, " ",false);

		//行の初めの単語によって場合分け
		//スクリプトを拡張するときはこことコマンドクラスを拡張すること
		ID_name =token.next();
		token.set_delimiter(",",false);

		if(ID_name == "enemy1")
		{
			if((int)token.count() <11)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy1(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],inum[0],
				fnum[6],fnum[7],inum[1],inum[2]));
		}
		else if(ID_name == "enemy1_2Point")
		{
			if((int)token.count() <14)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());
			inum[3] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			inum[4] =atoi(token.next().c_str());
			inum[5] =atoi(token.next().c_str());
			

			Command.push_back(
				new CCommandNormalEnemy1_2Point(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],
				inum[0],inum[1],inum[2],inum[3],
				fnum[6],fnum[7],inum[4],inum[5]));
		}
		else if(ID_name == "enemy2")
		{
			if((int)token.count() <9)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			inum[1] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy2(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],inum[0],
				fnum[6],inum[1]));
		}
		else if(ID_name == "enemy2_2Point")
		{
			if((int)token.count() <12)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());
			inum[3] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			inum[4] =atoi(token.next().c_str());
			
			Command.push_back(
				new CCommandNormalEnemy2_2Point(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],
				inum[0],inum[1],inum[2],inum[3],
				fnum[6],inum[4]));
		}
		else if(ID_name == "enemy3")
		{
			if((int)token.count() <10)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy3(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],inum[0],
				fnum[6],inum[1],inum[2]));
		}
		else if(ID_name == "enemy3_2Point")
		{
			if((int)token.count() <13)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());
			inum[3] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			inum[4] =atoi(token.next().c_str());
			inum[5] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy3_2Point(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],
				inum[0],inum[1],inum[2],inum[3],
				fnum[6],inum[4],inum[5]));
		}
		else if(ID_name == "enemy4")
		{
			if((int)token.count() <12)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());
			fnum[8] =(float)atof(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy4(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],inum[0],
				fnum[6],fnum[7],inum[1],inum[2],fnum[8]));
		}
		else if(ID_name == "enemy4_2Point")
		{
			if((int)token.count() <15)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());
			inum[3] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			inum[4] =atoi(token.next().c_str());
			inum[5] =atoi(token.next().c_str());
			fnum[8] =(float)atof(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy4_2Point(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],
				inum[0],inum[1],inum[2],inum[3],
				fnum[6],fnum[7],inum[4],inum[5],fnum[8]));
		}
		else if(ID_name == "enemy5")
		{
			if((int)token.count() <18)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			fnum[8] =(float)atof(token.next().c_str());
			fnum[9] =(float)atof(token.next().c_str());
			fnum[10] =(float)atof(token.next().c_str());
			fnum[11] =(float)atof(token.next().c_str());
			fnum[12] =(float)atof(token.next().c_str());
			fnum[13] =(float)atof(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());
			inum[3] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy5(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],inum[0],
				fnum[6],fnum[7],fnum[8],fnum[9],fnum[10],fnum[11],fnum[12],fnum[13],inum[1],inum[2],inum[3]));
		}
		else if(ID_name == "enemy5_2Point")
		{
			if((int)token.count() <21)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());
			inum[3] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			fnum[8] =(float)atof(token.next().c_str());
			fnum[9] =(float)atof(token.next().c_str());
			fnum[10] =(float)atof(token.next().c_str());
			fnum[11] =(float)atof(token.next().c_str());
			fnum[12] =(float)atof(token.next().c_str());
			fnum[13] =(float)atof(token.next().c_str());
			inum[4] =atoi(token.next().c_str());
			inum[5] =atoi(token.next().c_str());
			inum[6] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy5_2Point(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],
				inum[0],inum[1],inum[2],inum[3],
				fnum[6],fnum[7],fnum[8],fnum[9],fnum[10],fnum[11],fnum[12],fnum[13],inum[4],inum[5],inum[6]));
		}
		else if(ID_name == "enemy6")
		{
			if((int)token.count() <11)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy6(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],inum[0],
				fnum[6],fnum[7],inum[1],inum[2]));
		}
		else if(ID_name == "enemy6_2Point")
		{
			if((int)token.count() <14)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());
			inum[3] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			inum[4] =atoi(token.next().c_str());
			inum[5] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy6_2Point(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],
				inum[0],inum[1],inum[2],inum[3],
				fnum[6],fnum[7],inum[4],inum[5]));
		}
		else if(ID_name == "enemy7")
		{
			if((int)token.count() <13)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			fnum[8] =(float)atof(token.next().c_str());
			fnum[9] =(float)atof(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy7(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],inum[0],
				fnum[6],fnum[7],fnum[8],fnum[9],inum[1],inum[2]));
		}
		else if(ID_name == "enemy7_2Point")
		{
			if((int)token.count() <16)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());
			inum[3] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			fnum[8] =(float)atof(token.next().c_str());
			fnum[9] =(float)atof(token.next().c_str());
			inum[4] =atoi(token.next().c_str());
			inum[5] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy7_2Point(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],
				inum[0],inum[1],inum[2],inum[3],
				fnum[6],fnum[7],fnum[8],fnum[9],inum[4],inum[5]));
		}
		else if(ID_name == "enemy8")
		{
			if((int)token.count() <12)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			fnum[8] =(float)atof(token.next().c_str());
			fnum[9] =(float)atof(token.next().c_str());
			inum[1] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy8(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],inum[0],
				fnum[6],fnum[7],fnum[8],fnum[9],inum[1]));
		}
		else if(ID_name == "enemy8_2Point")
		{
			if((int)token.count() <15)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());
			fnum[2] =(float)atof(token.next().c_str());
			fnum[3] =(float)atof(token.next().c_str());
			fnum[4] =(float)atof(token.next().c_str());
			fnum[5] =(float)atof(token.next().c_str());
			inum[0] =atoi(token.next().c_str());
			inum[1] =atoi(token.next().c_str());
			inum[2] =atoi(token.next().c_str());
			inum[3] =atoi(token.next().c_str());

			fnum[6] =(float)atof(token.next().c_str());
			fnum[7] =(float)atof(token.next().c_str());
			fnum[8] =(float)atof(token.next().c_str());
			fnum[9] =(float)atof(token.next().c_str());
			inum[4] =atoi(token.next().c_str());

			Command.push_back(
				new CCommandNormalEnemy8_2Point(
				fnum[0],fnum[1],fnum[2],fnum[3],fnum[4],fnum[5],
				inum[0],inum[1],inum[2],inum[3],
				fnum[6],fnum[7],fnum[8],fnum[9],inum[4]));
		}
		else if(ID_name == "BOSS_1")
		{
			if((int)token.count() <2)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());

			Command.push_back(
				new CCommandBOSS_1(fnum[0],fnum[1]));
		}
		else if(ID_name == "BOSS_2")
		{
			if((int)token.count() <2)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());

			Command.push_back(
				new CCommandBOSS_2(fnum[0],fnum[1]));
		}
		else if(ID_name == "BOSS_3")
		{
			if((int)token.count() <2)
			{
				is_ok =false;
				return;
			}
			fnum[0] =(float)atof(token.next().c_str());
			fnum[1] =(float)atof(token.next().c_str());

			Command.push_back(
				new CCommandBOSS_3(fnum[0],fnum[1]));
		}
		else if(ID_name == "wait")
		{
			Command.push_back(
				new CCommandWait(this,atoi(token.next().c_str())));
		}
	}
}

CScript::~CScript(void)
{
	m_runIndex =0;
	while(m_runIndex<(int)Command.size())
	{
		delete Command[m_runIndex];
		++m_runIndex;
	}
}

void CScript::ResetScript()
{
	m_waitTime =0;
	m_runIndex =0;
}

void CScript::RunScript()
{
	--m_waitTime;

	while(m_runIndex<(int)Command.size() && m_waitTime <=0)
	{
		Command[m_runIndex]->RunCommand();
		++m_runIndex;
	}
}
