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
#include"main.h"

//=================================================================================================
//�@�@�@�C���X�^���X���̉�          
//=================================================================================================
CCamera *CManager::m_Camera = NULL;
CLight *CManager::m_Light = NULL;
CScene2D *CManager::m_Scene2D = NULL;
CScene3D *CManager::m_Scene3D = NULL;
CSceneModel *CManager::m_SceneModel = NULL;

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X��������         
//=================================================================================================
bool CManager::Init( HWND hWnd, BOOL bWindow)
{
	//DirectX�������N���X��������
	CRenderer::Init(hWnd, bWindow);
	m_Camera = new CCamera();
	m_Light = new CLight();
	m_Scene2D = new CScene2D();
	m_Scene2D->Init();
	m_Scene3D = new CScene3D();
	m_Scene3D->Init();
	m_SceneModel = new CSceneModel();
	m_SceneModel->Init();

	return true;
}

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X�I������         
//=================================================================================================
void CManager::Uninit(void)
{
	delete m_Camera;
	delete m_Light;
	m_Scene2D->Uninit();
	delete m_Scene2D;
	m_Scene3D->Uninit();
	delete m_Scene3D;
	m_SceneModel->Uninit();
	delete m_SceneModel;
	//DirectX�������N���X�I������
	CRenderer::Uninit();
}

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X�X�V����        
//=================================================================================================
void CManager::Update(void)
{
	m_Scene2D->Update();
	m_Scene3D->Update();
	m_SceneModel->Update();
}

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X�`�揈��         
//=================================================================================================
void CManager::Draw(void)
{
	//DirectX�������N���X�`��J�n���� 
	CRenderer::DrawBegin();

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(CRenderer::GetD3DDevice()->BeginScene()))
	{
		m_Camera->Update();
		m_Light->Update();
		//2D�|���S���`��
		m_Scene2D->Draw();
		//3D�|���S���`��
		m_Scene3D->Draw();
		//3D�|���S���`��
		m_SceneModel->Draw();
		//Present�̏I������
		CRenderer::GetD3DDevice()->EndScene();
	}
	//DirectX�������N���X�`��I������ 
	CRenderer::DrawEnd();
}
