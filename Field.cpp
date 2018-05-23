//=================================================================================================
//                                                        
//　　　3Dキューブクラスプログラム[Scene3D.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include"Field.h"
#include"main.h"
#include<d3d9.h>
#include<d3dx9.h>
#include"Renderer.h"

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================
//FVFの宣言
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)    //3Dポリゴンの頂点情報
//テクスチャファイルパス
#define TEXTUREFILENAME000	        "Data\\Texture\\Ground.png"	

#define MESH_FILEDX (4)
#define MESH_FILEDY (4)
//=================================================================================================
//　　　グローバル変数                                    
//=================================================================================================

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;            //XYZW座標
	D3DXVECTOR3 fs;				//法線
	D3DCOLOR color;             //色情報
	D3DXVECTOR2 texcoord;       //テクスチャ座標
}VERTEX_3D;

//=================================================================================================
//　　　3Dキューブクラスデストラクタ                                     
//=================================================================================================
CField::~CField()
{
}

//=================================================================================================
//　　　3Dキューブクラス初期処理                                     
//=================================================================================================
bool CField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	m_pTexture = new LPDIRECT3DTEXTURE9[1];

	HRESULT hr[2];


	hr[0] = D3DXCreateTextureFromFile(
		pDevice,
		TEXTUREFILENAME000,
		m_pTexture);

	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "フィールドのテクスチャが読み込めない。", "エラー", MB_OK);					//テクスチャが読み込めエラーメッセージ
		return false;
	}



	float fSizeX = 1.0f, fSizeZ = 1.0f;
	float fStartX = -fSizeX * (MESH_FILEDX / 2), fStartY = 0.0f, fStartZ = fSizeZ * (MESH_FILEDY / 2);

	int nCx = MESH_FILEDX + 1, nCy = MESH_FILEDY + 1;
	int nX, nZ;
	int nCount = 0;

	m_FiledPosNumber = nCx * nCy;														//頂点数
	m_FiledIndexNumber = (nCx * 2 + 1) * (nCy - 1) + ((nCy - 2) * 1);										//インデックス数
	m_FiledPrimitiveNumber = m_FiledIndexNumber - 2;								//Primitive数


	VERTEX_3D vMeshFiledPos[2048] = {};

	for (nZ = 0;nZ < nCy;nZ++)
	{
		for (nX = 0;nX < nCx;nX++)
		{
			vMeshFiledPos[nCount] = {
				D3DXVECTOR3(fStartX + (fSizeX * nX), fStartY, fStartZ - (fSizeZ * nZ)), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2((fSizeX * nX),(fSizeZ * nZ))
			};
			nCount++;
		}
	}

	//2X2のインデックス
	/*static WORD index[] = {
	3,0,4,1,5,2,2,6,6,3,7,4,8,5
	};*/

	int nS = 0, nF = 0, nC = 2 * nCx, nD = 2 * nCx + 1;
	static WORD index[1024];
	for (nCount = 0;nCount < m_FiledIndexNumber;nCount++)
	{
		//インデックス偶数番の縮退
		if (nCount == nC)
		{
			index[nCount] = index[nCount - 1];
			nC += (2 * (nCx + 1));
			continue;
		}
		//インデックス偶数番
		if (nCount % 2 == 0)
		{
			index[nCount] = nCx + nS;
			nS++;
		}
		//インデックス奇数番の縮退
		if (nCount == nD)
		{
			index[nCount] = nCx + nS;
			nD += (2 * (nCx + 1));
			continue;
		}
		//インデックス奇数番
		if (nCount % 2 == 1)
		{
			index[nCount] = nF;
			if (nCount == ((nC * nCx) - 1))
			{
				index[nCount] = nF;
				continue;
			}
			else
			{
				nF++;
			}
		}
	}

	//頂点Vertexバッファを作る
	hr[0] = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_FiledPosNumber,						//頂点情報領域確保
		D3DUSAGE_WRITEONLY,							//使用用途(書き込んでだけ)
		FVF_VERTEX_3D,								//FVF、０でも大丈夫
		D3DPOOL_MANAGED,							//頂点バッファの管理方法(Deviceに管理する)
		&m_pVertexBuffer,							//管理者のメモ帳場所
		NULL);

	//インデックスバッファを作る
	hr[1] = pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_FiledIndexNumber,							//ワールド行列情報領域確保
		D3DUSAGE_WRITEONLY,							//使用用途(書き込んでだけ)
		D3DFMT_INDEX16,								//FMT,DWORDの場合はD3DFMT_INDEX32
		D3DPOOL_MANAGED,							//頂点バッファの管理方法(Deviceに管理する)
		&m_pIndexBuffer,							//インデックスバッファ管理するメモ帳
		NULL);

	//頂点バッファNULLチェック
	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "メッシュフィ-ルド頂点バッファが作れない", "エラー", MB_OK);							//頂点バッファエラーメッセージ
		return false;
	}

	//インデックスバッファNULLチェック
	if (FAILED(hr[1]))
	{
		MessageBox(NULL, "メッシュフィ-ルドインデックスバッファが作れない", "エラー", MB_OK);							//頂点バッファエラーメッセージ
		return false;
	}

	VERTEX_3D* pV;
	m_pVertexBuffer->Lock(0, 0,						//頂点バッファロック(始まる、領域、voidのポイントポイント（つまり擬似アドレス）) 
		(void**)&pV,								//頂点バッファロック(voidのポイントポイント（つまり擬似アドレス）) 
		D3DLOCK_DISCARD);

	//頂点情報をpVに書き入れる
	//①今までの配列を使用…PVにVの内容コピーする。（memcpy使用して）
	memcpy(&pV[0], &vMeshFiledPos[0], sizeof(VERTEX_3D) * m_FiledPosNumber);

	//②直接書く

	m_pVertexBuffer->Unlock();


	LPWORD pIndex;
	m_pIndexBuffer->Lock(0, 0,						//頂点バッファロック(始まる、領域、voidのポイントポイント（つまり擬似アドレス）) 
		(void**)&pIndex,							//頂点バッファロック(voidのポイントポイント（つまり擬似アドレス）) 
		D3DLOCK_DISCARD);

	//インデックスをpIndexに書き入れる
	//①今までの配列を使用…PVにVの内容コピーする。（memcpy使用して）
	memcpy(&pIndex[0], &index[0], sizeof(WORD) * m_FiledIndexNumber);
	//②直接書く^

	m_pIndexBuffer->Unlock();


	return true;
}

