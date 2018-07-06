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
D3DXVECTOR3 CBullet::m_vePosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3 CBullet::m_veMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CBullet::m_nLife = 0;

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
	m_pBullet = CSceneModel::Create("Data\\Model\\Ball.x");

	m_nLife = 100;

	return false;
}

//=================================================================================================
//　　　バレット終了処理                                    
//=================================================================================================
void CBullet::Uninit(void)
{
	m_pBullet->Release();
}

//=================================================================================================
//　　　バレット更新処理                                      
//=================================================================================================
void CBullet::Update(void)
{
	m_nLife -= 1;
	m_vePosition += m_veMove;

	//バレットの座標をモデリングに転送
	m_pBullet->SetPosition(m_vePosition);
}

//=================================================================================================
//　　　バレット描画処理                                     
//=================================================================================================
void CBullet::Draw(void)
{
}

//=================================================================================================
//　　　バレットのインスタンス生成
//=================================================================================================
CBullet * CBullet::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 At)
{
	CBullet *Bullet = new CBullet(1);
	Bullet->Init();
	m_vePosition = Pos;
	m_veMove = (At - Pos) * 0.1f;
	
	return Bullet;
}