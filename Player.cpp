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
#include"Bullet.h"
#include"Collision.h"

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
	m_pPlayer = CSceneModel::Create("Data\\Model\\roboModel.x");
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
	

	if (m_veRotation.y > m_fRotYExactly)
	{
		if (m_veRotation.y - m_fRotYExactly < 180.f)
		{
			m_veRotation.y -= m_fRotYSpeed;
			m_fRotOnce = -m_fRotYSpeed;
		}
		else
		{
			m_veRotation.y += m_fRotYSpeed;
			m_fRotOnce = m_fRotYSpeed;
		}
	}
	else if (m_veRotation.y < m_fRotYExactly)
	{
		if (m_fRotYExactly - m_veRotation.y < 180.f)
		{
			m_veRotation.y += m_fRotYSpeed;
			m_fRotOnce = m_fRotYSpeed;
		}
		else
		{
			m_veRotation.y -= m_fRotYSpeed;
			m_fRotOnce = -m_fRotYSpeed;
		}
	}

	if (m_veRotation.y > 360.f)
	{
		m_veRotation.y -= 360.f;
	}
	if (m_veRotation.y < 0.0f)
	{
		m_veRotation.y += 360.f;
	}

	//�ړ�����
	if (GetKeyboardPress(DIK_LEFT))
	{
		m_fRotYExactly = 90.0f;
		m_vePosition += v3Left * m_fMoveSpeed;
		m_vePlayerFront += v3Left * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Left * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Left * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		m_fRotYExactly = 270.0f;
		m_vePosition += v3Right * m_fMoveSpeed;
		m_vePlayerFront += v3Right * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Right  * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Right  * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_UP))
	{
		m_fRotYExactly = 180.0f;
		m_vePosition += v3In * m_fMoveSpeed;
		m_vePlayerFront += v3In * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3In * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3In  * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		m_fRotYExactly = 0.0f;
		m_vePosition += v3Out * m_fMoveSpeed;
		m_vePlayerFront += v3Out * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Out * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Out  * m_fMoveSpeed));
	}

	if (GetKeyboardPress(DIK_SPACE))
	{
		CBullet::Create(m_vePosition, m_vePlayerFront);
	}

	if (m_veRotation.y > 360.0f)
	{
		m_veRotation.y -= 360.f;
	}
	if (m_veRotation.y < 0.0f)
	{
		m_veRotation.y = 360.0f;
	}
	if (m_fRotYExactly > 360.0f)
	{
		m_fRotYExactly -= 360.f;
	}
	if (m_fRotYExactly < 0.0f)
	{
		m_fRotYExactly = 360.0f;
	}

	if (GetKeyboardPress(DIK_UP) && GetKeyboardPress(DIK_LEFT))//�΂߂ɐi��
	{
		m_fRotYExactly = 135.0f;
	}
	if (GetKeyboardPress(DIK_UP) && GetKeyboardPress(DIK_RIGHT))//�΂߂ɐi��
	{
		m_fRotYExactly = 225.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) && GetKeyboardPress(DIK_RIGHT))//�΂߂ɐi��
	{
		m_fRotYExactly = 315.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) && GetKeyboardPress(DIK_LEFT))//�΂߂ɐi��
	{
		m_fRotYExactly = 45.0f;
	}

	m_vePlayerFront = m_pPlayer->GetModelAt();
	
	//�t�B�[���Փ˔���
	m_vePosition.y = (CCollision::GetFieldHeight(field->GetFiledPos(), m_vePosition, field->GetBlockNumX(), field->GetBlockNumZ()) + 0.5f);

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
