//=================================================================================================
//
//�@�@�@�O���b�h�`��N���X�v���O����[Grid.cpp]
//      Author:���ŝ�(AT-13A-281 04)�@2018.09.10
//
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
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

	//�g��k���s������
	D3DXMatrixScaling(&m_mtxWorldS, m_veScale.x, m_veScale.y, m_veScale.z);

	//��]�s������
	D3DXMatrixRotationX(&m_mtxWorldRX, D3DXToRadian(m_veRotation.x));
	D3DXMatrixRotationY(&m_mtxWorldRY, D3DXToRadian(m_veRotation.y));
	D3DXMatrixRotationZ(&m_mtxWorldRZ, D3DXToRadian(m_veRotation.z));

	//��]�s�������	
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldRX, &m_mtxWorldRY);
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldR, &m_mtxWorldRZ);

	//���s�ړ��s��̍���
	D3DXMatrixTranslation(&m_mtxWorldT, m_vePosition.x, m_vePosition.y, m_vePosition.z);

	//�s�񍇐� 	
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorldR);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);

	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_GRID);

	//���C�gOFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�e��s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�`�悷��DrawPrimitive
	pDevice->DrawPrimitiveUP(                 //�d�v
		D3DPT_LINELIST, 22, &m_v[0],			  //�`��̃��[�h
		sizeof(VERTEX_GRID));                   //�|���S����
}

CGrid * CGrid::Create(void)
{
	CGrid *Grid = new CGrid(0);
	Grid->Init();
	return Grid;
}
