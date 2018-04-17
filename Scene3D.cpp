//=================================================================================================
//                                                        
//　　　3Dポリゴンプログラム[Scene3D.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#include "Scene3D.h"

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================
//FVFの宣言
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)    //3Dポリゴンの頂点情報
//テクスチャファイルパス
#define TEXTUREFILENAME000	        "Data\\Texture\\horoCube.png"	

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
//　　　3Dポリゴンコンストラクタ                                       
//=================================================================================================
CScene3D::CScene3D()
{
	/*m_Position = D3DXVECTOR3(100.0f, 100.0f, 1.0f);
	m_Texture = NULL;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;*/
}

//=================================================================================================
//　　　3Dポリゴンデストラクタ                                     
//=================================================================================================
CScene3D::~CScene3D()
{
}

//=================================================================================================
//　　　3Dポリゴン初期処理                                     
//=================================================================================================
bool CScene3D::Init(void)
{
	HRESULT hr[2];
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	hr[0] = D3DXCreateTextureFromFile(
		pDevice,
		TEXTUREFILENAME000,
		&m_Texture);

	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "エラー", "テクスチャが読み込めない。", MB_OK);
		return false;
	}

	int tw = 1024;
	int th = 1024;

	float fu0[6], fv0[6], fu1[6], fv1[6];

	for (int nCount = 0;nCount < 6;nCount++)
	{
		fu0[nCount] = 256.0f * (nCount % 4) / tw;
		fv0[nCount] = 256.0f * (nCount / 4) / th;
		fu1[nCount] = ((256.0f * (nCount % 4)) + 256) / tw;
		fv1[nCount] = ((256.0f * (nCount / 4)) + 256) / th;
	}

	static WORD index[] = {
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		8,9,10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20,
	};



	//頂点の作成
	VERTEX_3D v[] = {
	// 前の面（黄色）
	{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(fu0[0],fv0[0]) },	//0
	{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(fu1[0],fv0[0]) },		//1
	{ D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(fu1[0],fv1[0]) },		//2
	{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(fu0[0],fv1[0]) },		//3

																																			// 左の面（緑色）
	{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu0[1],fv0[1]) },		//4
	{ D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[1],fv0[1]) },		//5
	{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[1],fv1[1]) },		//6
	{ D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu0[1],fv1[1]) },		//7

																																			// 後ろの面（青色）
	{ D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu0[2],fv0[2]) },			//8
	{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[2],fv0[2]) },		//9
	{ D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[2],fv1[2]) },		//10
	{ D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[2],fv1[2]) },		//11

																																		// 右の面（赤色）
	{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[3],fv0[3]) },		//12
	{ D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[3],fv0[3]) },			//13
	{ D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[3],fv1[3]) },		//14
	{ D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[3],fv1[3]) },		//15

																																			// 上の面（紫色）
	{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu0[4],fv0[4]) },		//16
	{ D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu1[4],fv0[4]) },		//17
	{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[4],fv1[4]) },		//18
	{ D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[4],fv1[4]) },		//19

																																			// 下の面（青緑色）
	{ D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[5],fv0[5]) },		//20
	{ D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu1[5],fv0[5]) },		//21
	{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu1[5],fv1[5]) },		//22
	{ D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[5],fv1[5]) },		//23
	};

	//頂点Vertexバッファを作る
	hr[0] = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 24,						//頂点情報領域確保
		D3DUSAGE_WRITEONLY,							//使用用途(書き込んでだけ)
		FVF_VERTEX_3D,								//FVF、０でも大丈夫
		D3DPOOL_MANAGED,							//頂点バッファの管理方法(Deviceに管理する)
		&m_pVertexBuffer,							//管理者のメモ帳場所
		NULL);

	//インデックスバッファを作る
	hr[1] = pDevice->CreateIndexBuffer(
		sizeof(WORD) * 36,							//ワールド行列情報領域確保
		D3DUSAGE_WRITEONLY,							//使用用途(書き込んでだけ)
		D3DFMT_INDEX16,								//FMT,DWORDの場合はD3DFMT_INDEX32
		D3DPOOL_MANAGED,							//頂点バッファの管理方法(Deviceに管理する)
		&m_pIndexBuffer,							//インデックスバッファ管理するメモ帳
		NULL);

	//頂点バッファNULLチェック
	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "頂点バッファが作れない", "エラー", MB_OK);							//頂点バッファエラーメッセージ
		return false;
	}

	//インデックスバッファNULLチェック
	if (FAILED(hr[1]))
	{
		MessageBox(NULL, "インデックスバッファが作れない", "エラー", MB_OK);							//頂点バッファエラーメッセージ
		return false;
	}

	VERTEX_3D* pV;
	m_pVertexBuffer->Lock(0, 0,						//頂点バッファロック(始まる、領域、voidのポイントポイント（つまり擬似アドレス）) 
		(void**)&pV,								//頂点バッファロック(voidのポイントポイント（つまり擬似アドレス）) 
		D3DLOCK_DISCARD);

	//頂点情報をpVに書き入れる
	//①今までの配列を使用…PVにVの内容コピーする。（memcpy使用して）
	memcpy(&pV[0], &v[0], sizeof(VERTEX_3D) * 24);

	//②直接書く

	m_pVertexBuffer->Unlock();


	LPWORD pIndex;
	m_pIndexBuffer->Lock(0, 0,						//頂点バッファロック(始まる、領域、voidのポイントポイント（つまり擬似アドレス）) 
		(void**)&pIndex,							//頂点バッファロック(voidのポイントポイント（つまり擬似アドレス）) 
		D3DLOCK_DISCARD);

	//インデックスをpIndexに書き入れる
	//①今までの配列を使用…PVにVの内容コピーする。（memcpy使用して）
	memcpy(&pIndex[0], &index[0], sizeof(WORD) * 36);
	//②直接書く

	m_pIndexBuffer->Unlock();

	return true;
}

