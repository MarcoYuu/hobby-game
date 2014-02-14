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
//超簡易的にDirectXの板ポリゴンだけ扱うクラス
//基本的にはひとつのアプリ内でひとつnewしてdeleteすればよろし
//多分あんまり効率的な動きはしない
//
///////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------//
//頂点構造体
struct CUSTOMVERTEX
{  	
	float 	x, y, z; 	// 頂点座標
	float 	rhw; 	// 除算数
	DWORD 	dwColor; 	// 頂点の色
	float 	u, v; 	//　テクスチャ座標
};

//-----------------------------------------------------------------//
//四角形構造体(直角とは限らない)
struct RECTANGLE
{  	
	CUSTOMVERTEX v1;
	CUSTOMVERTEX v2;
	CUSTOMVERTEX v3;
	CUSTOMVERTEX v4;
};
//-----------------------------------------------------------------//
//レンダリングタイプ列挙体
enum RENDERTYPE
{  	
	NORMAL,
	ADDITION,
};

//-----------------------------------------------------------------//
//テクスチャ管理クラス
//-----------------------------------------------------------------//
class CTexture
{
	IDirect3DTexture9* m_pTex;
	CGraphics *m_graphics;
	//RenderPattern　m_render; enumでいくつか定義して,描画時にこの値に応じてレンダリングステートを変えるとどうだろう
	//GetRender()か何かでゲットして、Draw呼んだときに内部でレンダリングステートを初期化するとか･･･
public:
	//コンストラクタ･デストラクタ
	CTexture(CGraphics *graphics, LPCWSTR file_name);
	virtual ~CTexture(void);

	//テクスチャ取得
	IDirect3DTexture9* GetTex()
	{
		return m_pTex;
	}
};

//-----------------------------------------------------------------//
//ポリゴン管理クラス(四角形&テクスチャ管理クラスの管理クラス
//-----------------------------------------------------------------//
class CPoligon
{
	RECTANGLE m_rect;
	CTexture *m_pTex;
public:
	//コンストラクタ･デストラクタ
	CPoligon(CTexture *pTex, float x, float y, float width, float height);
	virtual ~CPoligon(void);

	//メンバを返す
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
	//ちなみにPIは次のように定義されている。
	//
	//#define D3DX_PI ((FLOAT) 3.141592654f) 
	//
	//

	//頂点設定関数
	void SetVertex(CUSTOMVERTEX *ver, float x, float y, float u, float v, DWORD color);
	void SetVertex(CUSTOMVERTEX *ver, float x, float y, float u, float v);
	//頂点色設定関数
	void SetColor(DWORD color1, DWORD color2, DWORD color3, DWORD color4);

	//四角形設定関数
	//アニメーションしないとき
	void SetRect(float x, float y, float width, float height);
	void SetRect(float x, float y, float width, float height, float arg);
	void SetRect(float x, float y, float width, float height, float arg,
		DWORD color1, DWORD color2, DWORD color3, DWORD color4);

	//アニメーションするとき
	void SetRect(float x, float y, float width, float height, 
		float u1, float v1, float u2, float v2);
	void SetRect(float x, float y, float width, float height, float arg, 
		float u1, float v1, float u2, float v2);
	void SetRect(float x, float y, float width, float height, float arg, 
		float u1, float v1, float u2, float v2,
		DWORD color1, DWORD color2, DWORD color3, DWORD color4);
};

//-----------------------------------------------------------------//
//グラフィクスクラス
//-----------------------------------------------------------------//
class CGraphics
{
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDev;
	IDirect3DVertexBuffer9* m_pVertex;

	//初期化と開放
	BOOL Init(HWND hWnd, BOOL bWindowed,bool bHWVertex,bool bREF,bool bVSync,int WindowWidth,int WindowHeight);
	void UnInit();
public:
	//コンストラクタ･デストラクタ
	//フルスクリーンのときは640×480にすること
	CGraphics(HWND hWnd, BOOL bWindowed,bool bHWVertex,bool bREF,bool bVSync,int WindowWidth,int WindowHeight);
	virtual ~CGraphics(void);

	//初期化したウィンドウサイズ
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	//フルスクリーン時に対する画面の拡大率(フルスクリーン基準
	float GetRate()
	{
		return (float)WINDOW_WIDTH/640.0f;
	}
	
	//デバイス要求
	LPDIRECT3DDEVICE9 GetDevice()
	{
		return m_pD3DDev;
	}

	//描画開始
	BOOL BeginPaint()
	{
		m_pD3DDev->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
		m_pD3DDev->BeginScene();
		return TRUE;
	}
	//描画終了
	BOOL EndPaint()
	{
		m_pD3DDev->EndScene();
		return TRUE;
	}
	//表示
	void Present()
	{
		m_pD3DDev->Present( NULL, NULL, NULL, NULL );
	}
	//描画
	BOOL Draw(CPoligon* pPoligon,int num);
	
	//レンダリングステート変更
	BOOL SetRenderState(RENDERTYPE render);
};
