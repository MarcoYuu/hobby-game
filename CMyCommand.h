#pragma once
#pragma warning(disable : 4995)


class CScript;

//---------------------------------------------------------------------
//CMyCommandクラス（コマンドの基底クラス
//---------------------------------------------------------------------

class CMyCommand
{
public:
	CMyCommand(){}
	virtual ~CMyCommand(){}
	virtual void RunCommand(){}
};

//---------------------------------------------------------------------
//CCommandWaitクラス（指定時間待つことにするクラス
//---------------------------------------------------------------------

class CCommandWait :public CMyCommand
{
	CScript* m_script;
	int m_wait;
public:
	CCommandWait(CScript* script,int wait)
	:m_wait(wait),m_script(script)
	{
	}
	virtual void RunCommand();
};

//---------------------------------------------------------------------
//CCommandNormalEnemy1クラス（NormalEnemy1を生成する命令をするクラス
//---------------------------------------------------------------------

//曲線移動
class CCommandNormalEnemy1 :public CMyCommand
{
	float m_x,m_y;
	float m_x_spd,m_y_spd,m_x_axel,m_y_axel;
	int m_vital;

	float m_roll,m_shot_speed;
	int m_shot_num,m_count;
public:
	/*float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float roll,float shot_speed,int shot_num,int count*/
	CCommandNormalEnemy1(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
							   float roll,float shot_speed,int shot_num,int count)
	:m_x(x),m_y(y),m_x_spd(x_spd),m_y_spd(y_spd),m_x_axel(x_axel),m_y_axel(y_axel),m_vital(vital),
	m_roll(roll),m_shot_speed(shot_speed),m_shot_num(shot_num),m_count(count)
	{
	}
	virtual void RunCommand();
};

//二点間曲線移動
class CCommandNormalEnemy1_2Point :public CMyCommand
{
	float m_x1,m_y1,
		m_x2,m_y2,
		m_x3,m_y3;
	int m_time1,m_time2,m_shot_time,
		m_vital;

	float m_roll,m_shot_speed;
	int m_shot_num,m_count;
public:
	/*float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float roll,float shot_speed,int shot_num,int count*/
	CCommandNormalEnemy1_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float roll,float shot_speed,int shot_num,int count)
	:m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2),m_x3(x3),m_y3(y3),
	m_time1(time1),m_time2(time2),m_shot_time(shot_time),m_vital(vital),
	m_roll(roll),m_shot_speed(shot_speed),m_shot_num(shot_num),m_count(count)
	{
	}
	virtual void RunCommand();
};

//---------------------------------------------------------------------
//CCommandNormalEnemy2クラス（NormalEnemy2を生成する命令をするクラス
//---------------------------------------------------------------------

//曲線移動
class CCommandNormalEnemy2 :public CMyCommand
{
	float m_x,m_y;
	float m_x_spd,m_y_spd,m_x_axel,m_y_axel;
	int m_vital;

	float m_shot_speed;
	int m_count;
public:
	/*float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float shot_speed,int count*/
	CCommandNormalEnemy2(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
							   float shot_speed,int count)
	:m_x(x),m_y(y),m_x_spd(x_spd),m_y_spd(y_spd),m_x_axel(x_axel),m_y_axel(y_axel),m_vital(vital),
	m_shot_speed(shot_speed),m_count(count)
	{
	}
	virtual void RunCommand();
};
//二点間曲線移動
class CCommandNormalEnemy2_2Point :public CMyCommand
{
	float m_x1,m_y1,
		m_x2,m_y2,
		m_x3,m_y3;
	int m_time1,m_time2,m_shot_time,
		m_vital;

	float m_shot_speed;
	int m_count;
public:
	/*float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float shot_speed,int count*/
	CCommandNormalEnemy2_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float shot_speed,int count)
	:m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2),m_x3(x3),m_y3(y3),
	m_time1(time1),m_time2(time2),m_shot_time(shot_time),m_vital(vital),
	m_shot_speed(shot_speed),m_count(count)
	{
	}
	virtual void RunCommand();
};


//---------------------------------------------------------------------
//CCommandNormalEnemy3クラス（NormalEnemy3を生成する命令をするクラス
//---------------------------------------------------------------------

//曲線移動
class CCommandNormalEnemy3 :public CMyCommand
{
	float m_x,m_y;
	float m_x_spd,m_y_spd,m_x_axel,m_y_axel;
	int m_vital;

