//=================================================================================================
//                                                        
//�@�@�@���C�g�N���X�v���O����[Light.h]                  
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include "Light.h"
#include "Renderer.h"
#include "input.h"
#include "Camera.h"

//=================================================================================================
//�@�@�@���C�g�N���X�R���X�g���N�^                                    
//=================================================================================================
CLight::CLight()
{
	fRot = 0.0f;
	{
		ZeroMemory(&m_Light, sizeof(m_Light));

		//���C�g�^
		m_Light.Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̕���
		D3DXVECTOR3 vecDir(0.0f, -1.0f, 0.0f);							//���C�g�x�N�g��
		D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &vecDir);

		//�g�U���i���̃��C���F�j�F�̐ݒ�
		m_Light.Diffuse.r = 1.0f;
		m_Light.Diffuse.g = 1.0f;
		m_Light.Diffuse.b = 1.0f;
		m_Light.Diffuse.a = 1.0f;

		//�����i�e�Ɍ����F�j�F�̐ݒ�
		m_Light.Ambient.r = 0.5f;
		m_Light.Ambient.g = 0.5f;
		m_Light.Ambient.b = 0.5f;
		m_Light.Ambient.a = 1.0f;

		//���ʌ��i�}�e���A�����ݒ肳��Ă�����A�e�J�������j
		//�}�e���A�����ݒ肳��Ă��Ȃ��ƌ��ʂ͕\��Ȃ�
		m_Light.Specular.r = 0.5f;
		m_Light.Specular.g = 0.5f;
		m_Light.Specular.b = 0.5f;
		m_Light.Specular.a = 1.0f;
	}
}

//=================================================================================================
//�@�@�@���C�g�N���X�f�X�g���N�^                                     
//=================================================================================================
CLight::~CLight()
{
}

//=================================================================================================
//�@�@�@���C�g�N���X������                                    
//=================================================================================================
bool CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	LPD3DXEFFECT pEffect = CRenderer::GetD3DEffect();

	//�V�F�[�_�[�g�p����
	/*{
		m_lightDir = D3DXVECTOR4(0, 1, 0, 0);
		// Z�o�b�t�@�[������L���ɂ���
		pDevice->SetRenderState(D3DRS_ZENABLE, true);

		//�V�F�[�_�[��ǂݍ���
		HRESULT hr;
		hr = D3DXCreateEffectFromFile(pDevice, "HLSL\\directionalLight.fx", NULL, NULL,
			D3DXSHADER__DEBUG | D3DXSHADER_SKIPOPTIMIZATION, NULL, &pEffect, NULL);

		if (FAILED(hr))
		{
			MessageBox(NULL, "�V�F�[�_�[�t�@�C���ǂݍ��ݎ��s�B", "�G���[", MB_OK);					//�e�N�X�`�����ǂݍ��߃G���[���b�Z�[�W
			return false;
		}
		CRenderer::SetD3DEffect(pEffect);
	}*/

	return true;
}

