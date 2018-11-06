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
#include "Renderer.h"
#include "input.h"

//=================================================================================================
//　　　実体定義
//=================================================================================================

//=================================================================================================
//　　　カメラクラスコンストラクタ                                    
//=================================================================================================
CCamera::CCamera()
{
	//カメラ位置の初期化
	m_eye = D3DXVECTOR3(0.0f, 0.0f, -10.0f);
	m_at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLengthInterval = 0.0f;
	m_fLengthIntervalXZ = 0.0f;

	//視点操作フラッグ
	CameraViewFlag(false);

	float fLengthXZ;

	m_fLengthInterval = sqrtf((m_at.x - m_eye.x) * (m_at.x - m_eye.x)
		+ (m_at.y - m_eye.y) * (m_at.y - m_eye.y)
		+ (m_at.z - m_eye.z) * (m_at.z - m_eye.z));
	fLengthXZ = sqrtf((m_at.x - m_eye.x) * (m_at.x - m_eye.x)
		+ (m_at.z - m_eye.z) * (m_at.z - m_eye.z));

	m_rot.y = atan2f((m_at.x - m_eye.x), (m_at.z - m_eye.z));
	m_rot.x = atan2f((m_at.y - m_eye.y), fLengthXZ);

	m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;

	if (fLengthXZ == 0.0f)
	{
		m_up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}
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
	LPD3DXEFFECT pEffect = CRenderer::GetD3DEffect();

	// ビュー変換行列作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_eye, &m_at, &m_up);

	//プロジェクション行列作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45),								//or D3DXToRadian(60) D3DX_PI / 3
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,		//
		0.1f,										//
		1000.0f);									//

	//ビュー、プロジェクション行列の設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	if (m_bViewChange)
	{
		ViewChange();
	}
	
	
}

//=================================================================================================
//　　　カメラ位置の設定
//=================================================================================================
void CCamera::SetCameraPos(D3DXVECTOR3 veEyePos)
{
	m_eye = veEyePos;
}

//=================================================================================================
//　　　カメラ注視点の設定
//=================================================================================================
void CCamera::SetCameraAtPos(D3DXVECTOR3 veAtPos)
{
	m_at = veAtPos;
}

