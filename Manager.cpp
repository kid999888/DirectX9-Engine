//=================================================================================================
//                                                        
//　　　マネージャープログラム[Manager.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.19            
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include "Manager.h"
#include"main.h"

//=================================================================================================
//　　　インスタンス実体化          
//=================================================================================================
CCamera *CManager::m_Camera = NULL;
CLight *CManager::m_Light = NULL;
CScene2D *CManager::m_Scene2D = NULL;
CScene3D *CManager::m_Scene3D = NULL;
CSceneModel *CManager::m_SceneModel = NULL;

//=================================================================================================
//　　　マネージャークラス初期処理         
//=================================================================================================
bool CManager::Init( HWND hWnd, BOOL bWindow)
{
	//DirectX初期化クラス初期処理
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
//　　　マネージャークラス終了処理         
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
	//DirectX初期化クラス終了処理
	CRenderer::Uninit();
}

//=================================================================================================
//　　　マネージャークラス更新処理        
//=================================================================================================
void CManager::Update(void)
{
	m_Scene2D->Update();
	m_Scene3D->Update();
	m_SceneModel->Update();
}

//=================================================================================================
//　　　マネージャークラス描画処理         
//=================================================================================================
void CManager::Draw(void)
{
	//DirectX初期化クラス描画開始処理 
	CRenderer::DrawBegin();

	//Direct3Dによる描画の開始
	if (SUCCEEDED(CRenderer::GetD3DDevice()->BeginScene()))
	{
		m_Camera->Update();
		m_Light->Update();
		//2Dポリゴン描画
		m_Scene2D->Draw();
		//3Dポリゴン描画
		m_Scene3D->Draw();
		//3Dポリゴン描画
		m_SceneModel->Draw();
		//Presentの終了処理
		CRenderer::GetD3DDevice()->EndScene();
	}
	//DirectX初期化クラス描画終了処理 
	CRenderer::DrawEnd();
}
