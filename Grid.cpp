//=================================================================================================
//
//　　　グリッド描画クラスプログラム[Grid.cpp]
//      Author:王暁晨(AT-13A-281 04)　2018.09.10
//
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include "Grid.h"
#include "Renderer.h"

CGrid::~CGrid()
{
}

bool CGrid::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	m_fGridX = -5.0f;
	m_fGridZ = 5.0f;
	for (int nCount = 0;nCount < 22;nCount += 2)
	{
		if (nCount != 10)
		{
			m_v[nCount] = { D3DXVECTOR3(-5.0f,0.0f,m_fGridZ),D3DCOLOR_RGBA(255, 0, 0, 255) };
			m_v[nCount + 1] = { D3DXVECTOR3(5.0f,0.0f,m_fGridZ),D3DCOLOR_RGBA(255, 0, 0, 255) };
		}
		else
		{
			m_v[nCount] = { D3DXVECTOR3(-5.0f,0.0f,m_fGridZ),D3DCOLOR_RGBA(255, 255, 0, 255) };
			m_v[nCount + 1] = { D3DXVECTOR3(5.0f,0.0f,m_fGridZ),D3DCOLOR_RGBA(255, 255, 0, 255) };
		}

		m_fGridZ -= 1.0f;
	}
	for (int nCount = 22;nCount < 44;nCount += 2)
	{
		if (nCount != 32)
		{
			m_v[nCount] = { D3DXVECTOR3(m_fGridX,0.0f,5.0f),D3DCOLOR_RGBA(255, 0, 0, 255) };
			m_v[nCount + 1] = { D3DXVECTOR3(m_fGridX,0.0f,-5.0f),D3DCOLOR_RGBA(255, 0, 0, 255) };
		}
		else
		{
			m_v[nCount] = { D3DXVECTOR3(m_fGridX,0.0f,5.0f),D3DCOLOR_RGBA(255, 255, 0, 255) };
			m_v[nCount + 1] = { D3DXVECTOR3(m_fGridX,0.0f,-5.0f),D3DCOLOR_RGBA(255, 255, 0, 255) };
		}
		m_fGridX += 1.0f;
	}
	return true;
}

void CGrid::Uninit(void)
{
}

void CGrid::Update(void)
{
}

void CGrid::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	//拡大縮小行列を作る
	D3DXMatrixScaling(&m_mtxWorldS, m_veScale.x, m_veScale.y, m_veScale.z);

	//回転行列を作る
	D3DXMatrixRotationX(&m_mtxWorldRX, D3DXToRadian(m_veRotation.x));
	D3DXMatrixRotationY(&m_mtxWorldRY, D3DXToRadian(m_veRotation.y));
	D3DXMatrixRotationZ(&m_mtxWorldRZ, D3DXToRadian(m_veRotation.z));

	//回転行列を合成	
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldRX, &m_mtxWorldRY);
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldR, &m_mtxWorldRZ);

	//平行移動行列の作り方
	D3DXMatrixTranslation(&m_mtxWorldT, m_vePosition.x, m_vePosition.y, m_vePosition.z);

	//行列合成 	
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorldR);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);

	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_GRID);

	//ライトOFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//各種行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//描画するDrawPrimitive
	pDevice->DrawPrimitiveUP(                 //重要
		D3DPT_LINELIST, 22, &m_v[0],			  //描画のモード
		sizeof(VERTEX_GRID));                   //ポリゴン数
}

CGrid * CGrid::Create(void)
{
	CGrid *Grid = new CGrid(0);
	Grid->Init();
	return Grid;
}
