#include "Graphics.h"

//--------------------------------------------------------------------------------------//
/*--------------------------------ポリゴン(座標)管理クラス------------------------------*/
//--------------------------------------------------------------------------------------//
CPoligon::CPoligon(CTexture *pTex, float x, float y, float width, float height)
:m_pTex(pTex)
{
	SetRect(x, y, width, height);
	SetColor(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
}
CPoligon::~CPoligon(void)
{
}
void CPoligon::SetVertex(CUSTOMVERTEX *ver, float x, float y, float u, float v, DWORD color)
{
	ver->x =x;
	ver->y =y;
	ver->z =0.0f;
	ver->rhw =1.0f;
	ver->dwColor =color;
	ver->u =u;
	ver->v =v;
}
void CPoligon::SetVertex(CUSTOMVERTEX *ver, float x, float y, float u, float v)
{
	ver->x =x;
	ver->y =y;
	ver->z =0.0f;
	ver->rhw =1.0f;
	ver->u =u;
	ver->v =v;
}
void CPoligon::SetColor(DWORD color1, DWORD color2, DWORD color3, DWORD color4)
{
	m_rect.v1.dwColor =color1;
	m_rect.v2.dwColor =color2;
	m_rect.v3.dwColor =color3;
	m_rect.v4.dwColor =color4;
}
void CPoligon::SetRect(float x, float y, float width, float height)
{
	SetVertex(&m_rect.v1, 
		width/2+x, -height/2+y, 1.0f, 0.0f);
	SetVertex(&m_rect.v2, 
		width/2+x, height/2+y, 1.0f, 1.0f);
	SetVertex(&m_rect.v3, 
		-width/2+x, -height/2+y, 0.0f, 0.0f);
	SetVertex(&m_rect.v4, 
		-width/2+x, height/2+y, 0.0f, 1.0f);
}
void CPoligon::SetRect(float x, float y, float width, float height, float arg)
{
	SetVertex(&m_rect.v1, 
		(width/2)*cos(arg)-(-height/2)*sin(arg)+x, (width/2)*sin(arg)+(-height/2)*cos(arg)+y, 
		1.0f, 0.0f);
	SetVertex(&m_rect.v2, 
		(width/2)*cos(arg)-(height/2)*sin(arg)+x, (width/2)*sin(arg)+(height/2)*cos(arg)+y, 
		1.0f, 1.0f);
	SetVertex(&m_rect.v3, 
		(-width/2)*cos(arg)-(-height/2)*sin(arg)+x, (-width/2)*sin(arg)+(-height/2)*cos(arg)+y, 
		0.0f, 0.0f);
	SetVertex(&m_rect.v4, 
		(-width/2)*cos(arg)-(height/2)*sin(arg)+x, (-width/2)*sin(arg)+(height/2)*cos(arg)+y, 
		0.0f, 1.0f);
}
void CPoligon::SetRect(float x, float y, float width, float height, float arg,
		DWORD color1, DWORD color2, DWORD color3, DWORD color4)
{
	SetVertex(&m_rect.v1, 
		(width/2)*cos(arg)-(-height/2)*sin(arg)+x, (width/2)*sin(arg)+(-height/2)*cos(arg)+y, 
		1.0f, 0.0f, color1);
	SetVertex(&m_rect.v2, 
		(width/2)*cos(arg)-(height/2)*sin(arg)+x, (width/2)*sin(arg)+(height/2)*cos(arg)+y, 
		1.0f, 1.0f, color2);
	SetVertex(&m_rect.v3, 
		(-width/2)*cos(arg)-(-height/2)*sin(arg)+x, (-width/2)*sin(arg)+(-height/2)*cos(arg)+y, 
		0.0f, 0.0f, color3);
	SetVertex(&m_rect.v4, 
		(-width/2)*cos(arg)-(height/2)*sin(arg)+x, (-width/2)*sin(arg)+(height/2)*cos(arg)+y, 
		0.0f, 1.0f, color4);
}
void CPoligon::SetRect(float x, float y, float width, float height, 
		float u1, float v1, float u2, float v2)
{
	SetVertex(&m_rect.v1, 
		width/2+x, -height/2+y, u2, v1);
	SetVertex(&m_rect.v2, 
		width/2+x, height/2+y, u2, v2);
	SetVertex(&m_rect.v3, 
		-width/2+x, -height/2+y, u1, v1);
	SetVertex(&m_rect.v4, 
		-width/2+x, height/2+y, u1, v2);
}
void CPoligon::SetRect(float x, float y, float width, float height, float arg, 
		float u1, float v1, float u2, float v2)
{
	SetVertex(&m_rect.v1, 
		(width/2)*cos(arg)-(-height/2)*sin(arg)+x, (width/2)*sin(arg)+(-height/2)*cos(arg)+y, 
		u2, v1);
	SetVertex(&m_rect.v2, 
		(width/2)*cos(arg)-(height/2)*sin(arg)+x, (width/2)*sin(arg)+(height/2)*cos(arg)+y, 
		u2, v2);
	SetVertex(&m_rect.v3, 
		(-width/2)*cos(arg)-(-height/2)*sin(arg)+x, (-width/2)*sin(arg)+(-height/2)*cos(arg)+y, 
		u1, v1);
	SetVertex(&m_rect.v4, 
		(-width/2)*cos(arg)-(height/2)*sin(arg)+x, (-width/2)*sin(arg)+(height/2)*cos(arg)+y, 
		u1, v2);
}
void CPoligon::SetRect(float x, float y, float width, float height, float arg, 
		float u1, float v1, float u2, float v2,
		DWORD color1, DWORD color2, DWORD color3, DWORD color4)
{
	SetVertex(&m_rect.v1, 
		(width/2)*cos(arg)-(-height/2)*sin(arg)+x, (width/2)*sin(arg)+(-height/2)*cos(arg)+y, 
		u2, v1, color1);
	SetVertex(&m_rect.v2, 
		(width/2)*cos(arg)-(height/2)*sin(arg)+x, (width/2)*sin(arg)+(height/2)*cos(arg)+y, 
		u2, v2, color2);
	SetVertex(&m_rect.v3, 
		(-width/2)*cos(arg)-(-height/2)*sin(arg)+x, (-width/2)*sin(arg)+(-height/2)*cos(arg)+y, 
		u1, v1, color3);
	SetVertex(&m_rect.v4, 
		(-width/2)*cos(arg)-(height/2)*sin(arg)+x, (-width/2)*sin(arg)+(height/2)*cos(arg)+y, 
		u1, v2, color4);
}
//--------------------------------------------------------------------------------------//
/*--------------------------------テクスチャ管理クラス------------------------------*/
//--------------------------------------------------------------------------------------//
CTexture::CTexture(CGraphics *graphics, LPCWSTR file_name)
:m_graphics(graphics)
{
	// テクスチャの作成
	D3DXCreateTextureFromFileEx(
		graphics->GetDevice(), file_name, 
		D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
		D3DX_FILTER_LINEAR, D3DX_DEFAULT, 0, 
		NULL, NULL, &m_pTex);
}
CTexture::~CTexture(void)
{
	RELEASE(m_pTex);
}
//--------------------------------------------------------------------------------------//
/*---------------------------------グラフィッククラス------------------------------*/
//--------------------------------------------------------------------------------------//
CGraphics::CGraphics(HWND hWnd, BOOL bWindowed,bool bHWVertex,bool bREF,bool bVSync,int WindowWidth,int WindowHeight)
:m_pD3D(NULL),m_pD3DDev(NULL),m_pVertex(NULL),WINDOW_WIDTH(WindowWidth),WINDOW_HEIGHT(WindowHeight)
{
	Init(hWnd, bWindowed, bHWVertex, bREF, bVSync,WindowWidth, WindowHeight);
}

CGraphics::~CGraphics(void)
{
	UnInit();
}

BOOL CGraphics::Init(HWND hWnd, BOOL bWindowed,bool bHWVertex,bool bREF,bool bVSync,int WindowWidth,int WindowHeight)
{
	//Direct3Dの初期化
	if( !(m_pD3D = Direct3DCreate9( D3D_SDK_VERSION )) ) 
		return FALSE;

	D3DDISPLAYMODE d3ddm;
    if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
        return FALSE; 
	
	D3DPRESENT_PARAMETERS d3dpp;
		d3dpp.BackBufferWidth = WindowWidth;
		d3dpp.BackBufferHeight = WindowHeight;
		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferFormat = d3ddm.Format;//bWindowed? d3ddm.Format:D3DFMT_R5G6B5
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = NULL;
		d3dpp.Windowed = bWindowed;
		d3dpp.EnableAutoDepthStencil = FALSE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
		d3dpp.Flags = 0;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = bVSync? D3DPRESENT_INTERVAL_DEFAULT:D3DPRESENT_INTERVAL_IMMEDIATE;//強制的にFPSを60にするにはbWindowed? D3DPRESENT_INTERVAL_IMMEDIATE:D3DPRESENT_INTERVAL_DEFAULT
	/*D3DPRESENT_PARAMETERS d3dpp = {
		0,//バックバッファ幅
		0,//バックバッファ高さ
		D3DFMT_UNKNOWN,//画面フォーマット情報
		0,//バックバッファ数
		D3DMULTISAMPLE_NONE,//マルチサンプルをどうするか
		0,//マルチサンプルの品質
		D3DSWAPEFFECT_DISCARD,//スワップの際の処理
		NULL,//画面を描画するウィンドウハンドル
		TRUE,//スクリーンモードTRUE:ウィンドウFALSE:フルスクリーン
		0,//深度･ステンシルバッファの作成
		D3DFMT_UNKNOWN,//ステンシルバッファフォーマット
		0,//フルスクリーンでのリフレッシュレート
		0//スワップタイミング
	};*/

	//デバイスの作成
	if(bHWVertex)
	{
		if(bREF)
		{
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, 
				hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDev ) ) )
			{
				RELEASE(m_pD3D);
				return FALSE;
			}
		}
		else
		{
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
				hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDev ) ) )
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, 
				hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDev ) ) )
			{
				RELEASE(m_pD3D);
				return FALSE;
			}
		}
	}
	else
	{
		if(bREF)
		{
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, 
				hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDev ) ) )
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, 
				hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDev ) ) )
			{
				RELEASE(m_pD3D);
				return FALSE;
			}
		}
		else
		{
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
				hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDev ) ) )
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
				hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDev ) ) )
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, 
				hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDev ) ) )
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, 
				hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDev ) ) )
			{
				RELEASE(m_pD3D);
				return FALSE;
			}
		}
	}

	// 頂点バッファの作成
	if(FAILED(m_pD3DDev->CreateVertexBuffer(sizeof(RECTANGLE), D3DUSAGE_WRITEONLY, 
		FVF_CUSTOM, D3DPOOL_MANAGED, &m_pVertex, NULL)))
	{
		m_pD3DDev->Release(); 
		m_pD3D->Release();
		return 0;
	}

	// レンダリングステート
	m_pD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//αブレンド許可
	m_pD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャブレンド設定
	m_pD3DDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE	);
	m_pD3DDev->SetTextureStageState(0, D3DTSS_COLOROP,	 D3DTOP_MODULATE);
	m_pD3DDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE	);
	m_pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE	);
	m_pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAOP,	 D3DTOP_MODULATE);
	m_pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE	);

	return TRUE;
}

