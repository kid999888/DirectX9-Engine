//=================================================================================================
//                                                        
//　　　3Dポリゴンクラスプログラム[ScenePolygon.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.06.08   
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include"ScenePolygon.h"
#include"Material.h"
#include"Renderer.h"

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================
//FVFの宣言
#define FVF_VERTEX_POLYGON ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)    //3Dポリゴンの頂点情報
//テクスチャファイルパス
#define TEXTUREFILENAME000	        "Data\\Texture\\Laser.png"	

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;            //XYZW座標
	D3DXVECTOR3 fs;				//法線
	D3DCOLOR color;             //色情報
	D3DXVECTOR2 texcoord;       //テクスチャ座標
}VERTEX_POLYGON;

//=================================================================================================
//　　　3Dポリゴンクラスデストラクタ                                     
//=================================================================================================
CScenePolygon::~CScenePolygon()
{
}

//=================================================================================================
//　　　3Dポリゴンクラス初期処理                                    
//=================================================================================================
bool CScenePolygon::Init(void)
{
	HRESULT hr[2];
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	hr[0] = D3DXCreateTextureFromFile(
		pDevice,
		TEXTUREFILENAME000,
		&m_pTexture);

	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "エラー", "テクスチャが読み込めない。", MB_OK);
		return false;
	}

	static WORD index[] = {
		0,1,2,
		2,3,0,
	};

	//頂点の作成
	VERTEX_POLYGON v[] = {
		{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 0, 0, 128),D3DXVECTOR2(0.0f,0.0f) },		//0
		{ D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 0, 0, 128) ,D3DXVECTOR2(1.0f,0.0f) },		//1
		{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 0, 0, 128),D3DXVECTOR2(1.0f,1.0f) },		//2
		{ D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 0, 0, 128) ,D3DXVECTOR2(0.0f,1.0f) },		//3
	};

	//頂点Vertexバッファを作る
	hr[0] = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_POLYGON) * 4,						//頂点情報領域確保
		D3DUSAGE_WRITEONLY,							//使用用途(書き込んでだけ)
		FVF_VERTEX_POLYGON,								//FVF、０でも大丈夫
		D3DPOOL_MANAGED,							//頂点バッファの管理方法(Deviceに管理する)
		&m_pVertexBuffer,							//管理者のメモ帳場所
		NULL);

	//インデックスバッファを作る
	hr[1] = pDevice->CreateIndexBuffer(
		sizeof(WORD) * 6,							//ワールド行列情報領域確保
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

	VERTEX_POLYGON* pV;
	m_pVertexBuffer->Lock(0, 0,						//頂点バッファロック(始まる、領域、voidのポイントポイント（つまり擬似アドレス）) 
		(void**)&pV,								//頂点バッファロック(voidのポイントポイント（つまり擬似アドレス）) 
		D3DLOCK_DISCARD);

	//頂点情報をpVに書き入れる
	//①今までの配列を使用…PVにVの内容コピーする。（memcpy使用して）
	memcpy(&pV[0], &v[0], sizeof(VERTEX_POLYGON) * 4);

	//②直接書く

	m_pVertexBuffer->Unlock();


	LPWORD pIndex;
	m_pIndexBuffer->Lock(0, 0,						//頂点バッファロック(始まる、領域、voidのポイントポイント（つまり擬似アドレス）) 
		(void**)&pIndex,							//頂点バッファロック(voidのポイントポイント（つまり擬似アドレス）) 
		D3DLOCK_DISCARD);

	//インデックスをpIndexに書き入れる
	//①今までの配列を使用…PVにVの内容コピーする。（memcpy使用して）
	memcpy(&pIndex[0], &index[0], sizeof(WORD) * 6);
	//②直接書く

	m_pIndexBuffer->Unlock();

	//マテリアルのインスタンス生成&設定
	m_Material = new CMaterial();

	return true;
}

//=================================================================================================
//　　　3Dポリゴンクラス終了処理
//=================================================================================================
void CScenePolygon::Uninit(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_Material);
}

//=================================================================================================
//　　　3Dポリゴンクラス更新処理                                    
//=================================================================================================
void CScenePolygon::Update(void)
{
	//m_veRotation.x += 0.0f;
	//m_veRotation.y += 0.05f;
	//m_veRotation.z += 0.0f;
}

//=================================================================================================
//　　　3Dポリゴンクラス描画処理
//=================================================================================================
void CScenePolygon::Draw(void)
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


	pDevice->SetStreamSource(0,
		m_pVertexBuffer, 0, sizeof(VERTEX_POLYGON));

	pDevice->SetIndices(m_pIndexBuffer);


	//FVFの設定
	pDevice->SetFVF(FVF_VERTEX_POLYGON);

	//ライトOFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 64);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ワールド行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアルの更新
	m_Material->Update();

	//テクスチャ貼り付ける
	pDevice->SetTexture(0, m_pTexture);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//バッファ使い方
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,			//Primitive描画タイプ
		0,
		0,							//インデックスの最小値	
		4,							//頂点の数
		0,
		2);							//ヴァーテックスデータのサイズ

	//ライトON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=================================================================================================
//　　　3Dポリゴンのインスタンス生成
//=================================================================================================
CScenePolygon * CScenePolygon::Create(void)
{
	CScenePolygon *ScenePolygon = new CScenePolygon(1);
	ScenePolygon->Init();
	return ScenePolygon;
}