//=================================================================================================
//　　　3Dキューブクラス終了処理                                     
//=================================================================================================
void CField::Uninit(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_DELETE_ARRAY(m_pTexture);

}

//=================================================================================================
//　　　3Dキューブクラス更新処理                                     
//=================================================================================================
void CField::Update(void)
{
	/*g_fRotX[nCount] += rx;
	g_fRotY[nCount] += ry;
	g_fRotZ[nCount] += rz;*/
}

//=================================================================================================
//　　　3Dキューブクラス描画処理                                     
//=================================================================================================
void CField::Draw(void)
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

	pDevice->SetStreamSource(0,
		m_pVertexBuffer, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_pIndexBuffer);


	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ライトON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//ワールド行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//サンプラーステートの設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);			//テクスチャU座標大きな場合は,WRAPは画像を増える。

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);			//テクスチャV座標大きな場合は,WRAPは画像を増える。

	//テクスチャ貼り付ける
	pDevice->SetTexture(0, *m_pTexture);


	//バッファ使い方
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,			//Primitive描画タイプ
		0,
		0,								//インデックスの最小値	
		m_FiledPosNumber,				//頂点の数
		0,
		m_FiledPrimitiveNumber);		//描画するのポリゴン（三角形）の数
}

//=================================================================================================
//　　　3Dキューブクラスのインスタンス生成                                   
//=================================================================================================
CField * CField::Create(void)
{
	CField *Field = new CField(2);
	Field->Init();
	return Field;
}