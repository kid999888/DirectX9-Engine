//=================================================================================================
//                                                        
//　　　フィールドクラスプログラム[Scene3D.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include "Field.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>
#include <tchar.h>
#include "Renderer.h"
#include "input.h"

using namespace std;

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================
//FVFの宣言
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)    //3Dポリゴンの頂点情報
//テクスチャファイルパス
#define TEXTUREFILENAME000	        "Data\\Texture\\Ground.png"	
#define NOISEFILENAME000	        "Data\\Texture\\noise.png"	

//=================================================================================================
//　　　グローバル変数                                    
//=================================================================================================

CField::CField(int nPriority, int nNumX, int nNumZ, float fScaleX, float fScaleZ, bool bNeat) : CScene(nPriority)
{
	m_veScale = D3DXVECTOR3(fScaleX, 1.0f, fScaleZ);
	m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pTexture = nullptr;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	m_fheightScale = 0.005f;
	m_nNumX = nNumX;
	m_nNumZ = nNumZ;
	m_bDraw = true;
	m_bNeat = bNeat;
};
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

	HRESULT hr[2];

	hr[0] = D3DXCreateTextureFromFile(
		pDevice,
		TEXTUREFILENAME000,
		&m_pTexture);

	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "フィールドのテクスチャが読み込めない。", "エラー", MB_OK);					//テクスチャが読み込めエラーメッセージ
		return false;
	}

	float fSizeX = 1.0f, fSizeZ = 1.0f;
	fSizeX *= m_veScale.x;
	fSizeZ *= m_veScale.z;
	float fStartX = -fSizeX * (m_nNumX / 2), fStartY = 0.0f, fStartZ = fSizeZ * (m_nNumZ / 2);

	int nCx = m_nNumX + 1, nCy = m_nNumZ + 1;
	int nX, nZ;
	int nCount = 0;

	m_nFiledPosNumber = nCx * nCy;													//頂点数
	m_nFiledIndexNumber = (nCx * 2 + 1) * (nCy - 1) + ((nCy - 2) * 1);				//インデックス数
	m_nFiledPrimitiveNumber = m_nFiledIndexNumber - 2;								//Primitive数

	//頂点情報管理メモ帳のインスタンス生成
	m_pvMeshFiledPos = new VERTEX_3D[m_nFiledPosNumber];

	//高度の情報管理メモ帳（仮）
	vector<vector<float>> vaFieldHeight(nCx);
	for (nCount = 0; nCount < nCx; nCount++)
	{
		vaFieldHeight[nCount].resize(nCy);
	}
	//頂点情報管理メモ帳初期化
	nCount = 0;
	for (nZ = 0;nZ < nCy;nZ++)
	{
		for (nX = 0;nX < nCx;nX++)
		{
			vaFieldHeight[nX][nZ] = 0.0f;
		}
	}





	//高度図を読み方む
	ifstream InFile;
	InFile.open(NOISEFILENAME000, ios::binary);				//二進の方式にデータを読み込む

	InFile.seekg(0, ios::end);								//ポインタにファイル末端を移動
	vector<BYTE>vaInData(InFile.tellg());					//<BYTE>型のVector配列inDataを宣言
	int nSize = vaInData.size();
	InFile.seekg(ios::beg);									//ポインタにファイル先端を移動
	InFile.read((char*)&vaInData[0], vaInData.size());		//ファイルを読み込む
	InFile.close();											//ファイルを閉じる

	//高度ファイルを作る
	//ofstream OutFile;
	//OutFile.open("Data\\HeightMessage.txt", ios::out);
	///*OutFile.write("0.0", 3);*/

	//for (int i = 0;i < (int)vaInData.size(); i++)
	//{
	//	OutFile << (vaInData[i] * 0.005f);
	//	OutFile.write("\n", 2);
	//}

	//OutFile.close();


	//ファイルの高度情報に高度のメモ帳に入れる
	nCount = 0;
	for (nZ = 0;nZ < nCy;nZ++)
	{
		for (nX = 0;nX < nCx;nX++)
		{
			vaFieldHeight[nX][nZ] = (vaInData[nCount] * 0.005f);
			nCount++;
		}
	}
	//Vector配列inDataの消す
	vaInData.clear();
	if (m_bNeat)
	{
		nCount = 0;
		for (nZ = 0;nZ < nCy;nZ++)
		{
			for (nX = 0;nX < nCx;nX++)
			{
				m_pvMeshFiledPos[nCount] = {
					D3DXVECTOR3(fStartX + (fSizeX * nX), fStartY, fStartZ - (fSizeZ * nZ)), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2((fSizeX * nX),(fSizeZ * nZ))
				};
				m_pvMeshFiledPos[nCount].pos.y = 0.0f;

				nCount++;
			}
		}
	}
	else
	{
		nCount = 0;
		for (nZ = 0;nZ < nCy;nZ++)
		{
			for (nX = 0;nX < nCx;nX++)
			{
				m_pvMeshFiledPos[nCount] = {
					D3DXVECTOR3(fStartX + (fSizeX * nX), fStartY, fStartZ - (fSizeZ * nZ)), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2((fSizeX * nX),(fSizeZ * nZ))
				};
				m_pvMeshFiledPos[nCount].pos.y = vaFieldHeight[nX][nZ];

				nCount++;
			}
		}
	}


	//Vector配列vaFieldHeightの消す
	vaFieldHeight.clear();


	//法線の凹凸として自動計算
	for (nZ = 1;nZ < (nCy - 1);nZ++)
	{
		for (nX = 1;nX < (nCx - 1);nX++)
		{
			D3DXVECTOR3 vx, nx, vz, nz, n;
			vx = m_pvMeshFiledPos[nZ * nCx + (nX + 1)].pos - m_pvMeshFiledPos[nZ * nCx + (nX - 1)].pos;
			nx.x = -vx.y;
			nx.y = vx.x;
			nx.z = 0.0f;

			vz = m_pvMeshFiledPos[nX * nCy + (nZ + 1)].pos - m_pvMeshFiledPos[nX * nCy + (nZ - 1)].pos;
			nz.x = 0.0f;
			nz.y = vz.z;
			nz.z = vz.y;

			n = nx + nz;

			D3DXVec3Normalize(&n, &n);
			m_pvMeshFiledPos[nZ * nCx + (nX + 1)].fs = n;
		}
	}

	/*for (nZ = 1;nZ < (nCy - 1);nZ++)
	{
		for (nX = 1;nX < (nCx - 1);nX++)
		{
			D3DXVECTOR3 vx, vx0, nx, nx0, vz, vz0, nz, nz0, n;
			vx = m_pvMeshFiledPos[nZ * nCx + (nX + 1)].pos - m_pvMeshFiledPos[nZ * nCx + (nX - 1)].pos;
			nx.x = -vx.y;
			nx.y = vx.x;
			nx.z = 0.0f;

			vx0 = m_pvMeshFiledPos[nZ * nCx + (nX - 1)].pos - m_pvMeshFiledPos[nZ * nCx + (nX + 1)].pos;
			nx0.x = -vx.y;
			nx0.y = -vx.x;
			nx0.z = 0.0f;

			vz = m_pvMeshFiledPos[nX * nCy + (nZ + 1)].pos - m_pvMeshFiledPos[nX * nCy + (nZ - 1)].pos;
			nz.x = 0.0f;
			nz.y = vz.z;
			nz.z = vz.y;

			vz0 = m_pvMeshFiledPos[nX * nCy + (nZ - 1)].pos - m_pvMeshFiledPos[nX * nCy + (nZ + 1)].pos;
			nz0.x = 0.0f;
			nz0.y = -vz.z;
			nz0.z = vz.y;

			n = nx + nz + nx0 + nz0;

			D3DXVec3Normalize(&n, &n);
			m_pvMeshFiledPos[nZ * nCx + (nX + 1)].fs = n;
		}
	}*/

	//2X2のインデックス
	/*static WORD index[] = {
	3,0,4,1,5,2,2,6,6,3,7,4,8,5
	};*/

	int nS = 0, nF = 0, nC = 2 * nCx, nD = 2 * nCx + 1;
	static WORD *index;
	index = new WORD[m_nFiledIndexNumber];
	for (nCount = 0;nCount < m_nFiledIndexNumber;nCount++)
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
		sizeof(VERTEX_3D) * m_nFiledPosNumber,		//頂点情報領域確保
		D3DUSAGE_WRITEONLY,							//使用用途(書き込んでだけ)
		FVF_VERTEX_3D,								//FVF、０でも大丈夫
		D3DPOOL_MANAGED,							//頂点バッファの管理方法(Deviceに管理する)
		&m_pVertexBuffer,							//管理者のメモ帳場所
		NULL);

	//インデックスバッファを作る
	hr[1] = pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nFiledIndexNumber,			//ワールド行列情報領域確保
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
	memcpy(&pV[0], &m_pvMeshFiledPos[0], sizeof(VERTEX_3D) * m_nFiledPosNumber);



	//②直接書く

	m_pVertexBuffer->Unlock();


	LPWORD pIndex;
	m_pIndexBuffer->Lock(0, 0,						//頂点バッファロック(始まる、領域、voidのポイントポイント（つまり擬似アドレス）) 
		(void**)&pIndex,							//頂点バッファロック(voidのポイントポイント（つまり擬似アドレス）) 
		D3DLOCK_DISCARD);

	//インデックスをpIndexに書き入れる
	//①今までの配列を使用…PVにVの内容コピーする。（memcpy使用して）
	memcpy(&pIndex[0], &index[0], sizeof(WORD) * m_nFiledIndexNumber);

	//頂点情報管理メモ帳（仮）の消す
	SAFE_DELETE_ARRAY(index);

	//②直接書く^

	m_pIndexBuffer->Unlock();

	//マテリアルのインスタンス生成&設定
	m_Material = new CMaterial();
	/*m_Material->SetAmbient(0.9f, 0.1f, 0.1f, 1.0f);*/

	return true;
}

