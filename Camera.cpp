//=================================================================================================
//                                                        
//　　　カメラクラスプログラム[Camera.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include "Camera.h"
#include"main.h"
#include"Renderer.h"

//=================================================================================================
//　　　カメラクラスコンストラクタ                                    
//=================================================================================================
CCamera::CCamera()
{
	//カメラ位置の初期化
	m_eye = D3DXVECTOR3(0.0f, 6.0f, -10.0f);
	m_at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//=================================================================================================
//　　　カメラクラスデストラクタ                                     
//=================================================================================================
CCamera::~CCamera()
{
}

//=================================================================================================
//　　　カメラクラス更新処理                                    
//=================================================================================================
void CCamera::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	// ビュー変換行列作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_eye, &m_at, &m_up);

	//プロジェクション行列作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DX_PI / 3,								//or D3DXToRadian(60)
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,		//
		0.1f,										//
		1000.0f);									//

	//ビュー、プロジェクション行列の設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
