#pragma once

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x800
#endif

#include <dinput.h>
#include <vector>
#include <string>

#define RELEASE(p) { if(p){(p)->Release();p=NULL;} }

///////////////////////////////////////////////////////////////////
//
//DirectInputを使うときに使うクラス
//基本的にはひとつのアプリ内でひとつnewしてdeleteすればよろし
//キーボードとコントローラの9ボタンに対応
//実質使うのはGetKeyStateとかだけでいい
//
///////////////////////////////////////////////////////////////////

#define MYBIT_RIGHT	 0x01
#define MYBIT_LEFT	 0x02
#define MYBIT_DOWN	 0x04
#define MYBIT_UP	 0x08
#define MYBIT_Z		 0x10
#define MYBIT_X		 0x20
#define MYBIT_SHIFT	 0x40
#define MYBIT_C		 0x80

//-----------------------------------------------------------------//
//キー列挙体
//-----------------------------------------------------------------//
enum MY_KEYSTATE
{
	MY_RIGHT	=DIK_RIGHT,
	MY_LEFT		=DIK_LEFT,
	MY_DOWN		=DIK_DOWN,
	MY_UP		=DIK_UP,
	MY_Z		=DIK_Z,
	MY_X		=DIK_X,
	MY_C		=DIK_C,
	MY_SHIFT	=DIK_LSHIFT,
	MY_CTRL		=DIK_LCONTROL,
	MY_ESCAPE	=DIK_ESCAPE
};

//-----------------------------------------------------------------//
//キー構造体
//-----------------------------------------------------------------//
struct KEYSTATE
{
	bool RIGHT;
	bool LEFT;
	bool DOWN;
	bool UP;
	bool Z;
	bool X;
	bool C;
	bool SHIFT;
	bool CTRL;
	bool ESCAPE;
};

//-----------------------------------------------------------------//
//Inputクラス
//-----------------------------------------------------------------//
class CInput
{
	LPDIRECTINPUT8 m_lpDI;
	LPDIRECTINPUTDEVICE8 m_lpKeyBoardDev;
	LPDIRECTINPUTDEVICE8 m_lpGamePad;
	DIDEVCAPS m_diDevCaps;

	BYTE m_KeyState[256];
	DIJOYSTATE m_digamepad;

	std::vector<char> m_input;
	int m_Index;
	
	void Init(HINSTANCE hCurInst,HWND hWnd);
	void UnInit();
	LPDIRECTINPUTDEVICE8 GetKeyDevice()
	{
		return m_lpKeyBoardDev;
	}
	LPDIRECTINPUTDEVICE8 GetPadDevice()
	{
		return m_lpGamePad;
	}
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* lpddi, LPVOID lpContext);
	static BOOL CALLBACK EnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID lpvRef);
public:
	//コンストラクタ･デストラクタ
	CInput(HINSTANCE hCurInst,HWND hWnd);
	virtual ~CInput(void);
	
	//キーの情報を更新
	BOOL UpdateKeyState();
	//キーの情報を取得
	BOOL GetKeyState(MY_KEYSTATE key);
	void GetAllState(KEYSTATE *key);

	//キー情報を外部ファイルから更新
	BOOL SetUpKeyStateFromFile(std::string file_name, std::string delim ="");
	BOOL UpdateKeyStateFromFile();
	BOOL SaveKeyStateToVariant(std::vector<char> *input);
	BOOL SaveKeyStateToFile(std::vector<char> *input, std::string file_name, std::string delim ="", bool bEraseFile =false);
};
