#include "Main.h"
#include "CMyCommand.h"
#include "Script.h"
#include "Enemy.h"
#include "BOSS.h"

//---------------------------------------------------------------------
//CCommandWaitクラス（指定時間待つことにするクラス
//---------------------------------------------------------------------

void CCommandWait::RunCommand()
{
	m_script->PlusWait(m_wait);
}

//---------------------------------------------------------------------
//CCommandNormalEnemy1クラス（NormalEnemy1を生成する命令をするクラス
//---------------------------------------------------------------------

void CCommandNormalEnemy1::RunCommand()
{
	new CNormalEnemy_1(m_x,m_y,m_x_spd,m_y_spd,m_x_axel,m_y_axel,m_vital,
		m_roll,m_shot_speed,m_shot_num,m_count);
}
void CCommandNormalEnemy1_2Point::RunCommand()
{
	new CNormalEnemy_1_2Point(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3,
		m_time1, m_time2,m_shot_time,m_vital,
		m_roll,m_shot_speed,m_shot_num,m_count);
}

//---------------------------------------------------------------------
//CCommandNormalEnemy2クラス（NormalEnemy2を生成する命令をするクラス
//---------------------------------------------------------------------

void CCommandNormalEnemy2::RunCommand()
{
	new CNormalEnemy_2(m_x,m_y,m_x_spd,m_y_spd,m_x_axel,m_y_axel,m_vital,
		m_shot_speed,m_count);
}
void CCommandNormalEnemy2_2Point::RunCommand()
{
	new CNormalEnemy_2_2Point(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3,
		m_time1, m_time2,m_shot_time,m_vital,
		m_shot_speed,m_count);
}

//---------------------------------------------------------------------
//CCommandNormalEnemy3クラス（NormalEnemy3を生成する命令をするクラス
//---------------------------------------------------------------------

void CCommandNormalEnemy3::RunCommand()
{
	new CNormalEnemy_3(m_x,m_y,m_x_spd,m_y_spd,m_x_axel,m_y_axel,m_vital,
		m_shot_speed,m_max_shot_num,m_count);
}
void CCommandNormalEnemy3_2Point::RunCommand()
{
	new CNormalEnemy_3_2Point(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3,
		m_time1, m_time2,m_shot_time,m_vital,
		m_shot_speed,m_max_shot_num,m_count);
}

//---------------------------------------------------------------------
//CCommandNormalEnemy4クラス（NormalEnemy4を生成する命令をするクラス
//---------------------------------------------------------------------

void CCommandNormalEnemy4::RunCommand()
{
	new CNormalEnemy_4(m_x,m_y,m_x_spd,m_y_spd,m_x_axel,m_y_axel,m_vital,
		m_shot_speed,m_shot_axel,m_count,m_max_shot_num,m_delta_x);
}
void CCommandNormalEnemy4_2Point::RunCommand()
{
	new CNormalEnemy_4_2Point(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3,
		m_time1, m_time2,m_shot_time,m_vital,
		m_shot_speed,m_shot_axel,m_count,m_max_shot_num,m_delta_x);
}

//---------------------------------------------------------------------
//CCommandNormalEnemy5クラス（NormalEnemy5を生成する命令をするクラス
//---------------------------------------------------------------------

void CCommandNormalEnemy5::RunCommand()
{
	new CNormalEnemy_5(m_x,m_y,m_x_spd,m_y_spd,m_x_axel,m_y_axel,m_vital,
		m_line_speed,m_roll,m_delta_roll,m_angle_spd,m_angle_axel,
		m_radius,m_rad_spd,m_rad_axel,m_shot_num,m_erase_count,m_max_shot_count);
}
void CCommandNormalEnemy5_2Point::RunCommand()
{
	new CNormalEnemy_5_2Point(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3,
		m_time1, m_time2,m_shot_time,m_vital,
		m_line_speed,m_roll,m_delta_roll,m_angle_spd,m_angle_axel,
		m_radius,m_rad_spd,m_rad_axel,m_shot_num,m_erase_count,m_max_shot_count);
}

//---------------------------------------------------------------------
//CCommandNormalEnemy6クラス（NormalEnemy6を生成する命令をするクラス
//---------------------------------------------------------------------

void CCommandNormalEnemy6::RunCommand()
{
	new CNormalEnemy_6(m_x,m_y,m_x_spd,m_y_spd,m_x_axel,m_y_axel,m_vital,
		m_speed,m_axel,m_shot_num,m_max_shot_count);
}
void CCommandNormalEnemy6_2Point::RunCommand()
{
	new CNormalEnemy_6_2Point(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3,
		m_time1, m_time2,m_shot_time,m_vital,
		m_speed,m_axel,m_shot_num,m_max_shot_count);
}
//---------------------------------------------------------------------
//CCommandNormalEnemy7クラス（NormalEnemy7を生成する命令をするクラス
//---------------------------------------------------------------------

void CCommandNormalEnemy7::RunCommand()
{
	new CNormalEnemy_7(m_x,m_y,m_x_spd,m_y_spd,m_x_axel,m_y_axel,m_vital,
		m_speed,m_max_speed,m_axel,m_angle,m_max_shot_num,m_max_shot_count);
}
void CCommandNormalEnemy7_2Point::RunCommand()
{
	new CNormalEnemy_7_2Point(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3,
		m_time1, m_time2,m_shot_time,m_vital,
		m_speed,m_max_speed,m_axel,m_angle,m_max_shot_num,m_max_shot_count);
}
//---------------------------------------------------------------------
//CCommandNormalEnemy8クラス（NormalEnemy8を生成する命令をするクラス
//---------------------------------------------------------------------

void CCommandNormalEnemy8::RunCommand()
{
	new CNormalEnemy_8(m_x,m_y,m_x_spd,m_y_spd,m_x_axel,m_y_axel,m_vital,
		m_speed,m_axel,m_angle,m_max_angle,m_max_shot_count);
}
void CCommandNormalEnemy8_2Point::RunCommand()
{
	new CNormalEnemy_8_2Point(m_x1, m_y1, m_x2, m_y2, m_x3, m_y3,
		m_time1, m_time2,m_shot_time,m_vital,
		m_speed,m_axel,m_angle,m_max_angle,m_max_shot_count);
}
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

void CCommandBOSS_1::RunCommand()
{
	new CBOSS_1(m_x,m_y);
}

//---------------------------------------------------------------------
//CCommandBOSS_2クラス（CCommandBOSS_2を生成する命令をするクラス
//---------------------------------------------------------------------

void CCommandBOSS_2::RunCommand()
{
	new CBOSS_2(m_x,m_y);
}

//---------------------------------------------------------------------
//CCommandBOSS_3クラス（CCommandBOSS_3を生成する命令をするクラス
//---------------------------------------------------------------------

void CCommandBOSS_3::RunCommand()
{
	new CBOSS_3(m_x,m_y);
}