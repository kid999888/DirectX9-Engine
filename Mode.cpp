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
#include "Performance.h"

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
	this->m_Camera = CCamera::Create(D3DXVECTOR3(7.0f, 14.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	this->m_Light = new CLight();
	m_Light->Init();
	m_Light->SetDir(D3DXVECTOR3(1.0f, -1.0f, 1.0f));
	this->m_Xorshift = new CXorshift();
	m_Field = CField::Create(125, 125, 2.0f, 2.0f, false);
	m_Player = CPlayer::Create(this, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	m_SceneModelEnemy = CSceneModel::Create("Data\\Model\\ufo.x");
	m_SceneModelEnemy->m_bDraw = false;
	m_SceneModelBuliding = CSceneModel::Create("Data\\Model\\building001.x");
	m_SceneModelBuliding->m_bDraw = false;
	m_Enemy = CEnemy::Create();
	m_Enemy->SetPlayer(m_Player);
	m_Bulid = CEnemy::Create();

	D3DXVECTOR3 veUFOIconPos = D3DXVECTOR3(500.0f, 20.0f, -1.0f);

	//UFOアイコン
	m_UFOIcon = CScene2D::Create(2, "Data\\Texture\\UFOIcon.png", 1, 1);
	m_UFOIcon->SetPosition(D3DXVECTOR3(veUFOIconPos.x, veUFOIconPos.y, veUFOIconPos.z));
	m_UFOIcon->SetScale(D3DXVECTOR3(0.6f, 0.6f, 0.6f));

	//残敵数
	m_nEnemyCount = 16;
	m_NumberEnemyCount = CNumber::Create(m_nEnemyCount, 2);
	m_NumberEnemyCount->SetPosition(D3DXVECTOR3(veUFOIconPos.x + 80.0f, veUFOIconPos.y + 15.0f, veUFOIconPos.z));

	//スコア
	m_nMoney = 0;
	m_Number = CNumber::Create(m_nMoney);
	m_Number->SetPosition(D3DXVECTOR3(960.0f, 20.0f, -1.0f));



	//敵
	/*m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(0.0f, 2.0f, 20.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(36.0f, 2.0f, 42.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(-26.0f, 2.0f, 20.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(30.0f, 2.0f, -20.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(15.0f, 2.0f, -60.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(-44.0f, 2.0f, -70.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(56.0f, 2.0f, 80.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(22.0f, 2.0f, 45.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));

	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(0.0f, 2.0f, 20.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(36.0f, 2.0f, 42.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(-26.0f, 2.0f, 20.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(30.0f, 2.0f, -20.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(15.0f, 2.0f, -60.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(-44.0f, 2.0f, -70.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(56.0f, 2.0f, 80.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Enemy->Generate(ENEMY_TYPES_ZAKU, D3DXVECTOR3(22.0f, 2.0f, 45.0f), m_SceneModelEnemy, D3DXVECTOR3(0.5f, 0.5f, 0.5f));*/

	

	//建物
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-10.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-10.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-8.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-8.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-6.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-6.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-4.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-4.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));

	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-10.0f, 2.0f, 20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(10.0f, 2.0f, -22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(8.0f, 2.0f, -20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-8.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(6.0f, 2.0f, -20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-6.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(4.0f, 2.0f, -20.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-4.0f, 2.0f, 22.0f), m_SceneModelBuliding, D3DXVECTOR3(0.025f, 0.025f, 0.025f));


	m_PolygonLazer = CScenePolygon::Create();
	m_PolygonLazer->SetScale(D3DXVECTOR3(40.0f, 1.0f, 0.0625f));
	m_SceneBillBoard = CSceneBillBoard::Create(m_Camera, "Data\\Texture\\Circle.png");
	m_SceneBillBoard->m_bDraw = false;
	m_SceneModel = CSceneModel::Create("Data\\Model\\Ball.x");
	m_SceneModel->SetScale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));
	m_SceneModel->m_bDraw = false;
	m_Bullet = CBullet::Create();
	m_Bullet->Load(m_SceneModel);
	m_Map = CMap::Create(m_Enemy);
	m_Map->SetPlayer(m_Player);

	m_Shadow = CSceneShadow::Create(m_Field);
	m_Shadow->SetPositionX(m_Player->GetPositionX());
	m_Shadow->SetPositionZ(m_Player->GetPositionZ());

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
	m_PolygonLazer->SetPosition(m_Player->GetPosition());
	m_PolygonLazer->SetPositionY(m_Player->GetPosition().y + 1.2f);
	m_PolygonLazer->SetRotationY(m_Player->GetRotationY() + 90.0f);
	if (CInputMouse::GetRightPress() == true)
	{
		m_PolygonLazer->m_bDraw = true;
	}
	else
	{
		m_PolygonLazer->m_bDraw = false;
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
					if (m_Player->GetPlayerHp() > 0)
					{
						m_Player->SetPlayerHp(m_Player->GetPlayerHp() - 10);
						D3DXVECTOR3 veMoved = m_Enemy->GetEnemyManager(nCountX).vePos - m_Player->GetPosition();
						CPerformance::Create(PERFORMANCE_MOVE, m_Player, veMoved * 2.0f, 30);
					}
					else
					{
						CManager::SetMode(new CModeGameOver(m_nMoney));
					}
					return;
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

			}
			if (m_Bullet != NULL)
			{

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
							m_Enemy->SetEnemyLife(nCountX, m_Enemy->GetEnemyManager(nCountX).nLife - 4);
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
									return;
								}
							}
							m_nMoney += 40;
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
	m_NumberEnemyCount->SetNumber(m_nEnemyCount);

	m_Shadow->SetPositionX(m_Player->GetPositionX());
	m_Shadow->SetPositionZ(m_Player->GetPositionZ());
}

