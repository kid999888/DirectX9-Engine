#include "LifeBar.h"


CLifeBar::CLifeBar(int nPriority) : CScene(nPriority)
{
	m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vePosition = D3DXVECTOR3(0.0f, 2.0f, 10.0f);
}

CLifeBar::~CLifeBar()
{

}

bool CLifeBar::Init(void)
{
	m_LifeBarHP = CScene2DUV::Create(2, "Data\\Texture\\LifeBarHP.png");
	m_LifeBarHP->SetPosition(D3DXVECTOR3(640.0f - 64.0f, 360.0f - 6.0f, 0.0f));
	m_LifeBar = CScene2D::Create(2, "Data\\Texture\\LifeBar.png", 1, 1);
	m_LifeBar->SetPosition(D3DXVECTOR3(640.0f - 64.0f, 360.0f - 6.0f, 0.0f));
	m_LifeBarHP->SetTextureUV(0.0f,0.0f,0.8f,1.0f);
	return true;
}

void CLifeBar::Uninit(void)
{
}

void CLifeBar::Update(void)
{
}

void CLifeBar::Draw(void)
{
}

CLifeBar * CLifeBar::Create(void)
{
	CLifeBar* LifeBar = new CLifeBar(0);
	LifeBar->Init();
	return LifeBar;
}