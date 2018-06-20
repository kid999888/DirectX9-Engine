//=================================================================================================
//                                                        
//�@�@�@���͏���[input.cpp]                   
//      Author:���ŝ�(AT-12B-242 04)�@2017.06.05   
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include "input.h"

//=================================================================================================
//		�}�N����`
//=================================================================================================

//=================================================================================================
//		�O���[�o���ϐ�
//=================================================================================================
LPDIRECTINPUT8			g_pInput = NULL;					// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;				// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE					g_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��񃏁[�N
BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��񃏁[�N
BYTE					g_aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��񃏁[�N
int						g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

//=================================================================================================
//		���͏����̏�����
//=================================================================================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	hWnd = hWnd;
	//UNREFERENCED_PARAMETER(hWnd);
	if(g_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
										IID_IDirectInput8, (void**)&g_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=================================================================================================
//		���͏����̏I������
//=================================================================================================
void UninitInput(void)
{
	if(g_pInput != NULL)
	{// DirectInput�I�u�W�F�N�g�̊J��
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=================================================================================================
//		���͏����̍X�V����
//=================================================================================================
void UpdateInput(void)
{

}

//=================================================================================================
//		�L�[�{�[�h�̏�����
//=================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// ���͏����̏�����
	if(FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�o�C�X�̍쐬
	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))    //FOREGROUND���̃v���O���������ABACKGROUND�S���̃v���O�����L�[����͂ł���
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//=================================================================================================
//		�L�[�{�[�h�̏I������
//=================================================================================================
void UninitKeyboard(void)
{
	if(g_pDevKeyboard != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		g_pDevKeyboard->Unacquire();

		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// ���͏����̏I������
	UninitInput();
}

//=================================================================================================
//		�L�[�{�[�h�̍X�V����
//=================================================================================================
void UpdateKeyboard(void)
{
	//��t������
	BYTE aKeyState[NUM_KEY_MAX];

	// �f�o�C�X����f�[�^���擾
	if(SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for(int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];             //�������u��
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aKeyState[nCnKey];            //�����u��

			// �L�[���s�[�g���𐶐�
			if(aKeyState[nCnKey])
			{
				if(g_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					g_aKeyStateRepeatCnt[nCnKey]++;
					if(g_aKeyStateRepeatCnt[nCnKey] == 1
					|| g_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{// �L�[�������n�߂��ŏ��̃t���[���A�܂��͈�莞�Ԍo�߂�����L�[���s�[�g���ON
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

			// �L�[�v���X����ۑ�
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		g_pDevKeyboard->Acquire();
	}
}

//=================================================================================================
//		�L�[�{�[�h�̃v���X��Ԃ��擾
//=================================================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true: false;
}

//=================================================================================================
//		�L�[�{�[�h�̃g���K�[��Ԃ��擾
//=================================================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true: false;
}

//=================================================================================================
//		�L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=================================================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true: false;
}

//=================================================================================================
//		�L�[�{�[�h�̃����|�X��Ԃ��擾
//=================================================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true: false;
}

/*
CInput::CInput()
{
	m_pInput = NULL;					// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	m_pDevKeyboard = NULL;				// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
}

CInput::~CInput()
{
}

HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ���͏����̏�����
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�o�C�X�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))    //FOREGROUND���̃v���O���������ABACKGROUND�S���̃v���O�����L�[����͂ł���
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevKeyboard->Acquire();

	return S_OK;
}

void CInput::Uninit(void)
{
	if (m_pDevKeyboard != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	 // �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		m_pDevKeyboard->Unacquire();

		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	// ���͏����̏I������
	Uninit();
}

void CInput::Update(void)
{
	//��t������
	BYTE aKeyState[NUM_KEY_MAX];

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			m_aKeyStateTrigger[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];             //�������u��
			m_aKeyStateRelease[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & m_aKeyState[nCnKey];            //�����u��

																													 // �L�[���s�[�g���𐶐�
			if (aKeyState[nCnKey])
			{
				if (m_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					m_aKeyStateRepeatCnt[nCnKey]++;
					if (m_aKeyStateRepeatCnt[nCnKey] == 1
						|| m_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{// �L�[�������n�߂��ŏ��̃t���[���A�܂��͈�莞�Ԍo�߂�����L�[���s�[�g���ON
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

			// �L�[�v���X����ۑ�
			m_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
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
