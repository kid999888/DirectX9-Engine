//=================================================================================================
//                                                        
//�@�@�@�}�l�[�W���[�v���O����[Manager.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.19            
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include "Manager.h"

//=================================================================================================
//�@�@�@���̒�`       
//=================================================================================================
CMode *CManager::m_Mode = nullptr;
CScene2D* CManager::m_Scene2D = nullptr;
bool CManager::m_bBlur = true;

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X��������         
//=================================================================================================
bool CManager::Init( HWND hWnd, BOOL bWindow)
{
	//DirectX�������N���X��������
	CRenderer::Init(hWnd, bWindow);
	m_Scene2D = CScene2D::Create(4, "Data\\Texture\\Null.png",1,1);
	m_Scene2D->m_bDraw = false;
	SetMode(new CModeTitle());
	m_bBlur = false;

	return true;
}

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X�I������         
//=================================================================================================
void CManager::Uninit(void)
{
	//���[�h�Ǘ��|�C���^�̉��
	m_Mode->Uninit();
	delete m_Mode;
	//�V�[���I�u�W�F�N�g�̃����[�X
	CScene::ReleaseAll();
	//DirectX�������N���X�I������
	CRenderer::Uninit();
}

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X�X�V����        
//=================================================================================================
void CManager::Update(void)
{
	//�V�[���I�u�W�F�N�g�̍X�V
	CScene::UpdateAll();
	//���[�h�̍X�V
	m_Mode->Update();
}

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X�`�揈��         
//=================================================================================================
void CManager::Draw(void)
{
#if defined(_DEBUG)
	//ImGuiDirectX�`��O�̏���
	ImGui::EndFrame();
#endif//defined(_DEBUG)
	if (m_bBlur)
	{
		CRenderer::GetD3DDevice()->SetRenderTarget(0, CRenderer::GetBlurSurface1());
	}
	//DirectX�������N���X�`��J�n���� 
	CRenderer::DrawBegin();

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(CRenderer::GetD3DDevice()->BeginScene()))
	{
		//���[�h�̕`��
		m_Mode->Draw();
		//�V�[���I�u�W�F�N�g�̕`��
		CScene::DrawAll();
		if (m_bBlur)
		{
			CRenderer::GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			CRenderer::GetD3DDevice()->SetTexture(0, CRenderer::GetBlurTexture2());
			m_Scene2D->SetScaleX(1.001f);
			m_Scene2D->SetScaleY(1.001f);
			m_Scene2D->DrawWithOutTexture(240);
			CRenderer::GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
		//Present�̏I������
		CRenderer::GetD3DDevice()->EndScene();

#if defined(_DEBUG)
		//ImGui����
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
#endif//defined(_DEBUG)

	}
	if (m_bBlur)
	{
		CRenderer::GetD3DDevice()->SetRenderTarget(0, CRenderer::GetBackBufferSurface());
		CRenderer::GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		CRenderer::GetD3DDevice()->SetTexture(0, CRenderer::GetBlurTexture1());
		m_Scene2D->SetScaleX(1.0f);
		m_Scene2D->SetScaleY(1.0f);
		m_Scene2D->DrawWithOutTexture(255);
		CRenderer::GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
	//DirectX�������N���X�`��I������ 
	CRenderer::DrawEnd();
}

//=================================================================================================
//�@�@�@�Q�[�����[�h�̐ݒ�       
//=================================================================================================
void CManager::SetMode(CMode * Mode)
{
	if (m_Mode != NULL)
	{
		m_Mode->Uninit();
		delete m_Mode;
	}
	m_Mode = Mode;
	if (m_Mode != NULL)
	{
		m_Mode->Init();
	}
}