//=================================================================================================
//　　　2Dポリゴン終了処理                                     
//=================================================================================================
void CScene3D::Uninit(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_Texture);
}

//=================================================================================================
//　　　2Dポリゴン更新処理                                     
//=================================================================================================
void CScene3D::Update(void)
{
	UpdateCamera();
}

//=================================================================================================
//　　　2Dポリゴン描画処理                                     
//=================================================================================================
void CScene3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	///saasad

	//拡大縮小行列を作る
	D3DXMatrixScaling(&g_mtxWorldS, 1.0f, 1.0f, 1.0f);

	//回転行列を作る
	D3DXMatrixRotationX(&g_mtxWorldRX, 0.0f);
	D3DXMatrixRotationY(&g_mtxWorldRY, 0.0f);
	D3DXMatrixRotationZ(&g_mtxWorldRZ, 0.0f);

	/*g_fRotX[nCount] += rx;
	g_fRotY[nCount] += ry;
	g_fRotZ[nCount] += rz;*/

	//回転行列を合成	
	D3DXMatrixMultiply(&g_mtxWorldR, &g_mtxWorldRX, &g_mtxWorldRY);
	D3DXMatrixMultiply(&g_mtxWorldR, &g_mtxWorldR, &g_mtxWorldRZ);

	//平行移動行列の作り方
	D3DXMatrixTranslation(&g_mtxWorldT, 0.0f, 0.0f, 0.0f);

	//行列成	
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorldS, &g_mtxWorldR);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &g_mtxWorldT);


	pDevice->SetStreamSource(0,
		m_pVertexBuffer, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_pIndexBuffer);


	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ライトOFF
	//pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	//ワールド行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);


	//テクスチャ貼り付ける
	pDevice->SetTexture(0, m_Texture);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//pDevice->DrawIndexedPrimitiveUP(
	//	D3DPT_TRIANGLELIST,			//Primitive描画タイプ
	//	0,							//インデックスの最小値	
	//	24,							//頂点の数
	//	12,							//描画するのポリゴン（三角形）の数
	//	&index[0],					//インデックスデータの先頭アドレス
	//	D3DFMT_INDEX16,				//インデックスデータフォーマット（DWORDの場合はINDEX32）
	//	&v[0],						//ヴァーテックスデータの先頭アドレス
	//	sizeof(VERTEX_3D));			//ヴァーテックスデータのサイズ

	//バッファ使い方
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,			//Primitive描画タイプ
		0,
		0,							//インデックスの最小値	
		24,							//頂点の数
		0,
		12);						//ヴァーテックスデータのサイズ
}