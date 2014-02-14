#include <string>
#include <fstream>
#include <stdlib.h>
#include "Input.h"

//コンストラクタ
CInput::CInput(HINSTANCE hCurInst,HWND hWnd)
:m_lpDI(NULL),m_lpKeyBoardDev(NULL),m_lpGamePad(NULL)
{
	memset( &m_diDevCaps, 0, sizeof(m_diDevCaps) );
	memset( &m_digamepad, 0, sizeof(m_digamepad) );
	Init(hCurInst,hWnd);
}

//デストラクタ
CInput::~CInput(void)
{
	UnInit();
}

void CInput::Init(HINSTANCE hCurInst,HWND hWnd)
{
	/*-------------------------DirectInputの初期化--------------------*/
	//インタフェースの取得
	DirectInput8Create(hCurInst, DIRECTINPUT_VERSION, 
		IID_IDirectInput8,(LPVOID*)&m_lpDI, NULL );

	//デバイスの取得（キーボード
	m_lpDI->CreateDevice( GUID_SysKeyboard, &m_lpKeyBoardDev, NULL );
	//デバイスのアクセス権取得（キーボード
	m_lpKeyBoardDev->SetDataFormat( &c_dfDIKeyboard );
	m_lpKeyBoardDev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
	m_lpKeyBoardDev->Acquire();
	// キーボードの状態を取得
	m_lpKeyBoardDev->GetDeviceState( 256, m_KeyState );


	//デバイスの取得（パッド
	m_lpDI->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,
		(LPVOID)this, DIEDFL_ATTACHEDONLY );
	if(m_lpGamePad)
	{
		m_lpGamePad->EnumObjects( EnumAxesCallback, (LPVOID)this, DIDFT_AXIS );
	
		//デバイスのアクセス権取得（パッド
		m_lpGamePad->SetDataFormat( &c_dfDIJoystick );
		m_lpGamePad->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		m_lpGamePad->Acquire();
		// ジョイスティックの状態を取得
		m_lpGamePad->Poll();
		m_lpGamePad->GetDeviceState( sizeof(DIJOYSTATE), &m_digamepad );
	}
}

void CInput::UnInit()
{
	m_lpKeyBoardDev->Unacquire();
	
	if(m_lpGamePad)
	{
		m_lpGamePad->Unacquire();
	}
	RELEASE( m_lpKeyBoardDev );
	RELEASE( m_lpGamePad );
	RELEASE( m_lpDI );
}

//入力を更新する関数
BOOL CInput::UpdateKeyState()
{
	m_lpKeyBoardDev->Acquire();
	m_lpKeyBoardDev->GetDeviceState( 256, m_KeyState );

	if(m_lpGamePad)
	{
		m_lpGamePad->Acquire();
		m_lpGamePad->Poll();
		m_lpGamePad->GetDeviceState( sizeof(DIJOYSTATE), &m_digamepad );
	}
	return TRUE;
}

//外部ファイルから入力を読み込む関数
BOOL CInput::SetUpKeyStateFromFile(std::string file_name, std::string delim)
{
	m_input.clear();
	m_Index =0;
	std::ifstream ifs(file_name.c_str(),std::ios::in| std::ios::binary);
	char key_state =0;
	std::string str;

	while(getline(ifs,str))
	{
		if(str == delim)
		{
			while(ifs.get(key_state))
			{
				if(key_state == '\n')
					break;
				m_input.push_back(key_state);
			}
			break;
		}
	}
	
	return TRUE;
}