void CGraphics::UnInit()
{
	RELEASE(m_pD3DDev);
	RELEASE(m_pD3D);
	RELEASE(m_pVertex);
}

BOOL CGraphics::Draw(CPoligon* pPoligon,int num)
{
	// 頂点バッファをロックして頂点を書き込み
	void *pData;
	if(SUCCEEDED(m_pVertex->Lock(0, sizeof(RECTANGLE), (void**)&pData, 0)))
	{
		memcpy(pData, pPoligon->GetpRect(), sizeof(RECTANGLE));
		m_pVertex->Unlock();
	}else{
		return FALSE;
	}
	//テクスチャ設定
	m_pD3DDev->SetTexture(0, pPoligon->GetpCTex()->GetTex());
	// 描画
	m_pD3DDev->SetStreamSource(0, m_pVertex, 0, sizeof(CUSTOMVERTEX));
	m_pD3DDev->SetFVF(FVF_CUSTOM);
	for(int i=0;i<num;++i)
	{
		m_pD3DDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	return TRUE;
}

BOOL CGraphics::SetRenderState(RENDERTYPE render)
{
	switch(render)
	{
	case NORMAL:
		m_pD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//αブレンド許可
		m_pD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	case ADDITION:
		// レンダリングステート
		m_pD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//αブレンド許可
		m_pD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

