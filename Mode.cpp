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
CXorshift* CModeGame::m_Xorshift = NULL;
CField *CModeGame::m_Field = NULL;
CPlayer *CModeGame::m_Player = NULL;
CScene3D *CModeGame::m_Scene3D = NULL;
CNumber *CModeGame::m_Number = NULL;
CScenePolygon* CModeGame::m_ScenePolygon = NULL;
CSceneBillBoard* CModeGame::m_SceneBillBoard = NULL;
CSceneModel* CModeGame::m_SceneModel = NULL;
CBullet* CModeGame::m_Bullet = NULL;
CEnemy* CModeGame::m_Enemy = NULL;
CEnemy* CModeGame::m_Bulid = NULL;

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
	this->m_Xorshift = new CXorshift();
	m_Field = CField::Create(120, 120);
	m_Player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Number = CNumber::Create(0);
	m_Scene3D = CScene3D::Create();
	m_Scene3D->m_bDraw = false;
	m_Enemy = CEnemy::Create(m_Scene3D);
	m_Bulid = CEnemy::Create(m_Scene3D);

	//敵
	m_Enemy->Generate(ENEMY_TYPES_ZAKU,D3DXVECTOR3(0.0f, 2.0f, 20.0f));
	m_nEnemyCount = 1;
	//建物
	m_Bulid->Generate(ENEMY_TYPES_BULIDING, D3DXVECTOR3(-10.0f, 2.0f, 20.0f));

	m_ScenePolygon = CScenePolygon::Create();
	m_ScenePolygon->SetScale(D3DXVECTOR3(40.0f, 1.0f, 0.125f));
	m_SceneBillBoard = CSceneBillBoard::Create();
	m_SceneBillBoard->m_bDraw = false;
	m_SceneModel = CSceneModel::Create("Data\\Model\\Ball.x");
	m_SceneModel->m_bDraw = false;
	m_Bullet = CBullet::Create(m_SceneModel);
	CMap::Create();
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
	D3DXVECTOR3 veTempVector3(0.0f,0.0f,0.0f);
	//レーザー部分
	m_ScenePolygon->SetPosition(CPlayer::GetPlayerPos());
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
		if (CEnemy::GetEnemyManager(nCountX).status != 0)
		{
			//敵とプレーヤーの当たり
			if (CCollision::BallJudgement(CEnemy::GetEnemyManager(nCountX).vePos, CPlayer::GetPlayerPos(), 1.0f, 1.0f))
			{
				switch (CEnemy::GetEnemyManager(nCountX).EnemyType)
				{
					//ザグ
				case ENEMY_TYPES_ZAKU:
					CManager::SetMode(new CModeGameOver());
					break;
					//建物
				case ENEMY_TYPES_BULIDING:
					vePos = CEnemy::GetEnemyManager(nCountX).vePos;
					CEnemy::Destory(nCountX);
					m_SceneBillBoard->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
					CParticle::Create(m_SceneBillBoard, vePos, 5.0f, 100, 90);
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
				if (CBullet::GetBulletManager(nCount).status != 0)
				{
					if (CCollision::BallJudgement(CEnemy::GetEnemyManager(nCountX).vePos, CBullet::GetBulletManager(nCount).vePos, 0.8f, 0.3f))
					{
						switch (CEnemy::GetEnemyManager(nCountX).EnemyType)
						{
							//ザグ
						case ENEMY_TYPES_ZAKU:
							CEnemy::SetEnemyLife(nCountX, CEnemy::GetEnemyManager(nCountX).nLife - 1);
							CBullet::Destory(nCount);
							m_SceneBillBoard->SetScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
							CParticle::Create(m_SceneBillBoard, CEnemy::GetEnemyManager(nCountX).vePos, 1.0f, 100, 90);
							if (CEnemy::GetEnemyManager(nCountX).nLife <= 0)
							{
								vePos = CEnemy::GetEnemyManager(nCountX).vePos;
								CEnemy::Destory(nCountX);
								CBullet::Destory(nCount);
								m_nEnemyCount -= 1;
								m_SceneBillBoard->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
								CParticle::Create(m_SceneBillBoard, vePos, 5.0f, 100, 90);
								//リザルトシーン判定
								if (m_nEnemyCount <= 0)
								{
									CManager::SetMode(new CModeResult());
								}
							}
							break;
							//建物
						case ENEMY_TYPES_BULIDING:
							CEnemy::SetEnemyLife(nCountX, CEnemy::GetEnemyManager(nCountX).nLife - 1);
							CBullet::Destory(nCount);
							m_SceneBillBoard->SetScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
							CParticle::Create(m_SceneBillBoard, CEnemy::GetEnemyManager(nCountX).vePos, 1.0f, 100, 90);
							if (CEnemy::GetEnemyManager(nCountX).nLife <= 0)
							{
								vePos = CEnemy::GetEnemyManager(nCountX).vePos;
								CEnemy::Destory(nCountX);
								CBullet::Destory(nCount);
								m_SceneBillBoard->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
								CParticle::Create(m_SceneBillBoard, vePos, 5.0f, 100, 90);
							}
							break;
						default:break;
						}
					}
				}
			}
		}
	}




	if (CInputMouse::GetLeftTrigger())
	{
		veTempVector3 = CPlayer::GetPlayerPos();
		veTempVector3.y += 1.5f;
		CBullet::Shoot(veTempVector3, m_Player->GetPlayerMouse());
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
	m_Scene2D = CScene2D::Create(2, "Data\\Texture\\Title.png", 1, 1);
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
	m_Scene2D = CScene2D::Create(2, "Data\\Texture\\Result.png", 1, 1);
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
	m_Scene2D = CScene2D::Create(2, "Data\\Texture\\GameOver.png", 1, 1);
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
