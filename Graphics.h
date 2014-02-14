#pragma once

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>

#define FVF_CUSTOM ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define RELEASE(p) { if(p){(p)->Release();p=NULL;} }

class CGraphics;
class CTexture;

///////////////////////////////////////////////////////////////////
//
//���ȈՓI��DirectX�̔|���S�����������N���X
//��{�I�ɂ͂ЂƂ̃A�v�����łЂƂ�new����delete����΂�낵
//��������܂�����I�ȓ����͂��Ȃ�
//
///////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------//
//���_�\����
struct CUSTOMVERTEX
{  	
	float 	x, y, z; 	// ���_���W
	float 	rhw; 	// ���Z��
	DWORD 	dwColor; 	// ���_�̐F
	float 	u, v; 	//�@�e�N�X�`�����W
};

//-----------------------------------------------------------------//
//�l�p�`�\����(���p�Ƃ͌���Ȃ�)
struct RECTANGLE
{  	
	CUSTOMVERTEX v1;
	CUSTOMVERTEX v2;
	CUSTOMVERTEX v3;
	CUSTOMVERTEX v4;
};
//-----------------------------------------------------------------//
//�����_�����O�^�C�v�񋓑�
enum RENDERTYPE
{  	
	NORMAL,
	ADDITION,
};

//-----------------------------------------------------------------//
//�e�N�X�`���Ǘ��N���X
//-----------------------------------------------------------------//
class CTexture
{
	IDirect3DTexture9* m_pTex;
	CGraphics *m_graphics;
	//RenderPattern�@m_render; enum�ł�������`����,�`�掞�ɂ��̒l�ɉ����ă����_�����O�X�e�[�g��ς���Ƃǂ����낤
	//GetRender()�������ŃQ�b�g���āADraw�Ă񂾂Ƃ��ɓ����Ń����_�����O�X�e�[�g������������Ƃ����
public:
	//�R���X�g���N�^��f�X�g���N�^
	CTexture(CGraphics *graphics, LPCWSTR file_name);
	virtual ~CTexture(void);

	//�e�N�X�`���擾
	IDirect3DTexture9* GetTex()
	{
		return m_pTex;
	}
};

//-----------------------------------------------------------------//
//�|���S���Ǘ��N���X(�l�p�`&�e�N�X�`���Ǘ��N���X�̊Ǘ��N���X
//-----------------------------------------------------------------//
class CPoligon
{
	RECTANGLE m_rect;
	CTexture *m_pTex;
public:
	//�R���X�g���N�^��f�X�g���N�^
	CPoligon(CTexture *pTex, float x, float y, float width, float height);
	virtual ~CPoligon(void);

	//�����o��Ԃ�
	RECTANGLE* GetpRect()
	{
		return &m_rect;
	}
	RECTANGLE GetRect()
	{
		return m_rect;
	}
	CTexture* GetpCTex()
	{
		return m_pTex;
	}
	//#define D3DXToRadian( degree ) ((degree) * (D3DX_PI / 180.0f))
	//#define D3DXToDegree( radian ) ((radian) * (180.0f / D3DX_PI))
	//
	//���Ȃ݂�PI�͎��̂悤�ɒ�`����Ă���B
	//
	//#define D3DX_PI ((FLOAT) 3.141592654f) 
	//
	//

	//���_�ݒ�֐�
	void SetVertex(CUSTOMVERTEX *ver, float x, float y, float u, float v, DWORD color);
	void SetVertex(CUSTOMVERTEX *ver, float x, float y, float u, float v);
	//���_�F�ݒ�֐�
	void SetColor(DWORD color1, DWORD color2, DWORD color3, DWORD color4);

	//�l�p�`�ݒ�֐�
	//�A�j���[�V�������Ȃ��Ƃ�
	void SetRect(float x, float y, float width, float height);
	void SetRect(float x, float y, float width, float height, float arg);
	void SetRect(float x, float y, float width, float height, float arg,
		DWORD color1, DWORD color2, DWORD color3, DWORD color4);

	//�A�j���[�V��������Ƃ�
	void SetRect(float x, float y, float width, float height, 
		float u1, float v1, float u2, float v2);
	void SetRect(float x, float y, float width, float height, float arg, 
		float u1, float v1, float u2, float v2);
	void SetRect(float x, float y, float width, float height, float arg, 
		float u1, float v1, float u2, float v2,
		DWORD color1, DWORD color2, DWORD color3, DWORD color4);
};

//-----------------------------------------------------------------//
//�O���t�B�N�X�N���X
//-----------------------------------------------------------------//
class CGraphics
{
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDev;
	IDirect3DVertexBuffer9* m_pVertex;

	//�������ƊJ��
	BOOL Init(HWND hWnd, BOOL bWindowed,bool bHWVertex,bool bREF,bool bVSync,int WindowWidth,int WindowHeight);
	void UnInit();
public:
	//�R���X�g���N�^��f�X�g���N�^
	//�t���X�N���[���̂Ƃ���640�~480�ɂ��邱��
	CGraphics(HWND hWnd, BOOL bWindowed,bool bHWVertex,bool bREF,bool bVSync,int WindowWidth,int WindowHeight);
	virtual ~CGraphics(void);

	//�����������E�B���h�E�T�C�Y
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	//�t���X�N���[�����ɑ΂����ʂ̊g�嗦(�t���X�N���[���
	float GetRate()
	{
		return (float)WINDOW_WIDTH/640.0f;
	}
	
	//�f�o�C�X�v��
	LPDIRECT3DDEVICE9 GetDevice()
	{
		return m_pD3DDev;
	}

	//�`��J�n
	BOOL BeginPaint()
	{
		m_pD3DDev->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
		m_pD3DDev->BeginScene();
		return TRUE;
	}
	//�`��I��
	BOOL EndPaint()
	{
		m_pD3DDev->EndScene();
		return TRUE;
	}
	//�\��
	void Present()
	{
		m_pD3DDev->Present( NULL, NULL, NULL, NULL );
	}
	//�`��
	BOOL Draw(CPoligon* pPoligon,int num);
	
	//�����_�����O�X�e�[�g�ύX
	BOOL SetRenderState(RENDERTYPE render);
};
