//=================================================================================================
//                                                        
//�@�@�@�G�N���X�v���O����[Enemy.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.16      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"Enemy.h"
#include"Collision.h"
#include"Xorshift.h"

//=================================================================================================
//�@�@�@���̒�`
//=================================================================================================
ENEMY CEnemy::m_Enemy[ENEMY_NUM];
CScene3D* CEnemy::m_pScene3D = NULL;

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
			m_pScene3D->SetPosition(m_Enemy[nCount].vePos);
			m_pScene3D->Draw();
		}
	}
}

//=================================================================================================
//�@�@�@�G�̃C���X�^���X����
//=================================================================================================
CEnemy * CEnemy::Create(CScene3D * pScene3D)
{
	CEnemy *Enemy = new CEnemy(1);
	Enemy->Init();
	Load(pScene3D);
	m_pScene3D->SetScale(D3DXVECTOR3(1.0f, 1.0f, 01.0f));
	m_pScene3D->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	return Enemy;
}

//=================================================================================================
//�@�@�@�G�̎��̂�ǂݍ���
//=================================================================================================
void CEnemy::Load(CScene3D * pScene3D)
{
	m_pScene3D = pScene3D;
}

//=================================================================================================
//�@�@�@�V�����G�𐶐�
//=================================================================================================
void CEnemy::Generate(D3DXVECTOR3 vePosition)
{
	for (int nCount = 0;nCount < ENEMY_NUM;nCount++)
	{
		if (m_Enemy[nCount].status != 1)
		{
			m_Enemy[nCount].vePos = vePosition;
			m_Enemy[nCount].veMov = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_Enemy[nCount].status = 1;
			m_Enemy[nCount].nLife = 10;
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
//�@�@�@�G�ړ��p�^�[��
//=================================================================================================
D3DXVECTOR3 CEnemy::GetMovePattern(int nNum)
{
	D3DXVECTOR3 Vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Vec0 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Vec1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	
	return Vec;
}