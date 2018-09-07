#include "Motion.h"

CMotion::~CMotion()
{
}

bool CMotion::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	LPD3DXBUFFER pAdjacencyBuffer;
	HRESULT hr;

	hr = D3DXLoadMeshFromX("Data\\Model\\body.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[0].Material,
		NULL,
		&m_Part[0].MaterialNum,
		&m_Part[0].mesh);

	hr = D3DXLoadMeshFromX("Data\\Model\\head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[1].Material,
		NULL,
		&m_Part[1].MaterialNum,
		&m_Part[1].mesh);

	hr = D3DXLoadMeshFromX("Data\\Model\\arm_r.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[2].Material,
		NULL,
		&m_Part[2].MaterialNum,
		&m_Part[2].mesh);
	hr = D3DXLoadMeshFromX("Data\\Model\\hand_r.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[3].Material,
		NULL,
		&m_Part[3].MaterialNum,
		&m_Part[3].mesh);

	hr = D3DXLoadMeshFromX("Data\\Model\\arm_l.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[4].Material,
		NULL,
		&m_Part[4].MaterialNum,
		&m_Part[4].mesh);
	hr = D3DXLoadMeshFromX("Data\\Model\\hand_l.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[5].Material,
		NULL,
		&m_Part[5].MaterialNum,
		&m_Part[5].mesh);

	hr = D3DXLoadMeshFromX("Data\\Model\\thigh_r.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[6].Material,
		NULL,
		&m_Part[6].MaterialNum,
		&m_Part[6].mesh);
	hr = D3DXLoadMeshFromX("Data\\Model\\smallthigh_r.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[7].Material,
		NULL,
		&m_Part[7].MaterialNum,
		&m_Part[7].mesh);

	hr = D3DXLoadMeshFromX("Data\\Model\\thigh_l.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[8].Material,
		NULL,
		&m_Part[8].MaterialNum,
		&m_Part[8].mesh);
	hr = D3DXLoadMeshFromX("Data\\Model\\smallthigh_l.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[9].Material,
		NULL,
		&m_Part[9].MaterialNum,
		&m_Part[9].mesh);

	//親子関係
	m_Part[0].Parent = NULL;
	m_Part[1].Parent = &m_Part[0];
	m_Part[2].Parent = &m_Part[0];
	m_Part[3].Parent = &m_Part[2];
	m_Part[4].Parent = &m_Part[0];
	m_Part[5].Parent = &m_Part[4];
	m_Part[6].Parent = &m_Part[0];
	m_Part[7].Parent = &m_Part[6];
	m_Part[8].Parent = &m_Part[0];
	m_Part[9].Parent = &m_Part[8];

	m_Part[0].Position = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	m_Part[0].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Part[1].Position = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	m_Part[1].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Part[2].Position = D3DXVECTOR3(0.5f, 1.2f, 0.0f);
	m_Part[2].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Part[3].Position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_Part[3].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Part[4].Position = D3DXVECTOR3(-0.5f, 1.2f, 0.0f);
	m_Part[4].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Part[5].Position = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_Part[5].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Part[6].Position = D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	m_Part[6].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Part[7].Position = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	m_Part[7].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Part[8].Position = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	m_Part[8].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Part[9].Position = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	m_Part[9].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return true;
}

void CMotion::Uninit(void)
{
}

void CMotion::Update(void)
{
}

void CMotion::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	for (int nCount = 0;nCount < 10;nCount++)
	{
		D3DXMatrixIdentity(&m_mtxWorld);
		D3DXMatrixRotationYawPitchRoll(&m_mtxWorldR, m_Part[nCount].Rotation.y,0.0f,0.0f);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldR);
		D3DXMatrixTranslation(&m_mtxWorldT, m_Part[nCount].Position.x, m_Part[nCount].Position.y, m_Part[nCount].Position.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldT, &m_mtxWorldT);

		if (m_Part[nCount].Parent != NULL)
		{
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld,&m_Part[nCount].Parent->Matrix);
		}
		m_Part[nCount].Matrix = m_mtxWorld;
		//ワールド行列の設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//モデル描画
		m_Part[nCount].mesh->DrawSubset(0);
	}

	//for (int nCount = 0;nCount < 3;nCount++)
	//{
	//	//拡大縮小行列を作る
	//	D3DXMatrixScaling(&m_mtxWorldS, m_veScale.x, m_veScale.y, m_veScale.z);

	//	//回転行列を作る
	//	D3DXMatrixRotationX(&m_mtxWorldRX, D3DXToRadian(m_Part[nCount].Rotation.x));
	//	D3DXMatrixRotationY(&m_mtxWorldRY, D3DXToRadian(m_Part[nCount].Rotation.y));
	//	D3DXMatrixRotationZ(&m_mtxWorldRZ, D3DXToRadian(m_Part[nCount].Rotation.z));

	//	//回転行列を合成	
	//	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldRX, &m_mtxWorldRY);
	//	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldR, &m_mtxWorldRZ);

	//	//平行移動行列の作り方
	//	D3DXMatrixTranslation(&m_mtxWorldT, m_Part[nCount].Position.x, m_Part[nCount].Position.y, m_Part[nCount].Position.z);

	//	//行列合成 	
	//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorldR);
	//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);

	//	//ワールド行列の設定
	//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//	m_Part[nCount].mesh->DrawSubset(0);
	//}

	////拡大縮小行列を作る
	//D3DXMatrixScaling(&m_mtxWorldS, m_veScale.x, m_veScale.y, m_veScale.z);

	////回転行列を作る
	//D3DXMatrixRotationX(&m_mtxWorldRX, D3DXToRadian(m_veRotation.x));
	//D3DXMatrixRotationY(&m_mtxWorldRY, D3DXToRadian(m_veRotation.y));
	//D3DXMatrixRotationZ(&m_mtxWorldRZ, D3DXToRadian(m_veRotation.z));

	////回転行列を合成	
	//D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldRX, &m_mtxWorldRY);
	//D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldR, &m_mtxWorldRZ);

	////平行移動行列の作り方
	//D3DXMatrixTranslation(&m_mtxWorldT, m_vePosition.x, m_vePosition.y, m_vePosition.z);

	////行列合成 	
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorldR);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);

	////ワールド行列の設定
	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//m_Part[0].mesh->DrawSubset(0);
	//m_Part[1].mesh->DrawSubset(0);
	//m_Part[2].mesh->DrawSubset(0);
	//m_Part[3].mesh->DrawSubset(0);
	//m_Part[4].mesh->DrawSubset(0);
	//m_Part[5].mesh->DrawSubset(0);
	//m_Part[6].mesh->DrawSubset(0);
	//m_Part[7].mesh->DrawSubset(0);
	//m_Part[8].mesh->DrawSubset(0);
	//m_Part[9].mesh->DrawSubset(0);
}

CMotion * CMotion::Create(void)
{
	CMotion *Motion = new CMotion(1);
	Motion->Init();
	return Motion;
}
