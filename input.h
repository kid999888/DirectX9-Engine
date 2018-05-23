//=================================================================================================
//                                                        
//　　　入力処理[input.h]                   
//      Author:王暁晨(AT-12B-242 04)　2017.06.05   
//                                                        
//=================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include<Windows.h>
#include<dinput.h>

//=================================================================================================
//		マクロ定義
//=================================================================================================
#define DIRECTINPUT_VERSION (0x0800)
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define	LIMIT_COUNT_REPEAT	(20)	// リピートカウントリミッター

//=================================================================================================
//		プロトタイプ宣言
//=================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);							//入力処理の初期化
void UninitKeyboard(void);														//キーボードの終了処理
void UpdateKeyboard(void);														//キーボードの更新処理
bool GetKeyboardPress(int nKey);												//キーボードのプレス状態を取得
bool GetKeyboardTrigger(int nKey);												//キーボードのトリガー状態を取得
bool GetKeyboardRepeat(int nKey);												//キーボードのリピート状態を取得
bool GetKeyboardRelease(int nKey);												//キーボードのリリ－ス状態を取得

/*
//=================================================================================================
//　　　入力処理クラス                                       
//=================================================================================================
class CInput
{
public:
	CInput();											//入力処理コンストラクタ
	~CInput();											//入力処理デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//入力処理の初期化
	void Uninit(void);									//キーボードの終了処理
	void Update(void);									//キーボードの更新処理
	bool GetPress(int nKey);							//キーボードのプレス状態を取得
	bool GetTrigger(int nKey);							//キーボードのトリガー状態を取得
	bool GetRepeat(int nKey);							//キーボードのリピート状態を取得
	bool GetRelease(int nKey);							//キーボードのリリ－ス状態を取得

private:
	LPDIRECTINPUT8			m_pInput;							// DirectInputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8	m_pDevKeyboard;						// 入力デバイス(キーボード)へのポインタ
	BYTE					m_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
	BYTE					m_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
	BYTE					m_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク
	BYTE					m_aKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート情報ワーク
	int						m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ
};
*/

#endif		//_INPUT_H_