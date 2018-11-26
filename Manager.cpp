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

//=================================================================================================
//　　　実体定義       
//=================================================================================================
CMode *CManager::m_Mode = nullptr;
CScene2D* CManager::m_Scene2D = nullptr;
bool CManager::m_bBlur = true;

//=================================================================================================
//　　　マネージャークラス初期処理         
//=================================================================================================
bool CManager::Init( HWND hWnd, BOOL bWindow)
{
	//DirectX初期化クラス初期処理
	CRenderer::Init(hWnd, bWindow);
	m_Scene2D = CScene2D::Create(4, "Data\\Texture\\Null.png",1,1);
	m_Scene2D->m_bDraw = false;
	SetMode(new CModeTitle());
	m_bBlur = false;

	return true;
}

//=================================================================================================
//　　　マネージャークラス終了処理         
//=================================================================================================
void CManager::Uninit(void)
{
	//モード管理ポインタの解放
	m_Mode->Uninit();
	delete m_Mode;
	//シーンオブジェクトのリリース
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
	//モードの更新
	m_Mode->Update();
}

//=================================================================================================
//　　　マネージャークラス描画処理         
//=================================================================================================
void CManager::Draw(void)
{
#if defined(_DEBUG)
	//ImGuiDirectX描画前の処理
	ImGui::EndFrame();
#endif//defined(_DEBUG)
	if (m_bBlur)
	{
		CRenderer::GetD3DDevice()->SetRenderTarget(0, CRenderer::GetBlurSurface1());
	}
	//DirectX初期化クラス描画開始処理 
	CRenderer::DrawBegin();

	//Direct3Dによる描画の開始
	if (SUCCEEDED(CRenderer::GetD3DDevice()->BeginScene()))
	{
		//モードの描画
		m_Mode->Draw();
		//シーンオブジェクトの描画
		CScene::DrawAll();
		if (m_bBlur)
		{
			CRenderer::GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			CRenderer::GetD3DDevice()->SetTexture(0, CRenderer::GetBlurTexture2());
			m_Scene2D->SetScaleX(1.001f);
			m_Scene2D->SetScaleY(1.001f);
			m_Scene2D->DrawWithOutTexture(240);
			CRenderer::GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
		//Presentの終了処理
		CRenderer::GetD3DDevice()->EndScene();

#if defined(_DEBUG)
		//ImGui処理
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
#endif//defined(_DEBUG)

	}
	if (m_bBlur)
	{
		CRenderer::GetD3DDevice()->SetRenderTarget(0, CRenderer::GetBackBufferSurface());
		CRenderer::GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		CRenderer::GetD3DDevice()->SetTexture(0, CRenderer::GetBlurTexture1());
		m_Scene2D->SetScaleX(1.0f);
		m_Scene2D->SetScaleY(1.0f);
		m_Scene2D->DrawWithOutTexture(255);
		CRenderer::GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
	//DirectX初期化クラス描画終了処理 
	CRenderer::DrawEnd();
}

//=================================================================================================
//　　　ゲームモードの設定       
//=================================================================================================
void CManager::SetMode(CMode * Mode)
{
	if (m_Mode != NULL)
	{
		m_Mode->Uninit();
		delete m_Mode;
	}
	m_Mode = Mode;
	if (m_Mode != NULL)
	{
		m_Mode->Init();
	}
}
