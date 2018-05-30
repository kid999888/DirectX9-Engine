//=================================================================================================
//                                                        
//�@�@�@�I�u�W�F�N�g�����v���O����[Scene2D.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"Scene.h"

//=================================================================================================
//�@�@�@�C���X�^���X���̉�(�ÓI�ϐ�)
//=================================================================================================
CScene *CScene::m_Scene[3][10] = { NULL };

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
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
//�@�@�@�I�u�W�F�N�g�S�̍X�V����           
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
//�@�@�@�I�u�W�F�N�g�S�̕`�揈��	          
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
//�@�@�@�I�u�W�F�N�g�̑S�̃����[�X����          
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
//�@�@�@�I�u�W�F�N�g�̈ʒu�ݒ�                                       
//=================================================================================================
void CScene::SetPosition(D3DXVECTOR3 vePosition)
{
	m_vePosition = vePosition;
}

//=================================================================================================
//�@�@�@�I�u�W�F�N�g�̃����[�X                                     
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
