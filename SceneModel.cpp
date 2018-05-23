//=================================================================================================
//                                                        
//　　　3Dモデルクラスプログラム[SceneModel.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include"SceneModel.h"
#include"main.h"
#include"Renderer.h"

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================
//モデルファイルパス
#define MODELFILENAME000	        "Data\\Model\\cart.x"

//=================================================================================================
//　　　3Dモデルクラスデストラクタ                                     
//=================================================================================================
CSceneModel::~CSceneModel()
{

}

//=================================================================================================
//　　　3Dモデルクラス初期処理                                     
//=================================================================================================
bool CSceneModel::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	//メンバー変数初期化 
	
	m_pMesh = NULL;
	m_nMaterialNum = 0;
	m_pMaterial = NULL;
	m_nMaterialPointNum = 0;

	LPD3DXBUFFER pAdjacencyBuffer;
	HRESULT hr;

	hr = D3DXLoadMeshFromX(MODELFILENAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_pMaterial,
		NULL,
		&m_nMaterialNum,
		&m_pMesh);



	if (FAILED(hr))
	{
		MessageBox(NULL, "3Dメッシュを読み込めない", "エラー", MB_OK);							//頂点バッファエラーメッセージ
		return false;
	}

	if (pDevice == NULL)
	{
		return false;
	}


	//Xモデルのマテリアル情報を読み込む
	LPD3DXMATERIAL pMaterial = (LPD3DXMATERIAL)m_pMaterial->GetBufferPointer();
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nMaterialNum];

	int nCount = 0;
	for (nCount = 0; nCount < m_nMaterialNum;nCount++)
	{
		pDevice->SetMaterial(&pMaterial->MatD3D);
		hr = D3DXCreateTextureFromFile(
			pDevice,
			pMaterial->pTextureFilename,
			&m_pTexture[nCount]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "3Dモデリングテクスチャが読み込めない。", "エラー", MB_OK);					//テクスチャが読み込めエラーメッセージ
			return false;
		}
		pMaterial++;
	}
	m_nMaterialPointNum = m_nMaterialPointNum + m_nMaterialNum;

	LPD3DXMESH pTempMesh;

	hr = m_pMesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pAdjacencyBuffer->GetBufferPointer(),
		NULL, NULL, NULL);

	SAFE_RELEASE(pAdjacencyBuffer);

	LPD3DVERTEXELEMENT9 pElements = NULL;
	m_pMesh->GetDeclaration(pElements);
	hr = m_pMesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,
		pElements,
		pDevice,
		&pTempMesh);

	SAFE_RELEASE(m_pMesh);
	m_pMesh = pTempMesh;

	if (FAILED(hr))
	{
		MessageBox(NULL, "メッシュ最適化できない", "エラー", MB_OK);			//メッシュ最適化エラーメッセージ
		return false;
	}

	//インスタンス生成
	m_Material = new CMaterial();

	return true;
}

//=================================================================================================
//　　　3Dモデルクラス終了処理                                     
//=================================================================================================
void CSceneModel::Uninit(void)
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMaterial);
	SAFE_DELETE_ARRAY(m_pTexture);
	SAFE_DELETE(m_Material);
}

//=================================================================================================
//　　　3Dモデルクラス更新処理                                     
//=================================================================================================
void CSceneModel::Update(void)
{
	m_Material->Update();
	//m_fRotX += 0.0f;
	//m_fRotY -= 0.01f;
	//m_fRotZ += 0.0f;
}

//=================================================================================================
//　　　3Dモデルクラス描画処理                                     
//=================================================================================================
void CSceneModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	//拡大縮小行列を作る
	D3DXMatrixScaling(&m_mtxWorldS, 1.0f, 1.0f, 1.0f);

	//回転行列を作る
	D3DXMatrixRotationX(&m_mtxWorldRX, m_fRotX);
	D3DXMatrixRotationY(&m_mtxWorldRY, m_fRotY);
	D3DXMatrixRotationZ(&m_mtxWorldRZ, m_fRotZ);

	//回転行列を合成	
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldRX, &m_mtxWorldRY);
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldR, &m_mtxWorldRZ);

	//平行移動行列の作り方
	D3DXMatrixTranslation(&m_mtxWorldT, m_vePosition.x, m_vePosition.y, m_vePosition.z);

	//行列成	
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorldR);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);

	//ワールド行列
	D3DXMATRIX Vec;
	D3DXMatrixTranslation(&Vec, v3In.x, v3In.y, v3In.z);
	D3DXMatrixMultiply(&Vec, &Vec, &m_mtxWorld);

	m_XmodelAt = D3DXVECTOR3(Vec._41, Vec._42, Vec._43);

	//ワールド行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアルと光の設定
	//MaterialSet(FCOLOR{ 0.8f,0.8f,0.8f,1.0f }, FCOLOR{ 0.8f,0.8f,0.8f,1.0f });
	//LightSet(D3DXVECTOR3(1.0f, -1.0f, 0.0f), FCOLOR{ 0.8f,0.8f,0.8f,1.0f }, FCOLOR{ 0.8f,0.8f,0.8f,1.0f }, FCOLOR{ 0.3f,0.3f,0.3f,1.0f });

	//描画
	int nCount = 0;
	for (nCount = 0;nCount < m_nMaterialNum;nCount++)
	{
		//テクスチャ貼り付ける
		pDevice->SetTexture(0, m_pTexture[nCount]);
		//マテリアル設定（テクスチャ含む）
		m_pMesh->DrawSubset(nCount);
	}
	
}

//=================================================================================================
//　　　3Dモデルクラスのインスタンス生成                                    
//=================================================================================================
CSceneModel * CSceneModel::Create(void)
{
	CSceneModel *SceneModel = new CSceneModel(1);
	SceneModel->Init();
	return SceneModel;
}
