//=================================================================================================
//                                                        
//　　　バレットクラスプログラム[ExplosionBB.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2019.09.18      
//                                                        
//=================================================================================================
#include "ExplosionBB.h"


CExplosionBB::CExplosionBB(int nPriority, CCamera* pCamera) : CScene(nPriority)
{
	m_Type = SCENE_TYPE_EXPLOSIONBB;

	bFinish = false;
	m_fU0 = 0.0f;
	m_fV0 = 0.0f;
	m_fU1 = 1.0f/6 * 1.0f;
	m_fV1 = 1.0f/2 * 1.0f;
	m_nAnimeCount = 0;
	m_patternNum = 0;
	m_patternH = 0;
	m_patternV = 0;
	
}

CExplosionBB::~CExplosionBB()
{
}

bool CExplosionBB::Init(CCamera* pCamera, D3DXVECTOR3 vePos)
{
	ExplosionBB = CSceneBillBoardUV::Create(pCamera, "Data\\Texture\\bakuhatsu.png");

	ExplosionBB->SetTextureUV(m_fU0, m_fV0, m_fU1, m_fV1);

	ExplosionBB->SetScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));

	vePos.x *= 0.83f;

	ExplosionBB->SetPosition(vePos);

	return false;
}

void CExplosionBB::Uninit(void)
{
	ExplosionBB->Release();
}

void CExplosionBB::Update(void)
{
	m_nAnimeCount++;

	m_patternNum = m_nAnimeCount / 5 % 12;
	m_patternH = m_patternNum % 6;
	m_patternV = m_patternNum / 6;


	m_fU0 = (float)m_patternH / 6.0f;
	m_fV0 = (float)m_patternV / 2.0f;
	m_fU1 = (float)(m_patternH + 1) / 6.0f;
	m_fV1 = (float)(m_patternV + 1) / 2.0f;

	ExplosionBB->SetTextureUV(m_fU0, m_fV0, m_fU1, m_fV1);
	
	if (m_nAnimeCount > (5 * 12))
	{
		this->Release();
	}
}

void CExplosionBB::Draw(void)
{
}

CExplosionBB * CExplosionBB::Create(int nPriority, CCamera* pCamera, D3DXVECTOR3 vePos)
{
	CExplosionBB *Objects = new CExplosionBB(2, pCamera);
	Objects->Init(pCamera, vePos);
	return Objects;
}
