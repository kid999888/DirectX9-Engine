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

//=================================================================================================
//　　　実体定義
//=================================================================================================
CScene *CScene::m_Scene[3][30] = { NULL };

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
CScene::CScene(int nPriorty)
{
	int nCount = 0;
	for (nCount = 0;nCount < 30;nCount++)
	{
		if (m_Scene[nPriorty][nCount] == NULL)
		{
			m_Scene[nPriorty][nCount]=this;
			break;
		}
	}
}

CScene::CScene(void)
{

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
		for (nCount = 0;nCount < 30;nCount++)
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
		for (nCount = 0;nCount < 30;nCount++)
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
		for (nCount = 0;nCount < 30;nCount++)
		{
			if (m_Scene[nCountPriority][nCount] != NULL)
			{
				m_Scene[nCountPriority][nCount]->Release();
			}
		}
	}
}

//=================================================================================================
//　　　オブジェクトの拡縮倍率設定                                      
//=================================================================================================
void CScene::SetScale(D3DXVECTOR3 veScale)
{
	m_veScale = veScale;
}

//=================================================================================================
//　　　オブジェクトの拡縮倍率X設定                                      
//=================================================================================================
void CScene::SetScaleX(float fX)
{
	m_veScale.x = fX;
}

//=================================================================================================
//　　　オブジェクトの拡縮倍率Y設定                                      
//=================================================================================================
void CScene::SetScaleY(float fY)
{
	m_veScale.y = fY;
}

//=================================================================================================
//　　　オブジェクトの拡縮倍率Z設定                                      
//=================================================================================================
void CScene::SetScaleZ(float fZ)
{
	m_veScale.z = fZ;
}

//=================================================================================================
//　　　オブジェクトの軸回転値設定                                      
//=================================================================================================
void CScene::SetRotation(D3DXVECTOR3 veRotation)
{
	m_veRotation = veRotation;
}

//=================================================================================================
//　　　オブジェクトの軸回転値設定                                      
//=================================================================================================
void CScene::SetRotationX(float fX)
{
	m_veRotation.x = fX;
}

//=================================================================================================
//　　　オブジェクトの軸回転値設定                                      
//=================================================================================================
void CScene::SetRotationY(float fY)
{
	m_veRotation.y = fY;
}

//=================================================================================================
//　　　オブジェクトの軸回転値設定                                      
//=================================================================================================
void CScene::SetRotationZ(float fZ)
{
	m_veRotation.z = fZ;
}

//=================================================================================================
//　　　オブジェクトの位置設定                                       
//=================================================================================================
void CScene::SetPosition(D3DXVECTOR3 vePosition)
{
	m_vePosition = vePosition;
}

//=================================================================================================
//　　　オブジェクトの位置X設定                                       
//=================================================================================================
void CScene::SetPositionX(float fX)
{
	m_vePosition.x = fX;
}

//=================================================================================================
//　　　オブジェクトの位置Y設定                                       
//=================================================================================================
void CScene::SetPositionY(float fY)
{
	m_vePosition.y = fY;
}

//=================================================================================================
//　　　オブジェクトの位置Z設定                                       
//=================================================================================================
void CScene::SetPositionZ(float fZ)
{
	m_vePosition.z = fZ;
}

//=================================================================================================
//　　　オブジェクトの拡縮倍率取得                                    
//=================================================================================================
D3DXVECTOR3 CScene::GetScale(void)
{
	return m_veScale;
}

//=================================================================================================
//　　　オブジェクトの拡縮倍率X取得                                    
//=================================================================================================
float CScene::GetScaleX(void)
{
	return m_veScale.x;
}

//=================================================================================================
//　　　オブジェクトの拡縮倍率Y取得                                    
//=================================================================================================
float CScene::GetScaleY(void)
{
	return m_veScale.y;
}

//=================================================================================================
//　　　オブジェクトの拡縮倍率Z取得                                    
//=================================================================================================
float CScene::GetScaleZ(void)
{
	return m_veScale.z;
}

//=================================================================================================
//　　　オブジェクトの軸回転値取得                                    
//=================================================================================================
D3DXVECTOR3 CScene::GetRotation(void)
{
	return m_veRotation;
}

//=================================================================================================
//　　　オブジェクトのX軸回転値取得                                    
//=================================================================================================
float CScene::GetRotationX(void)
{
	return m_veRotation.x;
}

//=================================================================================================
//　　　オブジェクトのY軸回転値取得                                    
//=================================================================================================
float CScene::GetRotationY(void)
{
	return m_veRotation.y;
}

//=================================================================================================
//　　　オブジェクトのZ軸回転値取得                                    
//=================================================================================================
float CScene::GetRotationZ(void)
{
	return m_veRotation.z;
}

//=================================================================================================
//　　　オブジェクトの位置取得                                   
//=================================================================================================
D3DXVECTOR3 CScene::GetPosition(void)
{
	return m_vePosition;
}

//=================================================================================================
//　　　オブジェクトの位置X取得                                   
//=================================================================================================
float CScene::GetPositionX(void)
{
	return m_vePosition.x;
}

//=================================================================================================
//　　　オブジェクトの位置Y取得                                   
//=================================================================================================
float CScene::GetPositionY(void)
{
	return m_vePosition.y;
}

//=================================================================================================
//　　　オブジェクトの位置Z取得                                   
//=================================================================================================
float CScene::GetPositionZ(void)
{
	return m_vePosition.z;
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
		for (nCount = 0;nCount < 30;nCount++)
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
