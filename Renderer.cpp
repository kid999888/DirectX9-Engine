//=================================================================================================
//                                                        
//　　　DirectX初期化クラスプログラム[Renderer.cpp]
//      Author:王暁晨(AT-13A-281 04)　2018.04.25      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include "Renderer.h"

//=================================================================================================
//　　　実体定義
//=================================================================================================
LPDIRECT3D9 CRenderer::m_pD3D = NULL;
LPDIRECT3DDEVICE9 CRenderer::m_pD3DDevice = NULL;
LPD3DXEFFECT CRenderer::m_pEffect = NULL;
#if defined(DEBUG)
D3DPRESENT_PARAMETERS CRenderer::m_d3dpp;
#endif//defined(DEBUG)

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
	D3DPRESENT_PARAMETERS d3dpp;										//デバイスをつくっみ
	ZeroMemory(&d3dpp, sizeof(d3dpp));									//d3dppのメモリに初期化
	d3dpp.BackBufferWidth = SCREEN_WIDTH;								//スクリーンの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;								//スクリーンの高さ
	d3dpp.BackBufferFormat = d3ddm.Format;								//バック・バッファのフォーマット(ディスプレイ・フォーマットの指定ｖ)
	d3dpp.BackBufferCount = 1;											//前のものと後ろのもの交換する
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//スワップ・エフェクト
	d3dpp.EnableAutoDepthStencil = TRUE;								//3D描画モード
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;							//
	d3dpp.Windowed = bWindow;											//ウインドウモードを指定
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//Full screen のFPSコントロール
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//描画FPS固定

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
#if defined(DEBUG)
	//DirectXプレゼンテーションパラメータのcopy
	memcpy(&m_d3dpp, &d3dpp, sizeof(d3dpp));

	//ImGui処理
	//Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplDX9_Init(hWnd, m_pD3DDevice);

	//Setup style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//io.Fonts->AddFontFromFileTTF("Data\\Fonts\\msmincho.ttc", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msmincho.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);
#endif//defined(DEBUG)

	return true;
}

//=================================================================================================
//　　　DirectX初期化クラス終了処理                                       
//=================================================================================================
void CRenderer::Uninit(void)
{
#if defined(DEBUG)
	//ImGui終了処理
	ImGui_ImplDX9_Shutdown();
	ImGui::DestroyContext();
#endif//defined(DEBUG)

	//DirectXデバイス終了処理
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
#if defined(DEBUG)
	HRESULT hr;
	//Presentの終了処理
	hr = m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	//ImGui処理(Handle loss of D3D9 device)
	if (hr == D3DERR_DEVICELOST && m_pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		m_pD3DDevice->Reset(&m_d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
#else//defined(DEBUG)
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
#endif//defined(DEBUG)
}

//=================================================================================================
//　　　D3DDeviceの伝達                                    
//=================================================================================================
LPDIRECT3DDEVICE9 CRenderer::GetD3DDevice(void)
{
	return m_pD3DDevice;
}

//=================================================================================================
//　　　D3DEffectの伝達                                    
//=================================================================================================
LPD3DXEFFECT CRenderer::GetD3DEffect(void)
{
	return m_pEffect;
}

//=================================================================================================
//　　　D3DXEFFECTの設定                                    
//=================================================================================================
void CRenderer::SetD3DEffect(LPD3DXEFFECT D3DEffect)
{
	m_pEffect = D3DEffect;
}

#if defined(DEBUG)
//=================================================================================================
//　　　D3DPARAMETERSの伝達                                   
//=================================================================================================
D3DPRESENT_PARAMETERS CRenderer::GetD3DPARAMETERS(void)
{
	return m_d3dpp;
}

//=================================================================================================
//　　　D3DPARAMETERSのBackBufferの設定                                  
//=================================================================================================
void CRenderer::SetBackBuffer(LPARAM lParam)
{
	m_d3dpp.BackBufferWidth = LOWORD(lParam);
	m_d3dpp.BackBufferHeight = HIWORD(lParam);
}
#endif//defined(DEBUG)
