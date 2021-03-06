//=================================================================================================
//                                                        
//　　　入力処理クラスプログラム[input.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.23      
//                                                        
//=================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=================================================================================================
//　　　マクロ定義                                        
//=================================================================================================
#include "main.h"
#define DIRECTINPUT_VERSION 0x0800
#include<dinput.h>


//=================================================================================================
//　　　入力クラス
//=================================================================================================
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInst, HWND hWnd);
	virtual void Uninit(void);
	virtual HRESULT Update(void) = 0;		// ---> 純粋仮想関数化

protected:
	LPDIRECTINPUTDEVICE8		m_pDIDevice;		// IDirectInputDevice8インターフェースへのポインタ
	static LPDIRECTINPUT8		m_pDInput;			// IDirectInput8インターフェースへのポインタ
};

//=================================================================================================
//　　　キーボード入力クラス
//=================================================================================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	HRESULT Update(void);

	static BOOL GetKeyPress(int nKey);
	static BOOL GetKeyTrigger(int nKey);
	static BOOL GetKeyRelease(int nKey);
	static BOOL GetKeyRepeat(int nKey);
	void FlushKeyTrigger(int nKey);

private:
	static BYTE			m_aKeyState[256];			// キーボードの状態を受け取るワーク
	static BYTE			m_aKeyStateTrigger[256];	// トリガーワーク
	static BYTE			m_aKeyStateRelease[256];	// リリースワーク
	static BYTE			m_aKeyStateRepeat[256];		// リピートワーク
	static int			m_aKeyStateRepeatCnt[256];	// リピートカウンタ
};

//=================================================================================================
//　　　マウス入力クラス
//=================================================================================================
class CInputMouse : public CInput
{
public:
	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	HRESULT Update(void);

	static BOOL GetLeftPress(void);
	static BOOL GetLeftTrigger(void);
	static BOOL GetRightPress(void);
	static BOOL GetRightTrigger(void);
	static BOOL GetCenterPress(void);
	static BOOL GetCenterTrigger(void);
	static LONG GetAxisX(void);
	static LONG GetAxisY(void);
	static LONG GetAxisZ(void);
	static POINT *GetPosWorld(void){ return &m_posMouseWorld; }
	static POINT *GetPosUserScreen(void) { return &m_posMouseUserScreen; }

private:
	static DIMOUSESTATE2	m_mouseState;				// マウスの状態を受け取るワーク
	static DIMOUSESTATE2	m_mouseStateTrigger;		// トリガーワーク
	static POINT	m_posMouseWorld;					// マウスのスクリーン座標
	static POINT	m_posMouseUserScreen;				// マウスのユーザースクリーン座標
};

//=================================================================================================
//　　　ジョイパッド入力クラス
//=================================================================================================
class CInputJoypad : public CInput
{
public:
	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	HRESULT Update(void);

	// キーの種類
	typedef enum
	{
		KEY_LEFT = 0,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_JUMP,
		KEY_SHOT,
		KEY_TURN_LEFT,
		KEY_TURN_RIGHT,
		KEY_TURN_UP,
		KEY_TURN_DOWN,
		KEY_START,
		KEY_SELECT,
		KEY_MAX
	} KEY;

	static bool GetKeyPress(KEY key);
	static bool GetKeyTrigger(KEY key);
	static bool GetKeyRelease(KEY key);
	static bool GetKeyRepeat(KEY key);

private:
	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);
	static BOOL CALLBACK EnumAxesCallback(const LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
	void SetKeyState(void);

	static DIJOYSTATE2		m_joypadState;					// ジョイパッド状態を受け取るワーク
	static bool				m_aKeyState[KEY_MAX];			// プレスワーク
	static bool				m_aKeyStateTrigger[KEY_MAX];	// トリガーワーク
	static bool				m_aKeyStateRelease[KEY_MAX];	// リリースワーク
	static bool				m_aKeyStateRepeat[KEY_MAX];		// リピートワーク
	static int				m_aKeyStateRepeatCnt[KEY_MAX];	// リピートカウンタ
};

#endif