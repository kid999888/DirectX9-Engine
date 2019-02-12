//=================================================================================================
//                                                        
//　　　バレットクラスプログラム[Map.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.07.23      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include "Map.h"
#include "Math.h"

CMap::CMap(CEnemy* pEnemy, int nPriority) : CScene(nPriority)
{
	m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bDraw = true;
	m_pEnemy = pEnemy;
}

CMap::~CMap()
{

}

bool CMap::Init(void)
{
	m_pScene2DMap = CScene2D::Create(2, "Data\\Texture\\Map.png", 1, 1);
	m_pScene2DMap->SetPosition(D3DXVECTOR3(60.0f, 60.0f, -1.0f));
	m_pScene2DMap->SetScale(D3DXVECTOR3(2.0f, 2.0f, 1.0f));
	m_pScene2DMap->m_bDraw = false;
	m_pScene2DBlock = CScene2D::Create(3, "Data\\Texture\\Ball.png", 1, 1);
	m_pScene2DBlock->m_bDraw = false;
	m_pScene2DBlock->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	m_pScene2DBlock->SetScale(D3DXVECTOR3(0.125f, 0.125f, 1.0f));
	return true;
}

void CMap::Uninit(void)
{
}

void CMap::Update(void)
{
}

void CMap::Draw(void)
{
	m_pScene2DMap->Draw();
	m_pScene2DBlock->SetPositionX(60.0f + 128.0f);
	m_pScene2DBlock->SetPositionY(60.0f + 72.0f);
	m_pScene2DBlock->Draw();
	
	for (int nCount = 0;nCount < ENEMY_NUM;nCount++)
	{
		if (m_pEnemy->GetEnemyManager(nCount).status != 0)
		{

			m_pScene2DBlock->SetPositionX(188.0f + ((m_pEnemy->GetEnemyManager(nCount).vePos.x - m_Player->GetPosition().x) / 0.25f));
			float nX = m_pScene2DBlock->GetPositionX();
			m_pScene2DBlock->SetPositionY(132.0f + (-(m_pEnemy->GetEnemyManager(nCount).vePos.z - m_Player->GetPosition().z) / 0.25f));
			float nY = m_pScene2DBlock->GetPositionY();
			m_pScene2DBlock->Draw();
		}
	}

}

CMap * CMap::Create(CEnemy* pEnemy)
{
	CMap *Map = new CMap(pEnemy,1);
	Map->Init();
	return Map;
}

void CMap::SetPlayer(CPlayer * Player)
{
	m_Player = Player;
}