//=================================================================================================
//　　　3Dキューブクラス終了処理                                     
//=================================================================================================
void CField::Uninit(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_Material);
	//頂点情報管理メモ帳の消す
	SAFE_DELETE_ARRAY(m_pvMeshFiledPos);

}

//=================================================================================================
//　　　3Dキューブクラス更新処理                                     
//=================================================================================================
void CField::Update(void)
{
	//m_veRotation.x += 0.0f;
	//m_veRotation.y += 0.01f;
	//m_veRotation.z += 0.0f;
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

	//マテリアルの更新
	m_Material->Update();

	//テクスチャ貼り付ける
	pDevice->SetTexture(0, m_pTexture);

	//線分描画ON
	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//バッファ使い方
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,			//Primitive描画タイプ
		0,
		0,								//インデックスの最小値	
		m_nFiledPosNumber,				//頂点の数
		0,
		m_nFiledPrimitiveNumber);		//描画するのポリゴン（三角形）の数

	//線分描画OFF
	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//=================================================================================================
//　　　3Dキューブクラスのインスタンス生成                                   
//=================================================================================================
CField * CField::Create(int nNumX, int nNumZ, float fScaleX, float fScaleZ, bool bNeat)
{
	CField *Field = new CField(2, nNumX, nNumZ, fScaleX, fScaleZ, bNeat);
	Field->Init();
	return Field;
}
