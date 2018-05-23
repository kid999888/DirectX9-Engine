//=================================================================================================
//                                                        
//�@�@�@���͏���[input.h]                   
//      Author:���ŝ�(AT-12B-242 04)�@2017.06.05   
//                                                        
//=================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include<Windows.h>
#include<dinput.h>

//=================================================================================================
//		�}�N����`
//=================================================================================================
#define DIRECTINPUT_VERSION (0x0800)
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define	LIMIT_COUNT_REPEAT	(20)	// ���s�[�g�J�E���g���~�b�^�[

//=================================================================================================
//		�v���g�^�C�v�錾
//=================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);							//���͏����̏�����
void UninitKeyboard(void);														//�L�[�{�[�h�̏I������
void UpdateKeyboard(void);														//�L�[�{�[�h�̍X�V����
bool GetKeyboardPress(int nKey);												//�L�[�{�[�h�̃v���X��Ԃ��擾
bool GetKeyboardTrigger(int nKey);												//�L�[�{�[�h�̃g���K�[��Ԃ��擾
bool GetKeyboardRepeat(int nKey);												//�L�[�{�[�h�̃��s�[�g��Ԃ��擾
bool GetKeyboardRelease(int nKey);												//�L�[�{�[�h�̃����|�X��Ԃ��擾

/*
//=================================================================================================
//�@�@�@���͏����N���X                                       
//=================================================================================================
class CInput
{
public:
	CInput();											//���͏����R���X�g���N�^
	~CInput();											//���͏����f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//���͏����̏�����
	void Uninit(void);									//�L�[�{�[�h�̏I������
	void Update(void);									//�L�[�{�[�h�̍X�V����
	bool GetPress(int nKey);							//�L�[�{�[�h�̃v���X��Ԃ��擾
	bool GetTrigger(int nKey);							//�L�[�{�[�h�̃g���K�[��Ԃ��擾
	bool GetRepeat(int nKey);							//�L�[�{�[�h�̃��s�[�g��Ԃ��擾
	bool GetRelease(int nKey);							//�L�[�{�[�h�̃����|�X��Ԃ��擾

private:
	LPDIRECTINPUT8			m_pInput;							// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8	m_pDevKeyboard;						// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	BYTE					m_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE					m_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��񃏁[�N
	BYTE					m_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��񃏁[�N
	BYTE					m_aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��񃏁[�N
	int						m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^
};
*/

#endif		//_INPUT_H_