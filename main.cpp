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
#include"Manager.h"
#include"input.h"
#include"DebugGUI.h"
#include <crtdbg.h>

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================
#define CLASS_NAME			"サンプル"
#define WINDOW_NAME			"ウィンドウ表示"

//=================================================================================================
//		プロトタイプ宣言                                  
//=================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=================================================================================================
//　　　グローバル変数                                    
//=================================================================================================
float g_fStartWidth = 0.0f;
float g_fStartHeight = 0.0f;
RECT g_UserRectSize;
static HWND g_hWnd;
#if defined(DEBUG)
//ImGUI実体コントローラー
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif//defined(DEBUG)

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================

//=================================================================================================
//　　　静的インスタンス                           
//=================================================================================================
CInputKeyboard* g_pInputKeyboard;
CInputMouse* g_pInputMouse;
CInputJoypad* g_pInputJoypad;

//=================================================================================================
//　　　メイン関数                                        
//=================================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)					//int Main(void)と同じ
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(0);				//メモリリークの検査、0はエラー帰るのブロックナンバー。

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
	RECT dr;                                          //デスクトップサイズ<ウインドウサイズ　？　0:ウインドウ
	AdjustWindowRect(&wr, (WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX) ^ WS_THICKFRAME, false);

	GetWindowRect(GetDesktopWindow(), &dr);
	g_fStartWidth = (dr.right - wr.right) / 2;
	g_fStartHeight = (dr.bottom - wr.bottom) / 2;

	

	//ウィンドハンドル型
	g_hWnd = CreateWindowEx(
		0,
		CLASS_NAME, 									//クラス名
		WINDOW_NAME,									//ウインドウのタイトル名
		(WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX) ^ WS_THICKFRAME,							//ウィンドスタイル    // WS_POPUP //fullscreen //(WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX) ^ WS_THICKFRAME
		g_fStartWidth,									//ウィンドの左上座標X
		g_fStartHeight,                                  //ウィンドの左上座標Y
		SCREEN_WIDTH,									//フレイムを含めたウィンドの幅
		SCREEN_HEIGHT,                                   //フレイムを含めたウィンドの高さ
		NULL,											//親がない
		NULL,											//メニューがない
		hInstance,
		NULL
	);

	//ユーザー区域取得、leftユーザー区域開始Y座標、topユーザー区域開始X座標、rightユーザー区域幅、bottomユーザー区域高さ
	GetClientRect(g_hWnd, &g_UserRectSize);
	g_UserRectSize.left = g_fStartWidth - wr.left;
	g_UserRectSize.top = g_fStartHeight - wr.top;
	
	

	//ウィンド表示
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	

	//メッセージループ
	MSG msg;											//メッセージを受け取る変数


	//ゲームロープ
	DWORD dwCurrentTime = timeGetTime();                       //今の時間
	DWORD dwFPSLastTime = 0;                                   //前のフレームの時間




	//初期処理
	if (!CManager::Init(g_hWnd, TRUE))
	{
		MessageBox(g_hWnd, "エラー", "初期化エラー", MB_OK);
		return -1;
	}
	//入力処理の初期化
	/*InitKeyboard(hInstance, g_hWnd);*/
	g_pInputKeyboard = new CInputKeyboard;
	g_pInputKeyboard->Init(hInstance, g_hWnd);
	g_pInputMouse = new CInputMouse;
	g_pInputMouse->Init(hInstance, g_hWnd);
	g_pInputJoypad = new CInputJoypad;
	g_pInputJoypad->Init(hInstance, g_hWnd);

#if defined(DEBUG)
	//DebugGUI初期処理
	CDebugGUI::Init();
#endif//defined(DEBUG)

	timeBeginPeriod(1);											//分解能を設定

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

#if defined(DEBUG)
				//ImGUI処理
				CDebugGUI::UpdateWindow();
#endif//defined(DEBUG)

				//更新処理
				CManager::Update();
				//入力処理の更新処理
				/*UpdateKeyboard();*/						
				g_pInputKeyboard->Update();
				g_pInputMouse->Update();
				g_pInputJoypad->Update();
				//描画処理
				CManager::Draw();


			}
		}
	}

	timeEndPeriod(1);									//分解能を戻す

	CManager::Uninit();									//後処理
	//入力処理の終了処理
	/*UninitKeyboard();*/									
	g_pInputKeyboard->Uninit();
	delete g_pInputKeyboard;
	g_pInputMouse->Uninit();
	delete g_pInputMouse;
	g_pInputJoypad->Uninit();
	delete g_pInputJoypad;

	//終了 戻り値設定
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#if defined(DEBUG)
	//ImGuiのWindowsandler生成
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
#endif//defined(DEBUG)

	switch (uMsg)
	{
#if defined(DEBUG)
	case WM_SIZE:
		if (CRenderer::GetD3DDevice() != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			CRenderer::SetBackBuffer(lParam);
			HRESULT hr = CRenderer::GetD3DDevice()->Reset(&CRenderer::GetD3DPARAMETERS());
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		return 0;
#endif//defined(DEBUG)
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
	//マウスの表示設定
	case WM_SETCURSOR:
	{
		if (LOWORD(lParam) == HTCLIENT)
		{
			//SetCursor(NULL);								//マウスの消す
			CRenderer::GetD3DDevice()->ShowCursor(true);	//falseはマウスを表示されない

			return true;
		}
		break;
	}
	case WM_NCPAINT:
	{
		HDC hdc;
		hdc = GetDCEx(hWnd, (HRGN)wParam, DCX_WINDOW | DCX_INTERSECTRGN);
		// Paint into this DC
		InvalidateRect(hWnd, 0, false);
		UpdateWindow(hWnd);

		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_PAINT:
	{
		InvalidateRect(hWnd, 0, false);
		UpdateWindow(hWnd);
		break;
	}
	default: break;                                     //他の場合はswitchに出し
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

RECT GetUserWindowsSize(void)
{
	return g_UserRectSize;
}
