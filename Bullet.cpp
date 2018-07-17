//=================================================================================================
//                                                        
//�@�@�@�o���b�g�N���X�v���O����[Bullet.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.23      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"Bullet.h"
#include"Player.h"
#include"Renderer.h"
#include"Manager.h"

//=================================================================================================
//		�}�N����`                                        
//=================================================================================================

//=================================================================================================
//�@�@�@���̒�`
//=================================================================================================
CSceneModel* CBullet::m_pBullet = NULL;
BULLET CBullet::m_Bullet[BULLET_NUM];

//=================================================================================================
//�@�@�@�\���̒�`                                         
//=================================================================================================

//=================================================================================================
//�@�@�@�o���b�g�f�X�g���N�^                                        
//=================================================================================================
CBullet::~CBullet()
{
}

//=================================================================================================
//�@�@�@�o���b�g��������                                       
//=================================================================================================
bool CBullet::Init(void)
{
	//�o���b�g��񏉊���
	for (int nCount = 0;nCount < BULLET_NUM;nCount++)
	{
		m_Bullet[nCount].status = 0;
		m_Bullet[nCount].vePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Bullet[nCount].veMov = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Bullet[nCount].nLife = 200;
	}

	

	return false;
}

//=================================================================================================
//�@�@�@�o���b�g�I������                                    
//=================================================================================================
void CBullet::Uninit(void)
{
}

//=================================================================================================
//�@�@�@�o���b�g�X�V����                                      
//=================================================================================================
void CBullet::Update(void)
{
	for (int nCount = 0;nCount < BULLET_NUM;nCount++)
	{
		switch (m_Bullet[nCount].status)
		{
		case 0:					// �ҋ@���
			break;
		case 1:
			if (m_Bullet[nCount].nLife <= 0)
			{
				m_Bullet[nCount].status = 0;
				m_Bullet[nCount].vePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_Bullet[nCount].veMov = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_Bullet[nCount].nLife = 200;
				break;
			}
			m_Bullet[nCount].vePos += m_Bullet[nCount].veMov;
			m_Bullet[nCount].nLife -= 2;
			break;
		default:break;
		}
	}
	//�o���b�g�̍��W�����f�����O�ɓ]��
	m_pBullet->SetPosition(m_vePosition);
}

//=================================================================================================
//�@�@�@�o���b�g�`�揈��                                     
//=================================================================================================
void CBullet::Draw(void)
{
	for (int nCount = 0;nCount < BULLET_NUM;nCount++)
	{
		if (m_Bullet[nCount].status != 0)
		{
			m_pBullet->SetPosition(m_Bullet[nCount].vePos);
			m_pBullet->Draw();
		}
	}
}

//=================================================================================================
//�@�@�@�o���b�g�̃C���X�^���X����
//=================================================================================================
CBullet * CBullet::Create(CSceneModel* pBullet)
{
	CBullet *Bullet = new CBullet(1);
	Bullet->Init();
	Load(pBullet);
	m_pBullet->SetScale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));
	m_pBullet->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	return Bullet;
}

void CBullet::Load(CSceneModel* pBullet)
{
	m_pBullet = pBullet;
	
}

void CBullet::Shoot(D3DXVECTOR3 vePosition, D3DXVECTOR3 veVec)
{
	for (int nCount = 0;nCount < BULLET_NUM;nCount++)
	{
		if (m_Bullet[nCount].status != 1)
		{
			m_Bullet[nCount].vePos = vePosition;
			m_Bullet[nCount].vePos.y = 2.0f;
			m_Bullet[nCount].veMov = (veVec - vePosition);
			D3DXVec3Normalize(&m_Bullet[nCount].veMov, &m_Bullet[nCount].veMov);
			m_Bullet[nCount].veMov = m_Bullet[nCount].veMov * 0.12;
			m_Bullet[nCount].veMov.y = 0.0f;
			m_Bullet[nCount].status = 1;
			m_Bullet[nCount].nLife = 200;
			break;
		}
	}
}
