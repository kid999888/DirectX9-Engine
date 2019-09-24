//=================================================================================================
//                                                        
//　　　プレーヤークラスプログラム[Player.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.23      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include "Player.h"
#include "Renderer.h"
#include "input.h"
#include "Field.h"
#include "Manager.h"
#include "Bullet.h"
#include "Collision.h"
#include<cmath>



//=================================================================================================
//		マクロ定義                                        
//=================================================================================================

//=================================================================================================
//　　　グローバル変数                                    
//=================================================================================================

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================
CPlayer::CPlayer(CMode* Mode, int nPriority) : CScene(nPriority)
{
	m_CurrentMode = Mode;
	m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vePlayerFront = D3DXVECTOR3(m_vePosition.x, m_vePosition.y, (m_vePosition.z - 1.0f));
	m_vePlayerMousePoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMoveSpeed = 0.2f;
	m_fRotYSpeed = 5.0f;
	m_fRotOnce = 0.0f;
	m_fRotYExactly = 0;
	m_pTexture = nullptr;
	_nHp = 100;
};

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
	m_Camera = m_CurrentMode->GetMainCamera();
	//プレーヤーの座標をモデリングに転送
	m_pPlayer->SetPosition(m_vePosition);
	//プレーヤーの軸回転値をモデリングに転送
	
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
	CField *field = m_CurrentMode->GetField();
	

	//移動処理
	if (CInputKeyboard::GetKeyPress(DIK_A))
	{
		if (m_vePosition.x > -90.0f)
		{
			m_vePosition += v3Left * m_fMoveSpeed;
			m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Left * m_fMoveSpeed));
			m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Left * m_fMoveSpeed));
		}
	}
	if (CInputKeyboard::GetKeyPress(DIK_D))
	{
		if (m_vePosition.x < 90.0f)
		{
			m_vePosition += v3Right * m_fMoveSpeed;
			m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Right  * m_fMoveSpeed));
			m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Right  * m_fMoveSpeed));
		}
	}
	if (CInputKeyboard::GetKeyPress(DIK_W))
	{
		if (m_vePosition.z < 90.0f)
		{
			m_vePosition += v3In * m_fMoveSpeed;
			m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3In * m_fMoveSpeed));
			m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3In  * m_fMoveSpeed));
		}
	}
	if (CInputKeyboard::GetKeyPress(DIK_S))
	{
		if (m_vePosition.z > -90.0f)
		{
			m_vePosition += v3Out * m_fMoveSpeed;
			m_Camera->SetCameraPos(m_Camera->GetCameraPos() + (v3Out * m_fMoveSpeed));
			m_Camera->SetCameraAtPos(m_Camera->GetCameraAtPos() + (v3Out  * m_fMoveSpeed));
		}
	}

	D3DXVECTOR3 veMousePosToXZ(0.0f,0.0f,0.0f);
	
	CCollision::CalcScreenToXZ(&veMousePosToXZ, CInputMouse::GetPosUserScreen()->x, CInputMouse::GetPosUserScreen()->y,
	GetUserWindowsSize().right, GetUserWindowsSize().bottom, &m_CurrentMode->GetMainCamera()->GetCameraView(), &m_CurrentMode->GetMainCamera()->GetCameraProjection());
	m_vePlayerMousePoint = veMousePosToXZ;
	m_vePlayerMousePoint.y = 0.0f;
	veMousePosToXZ = veMousePosToXZ - m_vePosition;
	D3DXVec3Normalize(&veMousePosToXZ, &veMousePosToXZ);
	veMousePosToXZ.y = 0.0f;
	
	float fRotS = 0.0f;
	float fx1 = D3DXVec3Length(&v3Out);
	float fx2 = D3DXVec3Length(&veMousePosToXZ);
	float fx3 = D3DXVec3Dot(&v3Out, &veMousePosToXZ);
	fRotS = D3DXVec3Dot(&v3Out, &veMousePosToXZ) / (D3DXVec3Length(&v3Out) * D3DXVec3Length(&veMousePosToXZ));
	fRotS = D3DXToDegree(acos(fRotS));
	
	bool bClockwise = true;
	float fRotYOld = m_veRotation.y;
	float C0 = (v3Out.x * veMousePosToXZ.z) - (v3Out.z * veMousePosToXZ.x);

	if (C0 > 0.0f)
	{
		m_veRotation.y = (360.0f - fRotS);
	}
	else
	{
		m_veRotation.y = fRotS;
	}
	
	m_vePlayerFront = veMousePosToXZ;

	if (m_CurrentMode->m_ModeId == MODE_GAME)
	{
		//フィール衝突判定
		m_vePosition.y = (CCollision::GetFieldHeight(field->GetFiledPos(), m_vePosition, field->GetBlockNumX(), field->GetBlockNumZ()) + 0.5f);
	}

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
CPlayer * CPlayer::Create(CMode* Mode, D3DXVECTOR3 vePosition)
{
	CPlayer *Player = new CPlayer(Mode,1);
	Player->m_vePosition = vePosition;
	Player->Init();
	return Player;
}
