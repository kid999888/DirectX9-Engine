//=================================================================================================
//                                                        
//�@�@�@�v���[���[�N���X�v���O����[Player.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.23      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"Player.h"
#include"Renderer.h"
#include"input.h"
#include"Field.h"
#include"Manager.h"

//=================================================================================================
//		�}�N����`                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�O���[�o���ϐ�                                    
//=================================================================================================

//=================================================================================================
//�@�@�@�\���̒�`                                         
//=================================================================================================

//=================================================================================================
//�@�@�@�v���[���[�f�X�g���N�^                                        
//=================================================================================================
CPlayer::~CPlayer()
{
}

//=================================================================================================
//�@�@�@�v���[���[��������                                        
//=================================================================================================
bool CPlayer::Init(void)
{
	m_pPlayer = CSceneModel::Create();
	m_pPlayer->SetPosition(m_vePosition);
	m_Camera = CManager::GetMainCamera();
	//�v���[���[�̍��W�����f�����O�ɓ]��
	m_pPlayer->SetPosition(m_vePosition);
	//�v���[���[�̎���]�l�����f�����O�ɓ]��
	m_pPlayer->SetRotation(m_veRotation);
	return true;
}

//=================================================================================================
//�@�@�@�v���[���[�I������                                         
//=================================================================================================
void CPlayer::Uninit(void)
{
}

//=================================================================================================
//�@�@�@�v���[���[�X�V����                                        
//=================================================================================================
void CPlayer::Update(void)
{
	CField *field = CManager::GetField();
	//�ړ�����
	if (GetKeyboardPress(DIK_LEFT))
	{
		m_vePosition += v3Left * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Left * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Left * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		m_vePosition += v3Right * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Right  * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Right  * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_UP))
	{
		m_vePosition += v3In * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3In * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3In  * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		m_vePosition += v3Out * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Out * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Out  * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_A))
	{
		
	}
	if (GetKeyboardPress(DIK_D))
	{
		
	}

	//�t�B�[���Փ˔���
	m_vePosition.y = (field->GetHeight(m_vePosition) + 0.5f);

	//�v���[���[�̍��W�����f�����O�ɓ]��
	m_pPlayer->SetPosition(m_vePosition);
	//�v���[���[�̎���]�l�����f�����O�ɓ]��
	m_pPlayer->SetRotation(m_veRotation);
}

//=================================================================================================
//�@�@�@�v���[���[�`�揈��                                         
//=================================================================================================
void CPlayer::Draw(void)
{
}

//=================================================================================================
//�@�@�@�v���[���[�̃C���X�^���X����                                         
//=================================================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 vePosition)
{
	CPlayer *Player = new CPlayer(1);
	Player->m_vePosition = vePosition;
	Player->Init();
	return Player;
}
