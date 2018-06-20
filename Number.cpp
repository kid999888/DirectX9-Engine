//=================================================================================================
//                                                        
//　　　スコア数字表示処理[Number.h]                   
//      Author:王暁晨(AT-12B-242 04)　2018.06.12   
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include"Number.h"

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================

//=================================================================================================
//　　　グローバル変数                                    
//=================================================================================================

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================

CNumber::~CNumber()
{
}

bool CNumber::Init(void)
{
	int nX = 0;
	int nS = m_nNumber;
	int nCount;
	if (m_nNumber == 0)
	{
		nX = 1;
	}
	for (nCount = 0;nCount < m_nDigX; nCount++)
	{
		if (nS != 0)
		{
			nX++;
		}
		nS = nS / 10;
	}
	
	if (!m_bZero)
	{
		m_nDig = nX;
	}
	else
	{
		m_nDig = m_nDigX;
	}

	for (nCount = 0;nCount < m_nDig; nCount++)
	{
		Scene2DNumber[nCount] = CScene2D::Create("Data\\Texture\\Number.png",10, 2);
		Scene2DNumber[nCount]->SetPosition(D3DXVECTOR3(m_vePosition.x + ((float)nCount * 60.0f),
														m_vePosition.y,
														-1.0f));
	}

	nS = m_nNumber;
	for (nCount = m_nDig - 1;nCount >= 0; nCount--)
	{
		int n = nS % 10;
		nS = nS / 10;

		Scene2DNumber[nCount]->SetTextureNum(n,0);

		if (!m_bZero && nS == 0)
		{
			break;
		}
	}

	return true;
}

void CNumber::Uninit(void)
{
}

void CNumber::Update(void)
{
	int nS = m_nNumber;
	int nCount;
	for (nCount = m_nDig - 1;nCount >= 0; nCount--)
	{
		int n = nS % 10;
		nS = nS / 10;

		Scene2DNumber[nCount]->SetTextureNum(n, 0);

		if (!m_bZero && nS == 0)
		{
			break;
		}
	}
}

void CNumber::Draw(void)
{
}

CNumber * CNumber::Create(int nNum)
{
	CNumber *Number = new CNumber(2, nNum);
	Number->Init();
	return Number;
}
