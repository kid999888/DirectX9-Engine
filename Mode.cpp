//=================================================================================================
//                                                        
//　　　モード処理クラス プログラム[Mode.cpp]
//      Author:王暁晨(AT-13A-281 04)　2018.07.03      
//                                                        
//=================================================================================================
#include"Mode.h"
#include"Manager.h"
#include"input.h"
#include"Collision.h"

#if defined(DEBUG)
#include"DebugGUI.h"
#endif//defined(DEBUG)

//=================================================================================================
//　　　実体定義       
//=================================================================================================
CCamera *CModeGame::m_Camera = NULL;
CLight *CModeGame::m_Light = NULL;
CField *CModeGame::m_Field = NULL;
CPlayer *CModeGame::m_Player = NULL;
CScene3D *CModeGame::m_Scene3D = NULL;
CNumber *CModeGame::m_Number = NULL;
CScenePolygon* CModeGame::m_ScenePolygon = NULL;
CSceneBillBoard* CModeGame::m_SceneBillBoard = NULL;
CSceneModel* CModeGame::m_SceneModel = NULL;
CBullet* CModeGame::m_Bullet = NULL;

CCamera *CModeTitle::m_Camera = NULL;
CLight *CModeTitle::m_Light = NULL;
CScene2D *CModeTitle::m_Scene2D = NULL;

CCamera *CModeResult::m_Camera = NULL;
CLight *CModeResult::m_Light = NULL;
CScene2D *CModeResult::m_Scene2D = NULL;

CCamera* CModeGameOver::m_Camera = NULL;
CLight* CModeGameOver::m_Light = NULL;
CScene2D* CModeGameOver::m_Scene2D = NULL;

//=================================================================================================
//　　　ゲームモードクラス                                       
//=================================================================================================

//=================================================================================================
//　　　ゲームモードクラス初期処理                                       
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
	/*m_Scene3D->m_bDraw = false;*/
	m_ScenePolygon = CScenePolygon::Create();
	/*m_SceneBillBoard = CSceneBillBoard::Create();
	m_SceneBillBoard->m_bDraw = false;
	CParticle::Create(m_SceneBillBoard, D3DXVECTOR3(0.0f, 3.0f, 0.0f),1.0f,100);*/
	m_SceneModel = CSceneModel::Create("Data\\Model\\Ball.x");
	m_SceneModel->m_bDraw = false;
	m_Bullet = CBullet::Create(m_SceneModel);
#if defined(DEBUG)
	CDebugGUI::SetMainCamera(m_Camera);
	CDebugGUI::SetField(m_Field);
	CDebugGUI::SetPlayer(m_Player);
#endif//defined(DEBUG)
	return true;
}

//=================================================================================================
//　　　ゲームモードクラス終了処理                                       
//=================================================================================================
void CModeGame::Uninit(void)
{
	delete this->m_Camera;
	this->m_Camera = nullptr;
	delete this->m_Light;
	this->m_Light = nullptr;
	//シーンオブジェクトの解放
	CScene::ReleaseAll();
}

//=================================================================================================
//　　　ゲームモードクラス更新処理                                       
//=================================================================================================
void CModeGame::Update(void)
{
	//
	if (CCollision::BallJudgement(m_Scene3D->GetPosition(), m_Player->GetPosition(), 1.0f, 1.0f))
	{
		CManager::SetMode(new CModeGameOver());
	}

	//
	for (int nCount = 0;nCount < BULLET_NUM;nCount++)
	{
		if (CBullet::GetBulletManager(nCount).status != 0)
		{
			if (CCollision::BallJudgement(m_Scene3D->GetPosition(), CBullet::GetBulletManager(nCount).vePos, 0.8f, 0.3f))
			{
				CManager::SetMode(new CModeResult());
			}
		}
	}
	

	if (CInputMouse::GetLeftTrigger())
	{
		CBullet::Shoot(m_Player->GetPosition(), m_Player->GetPlayerMouse());
	}

	if (CInputKeyboard::GetKeyTrigger(DIK_Z))
	{
		m_Number->SetNumber(m_Number->GetNumber() + 1);
	}
}

//=================================================================================================
//　　　ゲームモードクラス描画処理                                       
//=================================================================================================
void CModeGame::Draw(void)
{
	m_Camera->Update();
	m_Light->Update();
}

//=================================================================================================
//　　　タートルモードクラス                                       
//=================================================================================================

//=================================================================================================
//　　　タートルモードクラス初期処理                                       
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
//　　　タートルモードクラス終了処理                                       
//=================================================================================================
void CModeTitle::Uninit(void)
{
	delete this->m_Camera;
	this->m_Camera = nullptr;
	delete this->m_Light;
	this->m_Light = nullptr;
	//シーンオブジェクトの解放
	CScene::ReleaseAll();
}

//=================================================================================================
//　　　タートルモードクラス更新処理                                       
//=================================================================================================
void CModeTitle::Update(void)
{
	if (CInputMouse::GetLeftTrigger())
	{
		CManager::SetMode(new CModeGame());
	}
}

//=================================================================================================
//　　　タートルモードクラス描画処理                                       
//=================================================================================================
void CModeTitle::Draw(void)
{
	m_Camera->Update();
	m_Light->Update();
}

//=================================================================================================
//　　　リザルトモードクラス                                       
//=================================================================================================

//=================================================================================================
//　　　リザルトモードクラス初期処理                                        
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
//　　　リザルトモードクラス終了処理                                       
//=================================================================================================
void CModeResult::Uninit(void)
{
	delete this->m_Camera;
	this->m_Camera = nullptr;
	delete this->m_Light;
	this->m_Light = nullptr;
	//シーンオブジェクトの解放
	CScene::ReleaseAll();
}

//=================================================================================================
//　　　リザルトモードクラス更新処理                                       
//=================================================================================================
void CModeResult::Update(void)
{
	if (CInputMouse::GetLeftTrigger())
	{
		CManager::SetMode(new CModeTitle());
	}
}

//=================================================================================================
//　　　リザルトモードクラス描画処理                                       
//=================================================================================================
void CModeResult::Draw(void)
{
	m_Camera->Update();
	m_Light->Update();
}

bool CModeGameOver::Init(void)
{
	m_ModeId = MODE_GAMEOVER;
	this->m_Camera = new CCamera();
	this->m_Light = new CLight();
	m_Scene2D = CScene2D::Create("Data\\Texture\\GameOver.png", 1, 1);
	return true;
}

void CModeGameOver::Uninit(void)
{
	delete this->m_Camera;
	this->m_Camera = nullptr;
	delete this->m_Light;
	this->m_Light = nullptr;
	//シーンオブジェクトの解放
	CScene::ReleaseAll();
}

void CModeGameOver::Update(void)
{
	if (CInputMouse::GetLeftTrigger())
	{
		CManager::SetMode(new CModeTitle());
	}
}

void CModeGameOver::Draw(void)
{
	m_Camera->Update();
	m_Light->Update();
}
