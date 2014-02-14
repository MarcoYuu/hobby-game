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
//DirectInput���g���Ƃ��Ɏg���N���X
//��{�I�ɂ͂ЂƂ̃A�v�����łЂƂ�new����delete����΂�낵
//�L�[�{�[�h�ƃR���g���[����9�{�^���ɑΉ�
//�����g���̂�GetKeyState�Ƃ������ł���
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
//�L�[�񋓑�
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
//�L�[�\����
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
//Input�N���X
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
	//�R���X�g���N�^��f�X�g���N�^
	CInput(HINSTANCE hCurInst,HWND hWnd);
	virtual ~CInput(void);
	
	//�L�[�̏����X�V
	BOOL UpdateKeyState();
	//�L�[�̏����擾
	BOOL GetKeyState(MY_KEYSTATE key);
	void GetAllState(KEYSTATE *key);

	//�L�[�����O���t�@�C������X�V
	BOOL SetUpKeyStateFromFile(std::string file_name, std::string delim ="");
	BOOL UpdateKeyStateFromFile();
	BOOL SaveKeyStateToVariant(std::vector<char> *input);
	BOOL SaveKeyStateToFile(std::vector<char> *input, std::string file_name, std::string delim ="", bool bEraseFile =false);
};
