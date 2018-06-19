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
	m_pPlayer = CSceneModel::Create();
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
	//移動処理
	if (GetKeyboardPress(DIK_LEFT))
	{
		m_vePosition += v3Left * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Left * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Left * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		m_vePosition += v3Right * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Right  * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Right  * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_UP))
	{
		m_vePosition += v3In * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3In * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3In  * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		m_vePosition += v3Out * m_fMoveSpeed;
		m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Out * m_fMoveSpeed));
		m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Out  * m_fMoveSpeed));
	}
	if (GetKeyboardPress(DIK_A))
	{
		
	}
	if (GetKeyboardPress(DIK_D))
	{
		
	}

	//フィール衝突判定
	m_vePosition.y = (field->GetHeight(m_vePosition) + 0.5f);

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