	float m_shot_speed;
	int m_max_shot_num;
	int m_count;
public:
	/*float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float shot_speed,int max_shot_num,int count*/
	CCommandNormalEnemy3(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float shot_speed,int max_shot_num,int count)
	:m_x(x),m_y(y),m_x_spd(x_spd),m_y_spd(y_spd),m_x_axel(x_axel),m_y_axel(y_axel),m_vital(vital),
	m_shot_speed(shot_speed),m_max_shot_num(max_shot_num),m_count(count)
	{
	}
	virtual void RunCommand();
};
//二点間曲線移動
class CCommandNormalEnemy3_2Point :public CMyCommand
{
	float m_x1,m_y1,
		m_x2,m_y2,
		m_x3,m_y3;
	int m_time1,m_time2,m_shot_time,
		m_vital;

	float m_shot_speed;
	int m_max_shot_num;
	int m_count;
public:
	/*float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int vital,
		float shot_speed,int max_shot_num,int shot_time,int count*/
	CCommandNormalEnemy3_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float shot_speed,int max_shot_num,int count)
	:m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2),m_x3(x3),m_y3(y3),
	m_time1(time1),m_time2(time2),m_vital(vital),
	m_shot_speed(shot_speed),m_max_shot_num(max_shot_num),m_shot_time(shot_time),m_count(count)
	{
	}
	virtual void RunCommand();
};

//---------------------------------------------------------------------
//CCommandNormalEnemy4クラス（NormalEnemy4を生成する命令をするクラス
//---------------------------------------------------------------------

//曲線移動
class CCommandNormalEnemy4 :public CMyCommand
{
	float m_x,m_y;
	float m_x_spd,m_y_spd,m_x_axel,m_y_axel;
	int m_vital;

	float m_shot_speed,m_shot_axel;
	int m_count;
	int m_max_shot_num;
	float m_delta_x;
public:
	/*float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float shot_speed,float shot_axel,int count,int max_shot_num,int delta_x*/
	CCommandNormalEnemy4(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
							   float shot_speed,float shot_axel,int count,int max_shot_num,float delta_x)
	:m_x(x),m_y(y),m_x_spd(x_spd),m_y_spd(y_spd),m_x_axel(x_axel),m_y_axel(y_axel),m_vital(vital),
	m_shot_speed(shot_speed),m_count(count),m_max_shot_num(max_shot_num),m_delta_x(delta_x),m_shot_axel(shot_axel)
	{
	}
	virtual void RunCommand();
};
//二点間曲線移動
class CCommandNormalEnemy4_2Point :public CMyCommand
{
	float m_x1,m_y1,
		m_x2,m_y2,
		m_x3,m_y3;
	int m_time1,m_time2,m_shot_time,
		m_vital;

	float m_shot_speed,m_shot_axel;
	int m_count;
	int m_max_shot_num;
	float m_delta_x;
public:
	/*float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float shot_speed,float shot_axel,int count,int max_shot_num,int delta_x*/
	CCommandNormalEnemy4_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float shot_speed,float shot_axel,int count,int max_shot_num,float delta_x)
	:m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2),m_x3(x3),m_y3(y3),
	m_time1(time1),m_time2(time2),m_shot_time(shot_time),m_vital(vital),
	m_shot_speed(shot_speed),m_count(count),m_max_shot_num(max_shot_num),m_delta_x(delta_x),m_shot_axel(shot_axel)
	{
	}
	virtual void RunCommand();
};


//---------------------------------------------------------------------
//CCommandNormalEnemy5クラス（NormalEnemy5を生成する命令をするクラス
//---------------------------------------------------------------------

//曲線移動
class CCommandNormalEnemy5 :public CMyCommand
{
	float m_x,m_y;
	float m_x_spd,m_y_spd,m_x_axel,m_y_axel;
	int m_vital;

	int m_max_shot_count;
	int m_shot_num;
	float m_line_speed;
	float m_delta_roll,m_roll;
	float m_angle_spd,m_angle_axel;
	float m_radius,m_rad_spd,m_rad_axel;
	int m_erase_count;
public:
	/*float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float shot_speed,float delta_roll,float angle_spd,float angle_axel,
		float radius,float rad_spd,float rad_axel,int shot_num,int erase_count,int shot_count*/
	CCommandNormalEnemy5(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float shot_speed,float roll,float delta_roll,float angle_spd,float angle_axel,
		float radius,float rad_spd,float rad_axel,int shot_num,int erase_count,int shot_count)
	:m_x(x),m_y(y),m_x_spd(x_spd),m_y_spd(y_spd),m_x_axel(x_axel),m_y_axel(y_axel),m_vital(vital),
	m_max_shot_count(shot_count),m_erase_count(erase_count),
	m_shot_num(shot_num),m_line_speed(shot_speed),m_delta_roll(delta_roll),m_roll(roll),
	m_angle_spd(angle_spd),m_angle_axel(angle_axel),m_radius(radius),m_rad_spd(rad_spd),m_rad_axel(rad_axel)
	{
	}
	virtual void RunCommand();
};
//二点間曲線移動
class CCommandNormalEnemy5_2Point :public CMyCommand
{
	float m_x1,m_y1,
		m_x2,m_y2,
		m_x3,m_y3;
	int m_time1,m_time2,m_shot_time,
		m_vital;

