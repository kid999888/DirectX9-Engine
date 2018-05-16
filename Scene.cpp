//=================================================================================================
//                                                        
//　　　オブジェクト処理プログラム[Scene2D.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include"Scene.h"
#include"main.h"

//=================================================================================================
//　　　インスタンス実体化          
//=================================================================================================
CScene *CScene::m_Scene[3][10] = { NULL };

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
CScene::CScene(int nPriorty)
{
	int nCount = 0;
	for (nCount = 0;nCount < 10;nCount++)
	{
		if (m_Scene[nPriorty][nCount] == NULL)
		{
			m_Scene[nPriorty][nCount]=this;
			break;
		}
	}
}

//=================================================================================================
//　　　オブジェクト全体更新処理           
//=================================================================================================
void CScene::UpdateAll(void)
{
	int nCount = 0;
	int nCountPriority = 0;
	for (nCountPriority = 0;nCountPriority < 3;nCountPriority++)
	{
		for (nCount = 0;nCount < 10;nCount++)
		{
			if (m_Scene[nCountPriority][nCount] != NULL)
			{
				m_Scene[nCountPriority][nCount]->Update();
			}
		}
	}
}

//=================================================================================================
//　　　オブジェクト全体描画処理	          
//=================================================================================================
void CScene::DrawAll(void)
{
	int nCount = 0;
	int nCountPriority = 0;
	for (nCountPriority = 0;nCountPriority < 3;nCountPriority++)
	{
		for (nCount = 0;nCount < 10;nCount++)
		{
			if (m_Scene[nCountPriority][nCount] != NULL)
			{
				m_Scene[nCountPriority][nCount]->Draw();
			}
		}
	}
}

//=================================================================================================
//　　　オブジェクトの全体リリース処理          
//=================================================================================================
void CScene::ReleaseAll(void)
{
	int nCount = 0;
	int nCountPriority = 0;
	for (nCountPriority = 0;nCountPriority < 3;nCountPriority++)
	{
		for (nCount = 0;nCount < 10;nCount++)
		{
			if (m_Scene[nCountPriority][nCount] != NULL)
			{
				m_Scene[nCountPriority][nCount]->Release();
			}
		}
	}
}

//=================================================================================================
//　　　オブジェクトの位置設定                                       
//=================================================================================================
void CScene::SetPosition(D3DXVECTOR3 vePosition)
{
	m_vePosition = vePosition;
}

//=================================================================================================
//　　　オブジェクトのリリース                                     
//=================================================================================================
void CScene::Release(void)
{
	int nCount = 0;
	int nCountPriority = 0;
	for (nCountPriority = 0;nCountPriority < 3;nCountPriority++)
	{
		for (nCount = 0;nCount < 10;nCount++)
		{
			if (m_Scene[nCountPriority][nCount] == this)
			{
				m_Scene[nCountPriority][nCount] == NULL;
				Uninit();
				delete this;
				break;
			}
		}
	}
	
}