//外部ファイルから読み込んだ入力を更新する関数
BOOL CInput::UpdateKeyStateFromFile()
{
	m_lpKeyBoardDev->Acquire();
	m_lpKeyBoardDev->GetDeviceState( 256, m_KeyState );

	m_input[m_Index] & MYBIT_RIGHT 
		?m_KeyState[DIK_RIGHT]|=0x80
		:m_KeyState[DIK_RIGHT]&=0x7f;
	m_input[m_Index] & MYBIT_LEFT 
		?m_KeyState[DIK_LEFT]|=0x80
		:m_KeyState[DIK_LEFT]&=0x7f;
	m_input[m_Index] & MYBIT_DOWN 
		?m_KeyState[DIK_DOWN]|=0x80
		:m_KeyState[DIK_DOWN]&=0x7f;
	m_input[m_Index] & MYBIT_UP 
		?m_KeyState[DIK_UP]|=0x80
		:m_KeyState[DIK_UP]&=0x7f;
	m_input[m_Index] & MYBIT_Z 
		?m_KeyState[DIK_Z]|=0x80
		:m_KeyState[DIK_Z]&=0x7f;
	m_input[m_Index] & MYBIT_X 
		?m_KeyState[DIK_X]|=0x80
		:m_KeyState[DIK_X]&=0x7f;
	m_input[m_Index] & MYBIT_SHIFT 
		?m_KeyState[DIK_LSHIFT]|=0x80
		:m_KeyState[DIK_LSHIFT]&=0x7f;
	
	if(m_Index<(int)m_input.size())
		++m_Index;

	return TRUE;
}

//入力を変数に格納する関数
BOOL CInput::SaveKeyStateToVariant(std::vector<char> *input)
{
	/*
	#define MYBIT_RIGHT	 0x01
	#define MYBIT_LEFT	 0x02
	#define MYBIT_DOWN	 0x04
	#define MYBIT_UP	 0x08
	#define MYBIT_Z		 0x10
	#define MYBIT_X		 0x20
	#define MYBIT_SHIFT	 0x40
	#define MYBIT_C		 0x80
	*/
	char key_state =0;
	KEYSTATE key;
	GetAllState(&key);

	key.RIGHT	? key_state |=MYBIT_RIGHT	:key_state |=0x00;
	key.LEFT	? key_state |=MYBIT_LEFT	:key_state |=0x00;
	key.DOWN	? key_state |=MYBIT_DOWN	:key_state |=0x00;
	key.UP		? key_state |=MYBIT_UP		:key_state |=0x00;
	key.Z		? key_state |=MYBIT_Z		:key_state |=0x00;
	key.X		? key_state |=MYBIT_X		:key_state |=0x00;
	key.SHIFT	? key_state |=MYBIT_SHIFT	:key_state |=0x00;

	input->push_back(key_state);

	return TRUE;
}
//入力を外部ファイルに格納する関数
BOOL CInput::SaveKeyStateToFile(std::vector<char> *input, std::string file_name, std::string delim, bool bEraseFile)
{
	if(bEraseFile)
		std::ofstream ofs(file_name.c_str(),std::ios::out|std::ios::binary| std::ios::trunc);

	std::ofstream ofs(file_name.c_str(),std::ios::out|std::ios::binary| std::ios::app);
	
	ofs << delim <<std::endl;
	for(int frame_num=0;frame_num<(int)input->size();++frame_num)
	{
		ofs << (*input)[frame_num];
	}
	ofs << std::endl;

	return TRUE;
}

void CInput::GetAllState(KEYSTATE *key)
{
	key->RIGHT	=(m_KeyState[DIK_RIGHT] & 0x80)||(m_digamepad.lX > 1000/2);
	key->LEFT	=(m_KeyState[DIK_LEFT] & 0x80)||(m_digamepad.lX < -1000/2);
	key->UP		=(m_KeyState[DIK_UP] & 0x80)||(m_digamepad.lY < -1000/2);
	key->DOWN	=(m_KeyState[DIK_DOWN] & 0x80)||(m_digamepad.lY > 1000/2);
	key->Z		=(m_KeyState[DIK_Z] & 0x80)||(m_digamepad.rgbButtons[0] & 0x80);
	key->X		=(m_KeyState[DIK_X] & 0x80)||(m_digamepad.rgbButtons[1] & 0x80);
	key->C		=(m_KeyState[DIK_C] & 0x80)||(m_digamepad.rgbButtons[2] & 0x80);
	key->SHIFT	=(m_KeyState[DIK_LSHIFT] & 0x80)||(m_digamepad.rgbButtons[4] & 0x80);
	key->CTRL	=(m_KeyState[DIK_LCONTROL] & 0x80)||(m_digamepad.rgbButtons[3] & 0x80);
	key->ESCAPE	=(m_KeyState[DIK_ESCAPE] & 0x80)||(m_digamepad.rgbButtons[5] & 0x80);
}

