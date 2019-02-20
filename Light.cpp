//=================================================================================================
//                                                        
//　　　ライトクラスプログラム[Light.h]                  
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include "Light.h"
#include "Renderer.h"
#include "input.h"
#include "Camera.h"

//=================================================================================================
//　　　ライトクラスコンストラクタ                                    
//=================================================================================================
CLight::CLight()
{
	fRot = 0.0f;
	{
		ZeroMemory(&m_Light, sizeof(m_Light));

		//ライト型
		m_Light.Type = D3DLIGHT_DIRECTIONAL;

		//ライトの方向
		D3DXVECTOR3 vecDir(0.0f, -1.0f, 0.0f);							//ライトベクトル
		D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &vecDir);

		//拡散光（光のメイン色）色の設定
		m_Light.Diffuse.r = 1.0f;
		m_Light.Diffuse.g = 1.0f;
		m_Light.Diffuse.b = 1.0f;
		m_Light.Diffuse.a = 1.0f;

		//環境光（影に現れる色）色の設定
		m_Light.Ambient.r = 0.5f;
		m_Light.Ambient.g = 0.5f;
		m_Light.Ambient.b = 0.5f;
		m_Light.Ambient.a = 1.0f;

		//鏡面光（マテリアルが設定されていたら、テカリ部分）
		//マテリアルが設定されていないと効果は表れない
		m_Light.Specular.r = 0.5f;
		m_Light.Specular.g = 0.5f;
		m_Light.Specular.b = 0.5f;
		m_Light.Specular.a = 1.0f;
	}
}

//=================================================================================================
//　　　ライトクラスデストラクタ                                     
//=================================================================================================
CLight::~CLight()
{
}

//=================================================================================================
//　　　ライトクラス初期化                                    
//=================================================================================================
bool CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	LPD3DXEFFECT pEffect = CRenderer::GetD3DEffect();

	//シェーダー使用部分
	/*{
		m_lightDir = D3DXVECTOR4(0, 1, 0, 0);
		// Zバッファー処理を有効にする
		pDevice->SetRenderState(D3DRS_ZENABLE, true);

		//シェーダーを読み込む
		HRESULT hr;
		hr = D3DXCreateEffectFromFile(pDevice, "HLSL\\directionalLight.fx", NULL, NULL,
			D3DXSHADER__DEBUG | D3DXSHADER_SKIPOPTIMIZATION, NULL, &pEffect, NULL);

		if (FAILED(hr))
		{
			MessageBox(NULL, "シェーダーファイル読み込み失敗。", "エラー", MB_OK);					//テクスチャが読み込めエラーメッセージ
			return false;
		}
		CRenderer::SetD3DEffect(pEffect);
	}*/

	return true;
}

//=================================================================================================
//　　　ライトクラス更新処理                                    
//=================================================================================================
void CLight::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	LPD3DXEFFECT pEffect = CRenderer::GetD3DEffect();

	{
		pDevice->SetLight(0, &m_Light);
		pDevice->LightEnable(0, TRUE);
		//グローバルアンビエントの設定
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

	//回転
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


	
	

	//シェーダー使用部分
	/*{
		//キーでライトを操作
		D3DXMATRIX m;
		D3DXMatrixIdentity(&m);
		static D3DXMATRIX mLightRot = m;
		static D3DXMATRIX mLightTran = m;

		//回転
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
		//ライト方向を渡す
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
//　　　ライト方向設定                               
//=================================================================================================
void CLight::SetDir(D3DXVECTOR3 vecDir)
{
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &vecDir);
}

//=================================================================================================
//　　　環境光（影に現れる色）色の設定                               
//=================================================================================================
void CLight::SetAmbient(float r, float g, float b, float a)
{
	m_Light.Ambient.r = r;
	m_Light.Ambient.g = g;
	m_Light.Ambient.b = b;
	m_Light.Ambient.a = a;
}

//=================================================================================================
//　　　拡散光（光のメイン色）色の設定                                 
//=================================================================================================
void CLight::SetDiffuse(float r, float g, float b, float a)
{
	m_Light.Diffuse.r = r;
	m_Light.Diffuse.g = g;
	m_Light.Diffuse.b = b;
	m_Light.Diffuse.a = a;
}

//=================================================================================================
//　　　反射光の設定                                    
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

	// 変換マトリックスの作成
	D3DXMatrixIdentity(&mat);
	mat._11 = cos(rt);   mat._13 = -sin(rt);
	mat._31 = sin(rt);   mat._33 = cos(rt);
	D3DXVec3TransformNormal(Vect, Vect, &mat);
}
