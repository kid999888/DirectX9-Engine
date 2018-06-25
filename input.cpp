//=============================================================================
//
//		���͏��� [input.cpp]
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.16
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		JOY_MIN_X		(-256)		// �w���ŏ��l
#define		JOY_MAX_X		(256)		// �w���ő�l
#define		JOY_MIN_Y		(-256)		// �x���ŏ��l
#define		JOY_MAX_Y		(256)		// �x���ő�l

//=================================================================================================
//�@�@�@���̒�`
//=================================================================================================
LPDIRECTINPUT8		CInput::m_pDInput = NULL;			// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
BYTE CInputKeyboard::m_aKeyState[256];
BYTE CInputKeyboard::m_aKeyStateTrigger[256];
BYTE CInputKeyboard::m_aKeyStateRelease[256];
BYTE CInputKeyboard::m_aKeyStateRepeat[256];
int CInputKeyboard::m_aKeyStateRepeatCnt[256];
DIMOUSESTATE2 CInputMouse::m_mouseState;
DIMOUSESTATE2 CInputMouse::m_mouseStateTrigger;
POINT CInputMouse::m_posMouseWorld;
DIJOYSTATE2 CInputJoypad::m_joypadState;
bool CInputJoypad::m_aKeyState[KEY_MAX];
bool CInputJoypad::m_aKeyStateTrigger[KEY_MAX];
bool CInputJoypad::m_aKeyStateRelease[KEY_MAX];
bool CInputJoypad::m_aKeyStateRepeat[KEY_MAX];
int CInputJoypad::m_aKeyStateRepeatCnt[KEY_MAX];

//=============================================================================
// CInput�R���X�g���X�^
//=============================================================================
CInput::CInput()
{
	m_pDIDevice = NULL;
}

//=============================================================================
// CInput�f�X�g���X�^
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// ���͏����̏���������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr = S_FALSE;

	// DirectInput�I�u�W�F�N�g�̍쐬
	if(!m_pDInput)
	{
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&m_pDInput, NULL);
	}

	return hr;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void CInput::Uninit(void)
{
	if(m_pDIDevice)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		m_pDIDevice->Unacquire();

		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}

	if(m_pDInput)
	{// DirectInput�I�u�W�F�N�g�̊J��
		m_pDInput->Release();
		m_pDInput = NULL;
	}
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
#if 0	// ---> �������z�֐���
HRESULT CInput::Update(void)
{
	return S_OK;
}
#endif

//=============================================================================
// CInputKeyboard�R���X�g���X�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	// �e���[�N�̃N���A
	ZeroMemory(m_aKeyState, sizeof m_aKeyState);
	ZeroMemory(m_aKeyStateTrigger, sizeof m_aKeyStateTrigger);
	ZeroMemory(m_aKeyStateRelease, sizeof m_aKeyStateRelease);
	ZeroMemory(m_aKeyStateRepeat, sizeof m_aKeyStateRepeat);
	ZeroMemory(m_aKeyStateRepeatCnt, sizeof m_aKeyStateRepeatCnt);
}

//=============================================================================
// CInputKeyboard�f�X�g���X�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// �L�[�{�[�h�̏���������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// ���͏����̏�����
	CInput::Init(hInst, hWnd);

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL);
	if(FAILED(hr) || m_pDIDevice == NULL)
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// m_pDIDevice�A�N�Z�X�����l��(���͐���J�n)
	m_pDIDevice->Acquire();

	return hr;
}