	int m_max_shot_count;
	int m_shot_num;
	float m_line_speed;
	float m_delta_roll,m_roll;
	float m_angle_spd,m_angle_axel;
	float m_radius,m_rad_spd,m_rad_axel;
	int m_erase_count;
public:
	/*float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float shot_speed,float delta_roll,float angle_spd,float angle_axel,
		float radius,float rad_spd,float rad_axel,int shot_num,int erase_count,int shot_count*/
	CCommandNormalEnemy5_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float shot_speed,float roll,float delta_roll,float angle_spd,float angle_axel,
		float radius,float rad_spd,float rad_axel,int shot_num,int erase_count,int shot_count)
	:m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2),m_x3(x3),m_y3(y3),
	m_time1(time1),m_time2(time2),m_shot_time(shot_time),m_vital(vital),
	m_max_shot_count(shot_count),m_erase_count(erase_count),
	m_shot_num(shot_num),m_line_speed(shot_speed),m_delta_roll(delta_roll),m_roll(roll),
	m_angle_spd(angle_spd),m_angle_axel(angle_axel),m_radius(radius),m_rad_spd(rad_spd),m_rad_axel(rad_axel)
	{
	}
	virtual void RunCommand();
};


//---------------------------------------------------------------------
//CCommandNormalEnemy6クラス（NormalEnemy6を生成する命令をするクラス
//---------------------------------------------------------------------

//曲線移動
class CCommandNormalEnemy6 :public CMyCommand
{
	float m_x,m_y;
	float m_x_spd,m_y_spd,m_x_axel,m_y_axel;
	int m_vital;

	int m_max_shot_count;
	int m_shot_num;
	float m_speed,m_axel;
public:
	/*float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float speed,float axel,int shot_num,int shot_count*/
	CCommandNormalEnemy6(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float speed,float axel,int shot_num,int shot_count)
	:m_x(x),m_y(y),m_x_spd(x_spd),m_y_spd(y_spd),m_x_axel(x_axel),m_y_axel(y_axel),m_vital(vital),
	m_max_shot_count(shot_count),m_shot_num(shot_num),m_speed(speed),m_axel(axel)
	{
	}
	virtual void RunCommand();
};
//二点間曲線移動
class CCommandNormalEnemy6_2Point :public CMyCommand
{
	float m_x1,m_y1,
		m_x2,m_y2,
		m_x3,m_y3;
	int m_time1,m_time2,m_shot_time,
		m_vital;

	int m_max_shot_count;
	int m_shot_num;
	float m_speed,m_axel;
public:
	/*float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float speed,float axel,int shot_num,int shot_count*/
	CCommandNormalEnemy6_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float speed,float axel,int shot_num,int shot_count)
	:m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2),m_x3(x3),m_y3(y3),
	m_time1(time1),m_time2(time2),m_shot_time(shot_time),m_vital(vital),
	m_max_shot_count(shot_count),m_shot_num(shot_num),m_speed(speed),m_axel(axel)
	{
	}
	virtual void RunCommand();
};


//---------------------------------------------------------------------
//CCommandNormalEnemy7クラス（NormalEnemy7を生成する命令をするクラス
//---------------------------------------------------------------------

//曲線移動
class CCommandNormalEnemy7 :public CMyCommand
{
	float m_x,m_y;
	float m_x_spd,m_y_spd,m_x_axel,m_y_axel;
	int m_vital;

