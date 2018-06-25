//=================================================================================================
//                                                        
//　　　プレーヤークラスプログラム[Player.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.23      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include"Player.h"
#include"Renderer.h"
#include"input.h"
#include"Field.h"
#include"Manager.h"
#include"Bullet.h"
#include"Collision.h"

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================

//=================================================================================================
//　　　グローバル変数                                    
//=================================================================================================

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================

//=================================================================================================
//　　　プレーヤーデストラクタ                                        
//=================================================================================================
CPlayer::~CPlayer()
{
}

//=================================================================================================
//　　　プレーヤー初期処理                                        
//=================================================================================================
bool CPlayer::Init(void)
{
	m_pPlayer = CSceneModel::Create("Data\\Model\\roboModel.x");
	m_pPlayer->SetPosition(m_vePosition);
	m_Camera = CManager::GetMainCamera();
	//プレーヤーの座標をモデリングに転送
	m_pPlayer->SetPosition(m_vePosition);
	//プレーヤーの軸回転値をモデリングに転送
	m_pPlayer->SetRotation(m_veRotation);
	return true;
}

//=================================================================================================
//　　　プレーヤー終了処理                                         
//=================================================================================================
void CPlayer::Uninit(void)
{
}

//=================================================================================================
//　　　プレーヤー更新処理                                        
//=================================================================================================
void CPlayer::Update(void)
{
	CField *field = CManager::GetField();
	

	if (m_veRotation.y > m_fRotYExactly)
	{
		if (m_veRotation.y - m_fRotYExactly < 180.f)
		{
			m_veRotation.y -= m_fRotYSpeed;
			m_fRotOnce = -m_fRotYSpeed;
		}
		else
		{
			m_veRotation.y += m_fRotYSpeed;
			m_fRotOnce = m_fRotYSpeed;
		}
	}
	else if (m_veRotation.y < m_fRotYExactly)
	{
		if (m_fRotYExactly - m_veRotation.y < 180.f)
		{
			m_veRotation.y += m_fRotYSpeed;
			m_fRotOnce = m_fRotYSpeed;
		}
		else
		{
			m_veRotation.y -= m_fRotYSpeed;
			m_fRotOnce = -m_fRotYSpeed;
		}
	}

	if (m_veRotation.y > 360.f)
	{
		m_veRotation.y -= 360.f;
	}
	if (m_veRotation.y < 0.0f)
	{
		m_veRotation.y += 360.f;
	}

	//移動処理
	if (GetKeyboardPress(DIK_LEFT))
	{
		m_fRotYExactly = 90.0f;
		m_vePosition += v3Left * m_fMoveSpeed;
		m_vePlayerFront += v3Left * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Left * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Left * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		m_fRotYExactly = 270.0f;
		m_vePosition += v3Right * m_fMoveSpeed;
		m_vePlayerFront += v3Right * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Right  * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Right  * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_UP))
	{
		m_fRotYExactly = 180.0f;
		m_vePosition += v3In * m_fMoveSpeed;
		m_vePlayerFront += v3In * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3In * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3In  * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		m_fRotYExactly = 0.0f;
		m_vePosition += v3Out * m_fMoveSpeed;
		m_vePlayerFront += v3Out * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Out * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Out  * m_fMoveSpeed));
	}

	if (GetKeyboardPress(DIK_SPACE))
	{
		CBullet::Create(m_vePosition, m_vePlayerFront);
	}

	if (m_veRotation.y > 360.0f)
	{
		m_veRotation.y -= 360.f;
	}
	if (m_veRotation.y < 0.0f)
	{
		m_veRotation.y = 360.0f;
	}
	if (m_fRotYExactly > 360.0f)
	{
		m_fRotYExactly -= 360.f;
	}
	if (m_fRotYExactly < 0.0f)
	{
		m_fRotYExactly = 360.0f;
	}

	if (GetKeyboardPress(DIK_UP) && GetKeyboardPress(DIK_LEFT))//斜めに進む
	{
		m_fRotYExactly = 135.0f;
	}
	if (GetKeyboardPress(DIK_UP) && GetKeyboardPress(DIK_RIGHT))//斜めに進む
	{
		m_fRotYExactly = 225.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) && GetKeyboardPress(DIK_RIGHT))//斜めに進む
	{
		m_fRotYExactly = 315.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) && GetKeyboardPress(DIK_LEFT))//斜めに進む
	{
		m_fRotYExactly = 45.0f;
	}

	m_vePlayerFront = m_pPlayer->GetModelAt();
	
	//フィール衝突判定
	m_vePosition.y = (CCollision::GetFieldHeight(field->GetFiledPos(), m_vePosition, field->GetBlockNumX(), field->GetBlockNumZ()) + 0.5f);

	//プレーヤーの座標をモデリングに転送
	m_pPlayer->SetPosition(m_vePosition);
	//プレーヤーの軸回転値をモデリングに転送
	m_pPlayer->SetRotation(m_veRotation);
}

//=================================================================================================
//　　　プレーヤー描画処理                                         
//=================================================================================================
void CPlayer::Draw(void)
{
}

//=================================================================================================
//　　　プレーヤーのインスタンス生成                                         
//=================================================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 vePosition)
{
	CPlayer *Player = new CPlayer(1);
	Player->m_vePosition = vePosition;
	Player->Init();
	return Player;
}
