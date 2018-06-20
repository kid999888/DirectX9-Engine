//=================================================================================================
//                                                        
//　　　入力処理[input.cpp]                   
//      Author:王暁晨(AT-12B-242 04)　2017.06.05   
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include "input.h"

//=================================================================================================
//		マクロ定義
//=================================================================================================

//=================================================================================================
//		グローバル変数
//=================================================================================================
LPDIRECTINPUT8			g_pInput = NULL;					// DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;				// 入力デバイス(キーボード)へのポインタ
BYTE					g_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク
BYTE					g_aKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート情報ワーク
int						g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

//=================================================================================================
//		入力処理の初期化
//=================================================================================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	hWnd = hWnd;
	//UNREFERENCED_PARAMETER(hWnd);
	if(g_pInput == NULL)
	{
		// DirectInputオブジェクトの作成
		if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
										IID_IDirectInput8, (void**)&g_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=================================================================================================
//		入力処理の終了処理
//=================================================================================================
void UninitInput(void)
{
	if(g_pInput != NULL)
	{// DirectInputオブジェクトの開放
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=================================================================================================
//		入力処理の更新処理
//=================================================================================================
void UpdateInput(void)
{

}

//=================================================================================================
//		キーボードの初期化
//=================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// 入力処理の初期化
	if(FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInputオブジェクトが作れねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// デバイスの作成
	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// データフォーマットを設定
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))    //FOREGROUNDこのプログラムだけ、BACKGROUND全部のプログラムキーを入力できる
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//=================================================================================================
//		キーボードの終了処理
//=================================================================================================
void UninitKeyboard(void)
{
	if(g_pDevKeyboard != NULL)
	{// 入力デバイス(キーボード)の開放
		// キーボードへのアクセス権を開放(入力制御終了)
		g_pDevKeyboard->Unacquire();

		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// 入力処理の終了処理
	UninitInput();
}

//=================================================================================================
//		キーボードの更新処理
//=================================================================================================
void UpdateKeyboard(void)
{
	//一フレム内
	BYTE aKeyState[NUM_KEY_MAX];

	// デバイスからデータを取得
	if(SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for(int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// キートリガー・リリース情報を生成
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];             //押した瞬間
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aKeyState[nCnKey];            //離す瞬間

			// キーリピート情報を生成
			if(aKeyState[nCnKey])
			{
				if(g_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					g_aKeyStateRepeatCnt[nCnKey]++;
					if(g_aKeyStateRepeatCnt[nCnKey] == 1
					|| g_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{// キーを押し始めた最初のフレーム、または一定時間経過したらキーリピート情報ON
						g_aKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
					}
					else
					{
						g_aKeyStateRepeat[nCnKey] = 0;
					}
				}
			}
			else
			{
				g_aKeyStateRepeatCnt[nCnKey] = 0;
				g_aKeyStateRepeat[nCnKey] = 0;
			}

			// キープレス情報を保存
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		g_pDevKeyboard->Acquire();
	}
}

//=================================================================================================
//		キーボードのプレス状態を取得
//=================================================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true: false;
}

//=================================================================================================
//		キーボードのトリガー状態を取得
//=================================================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true: false;
}

//=================================================================================================
//		キーボードのリピート状態を取得
//=================================================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true: false;
}

//=================================================================================================
//		キーボードのリリ－ス状態を取得
//=================================================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true: false;
}

/*
CInput::CInput()
{
	m_pInput = NULL;					// DirectInputオブジェクトへのポインタ
	m_pDevKeyboard = NULL;				// 入力デバイス(キーボード)へのポインタ
}

CInput::~CInput()
{
}

HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// 入力処理の初期化
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInputオブジェクトが作れねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// デバイスの作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))    //FOREGROUNDこのプログラムだけ、BACKGROUND全部のプログラムキーを入力できる
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevKeyboard->Acquire();

	return S_OK;
}

void CInput::Uninit(void)
{
	if (m_pDevKeyboard != NULL)
	{// 入力デバイス(キーボード)の開放
	 // キーボードへのアクセス権を開放(入力制御終了)
		m_pDevKeyboard->Unacquire();

		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	// 入力処理の終了処理
	Uninit();
}

void CInput::Update(void)
{
	//一フレム内
	BYTE aKeyState[NUM_KEY_MAX];

	// デバイスからデータを取得
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// キートリガー・リリース情報を生成
			m_aKeyStateTrigger[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];             //押した瞬間
			m_aKeyStateRelease[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & m_aKeyState[nCnKey];            //離す瞬間

																													 // キーリピート情報を生成
			if (aKeyState[nCnKey])
			{
				if (m_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					m_aKeyStateRepeatCnt[nCnKey]++;
					if (m_aKeyStateRepeatCnt[nCnKey] == 1
						|| m_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{// キーを押し始めた最初のフレーム、または一定時間経過したらキーリピート情報ON
						m_aKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
					}
					else
					{
						m_aKeyStateRepeat[nCnKey] = 0;
					}
				}
			}
			else
			{
				m_aKeyStateRepeatCnt[nCnKey] = 0;
				m_aKeyStateRepeat[nCnKey] = 0;
			}

			// キープレス情報を保存
			m_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		m_pDevKeyboard->Acquire();
	}
}

bool CInput::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

bool CInput::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

bool CInput::GetRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

bool CInput::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
*/