BOOL CInput::GetKeyState(MY_KEYSTATE key)
{
	switch(key)
	{
	case MY_RIGHT:
		return (m_KeyState[key] & 0x80)||(m_digamepad.lX > 1000/2);
	case MY_LEFT:
		return (m_KeyState[key] & 0x80)||(m_digamepad.lX < -1000/2);
	case MY_DOWN:
		return (m_KeyState[key] & 0x80)||(m_digamepad.lY > 1000/2);
	case MY_UP:
		return (m_KeyState[key] & 0x80)||(m_digamepad.lY < -1000/2);
	case MY_Z:
		return (m_KeyState[key] & 0x80)||(m_digamepad.rgbButtons[0] & 0x80);
	case MY_X:
		return (m_KeyState[key] & 0x80)||(m_digamepad.rgbButtons[1] & 0x80);
	case MY_C:
		return (m_KeyState[key] & 0x80)||(m_digamepad.rgbButtons[2] & 0x80);
	case MY_SHIFT:
		return (m_KeyState[key] & 0x80)||(m_digamepad.rgbButtons[4] & 0x80);
	case MY_CTRL:
		return (m_KeyState[key] & 0x80)||(m_digamepad.rgbButtons[3] & 0x80);
	case MY_ESCAPE:
		return (m_KeyState[key] & 0x80)||(m_digamepad.rgbButtons[5] & 0x80);
	default:
		return FALSE;
	}
}

//パッド列挙関数
BOOL CALLBACK CInput::EnumJoysticksCallback(const DIDEVICEINSTANCE* lpddi, LPVOID lpContext)
{
	HRESULT hr;
	CInput *pThis = (CInput*)lpContext;

	// 列挙されたジョイスティックへのインターフェイスを取得する。
	hr = pThis->m_lpDI->CreateDevice( lpddi->guidInstance, &pThis->m_lpGamePad, NULL );
	if( FAILED(hr) )  return DIENUM_CONTINUE;

	// ジョイスティックの能力を調べる
	pThis->m_diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = pThis->m_lpGamePad->GetCapabilities( &pThis->m_diDevCaps );
	if( FAILED(hr) )
	{
		// ジョイスティック能力の取得に失敗
		RELEASE( pThis->m_lpGamePad );
		return DIENUM_CONTINUE;
	}

	// このデバイスを使用
	return DIENUM_STOP;
}

//軸の設定
BOOL CALLBACK CInput::EnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID lpvRef )
{
  HRESULT hr;
  CInput *pThis = (CInput*)lpvRef;

  // 軸の値の範囲を設定（-1000～1000）
  DIPROPRANGE diprg;
  ZeroMemory( &diprg, sizeof(diprg) );
  diprg.diph.dwSize       = sizeof(diprg); 
  diprg.diph.dwHeaderSize = sizeof(diprg.diph); 
  diprg.diph.dwObj        = lpddoi->dwType;
  diprg.diph.dwHow        = DIPH_BYID;
  diprg.lMin              = -1000;
  diprg.lMax              = +1000;
  hr = pThis->m_lpGamePad->SetProperty( DIPROP_RANGE, &diprg.diph );
  if( FAILED(hr) )  return DIENUM_STOP;

  return DIENUM_CONTINUE;
}
