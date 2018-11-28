#include "LifeBarBillBoard.h"


CLifeBarBillBoard::CLifeBarBillBoard(int nPriority) : CScene(nPriority)
{
	m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vePosition = D3DXVECTOR3(0.0f, 2.0f, 10.0f);
}

CLifeBarBillBoard::~CLifeBarBillBoard()
{

}

bool CLifeBarBillBoard::Init(CCamera* pCamera)
{
	m_LifeBarHP = CSceneBillBoardUV::Create(pCamera, "Data\\Texture\\LifeBarHP.png");
	m_LifeBarHP->SetPosition(m_vePosition);
	m_LifeBarHP->SetScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	m_LifeBarHP->SetTextureUV(0.0f, 0.0f, 0.5f, 1.0f);
	m_LifeBar = CSceneBillBoard::Create(pCamera, "Data\\Texture\\LifeBar.png");
	m_LifeBar->SetPosition(m_vePosition);
	m_LifeBar->SetScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	
	return true;
}

void CLifeBarBillBoard::Uninit(void)
{
}

void CLifeBarBillBoard::Update(void)
{
	m_LifeBarHP->SetPosition(m_vePosition);
	/*m_LifeBar->SetPosition(m_vePosition);*/
}

void CLifeBarBillBoard::Draw(void)
{
}

CLifeBarBillBoard * CLifeBarBillBoard::Create(CCamera* pCamera)
{
	CLifeBarBillBoard* LifeBarBillBoard = new CLifeBarBillBoard(0);
	LifeBarBillBoard->Init(pCamera);
	return LifeBarBillBoard;
}