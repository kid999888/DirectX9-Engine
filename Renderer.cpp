//=================================================================================================
//                                                        
//　　　DirectX初期化クラスプログラム[Scene.cpp]
//      Author:王暁晨(AT-13A-281 04)　2018.04.25      
//                                                        
//=================================================================================================
#include"Renderer.h"

LPDIRECT3D9 CRenderer::m_pD3D = NULL;
LPDIRECT3DDEVICE9 CRenderer::m_pD3DDevice = NULL;

//=================================================================================================
//　　　DirectX初期化クラス初期処理                                     
//=================================================================================================
bool CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	//Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のデイスプレイモードを
	D3DDISPLAYMODE d3ddm;

	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;

	}

	//デバイスのプレゼンテーション
	D3DPRESENT_PARAMETERS d3dpp;                                      //デバイスをつくっみ
	ZeroMemory(&d3dpp, sizeof(d3dpp));                                //d3dppのメモリに初期化
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                             //スクリーンの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                           //スクリーンの高さ
	d3dpp.BackBufferFormat = d3ddm.Format;                            //バック・バッファのフォーマット(ディスプレイ・フォーマットの指定ｖ)
	d3dpp.BackBufferCount = 1;                                        //前のものと後ろのもの交換する
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                         //スワップ・エフェクト
	d3dpp.EnableAutoDepthStencil = TRUE;                              //3D描画モード
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                        //
	d3dpp.Windowed = bWindow;                                         //ウインドウモードを指定
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;       //Full screen のFPSコントロール
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;         //描画FPS固定

	//デバイスオブジェクトの生成
	//[デバイス作成制御]<描画>と<頂点処理>を
	// HALモードで3Dデバイス作成
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &m_pD3DDevice)))
		{
			// REFモードで3Dデバイス作成
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &m_pD3DDevice)))
			{
				if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &m_pD3DDevice)))
				{
					// 3Dデバイス作成失敗(このグラフィックボードではDirectXが使えない)
					m_pD3D->Release();
					return false;
				}
			}
		}
	}
	return true;
}

//=================================================================================================
//　　　DirectX初期化クラス終了処理                                       
//=================================================================================================
void CRenderer::Uninit(void)
{
	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3D);
}

//=================================================================================================
//　　　DirectX初期化クラス描画開始処理                                     
//=================================================================================================
void CRenderer::DrawBegin(void)
{
	//描画初期化
	m_pD3DDevice->Clear(
		0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(32, 64, 192, 100), 1.0f, 0    //色は白と黒選択ないほうが
	);
}

//=================================================================================================
//　　　DirectX初期化クラス描画終了処理                                    
//=================================================================================================
void CRenderer::DrawEnd(void)
{
	//Presentの終了処理
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=================================================================================================
//　　　D3DDeviceの伝達                                    
//=================================================================================================
LPDIRECT3DDEVICE9 CRenderer::GetD3DDevice(void)
{
	return m_pD3DDevice;
}