//=================================================================================================
//　　　ゲームモードクラス描画処理                                       
//=================================================================================================
void CModeGame::Draw(void)
{
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
	this->m_Camera = CCamera::Create(D3DXVECTOR3(0.075f, 3.61f, -7.86f), D3DXVECTOR3(0.0f, 8.0f, 0.0f), false);
	this->m_Light = new CLight();
	m_Light->Init();
	m_Scene2D = CScene2D::Create(2, "Data\\Texture\\TitleName.png", 1, 1);
	m_Scene2D->SetPosition(D3DXVECTOR3(320.0f, 50.0f, 0.0f));
	m_Model = CSceneModel::Create("Data\\Model\\roboModel.x");
	m_Model->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_ModelSkyBox = CSceneModel::Create("Data\\Model\\sky.x");
	m_fCameraRot = 0.0f;
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
	m_fCameraRot += 0.005f;
	m_Camera->SetCameraPos(D3DXVECTOR3(cosf(m_fCameraRot) * 7.86f, m_Camera->GetCameraPos().y, sinf(m_fCameraRot) * 7.86f));
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
	PlaySound(SOUND_LABEL_BGM_RESULT);
	this->m_Camera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
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
	StopSound(SOUND_LABEL_BGM_RESULT);
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
	m_Light->Update();
}

//=================================================================================================
//　　　トレーニングモードクラス                                       
//=================================================================================================

bool CModeGameOver::Init(void)
{
	m_ModeId = MODE_GAMEOVER;
	PlaySound(SOUND_LABEL_BGM_GAMEOVER);
	this->m_Camera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
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
	StopSound(SOUND_LABEL_BGM_GAMEOVER);
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
	m_Light->Update();
}

//=================================================================================================
//　　　トレーニングモードクラス                                       
//=================================================================================================

bool CModeTraining::Init(void)
{
	m_ModeId = MODE_TRAINING;
	this->m_Camera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
	this->m_Light = new CLight();
	m_Scene2D = CScene2D::Create(2, "Data\\Texture\\sosaku.png", 1, 1);
#if defined(_DEBUG)
	CDebugGUI::SetMainCamera(m_Camera);
#endif//defined(_DEBUG)
	return true;
}

void CModeTraining::Uninit(void)
{
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
	m_Light->Update();
}

//=================================================================================================
//　　　モーション編集モードクラス                                       
//=================================================================================================

bool CModeMotionEditing::Init(void)
{
	m_ModeId = MODE_MOTION_EDITING;
	this->m_Camera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false);
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
	m_Light->Update();
}

//=================================================================================================
//　　　テストモードクラス                                       
//=================================================================================================
bool CModeTest::Init(void)
{
	m_ModeId = MODE_TEST;
	this->m_Camera = CCamera::Create(D3DXVECTOR3(0.0f, 16.0f, -24.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), true);
	/*this->m_Camera = CCamera::Create(D3DXVECTOR3(0.075f, 3.61f, -7.86f), D3DXVECTOR3(0.0f, 8.0f, 0.0f), true);*/
	this->m_Light = new CLight();
	m_Light->Init();
	m_Light->SetDir(D3DXVECTOR3(1.0f, -1.0f, 1.0f));
	/*m_Field = CField::Create(20, 20, 2.0f, 2.0f, false);*/
	m_Model = CSceneModel::Create("Data\\Model\\ufo.x");
	m_Model->SetPositionY(1.0f);
	/*m_Model->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_Model->SetRotationZ(45.0f);
	*/

	/*m_Shadow = CSceneShadow::Create(m_Field);*/

	m_ModelSkyBox = CSceneModel::Create("Data\\Model\\sky.x");

	/*D3DXVECTOR3 veMoved = m_Model->GetPosition();
	veMoved.x = veMoved.x + 10.0f;
	CPerformance::Create(PERFORMANCE_MOVE, m_Model, veMoved, 60);*/

#if defined(_DEBUG)
	CDebugGUI::SetMainCamera(m_Camera);
#endif//defined(_DEBUG)
	return true;
}

void CModeTest::Uninit(void)
{
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
	m_Light->Update();
}
