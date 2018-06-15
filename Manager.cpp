//=================================================================================================
//                                                        
//　　　マネージャープログラム[Manager.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.19            
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include"Manager.h"

#if defined(DEBUG)
#include"DebugGUI.h"
#endif//defined(DEBUG)

//=================================================================================================
//　　　インスタンス実体化          
//=================================================================================================
CCamera *CManager::m_Camera = NULL;
CLight *CManager::m_Light = NULL;
CField *CManager::m_Field = NULL;

//=================================================================================================
//　　　マネージャークラス初期処理         
//=================================================================================================
bool CManager::Init( HWND hWnd, BOOL bWindow)
{
	//DirectX初期化クラス初期処理
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
//　　　マネージャークラス終了処理         
//=================================================================================================
void CManager::Uninit(void)
{
	delete m_Camera;
	delete m_Light;
	//シーンオブジェクトの解放
	CScene::ReleaseAll();
	//DirectX初期化クラス終了処理
	CRenderer::Uninit();
}

//=================================================================================================
//　　　マネージャークラス更新処理        
//=================================================================================================
void CManager::Update(void)
{
	//シーンオブジェクトの更新
	CScene::UpdateAll();
}

//=================================================================================================
//　　　マネージャークラス描画処理         
//=================================================================================================
void CManager::Draw(void)
{
#if defined(DEBUG)
	//ImGuiDirectX描画前の処理
	ImGui::EndFrame();
#endif//defined(DEBUG)

	//DirectX初期化クラス描画開始処理 
	CRenderer::DrawBegin();

	//Direct3Dによる描画の開始
	if (SUCCEEDED(CRenderer::GetD3DDevice()->BeginScene()))
	{
		m_Camera->Update();
		m_Light->Update();
		//シーンオブジェクトの描画
		CScene::DrawAll();
		//Presentの終了処理
		CRenderer::GetD3DDevice()->EndScene();

#if defined(DEBUG)
		//ImGui処理
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
#endif//defined(DEBUG)

	}
	//DirectX初期化クラス描画終了処理 
	CRenderer::DrawEnd();
}

CField * CManager::GetField(void)
{
	return CManager::m_Field;
}
