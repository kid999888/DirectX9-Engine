//=================================================================================================
//                                                        
//　　　バレットクラスプログラム[Bullet.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.23      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include"Bullet.h"
#include"Player.h"
#include"Renderer.h"
#include"Manager.h"

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================

//=================================================================================================
//　　　実体定義
//=================================================================================================
CSceneModel* CBullet::m_pBullet = NULL;
BULLET CBullet::m_Bullet[BULLET_NUM];

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================

//=================================================================================================
//　　　バレットデストラクタ                                        
//=================================================================================================
CBullet::~CBullet()
{
}

//=================================================================================================
//　　　バレット初期処理                                       
//=================================================================================================
bool CBullet::Init(void)
{
	//バレット情報初期化
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
//　　　バレット終了処理                                    
//=================================================================================================
void CBullet::Uninit(void)
{
}

//=================================================================================================
//　　　バレット更新処理                                      
//=================================================================================================
void CBullet::Update(void)
{
	for (int nCount = 0;nCount < BULLET_NUM;nCount++)
	{
		switch (m_Bullet[nCount].status)
		{
		case 0:					// 待機状態
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
	//バレットの座標をモデリングに転送
	m_pBullet->SetPosition(m_vePosition);
}

//=================================================================================================
//　　　バレット描画処理                                     
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
//　　　バレットのインスタンス生成
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
