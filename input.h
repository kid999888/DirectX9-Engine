//=============================================================================
//
// ���͏��� [input.h]
// Author : 
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include<dinput.h>

//*********************************************************
// ���̓N���X
//*********************************************************
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInst, HWND hWnd);
	virtual void Uninit(void);
	virtual HRESULT Update(void) = 0;		// ---> �������z�֐���

protected:
	LPDIRECTINPUTDEVICE8		m_pDIDevice;		// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^
	static LPDIRECTINPUT8		m_pDInput;			// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
};

//*********************************************************
// �L�[�{�[�h���̓N���X
//*********************************************************
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
	static BYTE			m_aKeyState[256];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	static BYTE			m_aKeyStateTrigger[256];	// �g���K�[���[�N
	static BYTE			m_aKeyStateRelease[256];	// �����[�X���[�N
	static BYTE			m_aKeyStateRepeat[256];		// ���s�[�g���[�N
	static int			m_aKeyStateRepeatCnt[256];	// ���s�[�g�J�E���^
};

//*********************************************************
// �}�E�X���̓N���X
//*********************************************************
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

private:
	static DIMOUSESTATE2	m_mouseState;				// �}�E�X�̏�Ԃ��󂯎�郏�[�N
	static DIMOUSESTATE2	m_mouseStateTrigger;		// �g���K�[���[�N
	static POINT	m_posMouseWorld;			// �}�E�X�̃X�N���[�����W
};

//*********************************************************
// �W���C�p�b�h���̓N���X
//*********************************************************
class CInputJoypad : public CInput
{
public:
	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	HRESULT Update(void);

	// �L�[�̎��
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

	static DIJOYSTATE2		m_joypadState;					// �W���C�p�b�h��Ԃ��󂯎�郏�[�N
	static bool				m_aKeyState[KEY_MAX];			// �v���X���[�N
	static bool				m_aKeyStateTrigger[KEY_MAX];	// �g���K�[���[�N
	static bool				m_aKeyStateRelease[KEY_MAX];	// �����[�X���[�N
	static bool				m_aKeyStateRepeat[KEY_MAX];		// ���s�[�g���[�N
	static int				m_aKeyStateRepeatCnt[KEY_MAX];	// ���s�[�g�J�E���^
};

#endif