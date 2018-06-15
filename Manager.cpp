//=================================================================================================
//                                                        
//�@�@�@�}�l�[�W���[�v���O����[Manager.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.19            
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"Manager.h"

#if defined(DEBUG)
#include"DebugGUI.h"
#endif//defined(DEBUG)

//=================================================================================================
//�@�@�@�C���X�^���X���̉�          
//=================================================================================================
CCamera *CManager::m_Camera = NULL;
CLight *CManager::m_Light = NULL;
CField *CManager::m_Field = NULL;

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X��������         
//=================================================================================================
bool CManager::Init( HWND hWnd, BOOL bWindow)
{
	//DirectX�������N���X��������
	CRenderer::Init(hWnd, bWindow);
	m_Camera = new CCamera();
#if defined(DEBUG)
	CDebugGUI::SetMainCameraPoint(m_Camera);
#endif//defined(DEBUG)
	m_Light = new CLight();
	CScene2D::Create(10,2);
	CScene3D::Create();
	m_Field = CField::Create(100,100);
#if defined(DEBUG)
	CDebugGUI::SetPlayerPoint(CPlayer::Create(D3DXVECTOR3(-0.5f, 1.0f, -0.4f)));
#else//defined(DEBUG)
	CPlayer::Create(D3DXVECTOR3(-0.5f, 1.0f, -0.4f));
#endif//defined(DEBUG)
	CScenePolygon::Create();
	return true;
}

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X�I������         
//=================================================================================================
void CManager::Uninit(void)
{
	delete m_Camera;
	delete m_Light;
	//�V�[���I�u�W�F�N�g�̉��
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
}

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X�`�揈��         
//=================================================================================================
void CManager::Draw(void)
{
#if defined(DEBUG)
	//ImGuiDirectX�`��O�̏���
	ImGui::EndFrame();
#endif//defined(DEBUG)

	//DirectX�������N���X�`��J�n���� 
	CRenderer::DrawBegin();

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(CRenderer::GetD3DDevice()->BeginScene()))
	{
		m_Camera->Update();
		m_Light->Update();
		//�V�[���I�u�W�F�N�g�̕`��
		CScene::DrawAll();
		//Present�̏I������
		CRenderer::GetD3DDevice()->EndScene();

#if defined(DEBUG)
		//ImGui����
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
#endif//defined(DEBUG)

	}
	//DirectX�������N���X�`��I������ 
	CRenderer::DrawEnd();
}

CField * CManager::GetField(void)
{
	return CManager::m_Field;
}
