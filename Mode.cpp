//=================================================================================================
//                                                        
//�@�@�@���[�h�����N���X �v���O����[Mode.h]
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.03      
//                                                        
//=================================================================================================

#include"input.h"
#include"Collision.h"

#if defined(DEBUG)
#include"DebugGUI.h"
#endif//defined(DEBUG)

//=================================================================================================
//�@�@�@���̒�`       
//=================================================================================================
CCamera *CModeGame::m_Camera = NULL;
CLight *CModeGame::m_Light = NULL;
CField *CModeGame::m_Field = NULL;
CPlayer *CModeGame::m_Player = NULL;
CScene3D *CModeGame::m_Scene3D = NULL;
CNumber *CModeGame::m_Number = NULL;
CScenePolygon* CModeGame::m_ScenePolygon = NULL;
CSceneBillBoard* CModeGame::m_SceneBillBoard = NULL;
CCamera *CModeTitle::m_Camera = NULL;
CLight *CModeTitle::m_Light = NULL;
CScene2D *CModeTitle::m_Scene2D = NULL;
CCamera *CModeResult::m_Camera = NULL;
CLight *CModeResult::m_Light = NULL;
CScene2D *CModeResult::m_Scene2D = NULL;

//=================================================================================================
//�@�@�@�Q�[�����[�h�N���X                                       
//=================================================================================================

//=================================================================================================
//�@�@�@�Q�[�����[�h�N���X��������                                       
//=================================================================================================
bool CModeGame::Init(void)
{
	m_ModeId = MODE_GAME;
	this->m_Camera = new CCamera();
	this->m_Light = new CLight();
	m_Field = CField::Create(100, 100);
	m_Player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Number = CNumber::Create(0);
	m_Scene3D = CScene3D::Create();
	m_ScenePolygon = CScenePolygon::Create();
	/*m_ScenePolygon->m_bDraw = false;*/
	m_SceneBillBoard = CSceneBillBoard::Create();
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
//�@�@�@�Q�[�����[�h�N���X�I������                                       
//=================================================================================================
void CModeGame::Uninit(void)
{
	delete this->m_Camera;
	this->m_Camera = nullptr;
	delete this->m_Light;
	this->m_Light = nullptr;
	//�V�[���I�u�W�F�N�g�̉��
	CScene::ReleaseAll();
}

//=================================================================================================
//�@�@�@�Q�[�����[�h�N���X�X�V����                                       
//=================================================================================================
void CModeGame::Update(void)
{
	if (CCollision::BallJudgement(m_Scene3D->GetPosition(), m_Player->GetPosition(), 1.0f, 1.0f))
	{
		m_Scene3D->SetPositionY(m_Scene3D->GetPositionY() + 0.06f);
		CManager::SetMode(new CModeResult());
	}
	else
	{
		m_Scene3D->SetPositionY(1.0f);
	}

	if (CInputKeyboard::GetKeyTrigger(DIK_Z))
	{
		m_Number->SetNumber(m_Number->GetNumber() + 1);
	}
}

//=================================================================================================
//�@�@�@�Q�[�����[�h�N���X�`�揈��                                       
//=================================================================================================
void CModeGame::Draw(void)
{
	m_Camera->Update();
	m_Light->Update();
}

//=================================================================================================
//�@�@�@�^�[�g�����[�h�N���X                                       
//=================================================================================================

//=================================================================================================
//�@�@�@�^�[�g�����[�h�N���X��������                                       
//=================================================================================================
bool CModeTitle::Init(void)
{
	m_ModeId = MODE_TITLE;
	this->m_Camera = new CCamera();
	this->m_Light = new CLight();
	m_Scene2D = CScene2D::Create("Data\\Texture\\Title.png", 1, 1);
	return true;
}

//=================================================================================================
//�@�@�@�^�[�g�����[�h�N���X�I������                                       
//=================================================================================================
void CModeTitle::Uninit(void)
{
	delete this->m_Camera;
	this->m_Camera = nullptr;
	delete this->m_Light;
	this->m_Light = nullptr;
	//�V�[���I�u�W�F�N�g�̉��
	CScene::ReleaseAll();
}

//=================================================================================================
//�@�@�@�^�[�g�����[�h�N���X�X�V����                                       
//=================================================================================================
void CModeTitle::Update(void)
{
	if (CInputMouse::GetLeftTrigger())
	{
		CManager::SetMode(new CModeGame());
	}
}

//=================================================================================================
//�@�@�@�^�[�g�����[�h�N���X�`�揈��                                       
//=================================================================================================
void CModeTitle::Draw(void)
{
	m_Camera->Update();
	m_Light->Update();
}

//=================================================================================================
//�@�@�@���U���g���[�h�N���X                                       
//=================================================================================================

//=================================================================================================
//�@�@�@���U���g���[�h�N���X��������                                        
//=================================================================================================
bool CModeResult::Init(void)
{
	m_ModeId = MODE_RESULT;
	this->m_Camera = new CCamera();
	this->m_Light = new CLight();
	m_Scene2D = CScene2D::Create("Data\\Texture\\Result.png", 1, 1);
	return true;
}

//=================================================================================================
//�@�@�@���U���g���[�h�N���X�I������                                       
//=================================================================================================
void CModeResult::Uninit(void)
{
	delete this->m_Camera;
	this->m_Camera = nullptr;
	delete this->m_Light;
	this->m_Light = nullptr;
	//�V�[���I�u�W�F�N�g�̉��
	CScene::ReleaseAll();
}

//=================================================================================================
//�@�@�@���U���g���[�h�N���X�X�V����                                       
//=================================================================================================
void CModeResult::Update(void)
{
	if (CInputMouse::GetLeftTrigger())
	{
		CManager::SetMode(new CModeTitle());
	}
}

//=================================================================================================
//�@�@�@���U���g���[�h�N���X�`�揈��                                       
//=================================================================================================
void CModeResult::Draw(void)
{
	m_Camera->Update();
	m_Light->Update();
}
