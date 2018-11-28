//=================================================================================================
//                                                        
//　　　モード処理クラス プログラム[Mode.cpp]
//      Author:王暁晨(AT-13A-281 04)　2018.07.03      
//                                                        
//=================================================================================================
#include "Mode.h"
#include "Manager.h"
#include "input.h"
#include "Collision.h"
#include<math.h>

#if defined(_DEBUG)
#include "DebugGUI.h"
#endif//defined(_DEBUG)

//=================================================================================================
//　　　ゲームモードクラス                                       
//=================================================================================================

//=================================================================================================
//　　　ゲームモードクラス初期処理                                       
//=================================================================================================
bool CModeGame::Init(void)
{
	m_ModeId = MODE_GAME;
	PlaySound(SOUND_LABEL_BGM_TITLE);
	this->m_Camera = new CCamera();
	m_Camera->SetCameraPos(D3DXVECTOR3(7.0f, 14.0f, -10.0f));
	m_Camera->SetCameraAtPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	this->m_Light = new CLight();
	m_Light->Init();
	this->m_Xorshift = new CXorshift();
	m_Field = CField::Create(120, 120);
	m_Player = CPlayer::Create(this,D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_nMoney = 800;
	m_Number = CNumber::Create(m_nMoney);
	m_Number->SetPosition(D3DXVECTOR3(960.0f, 0.0f, -1.0f));
	m_SceneModelEnemy = CSceneModel::Create("Data\\Model\\ufo.x");
	m_SceneModelEnemy->m_bDraw = false;
	m_SceneModelBuliding = CSceneModel::Create("Data\\Model\\building001.x");
	m_SceneModelBuliding->m_bDraw = false;
	m_Enemy = CEnemy::Create();
	m_Enemy->SetPlayer(m_Player);
	m_Bulid = CEnemy::Create();
	

	

	//敵
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(0.0f, 2.0f, 20.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(36.0f, 2.0f, 42.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(-26.0f, 2.0f, 20.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(30.0f, 2.0f, -20.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(15.0f, 2.0f, -60.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(-44.0f, 2.0f, -70.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(56.0f, 2.0f, 80.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(22.0f, 2.0f, 45.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_nEnemyCount = 8;
	//建物
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-10.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-10.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-8.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-8.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-6.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-6.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-4.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-4.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));

	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(10.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(10.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(8.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(8.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(6.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(6.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(4.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(4.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));


	m_ScenePolygon = CScenePolygon::Create();
	m_ScenePolygon->SetScale(D3DXVECTOR3(40.0f, 1.0f, 0.125f));
	m_SceneBillBoard = CSceneBillBoard::Create(m_Camera, "Data\\Texture\\Circle.png");
	m_SceneBillBoard->m_bDraw = false;
	m_SceneModel = CSceneModel::Create("Data\\Model\\Ball.x");
	m_SceneModel->SetScale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));
	m_SceneModel->m_bDraw = false;
	m_Bullet = CBullet::Create();
	m_Bullet->Load(m_SceneModel);
	m_Map = CMap::Create(m_Enemy);
	m_Map->SetPlayer(m_Player);
#if defined(_DEBUG)
	CDebugGUI::SetMainCamera(m_Camera);
	CDebugGUI::SetField(m_Field);
	CDebugGUI::SetPlayer(m_Player);
#endif//defined(_DEBUG)
	return true;
}

//=================================================================================================
//　　　ゲームモードクラス終了処理                                       
//=================================================================================================
void CModeGame::Uninit(void)
{
	StopSound(SOUND_LABEL_BGM_TITLE);
	delete this->m_Camera;
	this->m_Camera = nullptr;
	delete this->m_Light;
	this->m_Light = nullptr;
	delete this->m_Xorshift;
	this->m_Xorshift = nullptr;
	//シーンオブジェクトの解放
	CScene::ReleaseAll();
}

//=================================================================================================
//　　　ゲームモードクラス更新処理                                       
//=================================================================================================
void CModeGame::Update(void)
{
	D3DXVECTOR3 veTempVector3(0.0f, 0.0f, 0.0f);
	//レーザー部分
	m_ScenePolygon->SetPosition(m_Player->GetPosition());
	m_ScenePolygon->SetPositionY(2.2f);
	m_ScenePolygon->SetRotationY(m_Player->GetRotationY() + 90.0f);
	if (CInputMouse::GetRightPress() == true)
	{
		m_ScenePolygon->m_bDraw = true;
	}
	else
	{
		m_ScenePolygon->m_bDraw = false;;
	}

	//
	D3DXVECTOR3 vePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCountX = 0;nCountX < ENEMY_NUM;nCountX++)
	{
		if (m_Enemy->GetEnemyManager(nCountX).status != 0 && m_Enemy != NULL)
		{
			//敵とプレーヤーの当たり
			if (CCollision::BallJudgement(m_Enemy->GetEnemyManager(nCountX).vePos, m_Player->GetPosition(), 1.0f, 1.0f))
			{
				switch (m_Enemy->GetEnemyManager(nCountX).EnemyType)
				{
					//ザグ
				case ENEMY_TYPES_ZAKU:
					CManager::SetMode(new CModeGameOver(m_nMoney));
					break;
					//建物
				case ENEMY_TYPES_BULIDING:
					vePos = m_Enemy->GetEnemyManager(nCountX).vePos;
					m_Enemy->Destory(nCountX);
					m_SceneBillBoard->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
					CParticle::Create(m_SceneBillBoard, vePos, 5.0f, 100, 90);
					m_nMoney -= 100;
					break;
				default:break;
				}

				/*if (CEnemy::GetEnemyManager(nCountX).EnemyType != ENEMY_TYPES_BULIDING)
				{
					CManager::SetMode(new CModeGameOver());
				}
				else
				{

				}*/

			}
			for (int nCount = 0;nCount < BULLET_NUM;nCount++)
			{
				//敵とプレーヤーバレットの当たり
				if (m_Bullet->GetBulletManager(nCount).status != 0)
				{
					if (CCollision::BallJudgement(m_Enemy->GetEnemyManager(nCountX).vePos, m_Bullet->GetBulletManager(nCount).vePos, 0.8f, 0.3f))
					{
						switch (m_Enemy->GetEnemyManager(nCountX).EnemyType)
						{
							//ザグ
						case ENEMY_TYPES_ZAKU:
							m_Enemy->SetEnemyLife(nCountX, m_Enemy->GetEnemyManager(nCountX).nLife - 1);
							m_Bullet->Destory(nCount);
							m_SceneBillBoard->SetScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
							CParticle::Create(m_SceneBillBoard, m_Enemy->GetEnemyManager(nCountX).vePos, 1.0f, 100, 90);
							if (m_Enemy->GetEnemyManager(nCountX).nLife <= 0)
							{
								vePos = m_Enemy->GetEnemyManager(nCountX).vePos;
								m_Enemy->Destory(nCountX);
								m_Bullet->Destory(nCount);
								m_nEnemyCount -= 1;
								m_SceneBillBoard->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
								CParticle::Create(m_SceneBillBoard, vePos, 5.0f, 100, 90);
								//リザルトシーン判定
								if (m_nEnemyCount <= 0)
								{
									CManager::SetMode(new CModeResult(m_nMoney));
								}
							}
							m_nMoney +=40;
							break;
							//建物
						case ENEMY_TYPES_BULIDING:
							m_Enemy->SetEnemyLife(nCountX, m_Enemy->GetEnemyManager(nCountX).nLife - 1);
							m_Bullet->Destory(nCount);
							m_SceneBillBoard->SetScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
							CParticle::Create(m_SceneBillBoard, m_Enemy->GetEnemyManager(nCountX).vePos, 1.0f, 100, 90);
							if (m_Enemy->GetEnemyManager(nCountX).nLife <= 0)
							{
								vePos = m_Enemy->GetEnemyManager(nCountX).vePos;
								m_Enemy->Destory(nCountX);
								m_Bullet->Destory(nCount);
								m_SceneBillBoard->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
								CParticle::Create(m_SceneBillBoard, vePos, 5.0f, 100, 90);
							}
							m_nMoney -= 100;
							break;
						default:break;
						}
					}
				}
			}
		}
	}

	/*if (m_nMoney <= 0)
	{
		m_nMoney = 0;
		CManager::SetMode(new CModeGameOver(m_nMoney));
	}*/



	if (CInputMouse::GetLeftTrigger())
	{
		veTempVector3 = m_Player->GetPosition();
		veTempVector3.y += 1.5f;
		m_Bullet->Shoot(veTempVector3, m_Player->GetPlayerMouse());
	}

	if (CInputKeyboard::GetKeyTrigger(DIK_Z))
	{
		m_Number->SetNumber(m_Number->GetNumber() + 1);
	}
	m_Number->SetNumber(m_nMoney);
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
	PlaySound(SOUND_LABEL_BGM_GAME);
	this->m_Camera = new CCamera();
	this->m_Light = new CLight();
	m_Light->Init();
	m_Scene2D = CScene2D::Create(2, "Data\\Texture\\Title.png", 1, 1);
#if defined(_DEBUG)
	CDebugGUI::SetMainCamera(m_Camera);
#endif//defined(_DEBUG)
	return true;
}

//=================================================================================================
//　　　タートルモードクラス終了処理                                       
//=================================================================================================
void CModeTitle::Uninit(void)
{
	StopSound(SOUND_LABEL_BGM_GAME);
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
		CManager::SetMode(new CModeTraining());
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
	m_Scene2D = CScene2D::Create(2, "Data\\Texture\\Result.png", 1, 1);
	m_Money = CNumber::Create(m_nMoney);
	m_Money->SetPosition(D3DXVECTOR3(500.0f, 60.0f, -1.0f));
#if defined(_DEBUG)
	CDebugGUI::SetMainCamera(m_Camera);
#endif//defined(_DEBUG)
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

//=================================================================================================
//　　　トレーニングモードクラス                                       
//=================================================================================================

bool CModeGameOver::Init(void)
{
	m_ModeId = MODE_GAMEOVER;
	this->m_Camera = new CCamera();
	this->m_Light = new CLight();
	m_Scene2D = CScene2D::Create(2, "Data\\Texture\\GameOver.png", 1, 1);
	m_Money = CNumber::Create(m_nMoney);
	m_Money->SetPosition(D3DXVECTOR3(500.0f, 60.0f, -1.0f));
#if defined(_DEBUG)
	CDebugGUI::SetMainCamera(m_Camera);
#endif//defined(_DEBUG)
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

//=================================================================================================
//　　　トレーニングモードクラス                                       
//=================================================================================================

bool CModeTraining::Init(void)
{
	m_ModeId = MODE_TRAINING;
	this->m_Camera = new CCamera();
	this->m_Light = new CLight();
	m_Scene2D = CScene2D::Create(2, "Data\\Texture\\sosaku.png", 1, 1);
#if defined(_DEBUG)
	CDebugGUI::SetMainCamera(m_Camera);
#endif//defined(_DEBUG)
	return true;
}

void CModeTraining::Uninit(void)
{
	delete this->m_Camera;
	this->m_Camera = nullptr;
	delete this->m_Light;
	this->m_Light = nullptr;
	//シーンオブジェクトの解放
	CScene::ReleaseAll();
}

void CModeTraining::Update(void)
{
	if (CInputMouse::GetLeftTrigger())
	{
		CManager::SetMode(new CModeGame());
	}
}

void CModeTraining::Draw(void)
{
	m_Camera->Update();
	m_Light->Update();
}

//=================================================================================================
//　　　モーション編集モードクラス                                       
//=================================================================================================

bool CModeMotionEditing::Init(void)
{
	m_ModeId = MODE_MOTION_EDITING;
	this->m_Camera = new CCamera();
	m_Camera->SetCameraPos(D3DXVECTOR3(0.0f, 16.0f, -24.0f));
	m_Camera->SetCameraAtPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//視点操作フラッグ
	m_Camera->CameraViewFlag(true);
	this->m_Light = new CLight();
	m_Light->SetDir(D3DXVECTOR3(-1.0f, -1.0f, 1.0f));
	m_Grid = CGrid::Create();
	m_Motion = CMotion::Create();
#if defined(_DEBUG)
	CDebugGUI::SetMotion(m_Motion);
#endif//defined(_DEBUG)
	return true;
}

void CModeMotionEditing::Uninit(void)
{
	delete this->m_Camera;
	this->m_Camera = nullptr;
	delete this->m_Light;
	this->m_Light = nullptr;
	//シーンオブジェクトの解放
	CScene::ReleaseAll();
}

void CModeMotionEditing::Update(void)
{
}

void CModeMotionEditing::Draw(void)
{
	m_Camera->Update();
	m_Light->Update();
}

//=================================================================================================
//　　　テストモードクラス                                       
//=================================================================================================
bool CModeTest::Init(void)
{
	m_ModeId = MODE_TEST;
	this->m_Camera = new CCamera();
	m_Camera->SetCameraPos(D3DXVECTOR3(0.0f, 16.0f, -24.0f));
	m_Camera->SetCameraAtPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//視点操作フラッグ
	m_Camera->CameraViewFlag(true);
	this->m_Light = new CLight();
	m_Light->Init();
	m_Light->SetDir(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
	m_Field = CField::Create(2, 2,true);
	m_Model = CSceneModel::Create("Data\\Model\\cylinder.x");
	m_Model->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Model->SetRotationZ(45.0f);
	m_Model->SetPositionY(1.0f);
	m_Shadow = CSceneShadow::Create();
	CLifeBar::Create();

#if defined(_DEBUG)
	CDebugGUI::SetMainCamera(m_Camera);
#endif//defined(_DEBUG)
	return true;
}

void CModeTest::Uninit(void)
{
	delete this->m_Camera;
	this->m_Camera = nullptr;
	delete this->m_Light;
	this->m_Light = nullptr;
	//シーンオブジェクトの解放
	CScene::ReleaseAll();
}

void CModeTest::Update(void)
{
}

void CModeTest::Draw(void)
{
	m_Camera->Update();
	m_Light->Update();
}
