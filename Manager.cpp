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
#include"input.h"

#if defined(DEBUG)
#include"DebugGUI.h"
#endif//defined(DEBUG)

//=================================================================================================
//�@�@�@�C���X�^���X���̉�          
//=================================================================================================
CCamera *CManager::m_Camera = NULL;
CLight *CManager::m_Light = NULL;
CField *CManager::m_Field = NULL;
CPlayer *CManager:: m_Player = NULL;
CScene3D *CManager::m_Scene3D = NULL;
CScene2D *CManager::m_Scene2D = NULL;
CNumber *CManager::m_Number = NULL;
bool CManager::m_bDisable = false;

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X��������         
//=================================================================================================
bool CManager::Init( HWND hWnd, BOOL bWindow)
{
	m_bDisable = false;
	//DirectX�������N���X��������
	CRenderer::Init(hWnd, bWindow);
	m_Camera = new CCamera();
	m_Light = new CLight();
	m_Field = CField::Create(100, 100);
	m_Player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	/*m_Scene2D = CScene2D::Create(10,2);*/
	m_Number = CNumber::Create(0);
	m_Scene3D = CScene3D::Create();
	CScenePolygon::Create();
#if defined(DEBUG)
	CDebugGUI::SetMainCamera(m_Camera);
	CDebugGUI::SetField(m_Field);
	CDebugGUI::SetPlayer(m_Player);
#else//defined(DEBUG)
	CPlayer::Create(D3DXVECTOR3(-0.5f, 1.0f, -0.4f));
#endif//defined(DEBUG)
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

	if (m_Player->BallJudgement(m_Scene3D->GetPosition(), m_Player->GetPosition(), 1.0f, 1.0f))
	{
		m_Scene3D->SetPositionY(m_Scene3D->GetPositionY() + 0.06f);
	}
	else
	{
		m_Scene3D->SetPositionY(1.0f);
	}

	if (GetKeyboardTrigger(DIK_Z))//�΂߂ɐi��
	{
		m_Number->SetNumber(m_Number->GetNumber() + 1);
	}
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