void CCamera::ViewChange(void)
{
	float fValueX, fValueY, fValueZ;
	fValueX = CInputMouse::GetAxisX();
	fValueY = CInputMouse::GetAxisY();
	fValueZ = CInputMouse::GetAxisZ();


	// キー操作
	if (CInputKeyboard::GetKeyPress(DIK_LEFT))
	{
		if (CInputKeyboard::GetKeyPress(DIK_UP))
		{// 左前移動
			m_eye.x -= cosf(m_rot.y + PI * 0.25f) * VALUE_MOVE;
			m_eye.z += sinf(m_rot.y + PI * 0.25f) * VALUE_MOVE;
		}
		else if (CInputKeyboard::GetKeyPress(DIK_DOWN))
		{// 左後移動
			m_eye.x -= cosf(m_rot.y - PI * 0.25f) * VALUE_MOVE;
			m_eye.z += sinf(m_rot.y - PI * 0.25f) * VALUE_MOVE;
		}
		else
		{// 左移動
			m_eye.x -= cosf(m_rot.y) * VALUE_MOVE;
			m_eye.z += sinf(m_rot.y) * VALUE_MOVE;
		}

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	else if (CInputKeyboard::GetKeyPress(DIK_RIGHT))
	{// 右移動
		if (CInputKeyboard::GetKeyPress(DIK_UP))
		{// 右前移動
			m_eye.x += cosf(m_rot.y - PI * 0.25f) * VALUE_MOVE;
			m_eye.z -= sinf(m_rot.y - PI * 0.25f) * VALUE_MOVE;
		}
		else if (CInputKeyboard::GetKeyPress(DIK_DOWN))
		{// 右後移動
			m_eye.x += cosf(m_rot.y + PI * 0.25f) * VALUE_MOVE;
			m_eye.z -= sinf(m_rot.y + PI * 0.25f) * VALUE_MOVE;
		}
		else
		{// 右移動
			m_eye.x += cosf(m_rot.y) * VALUE_MOVE;
			m_eye.z -= sinf(m_rot.y) * VALUE_MOVE;
		}

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	else if (CInputKeyboard::GetKeyPress(DIK_UP))
	{// 前移動
		m_eye.x += sinf(m_rot.y) * VALUE_MOVE;
		m_eye.z += cosf(m_rot.y) * VALUE_MOVE;

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	else if (CInputKeyboard::GetKeyPress(DIK_DOWN))
	{// 後移動
		m_eye.x -= sinf(m_rot.y) * VALUE_MOVE;
		m_eye.z -= cosf(m_rot.y) * VALUE_MOVE;

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}

	if (CInputKeyboard::GetKeyPress(DIK_T))
	{// 注視点移動「上」
		m_rot.x += VALUE_ROTATE;
		if (m_rot.x > (PI / 2.0f - PI * 0.1f))
		{
			m_rot.x = (PI / 2.0f - PI * 0.1f);
		}

		m_at.y = m_eye.y + sinf(m_rot.x) * m_fLengthInterval;

		m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	if (CInputKeyboard::GetKeyPress(DIK_B))
	{// 注視点移動「下」
		m_rot.x -= VALUE_ROTATE;
		if (m_rot.x < (-PI / 2.0f + PI * 0.1f))
		{
			m_rot.x = (-PI / 2.0f + PI * 0.1f);
		}

		m_at.y = m_eye.y + sinf(m_rot.x) * m_fLengthInterval;

		m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	if (CInputKeyboard::GetKeyPress(DIK_Q))
	{// 注視点移動「左」
		m_rot.y -= VALUE_ROTATE;
		if (m_rot.y < -PI)
		{
			m_rot.y += PI * 2.0f;
		}

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	if (CInputKeyboard::GetKeyPress(DIK_E))
	{// 注視点移動「右」
		m_rot.y += VALUE_ROTATE;
		if (m_rot.y > PI)
		{
			m_rot.y -= PI * 2.0f;
		}

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}

	if (CInputKeyboard::GetKeyPress(DIK_Y))
	{// 視点移動「上」
		m_rot.x -= VALUE_ROTATE;
		if (m_rot.x < (-PI / 2.0f + PI * 0.02f))
		{
			m_rot.x = (-PI / 2.0f + PI * 0.02f);
		}

		m_eye.y = m_at.y - sinf(m_rot.x) * m_fLengthInterval;

		m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
		m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	if (CInputKeyboard::GetKeyPress(DIK_N))
	{// 視点移動「下」
		m_rot.x += VALUE_ROTATE;
		if (m_rot.x > (PI / 2.0f - PI * 0.02f))
		{
			m_rot.x = (PI / 2.0f - PI * 0.02f);
		}

		m_eye.y = m_at.y - sinf(m_rot.x) * m_fLengthInterval;

		m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
		m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	if (CInputKeyboard::GetKeyPress(DIK_Z))
	{// 視点移動「左」
		m_rot.y += VALUE_ROTATE;
		if (m_rot.y > PI)
		{
			m_rot.y -= PI * 2.0f;
		}

		m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	if (CInputKeyboard::GetKeyPress(DIK_C))
	{// 視点移動「右」
		m_rot.y -= VALUE_ROTATE;
		if (m_rot.y < -PI)
		{
			m_rot.y += PI * 2.0f;
		}

		m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
	}

	if (fValueZ)
	{// 注視点から視点の距離変更
		m_fLengthInterval -= (fValueZ / CAM_LENGTH_RATE);
		if (m_fLengthInterval < CAM_LENGTH_LIMIT_MIN)
		{
			m_fLengthInterval = CAM_LENGTH_LIMIT_MIN;
		}
		else if (m_fLengthInterval > CAM_LENGTH_LIMIT_MAX)
		{
			m_fLengthInterval = CAM_LENGTH_LIMIT_MAX;
		}
		m_eye.y = m_at.y - sinf(m_rot.x) * m_fLengthInterval;

		m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
		m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
	}

	if (CInputMouse::GetLeftPress())
	{
		if (CInputMouse::GetRightPress())
		{// 移動
			if (fValueX != 0 || fValueY != 0)
			{
				float angle = atan2f(fValueX, fValueY);
				float length = sqrtf(fValueX*fValueX + fValueY * fValueY) * VALUE_MOVE_DRAG;

				angle -= m_rot.y;
				if (angle < -PI) angle += PI * 2.0f;

				m_at.x -= sinf(angle) * length;
				m_at.z += cosf(angle) * length;

				m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
				m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
			}
		}
		else
		{// 回転
			if (fValueX < 0)
			{// 視点移動「左」
				m_rot.y -= PI * fValueX * VALUE_ROTATE_MOUSE;
				if (m_rot.y < -PI)
				{
					m_rot.y += PI * 2.0f;
				}

				m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
				m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
			}
			else if (fValueX > 0)
			{// 視点移動「右」
				m_rot.y -= PI * fValueX * VALUE_ROTATE_MOUSE;
				if (m_rot.y > PI)
				{
					m_rot.y -= PI * 2.0f;
				}

				m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
				m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
			}

			if (fValueY < 0)
			{// 視点移動「上」
				m_rot.x -= PI * fValueY * VALUE_ROTATE_MOUSE;
				if (m_rot.x >(PI / 2.0f - PI * 0.02f))
				{
					m_rot.x = (PI / 2.0f - PI * 0.02f);
				}

				m_eye.y = m_at.y - sinf(m_rot.x) * m_fLengthInterval;

				m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
				m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
				m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
			}
			else if (fValueY > 0)
			{// 視点移動「下」
				m_rot.x -= PI * fValueY * VALUE_ROTATE_MOUSE;
				if (m_rot.x < (-PI / 2.0f + PI * 0.02f))
				{
					m_rot.x = (-PI / 2.0f + PI * 0.02f);
				}

				m_eye.y = m_at.y - sinf(m_rot.x) * m_fLengthInterval;

				m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
				m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
				m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
			}
		}
	}
	else if (CInputMouse::GetRightPress())
	{
		if (fValueX < 0)
		{// 注視点移動「左」
			m_rot.y += PI * fValueX * VALUE_ROTATE_MOUSE;
			if (m_rot.y < -PI)
			{
				m_rot.y += PI * 2.0f;
			}

			m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
			m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
		}
		else if (fValueX > 0)
		{// 注視点移動「右」
			m_rot.y += PI * fValueX * VALUE_ROTATE_MOUSE;
			if (m_rot.y > PI)
			{
				m_rot.y -= PI * 2.0f;
			}

			m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
			m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
		}

		if (fValueY < 0)
		{// 注視点移動「上」
			m_rot.x -= PI * fValueY * VALUE_ROTATE_MOUSE;
			if (m_rot.x >(PI / 2.0f - PI * 0.1f))
			{
				m_rot.x = (PI / 2.0f - PI * 0.1f);
			}

			m_at.y = m_eye.y + sinf(m_rot.x) * m_fLengthInterval;

			m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
			m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
			m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
		}
		else if (fValueY > 0)
		{// 注視点移動「下」
			m_rot.x -= PI * fValueY * VALUE_ROTATE_MOUSE;
			if (m_rot.x < (-PI / 2.0f + PI * 0.1f))
			{
				m_rot.x = (-PI / 2.0f + PI * 0.1f);
			}

			m_at.y = m_eye.y + sinf(m_rot.x) * m_fLengthInterval;

			m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
			m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
			m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
		}
	}
}
