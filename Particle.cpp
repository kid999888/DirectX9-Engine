//=================================================================================================
//                                                        
//�@�@�@�p�[�e�B�N���N���X�v���O����[Particle.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.09      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"Particle.h"
#include"Xorshift.h"

//=================================================================================================
//�@�@�@���̒�`
//=================================================================================================
CSceneBillBoard* CParticle::m_pBillBoard = NULL;
D3DXVECTOR3 CParticle::m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
float CParticle::m_fSpeed = 0.0f;
int CParticle::m_nLifeLimit = 0;

//=================================================================================================
//�@�@�@�p�[�e�B�N���f�X�g���N�^
//=================================================================================================
CParticle::~CParticle()
{
}

//=================================================================================================
//�@�@�@�p�[�e�B�N����������
//=================================================================================================
bool CParticle::Init(void)
{
	//�p�[�e�B�N����񏉊���
	for (int nCount = 0;nCount < PARTICLE_NUM;nCount++)
	{
		m_Particle[nCount].status = 0;
		m_Particle[nCount].vePos = m_vePosition;
		m_Particle[nCount].veMov = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Particle[nCount].veAcc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Particle[nCount].nLife = 0;
	}

	m_pBillBoard->SetScale(m_veScale);
	m_pBillBoard->SetPosition(m_vePosition);
	return true;
}

//=================================================================================================
//�@�@�@�p�[�e�B�N���I������
//=================================================================================================
void CParticle::Uninit(void)
{
}

//=================================================================================================
//�@�@�@�p�[�e�B�N���X�V����
//=================================================================================================
void CParticle::Update(void)
{
	bool bBorn = false;
	for (int nCount = 0;nCount < PARTICLE_NUM;nCount++)
	{
		switch (m_Particle[nCount].status)
		{
		case 0:					// �ҋ@���
			if (!bBorn) {
				bBorn = true;
				m_Particle[nCount].status = 1;
			}
			break;
		case 1:
			m_Particle[nCount].vePos = m_vePosition;
			m_Particle[nCount].veMov = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_Particle[nCount].veAcc.x = (float)(CXorshift::xor64() * 0.0000000000005f * m_fSpeed) - ((CXorshift::xor64() * 0.0000000000005f * m_fSpeed) * 0.5f);
			m_Particle[nCount].veAcc.y = (float)(CXorshift::xor64() * 0.0000000000005f * m_fSpeed) - ((CXorshift::xor64() * 0.0000000000005f * m_fSpeed) * 0.5f);
			m_Particle[nCount].veAcc.z = (float)(CXorshift::xor64() * 0.0000000000005f * m_fSpeed) - ((CXorshift::xor64() * 0.0000000000005f * m_fSpeed) * 0.5f);
			m_Particle[nCount].nLife = m_nLifeLimit;
			m_Particle[nCount].status = 2;
		case 2:
			m_Particle[nCount].veMov += m_Particle[nCount].veAcc;
			m_Particle[nCount].vePos += m_Particle[nCount].veMov;
			m_Particle[nCount].nLife -= 1;
			if (m_Particle[nCount].nLife <= 0)
			{
				m_Particle[nCount].status = 0;
				m_Particle[nCount].vePos = m_vePosition;
				m_Particle[nCount].veMov = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_Particle[nCount].veAcc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_Particle[nCount].nLife = 0;
			}
		}
	}
}

//=================================================================================================
//�@�@�@�p�[�e�B�N���`�揈��
//=================================================================================================
void CParticle::Draw(void)
{
	for (int nCount = 0;nCount < PARTICLE_NUM;nCount++)
	{
		if (m_Particle[nCount].status != 0)
		{
			m_pBillBoard->SetPosition(m_Particle[nCount].vePos);
			m_pBillBoard->Draw();
		}
	}
}

//=================================================================================================
//�@�@�@�p�[�e�B�N���̃C���X�^���X����
//=================================================================================================
CParticle * CParticle::Create(CSceneBillBoard* pBillBoard, D3DXVECTOR3 vePosition, float fSpeed, int nLife)
{
	CParticle *Particle = new CParticle(1);
	LoadBillBoard(pBillBoard);
	m_vePosition = vePosition;
	m_fSpeed = fSpeed;
	m_nLifeLimit = nLife;
	Particle->Init();
	return Particle;
}

//=================================================================================================
//�@�@�@�p�[�e�B�N���̃r���{�[�h��ǂݍ���
//=================================================================================================
void CParticle::LoadBillBoard(CSceneBillBoard* pBillBoard)
{
	m_pBillBoard = pBillBoard;
}
