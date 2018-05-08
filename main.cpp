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
#include "Scene3D.h"
#include "SceneModel.h"

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
static HWND g_hWnd;

CScene2D		*g_Scene2D;
CScene3D		*g_Scene3D;
CSceneModel		*g_SceneModel;
CCamera			*g_Camera;
CLight			*g_Light;

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
	//
	case WM_SETCURSOR:
	{
		if (LOWORD(lParam) == HTCLIENT)
		{
			SetCursor(NULL);
			CRenderer::GetD3DDevice()->ShowCursor(false);

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

//=================================================================================================
//　　　ゲームロープ初期処理
//=================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//DirectX初期化クラス初期処理
	CRenderer::Init(hWnd, bWindow);
	g_Camera = new CCamera();
	g_Light = new CLight();
	g_Scene2D = new CScene2D();
	g_Scene2D->Init();
	g_Scene3D = new CScene3D();
	g_Scene3D->Init();
	g_SceneModel = new CSceneModel();
	g_SceneModel->Init();
	
	return true;
}

//=================================================================================================
//　　　ゲームロープ終了処理
//=================================================================================================
void Uninit(void)
{
	delete g_Camera;
	delete g_Light;
	g_Scene2D->Uninit();
	delete g_Scene2D;
	g_Scene3D->Uninit();
	delete g_Scene3D;
	g_SceneModel->Uninit();
	delete g_SceneModel;
	//DirectX初期化クラス終了処理
	CRenderer::Uninit();
}

//=================================================================================================
//　　　ゲームロープ更新処理
//=================================================================================================
void Update(void)
{
	g_Scene2D->Update();
	g_Scene3D->Update();
	g_SceneModel->Update();
}

//=================================================================================================
//　　　ゲームロープ描画処理
//=================================================================================================
void Draw(void)
{
	//DirectX初期化クラス描画開始処理 
	CRenderer::DrawBegin();

	//Direct3Dによる描画の開始
	if (SUCCEEDED(CRenderer::GetD3DDevice()->BeginScene()))
	{
		g_Camera->Update();
		g_Light->Update();
		//2Dポリゴン描画
		g_Scene2D->Draw();
		//3Dポリゴン描画
		g_Scene3D->Draw();
		//3Dポリゴン描画
		g_SceneModel->Draw();
		//Presentの終了処理
		CRenderer::GetD3DDevice()->EndScene();
	}
	//DirectX初期化クラス描画終了処理 
	CRenderer::DrawEnd();
}