	int m_max_shot_count;
	int m_max_shot_num;
	float m_speed,m_max_speed,m_axel,m_angle;
public:
	/*float speed,float max_speed,float axel,float angle,int max_shot_num,int shot_count*/
	CCommandNormalEnemy7(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float speed,float max_speed,float axel,float angle,int max_shot_num,int shot_count)
	:m_x(x),m_y(y),m_x_spd(x_spd),m_y_spd(y_spd),m_x_axel(x_axel),m_y_axel(y_axel),m_vital(vital),
	m_max_shot_count(shot_count),m_max_shot_num(max_shot_num),
	m_speed(speed),m_max_speed(max_speed),m_axel(axel),m_angle(angle)
	{
	}
	virtual void RunCommand();
};
//二点間曲線移動
class CCommandNormalEnemy7_2Point :public CMyCommand
{
	float m_x1,m_y1,
		m_x2,m_y2,
		m_x3,m_y3;
	int m_time1,m_time2,m_shot_time,
		m_vital;

	int m_max_shot_count;
	int m_max_shot_num;
	float m_speed,m_max_speed,m_axel,m_angle;
public:
	/*float speed,float max_speed,float axel,float angle,int max_shot_num,int shot_count*/
	CCommandNormalEnemy7_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float speed,float max_speed,float axel,float angle,int max_shot_num,int shot_count)
	:m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2),m_x3(x3),m_y3(y3),
	m_time1(time1),m_time2(time2),m_shot_time(shot_time),m_vital(vital),
	m_max_shot_count(shot_count),m_max_shot_num(max_shot_num),
	m_speed(speed),m_max_speed(max_speed),m_axel(axel),m_angle(angle)
	{
	}
	virtual void RunCommand();
};
//---------------------------------------------------------------------
//CCommandNormalEnemy8クラス（NormalEnemy8を生成する命令をするクラス
//---------------------------------------------------------------------

//曲線移動
class CCommandNormalEnemy8 :public CMyCommand
{
	float m_x,m_y;
	float m_x_spd,m_y_spd,m_x_axel,m_y_axel;
	int m_vital;

	int m_max_shot_count;
	float m_speed,m_axel,m_angle,m_max_angle;
public:
	CCommandNormalEnemy8(float x, float y, float x_spd, float y_spd, float x_axel, float y_axel,int vital,
		float speed,float axel,float angle,float max_angle,int shot_count)
	:m_x(x),m_y(y),m_x_spd(x_spd),m_y_spd(y_spd),m_x_axel(x_axel),m_y_axel(y_axel),m_vital(vital),
	m_max_shot_count(shot_count),
	m_speed(speed),m_axel(axel),m_angle(angle),m_max_angle(max_angle)
	{
	}
	virtual void RunCommand();
};
//二点間曲線移動
class CCommandNormalEnemy8_2Point :public CMyCommand
{
	float m_x1,m_y1,
		m_x2,m_y2,
		m_x3,m_y3;
	int m_time1,m_time2,m_shot_time,
		m_vital;

	int m_max_shot_count;
	float m_speed,m_axel,m_angle,m_max_angle;
public:
	CCommandNormalEnemy8_2Point(float x1, float y1, float x2, float y2, float x3, float y3,
		int time1, int time2,int shot_time,int vital,
		float speed,float axel,float angle,float max_angle,int shot_count)
	:m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2),m_x3(x3),m_y3(y3),
	m_time1(time1),m_time2(time2),m_shot_time(shot_time),m_vital(vital),
	m_max_shot_count(shot_count),
	m_speed(speed),m_axel(axel),m_angle(angle),m_max_angle(max_angle)
	{
	}
	virtual void RunCommand();
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++++++++		BOSS	++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//---------------------------------------------------------------------
//CCommandBOSS_1クラス（CCommandBOSS_1を生成する命令をするクラス
//---------------------------------------------------------------------

class CCommandBOSS_1 :public CMyCommand
{
	float m_x,m_y;
public:
	/*float x, float y*/
	CCommandBOSS_1(float x, float y)
	:m_x(x),m_y(y)
	{
	}
	virtual void RunCommand();
};

//---------------------------------------------------------------------
//CCommandBOSS_2クラス（CCommandBOSS_2を生成する命令をするクラス
//---------------------------------------------------------------------

class CCommandBOSS_2 :public CMyCommand
{
	float m_x,m_y;
public:
	/*float x, float y*/
	CCommandBOSS_2(float x, float y)
	:m_x(x),m_y(y)
	{
	}
	virtual void RunCommand();
};
//---------------------------------------------------------------------
//CCommandBOSS_3クラス（CCommandBOSS_3を生成する命令をするクラス
//---------------------------------------------------------------------

class CCommandBOSS_3 :public CMyCommand
{
	float m_x,m_y;
public:
	/*float x, float y*/
	CCommandBOSS_3(float x, float y)
	:m_x(x),m_y(y)
	{
	}
	virtual void RunCommand();
};