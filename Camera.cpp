//=================================================================================================
//                                                        
//�@�@�@�J�����N���X�v���O����[Camera.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include "Camera.h"
#include "Renderer.h"
#include "input.h"

//=================================================================================================
//�@�@�@���̒�`
//=================================================================================================

//=================================================================================================
//�@�@�@�J�����N���X�R���X�g���N�^                                    
//=================================================================================================
CCamera::CCamera()
{
	//�J�����ʒu�̏�����
	m_eye = D3DXVECTOR3(0.0f, 0.0f, -10.0f);
	m_at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLengthInterval = 0.0f;
	m_fLengthIntervalXZ = 0.0f;

	//���_����t���b�O
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
//�@�@�@�J�����N���X�f�X�g���N�^                                     
//=================================================================================================
CCamera::~CCamera()
{
}

//=================================================================================================
//�@�@�@�J�����N���X�X�V����                                    
//=================================================================================================
void CCamera::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	LPD3DXEFFECT pEffect = CRenderer::GetD3DEffect();

	// �r���[�ϊ��s��쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_eye, &m_at, &m_up);

	//�v���W�F�N�V�����s��쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45),								//or D3DXToRadian(60) D3DX_PI / 3
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,		//
		0.1f,										//
		1000.0f);									//

	//�r���[�A�v���W�F�N�V�����s��̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	if (m_bViewChange)
	{
		ViewChange();
	}
	
	
}

//=================================================================================================
//�@�@�@�J�����ʒu�̐ݒ�
//=================================================================================================
void CCamera::SetCameraPos(D3DXVECTOR3 veEyePos)
{
	m_eye = veEyePos;
}

//=================================================================================================
//�@�@�@�J���������_�̐ݒ�
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


	// �L�[����
	if (CInputKeyboard::GetKeyPress(DIK_LEFT))
	{
		if (CInputKeyboard::GetKeyPress(DIK_UP))
		{// ���O�ړ�
			m_eye.x -= cosf(m_rot.y + PI * 0.25f) * VALUE_MOVE;
			m_eye.z += sinf(m_rot.y + PI * 0.25f) * VALUE_MOVE;
		}
		else if (CInputKeyboard::GetKeyPress(DIK_DOWN))
		{// ����ړ�
			m_eye.x -= cosf(m_rot.y - PI * 0.25f) * VALUE_MOVE;
			m_eye.z += sinf(m_rot.y - PI * 0.25f) * VALUE_MOVE;
		}
		else
		{// ���ړ�
			m_eye.x -= cosf(m_rot.y) * VALUE_MOVE;
			m_eye.z += sinf(m_rot.y) * VALUE_MOVE;
		}

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	else if (CInputKeyboard::GetKeyPress(DIK_RIGHT))
	{// �E�ړ�
		if (CInputKeyboard::GetKeyPress(DIK_UP))
		{// �E�O�ړ�
			m_eye.x += cosf(m_rot.y - PI * 0.25f) * VALUE_MOVE;
			m_eye.z -= sinf(m_rot.y - PI * 0.25f) * VALUE_MOVE;
		}
		else if (CInputKeyboard::GetKeyPress(DIK_DOWN))
		{// �E��ړ�
			m_eye.x += cosf(m_rot.y + PI * 0.25f) * VALUE_MOVE;
			m_eye.z -= sinf(m_rot.y + PI * 0.25f) * VALUE_MOVE;
		}
		else
		{// �E�ړ�
			m_eye.x += cosf(m_rot.y) * VALUE_MOVE;
			m_eye.z -= sinf(m_rot.y) * VALUE_MOVE;
		}

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	else if (CInputKeyboard::GetKeyPress(DIK_UP))
	{// �O�ړ�
		m_eye.x += sinf(m_rot.y) * VALUE_MOVE;
		m_eye.z += cosf(m_rot.y) * VALUE_MOVE;

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	else if (CInputKeyboard::GetKeyPress(DIK_DOWN))
	{// ��ړ�
		m_eye.x -= sinf(m_rot.y) * VALUE_MOVE;
		m_eye.z -= cosf(m_rot.y) * VALUE_MOVE;

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}

	if (CInputKeyboard::GetKeyPress(DIK_T))
	{// �����_�ړ��u��v
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
	{// �����_�ړ��u���v
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
	{// �����_�ړ��u���v
		m_rot.y -= VALUE_ROTATE;
		if (m_rot.y < -PI)
		{
			m_rot.y += PI * 2.0f;
		}

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	if (CInputKeyboard::GetKeyPress(DIK_E))
	{// �����_�ړ��u�E�v
		m_rot.y += VALUE_ROTATE;
		if (m_rot.y > PI)
		{
			m_rot.y -= PI * 2.0f;
		}

		m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
	}

	if (CInputKeyboard::GetKeyPress(DIK_Y))
	{// ���_�ړ��u��v
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
	{// ���_�ړ��u���v
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
	{// ���_�ړ��u���v
		m_rot.y += VALUE_ROTATE;
		if (m_rot.y > PI)
		{
			m_rot.y -= PI * 2.0f;
		}

		m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
	}
	if (CInputKeyboard::GetKeyPress(DIK_C))
	{// ���_�ړ��u�E�v
		m_rot.y -= VALUE_ROTATE;
		if (m_rot.y < -PI)
		{
			m_rot.y += PI * 2.0f;
		}

		m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
		m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
	}

	if (fValueZ)
	{// �����_���王�_�̋����ύX
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
		{// �ړ�
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
		{// ��]
			if (fValueX < 0)
			{// ���_�ړ��u���v
				m_rot.y -= PI * fValueX * VALUE_ROTATE_MOUSE;
				if (m_rot.y < -PI)
				{
					m_rot.y += PI * 2.0f;
				}

				m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
				m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
			}
			else if (fValueX > 0)
			{// ���_�ړ��u�E�v
				m_rot.y -= PI * fValueX * VALUE_ROTATE_MOUSE;
				if (m_rot.y > PI)
				{
					m_rot.y -= PI * 2.0f;
				}

				m_eye.x = m_at.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
				m_eye.z = m_at.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
			}

			if (fValueY < 0)
			{// ���_�ړ��u��v
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
			{// ���_�ړ��u���v
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
		{// �����_�ړ��u���v
			m_rot.y += PI * fValueX * VALUE_ROTATE_MOUSE;
			if (m_rot.y < -PI)
			{
				m_rot.y += PI * 2.0f;
			}

			m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
			m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
		}
		else if (fValueX > 0)
		{// �����_�ړ��u�E�v
			m_rot.y += PI * fValueX * VALUE_ROTATE_MOUSE;
			if (m_rot.y > PI)
			{
				m_rot.y -= PI * 2.0f;
			}

			m_at.x = m_eye.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
			m_at.z = m_eye.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
		}

		if (fValueY < 0)
		{// �����_�ړ��u��v
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
		{// �����_�ړ��u���v
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
