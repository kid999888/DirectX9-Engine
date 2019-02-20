#include "SceneShadow.h"
#include "Renderer.h"


CSceneShadow::CSceneShadow(int nPriority, CField* pField) : CScene(nPriority)
{
	m_Type = SCENE_TYPE_SHADOW;
	m_Field = pField;

}


CSceneShadow::~CSceneShadow()
{
}

bool CSceneShadow::Init(void)
{
	m_Model = CSceneModel::Create("Data\\Model\\ufo.x");
	m_Model->m_bDraw = false;
	m_Model->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Model->SetPositionY(-1.0f);
	m_Model->SetScaleX(1.5f);
	m_Model->SetScaleZ(1.5f);
	this->SetPositionY(-1.0f);
	m_ShadowShade = CScene2D::Create(2, "Data\\Texture\\Shadow.png", 1, 1);
	m_ShadowShade->m_bDraw = false;
	return true;
}

void CSceneShadow::Uninit(void)
{
}

void CSceneShadow::Update(void)
{
}

void CSceneShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	m_Field->Draw();
	//ステンシルバッファ設定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_Model->SetPosition(this->GetPosition());

	m_Model->Draw();
	//ステンシルバッファ設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	m_Model->Draw();
	//ステンシルバッファ設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	m_ShadowShade->Draw();
	//ステンシルバッファ設定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

CSceneShadow * CSceneShadow::Create(CField* pField)
{
	CSceneShadow *SceneShadow = new CSceneShadow(2, pField);
	SceneShadow->Init();
	return SceneShadow;
}
