//=================================================================================================
//                                                        
//�@�@�@�G�N���X�v���O����[Enemy.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.16      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include "Enemy.h"
#include "Collision.h"
#include "Xorshift.h"

//=================================================================================================
//�@�@�@���̒�`
//=================================================================================================
ENEMY CEnemy::m_Enemy[ENEMY_NUM];

//=================================================================================================
//�@�@�@�G�f�X�g���N�^                                         
//=================================================================================================
CEnemy::~CEnemy()
{
}

//=================================================================================================
//�@�@�@�G��������                                      
//=================================================================================================
bool CEnemy::Init(void)
{
	//�o���b�g��񏉊���
	for (int nCount = 0;nCount < ENEMY_NUM;nCount++)
	{
		m_Enemy[nCount].status = 0;
		m_Enemy[nCount].vePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Enemy[nCount].veMov = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Enemy[nCount].nLife = 10;
	}
	return true;
}

//=================================================================================================
//�@�@�@�G�I������
//=================================================================================================
void CEnemy::Uninit(void)
{
}

//=================================================================================================
//�@�@�@�G�X�V����
//=================================================================================================
void CEnemy::Update(void)
{
	for (int nCount = 0;nCount < ENEMY_NUM;nCount++)
	{
		switch (m_Enemy[nCount].status)
		{
		case 0:					// �ҋ@���
			break;
		case 1:
			if (m_Enemy[nCount].nLife <= 0)
			{
				Destory(nCount);
				break;
			}
			m_Enemy[nCount].veMov = GetMovePattern(nCount);
			m_Enemy[nCount].vePos += m_Enemy[nCount].veMov;
			break;
		default:break;
		}
	}
}

//=================================================================================================
//�@�@�@�G�`�揈��
//=================================================================================================
void CEnemy::Draw(void)
{
	for (int nCount = 0;nCount < ENEMY_NUM;nCount++)
	{
		if (m_Enemy[nCount].status != 0)
		{
			m_Enemy[nCount].SceneModel->SetPosition(m_Enemy[nCount].vePos);
			m_Enemy[nCount].SceneModel->SetScale(m_Enemy[nCount].veScale);
			m_Enemy[nCount].SceneModel->Draw();
		}
	}
}

//=================================================================================================
//�@�@�@�G�̃C���X�^���X����
//=================================================================================================
CEnemy * CEnemy::Create(void)
{
	CEnemy *Enemy = new CEnemy(1);
	Enemy->Init();
	return Enemy;
}

//=================================================================================================
//�@�@�@�V�����G�𐶐�
//=================================================================================================
void CEnemy::Generate(ENEMY_TYPES_ID EnemyType, D3DXVECTOR3 vePosition, CSceneModel* pSceneModel, D3DXVECTOR3 veScale)
{
	for (int nCount = 0;nCount < ENEMY_NUM;nCount++)
	{
		if (m_Enemy[nCount].status != 1)
		{
			m_Enemy[nCount].vePos = vePosition;
			m_Enemy[nCount].veMov = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_Enemy[nCount].status = 1;
			m_Enemy[nCount].EnemyType = EnemyType;
			m_Enemy[nCount].SceneModel = pSceneModel;
			m_Enemy[nCount].veScale = veScale;
			switch (EnemyType)
			{
			//�U�O�̐���
			case ENEMY_TYPES_ZAKU:
				m_Enemy[nCount].nLife = 3;
				break;
			//�����̐���
			case ENEMY_TYPES_BULIDING:
				m_Enemy[nCount].nLife = 2;
				break;
			default:break;
			}
			break;
		}
	}
}

//=================================================================================================
//�@�@�@�G��p������
//=================================================================================================
void CEnemy::Destory(int nNum)
{
	m_Enemy[nNum].status = 0;
	m_Enemy[nNum].vePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Enemy[nNum].veMov = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Enemy[nNum].nLife = 10;
}

//=================================================================================================
//�@�@�@�GHP��ݒ�
//=================================================================================================
void CEnemy::SetEnemyLife(int nNum, int nLife)
{
	m_Enemy[nNum].nLife = nLife;
}

//=================================================================================================
//�@�@�@�G�ړ��p�^�[��
//=================================================================================================
D3DXVECTOR3 CEnemy::GetMovePattern(int nNum)
{
	D3DXVECTOR3 Vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Vec0 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Vec1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	switch (m_Enemy[nNum].EnemyType)
	{
	//�U�O�̈ړ��p�^�[��
	case ENEMY_TYPES_ZAKU:
		if (m_Enemy[nNum].status != 0)
		{
			if (CCollision::BallJudgement(m_Enemy[nNum].vePos, CPlayer::GetPlayerPos(), 10.0f, 1.0f))
			{
				Vec0 = m_Enemy[nNum].vePos;
				Vec0.y = 0.0f;
				Vec1 = CPlayer::GetPlayerPos();
				Vec1.y = 0.0f;
				Vec = Vec1 - Vec0;
				D3DXVec3Normalize(&Vec, &Vec);
				Vec.y = 0.0f;
				Vec *= 0.1f;
			}
			else
			{
				Vec.x = (float)(CXorshift::xor64() * 0.000000000005f * 1.0f) - ((CXorshift::xor64() * 0.000000000005f * 1.0f) * 0.5f);
				Vec.z = (float)(CXorshift::xor64() * 0.000000000005f * 1.0f) - ((CXorshift::xor64() * 0.000000000005f * 1.0f) * 0.5f);
			}
		}
		break;
	//�����̈ړ��p�^�[��
	case ENEMY_TYPES_BULIDING:
		break;
	default:break;
	}
	
	return Vec;
}
