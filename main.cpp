//=================================================================================================
//                                                        
//　　　ゲームフレームワークメインプログラム[main.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.13          
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include"main.h"
#include<windows.h>
#include "Scene2D.h"

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================
#define CLASS_NAME			"サンプル"
#define WINDOW_NAME			"ウィンドウ表示"

//=================================================================================================
//		プロトタイプ宣言                                  
//=================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);         //ゲームロープ初期処理
void Uninit(void);                                                  //ゲームロープ終了処理
void Update(void);                                                  //ゲームロープ更新処理
void Draw(void);                                                    //ゲームロープ描画処理

//=================================================================================================
//　　　グローバル変数                                    
//=================================================================================================
LPDIRECT3D9        g_pD3D = NULL;                                   //DirectXインターフェース
LPDIRECT3DDEVICE9  g_pD3DDevice = NULL;                             //デバイスのIDirect3Device9インタフェース
static HWND g_hWnd;
CScene2D *g_Scene2D;

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================

//=================================================================================================
//　　　メイン関数                                        
//=================================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)					//int Main(void)と同じ
{
	//構造体宣言
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),								//構造体のサイズ
		CS_VREDRAW | CS_HREDRAW,						//スタイル
		WndProc,
		0,
		0,
		hInstance,
		NULL,											//アイコン
		LoadCursor(NULL, IDC_ARROW),					//カソル
		(HBRUSH)(COLOR_WINDOW + 1),						//背景
		NULL,											//メニューの設定なし
		CLASS_NAME,                                     //クラス名
		NULL                                            //ボタンなし
	};

	RegisterClassEx(&wcex);
	RECT wr = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT dr;                                            //デスクトップサイズ<ウインドウサイズ　？　0:ウインドウ
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);

	GetWindowRect(GetDesktopWindow(), &dr);

	//ウィンドハンドル型
	g_hWnd = CreateWindowEx(
		0,
		CLASS_NAME, 									//クラス名
		WINDOW_NAME,									//ウインドウのタイトル名
		(WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX) ^ WS_THICKFRAME,							//ウィンドスタイル    // WS_POPUP //fullscreen
		CW_USEDEFAULT,									//ウィンドの左上座標
		CW_USEDEFAULT,                                  //ウィンドの右下座標
		SCREEN_WIDTH,									//フレイムを含めたウィンドの幅
		SCREEN_HEIGHT,                                   //フレイムを含めたウィンドの高さ
		NULL,											//親がない
		NULL,											//メニューがない
		hInstance,
		NULL
	);

	//ウィンド表示
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	//メッセージループ
	MSG msg;											//メッセージを受け取る変数


														//ゲームロープ
	DWORD dwCurrentTime = timeGetTime();                       //今の時間
	DWORD dwFPSLastTime = 0;                                   //前のフレームの時間

															   //初期処理
	if (!Init(hInstance, g_hWnd, TRUE))
	{
		MessageBox(g_hWnd, "エラー", "初期が", MB_OK);
		return -1;
	}


	timeBeginPeriod(1);									      //分解能を設定

	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージ処理
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//時間の更新処理
			dwCurrentTime = timeGetTime();
			//ゲーム処理
			if ((dwCurrentTime - dwFPSLastTime) >= (1000 / 60))
			{
				dwFPSLastTime = dwCurrentTime;
				//更新処理
				Update();
				//描画処理
				Draw();



			}
		}
	}

	timeEndPeriod(1);									//分解能を戻す

	Uninit();                                           //後処理

														//終了 戻り値設定
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY: PostQuitMessage(0);										//ウインドウを閉じてのメッセージ
		break;



	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			//[ESC]キーが押された
			int nID = MessageBox(hWnd, "終了しますが？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);         //メッセージ
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
			break;
		}



		}
		break;

	case WM_RBUTTONDOWN:
		//マウスの右キーが押された
		MessageBox(g_hWnd, "マウスの右キー", "ボーダーメッセージタイトル", MB_OK);							//メッセージ
		break;

	case WM_CLOSE:
	{
		//終了メッセージ
		int nID = MessageBox(hWnd, "終了しますが？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);			//メッセージ
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;
	}

	default: break;                                     //他の場合はswitchに出し
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=================================================================================================
//　　　ゲームロープ初期処理
//=================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}


	//現在のデイスプレイモードを
	D3DDISPLAYMODE d3ddm;

	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
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
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &g_pD3DDevice)))
		{
			// REFモードで3Dデバイス作成
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &g_pD3DDevice)))
			{
				if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &g_pD3DDevice)))
				{
					// 3Dデバイス作成失敗(このグラフィックボードではDirectXが使えない)
					g_pD3D->Release();
					return false;
				}
			}
		}
	}
	
	g_Scene2D = new CScene2D();
	g_Scene2D->Init();

	return true;
}

//=================================================================================================
//　　　ゲームロープ終了処理
//=================================================================================================
void Uninit(void)
{
	SAFE_RELEASE(g_pD3DDevice);
	SAFE_RELEASE(g_pD3D);
	g_Scene2D->Uninit();
	delete g_Scene2D;
}

//=================================================================================================
//　　　ゲームロープ更新処理
//=================================================================================================
void Update(void)
{
	g_Scene2D->Update();
}

//=================================================================================================
//　　　ゲームロープ描画処理
//=================================================================================================
void Draw(void)
{
	//描画初期化
	g_pD3DDevice->Clear(
		0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(32, 64, 192, 100), 1.0f, 0    //色は白と黒選択ないほうが
	);

	//Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//ポリゴン描画
		g_Scene2D->Draw();
		//Presentの終了処理
		g_pD3DDevice->EndScene();
	}
	//Presentの終了処理
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


//=================================================================================================
//　　　D3DDeviceの伝達
//=================================================================================================
LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;                                            //D3DDeviceの伝達
}