//=================================================================================================
//�@�@�@���C�g�N���X�X�V����                                    
//=================================================================================================
void CLight::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	LPD3DXEFFECT pEffect = CRenderer::GetD3DEffect();

	{
		pDevice->SetLight(0, &m_Light);
		pDevice->LightEnable(0, TRUE);
		//�O���[�o���A���r�G���g�̐ݒ�
		pDevice->SetRenderState(
			D3DRS_AMBIENT,
			D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	}

	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	static D3DXMATRIX mLightRot = m;
	
	/*fRot += 0.01f;
	D3DXVECTOR3 LigtDir;
	LigtDir.x = m_lightDir.x;
	LigtDir.y = m_lightDir.y;
	LigtDir.z = m_lightDir.z;

	MatRotate(&LigtDir, fRot);
	SetDir(LigtDir);*/

	//��]
	/*{
		if (CInputKeyboard::GetKeyPress(DIK_LEFT))
		{
			D3DXMatrixRotationZ(&m, 0.001);
			mLightRot = mLightRot * m;
		}
		else if (CInputKeyboard::GetKeyPress(DIK_RIGHT))
		{
			D3DXMatrixRotationZ(&m, -0.001);
			mLightRot = mLightRot * m;
		}
		else if (CInputKeyboard::GetKeyPress(DIK_DOWN))
		{
			D3DXMatrixRotationX(&m, 0.001);
			mLightRot = mLightRot * m;
		}
		else if (CInputKeyboard::GetKeyPress(DIK_UP))
		{
			D3DXMatrixRotationX(&m, -0.001);
			mLightRot = mLightRot * m;
		}

		D3DXVec3Transform(&m_lightDir, &D3DXVECTOR3(0, 1, 0), &mLightRot);
		m_Light.Direction.x = m_lightDir.x;
		m_Light.Direction.y = m_lightDir.y;
		m_Light.Direction.z = m_lightDir.z;
	}*/


	
	

	//�V�F�[�_�[�g�p����
	/*{
		//�L�[�Ń��C�g�𑀍�
		D3DXMATRIX m;
		D3DXMatrixIdentity(&m);
		static D3DXMATRIX mLightRot = m;
		static D3DXMATRIX mLightTran = m;

		//��]
		if (CInputKeyboard::GetKeyPress(DIK_LEFT))
		{
			D3DXMatrixRotationZ(&m, 0.001);
			mLightRot = mLightRot * m;
		}
		else if (CInputKeyboard::GetKeyPress(DIK_RIGHT))
		{
			D3DXMatrixRotationZ(&m, -0.001);
			mLightRot = mLightRot * m;
		}
		else if (CInputKeyboard::GetKeyPress(DIK_DOWN))
		{
			D3DXMatrixRotationX(&m, 0.001);
			mLightRot = mLightRot * m;
		}
		else if (CInputKeyboard::GetKeyPress(DIK_UP))
		{
			D3DXMatrixRotationX(&m, -0.001);
			mLightRot = mLightRot * m;
		}
		D3DXVec4Transform(&m_lightDir, &D3DXVECTOR4(0, 1, 0, 0), &mLightRot);

		pEffect->SetTechnique("Phong");
		//���C�g������n��
		pEffect->SetVector("g_lightDir", &m_lightDir);

		pEffect->Begin(NULL, 0);
		{
			pEffect->BeginPass(0);


			pEffect->EndPass();
			pEffect->End();
		}
	}*/
}

//=================================================================================================
//�@�@�@���C�g�����ݒ�                               
//=================================================================================================
void CLight::SetDir(D3DXVECTOR3 vecDir)
{
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &vecDir);
}

//=================================================================================================
//�@�@�@�����i�e�Ɍ����F�j�F�̐ݒ�                               
//=================================================================================================
void CLight::SetAmbient(float r, float g, float b, float a)
{
	m_Light.Ambient.r = r;
	m_Light.Ambient.g = g;
	m_Light.Ambient.b = b;
	m_Light.Ambient.a = a;
}

//=================================================================================================
//�@�@�@�g�U���i���̃��C���F�j�F�̐ݒ�                                 
//=================================================================================================
void CLight::SetDiffuse(float r, float g, float b, float a)
{
	m_Light.Diffuse.r = r;
	m_Light.Diffuse.g = g;
	m_Light.Diffuse.b = b;
	m_Light.Diffuse.a = a;
}

//=================================================================================================
//�@�@�@���ˌ��̐ݒ�                                    
//=================================================================================================
void CLight::SetSpecular(float r, float g, float b, float a)
{
	m_Light.Specular.r = r;
	m_Light.Specular.g = g;
	m_Light.Specular.b = b;
	m_Light.Specular.a = a;
}

void CLight::MatRotate(D3DXVECTOR3 * Vect, float rt)
{
	D3DXMATRIX   mat;

	// �ϊ��}�g���b�N�X�̍쐬
	D3DXMatrixIdentity(&mat);
	mat._11 = cos(rt);   mat._13 = -sin(rt);
	mat._31 = sin(rt);   mat._33 = cos(rt);
	D3DXVec3TransformNormal(Vect, Vect, &mat);
}