//=============================================================================
// �L�[�{�[�h���͏����̊J��
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// ���͏����̊J��
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
HRESULT CInputKeyboard::Update(void)
{
	HRESULT hr;
	BYTE aKeyState[256];

	if(!m_pDIDevice)
	{
		return S_FALSE;
	}

	// �f�o�C�X����f�[�^���擾
	hr = m_pDIDevice->GetDeviceState(sizeof(aKeyState), aKeyState);
	if(SUCCEEDED(hr))
	{
		for(int nCntKey = 0; nCntKey < 256; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			m_aKeyStateRepeat[nCntKey] = m_aKeyStateTrigger[nCntKey];

			if(aKeyState[nCntKey])
			{
				m_aKeyStateRepeatCnt[nCntKey]++;
				if(m_aKeyStateRepeatCnt[nCntKey] >= 20)
				{
					m_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
				}
			}
			else
			{
				m_aKeyStateRepeatCnt[nCntKey] = 0;
				m_aKeyStateRepeat[nCntKey] = 0;
			}

			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDIDevice->Acquire();
	}

	return hr;
}

//=============================================================================
// �L�[�{�[�h�f�[�^�擾(�v���X)
//=============================================================================
BOOL CInputKeyboard::GetKeyPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �L�[�{�[�h�f�[�^�擾(�g���K�[)
//=============================================================================
BOOL CInputKeyboard::GetKeyTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �L�[�{�[�h�f�[�^�擾(�����[�X)
//=============================================================================
BOOL CInputKeyboard::GetKeyRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �L�[�{�[�h�f�[�^�擾(���s�[�g)
//=============================================================================
BOOL CInputKeyboard::GetKeyRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �L�[�{�[�h�f�[�^�폜(�g���K�[)
//=============================================================================
void CInputKeyboard::FlushKeyTrigger(int nKey)
{
	m_aKeyStateTrigger[nKey] = 0;
}

//=============================================================================
// CInputMouse�R���X�g���X�^
//=============================================================================
CInputMouse::CInputMouse()
{
	ZeroMemory(&m_mouseState, sizeof(m_mouseState));
	ZeroMemory(&m_mouseStateTrigger, sizeof(m_mouseStateTrigger));
}

//=============================================================================
// CInputMouse�f�X�g���X�^
//=============================================================================
CInputMouse::~CInputMouse()
{
}

//=============================================================================
// �}�E�X�̏�����
//=============================================================================
HRESULT CInputMouse::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// ���͏����̏�����
	CInput::Init(hInst, hWnd);

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIDevice, NULL);
	if(FAILED(hr) || m_pDIDevice == NULL)
	{
		MessageBox(hWnd, "�}�E�X���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = m_pDIDevice->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�o�C�X�̐ݒ�
	{
		DIPROPDWORD dipdw;

		dipdw.diph.dwSize = sizeof(dipdw);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = DIPROPAXISMODE_REL;

		hr = m_pDIDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDIDevice->Acquire();

	return hr;
}

//=============================================================================
// �}�E�X���͏����̊J��
//=============================================================================
void CInputMouse::Uninit(void)
{
	// ���͏����̊J��
	CInput::Uninit();
}

//=============================================================================
// �}�E�X���͏����X�V
//=============================================================================
HRESULT CInputMouse::Update(void)
{
	HRESULT hr;
	DIMOUSESTATE2 mouseState;

	if(!m_pDIDevice)
	{
		return S_FALSE;
	}

	// �f�o�C�X����f�[�^���擾
	hr = m_pDIDevice->GetDeviceState(sizeof(mouseState), &mouseState);
	if(SUCCEEDED(hr))
	{
		m_mouseStateTrigger.lX = ((m_mouseState.lX ^ mouseState.lX) & mouseState.lX);
		m_mouseStateTrigger.lY = ((m_mouseState.lY ^ mouseState.lY) & mouseState.lY);
		m_mouseStateTrigger.lZ = ((m_mouseState.lZ ^ mouseState.lZ) & mouseState.lZ);
		for(int nCntKey = 0; nCntKey < 8; nCntKey++)
		{
			m_mouseStateTrigger.rgbButtons[nCntKey]
				= ((m_mouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & mouseState.rgbButtons[nCntKey]);
		}

		m_mouseState = mouseState;

		// �X�N���[�����W���擾
		GetCursorPos(&m_posMouseWorld);
	}
	else
	{
		m_pDIDevice->Acquire();
	}

	return hr;
}

//=============================================================================
// �}�E�X�f�[�^�擾(���v���X)
//=============================================================================
BOOL CInputMouse::GetLeftPress(void)
{
	return (m_mouseState.rgbButtons[0] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �}�E�X�f�[�^�擾(���g���K�[)
//=============================================================================
BOOL CInputMouse::GetLeftTrigger(void)
{
	return (m_mouseStateTrigger.rgbButtons[0] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�E�v���X)
//=============================================================================
BOOL CInputMouse::GetRightPress(void)
{
	return (m_mouseState.rgbButtons[1] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�E�g���K�[)
//=============================================================================
BOOL CInputMouse::GetRightTrigger(void)
{
	return (m_mouseStateTrigger.rgbButtons[1] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�����v���X)
//=============================================================================
BOOL CInputMouse::GetCenterPress(void)
{
	return (m_mouseState.rgbButtons[2] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�����g���K�[)
//=============================================================================
BOOL CInputMouse::GetCenterTrigger(void)
{
	return (m_mouseStateTrigger.rgbButtons[2] & 0x80) ? TRUE: FALSE;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�w���ړ�)
//=============================================================================
LONG CInputMouse::GetAxisX(void)
{
	return m_mouseState.lX;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�x���ړ�)
//=============================================================================
LONG CInputMouse::GetAxisY(void)
{
	return m_mouseState.lY;
}

//=============================================================================
// �}�E�X�f�[�^�擾(�y���ړ�)
//=============================================================================
LONG CInputMouse::GetAxisZ(void)
{
	return m_mouseState.lZ;
}

//=============================================================================
// CInputJoypad�R���X�g���X�^
//=============================================================================
CInputJoypad::CInputJoypad()
{
}

//=============================================================================
// CInputJoypad�f�X�g���X�^
//=============================================================================
CInputJoypad::~CInputJoypad()
{
}

//=============================================================================
// �W���C�p�b�h�̏�����
//=============================================================================
HRESULT CInputJoypad::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// ���͏����̏�����
	CInput::Init(hInst, hWnd);

	hr = m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, CInputJoypad::EnumJoyCallback, this, DIEDFL_ATTACHEDONLY);
	if(FAILED(hr) || m_pDIDevice == NULL)
	{
//		MessageBox(hWnd, "�W���C�p�b�h���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = m_pDIDevice->SetDataFormat(&c_dfDIJoystick2);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�W���C�p�b�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�W���C�p�b�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	hr = m_pDIDevice->EnumObjects(CInputJoypad::EnumAxesCallback, this, DIDFT_AXIS);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�W���C�p�b�h�́E�E�E", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�o�C�X�̐ݒ�
#if 0
	{
		DIPROPRANGE diprg;

		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);

		diprg.diph.dwObj = DIJOFS_X;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_X;
		diprg.lMax       = JOY_MAX_X;
		m_pDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);	// �w�����͈̔͂��w��

		diprg.diph.dwObj = DIJOFS_Y;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_Y;
		diprg.lMax       = JOY_MAX_Y;
		m_pDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);	// �x�����͈̔͂��w��

		diprg.diph.dwObj = DIJOFS_RY;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_Y;
		diprg.lMax       = JOY_MAX_Y;
		m_pDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);	// �x�����͈̔͂��w��
	}
#endif

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDIDevice->Acquire();

	return hr;
}

//=============================================================================
// �W���C�X�e�B�b�N�₢���킹�p�R�[���o�b�N�֐�
//=============================================================================
BOOL CALLBACK CInputJoypad::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	DIDEVCAPS	diDevCaps;			// �f�o�C�X���
	HRESULT		hRes;
	CInputJoypad *pThis = reinterpret_cast<CInputJoypad*>(pvRef);

	// �W���C�X�e�B�b�N�p�f�o�C�X�I�u�W�F�N�g���쐬
	hRes = pThis->m_pDInput->CreateDevice(lpddi->guidInstance, &pThis->m_pDIDevice, NULL);
	if(FAILED(hRes))
	{
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	}

	// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hRes = pThis->m_pDIDevice->GetCapabilities(&diDevCaps);
	if(FAILED(hRes))
	{
		SAFE_RELEASE(pThis->m_pDIDevice);
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	}

	return DIENUM_STOP;		// ���̃f�o�C�X���g���̂ŗ񋓂��I������
}

BOOL CALLBACK CInputJoypad::EnumAxesCallback(const LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	HRESULT hr;
	CInputJoypad *pThis = reinterpret_cast<CInputJoypad*>(pvRef);

	// ���̒l�͈̔͂�ݒ�i-1000�`1000�j
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize	= sizeof(diprg); 
	diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
	diprg.diph.dwObj	= lpddoi->dwType;
	diprg.diph.dwHow	= DIPH_BYID;
	diprg.lMin	= -1000;
	diprg.lMax	= +1000;
	hr = pThis->m_pDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

//=============================================================================
// �W���C�p�b�h���͏����̊J��
//=============================================================================
void CInputJoypad::Uninit(void)
{
	// ���͏����̊J��
	CInput::Uninit();
}

//=============================================================================
// �W���C�p�b�h���͏����X�V
//=============================================================================
HRESULT CInputJoypad::Update(void)
{
	HRESULT hr;
	bool aKeyStateOld[KEY_MAX];

	if(!m_pDIDevice)
	{
		return S_FALSE;
	}

	// �O��̃f�[�^��ۑ�
	for(int nCntKey = 0; nCntKey < KEY_MAX; nCntKey++)
	{
		aKeyStateOld[nCntKey] = m_aKeyState[nCntKey];
	}

	// �f�o�C�X����f�[�^���擾
	hr = m_pDIDevice->GetDeviceState(sizeof(m_joypadState), &m_joypadState);
	if(SUCCEEDED(hr))
	{
		// �L�[���ݒ�
		SetKeyState();

		for(int nCntKey = 0; nCntKey < KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (aKeyStateOld[nCntKey] ^ m_aKeyState[nCntKey]) & m_aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (aKeyStateOld[nCntKey] ^ m_aKeyState[nCntKey]) & !m_aKeyState[nCntKey];
			m_aKeyStateRepeat[nCntKey] = m_aKeyStateTrigger[nCntKey];

			if(m_aKeyState[nCntKey])
			{
				m_aKeyStateRepeatCnt[nCntKey]++;
				if(m_aKeyStateRepeatCnt[nCntKey] >= 20)
				{
					m_aKeyStateRepeat[nCntKey] = m_aKeyState[nCntKey];
				}
			}
			else
			{
				m_aKeyStateRepeatCnt[nCntKey] = 0;
				m_aKeyStateRepeat[nCntKey] = 0;
			}
		}
	}
	else
	{
		m_pDIDevice->Acquire();
	}

	return hr;
}

//=============================================================================
// �W���C�p�b�h�̃L�[���ݒ�
//=============================================================================
void CInputJoypad::SetKeyState(void)
{
	if(m_joypadState.lX <= -8)
	{
		m_aKeyState[KEY_LEFT] = true;
	}
	else
	{
		m_aKeyState[KEY_LEFT] = false;
	}

	if(m_joypadState.lX >= 8)
	{
		m_aKeyState[KEY_RIGHT] = true;
	}
	else
	{
		m_aKeyState[KEY_RIGHT] = false;
	}

	if(m_joypadState.lY <= -8)
	{
		m_aKeyState[KEY_UP] = true;
	}
	else
	{
		m_aKeyState[KEY_UP] = false;
	}

	if(m_joypadState.lY >= 8)
	{
		m_aKeyState[KEY_DOWN] = true;
	}
	else
	{
		m_aKeyState[KEY_DOWN] = false;
	}

	if(m_joypadState.rgbButtons[0])
	{
		m_aKeyState[KEY_JUMP] = true;
	}
	else
	{
		m_aKeyState[KEY_JUMP] = false;
	}

	if(m_joypadState.rgbButtons[1])
	{
		m_aKeyState[KEY_SHOT] = true;
	}
	else
	{
		m_aKeyState[KEY_SHOT] = false;
	}

	if(m_joypadState.rgbButtons[6])
	{
		m_aKeyState[KEY_TURN_LEFT] = true;
	}
	else
	{
		m_aKeyState[KEY_TURN_LEFT] = false;
	}

	if(m_joypadState.rgbButtons[8])
	{
		m_aKeyState[KEY_TURN_RIGHT] = true;
	}
	else
	{
		m_aKeyState[KEY_TURN_RIGHT] = false;
	}

	if(m_joypadState.rgbButtons[7])
	{
		m_aKeyState[KEY_TURN_UP] = true;
	}
	else
	{
		m_aKeyState[KEY_TURN_UP] = false;
	}

	if(m_joypadState.rgbButtons[9])
	{
		m_aKeyState[KEY_TURN_DOWN] = true;
	}
	else
	{
		m_aKeyState[KEY_TURN_DOWN] = false;
	}

	if(m_joypadState.rgbButtons[11])
	{
		m_aKeyState[KEY_START] = true;
	}
	else
	{
		m_aKeyState[KEY_START] = false;
	}

	if(m_joypadState.rgbButtons[10])
	{
		m_aKeyState[KEY_SELECT] = true;
	}
	else
	{
		m_aKeyState[KEY_SELECT] = false;
	}
}

//=============================================================================
// �W���C�p�b�h���擾
//=============================================================================
bool CInputJoypad::GetKeyPress(KEY key)
{
	return m_aKeyState[key];
}

//=============================================================================
// �W���C�p�b�h���擾
//=============================================================================
bool CInputJoypad::GetKeyTrigger(KEY key)
{
	return m_aKeyStateTrigger[key];
}

//=============================================================================
// �W���C�p�b�h���擾
//=============================================================================
bool CInputJoypad::GetKeyRelease(KEY key)
{
	return m_aKeyStateRelease[key];
}

//=============================================================================
// �W���C�p�b�h���擾
//=============================================================================
bool CInputJoypad::GetKeyRepeat(KEY key)
{
	return m_aKeyStateRepeat[key];
}

