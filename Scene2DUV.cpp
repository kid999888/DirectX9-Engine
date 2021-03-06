//=================================================================================================
//                                                        
//　　　2Dポリゴンプログラム[Scene2D.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include "Scene2DUV.h"
#include "Renderer.h"

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================
//FVF定義
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )			//2Dポリゴンの頂点情報

//=================================================================================================
//　　　実体定義                                       
//=================================================================================================

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================
typedef struct
{
	D3DXVECTOR4 pos;            //XYZW座標
	D3DCOLOR color;				//頂点色
	D3DXVECTOR2 texcoord;       //テクスチャ座標

}VERTEX_2D;

CScene2DUV::CScene2DUV(int nPriority, std::string stFileName): CScene(nPriority)
{
	m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vePosition = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_fU0 = 0.0f;
	m_fV0 = 0.0f;
	m_fU1 = 1.0f;
	m_fV1 = 1.0f;
	m_pTexture = nullptr;
	m_pVertexBuffer = NULL;
	stFileNameModel = stFileName;
}
//=================================================================================================
//　　　2Dポリゴンデストラクタ                                     
//=================================================================================================
CScene2DUV::~CScene2DUV()
{
}

//=================================================================================================
//　　　2Dポリゴン初期処理                                     
//=================================================================================================
bool CScene2DUV::Init(void)
{
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	hr = D3DXCreateTextureFromFile(
		pDevice,
		stFileNameModel.c_str(),
		&m_pTexture);

	if (FAILED(hr))
	{
		MessageBox(NULL, "エラー", "テクスチャが読み込めない。", MB_OK);
		return false;
	}

	//テクスチャの情報を読み込む
	hr = D3DXGetImageInfoFromFile(stFileNameModel.c_str(), &m_D3DTextureInfo);

	if (FAILED(hr))
	{
		MessageBox(NULL, "エラー", "テクスチャ情報が読み込めない。", MB_OK);
		return false;
	}

	/*m_veScaleOffset.x = m_vePosition.x + (float)(m_D3DTextureInfo.Width / 2);
	m_veScaleOffset.y = m_vePosition.y + (float)(m_D3DTextureInfo.Height / 2);
	m_veRotationOffset.x = m_veScaleOffset.x;
	m_veRotationOffset.y = m_veScaleOffset.y;*/

	//Vertexバッファを作る
	hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,                                       //頂点情報領域確保
		D3DUSAGE_WRITEONLY,                                          //使用用途(書き込んでだけ)
		FVF_VERTEX_2D,                                               //FVF、０でも大丈夫
		D3DPOOL_MANAGED,                                             //頂点バッファの管理方法(Deviceに管理する)
		&m_pVertexBuffer,                                           //管理者のメモ帳場所
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "頂点バッファが作れない", "エラー", MB_OK);							//頂点バッファエラーメッセージ
		return false;
	}

	return true;
}

//=================================================================================================
//　　　2Dポリゴン終了処理                                     
//=================================================================================================
void CScene2DUV::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pVertexBuffer);
}

//=================================================================================================
//　　　2Dポリゴン更新処理                                     
//=================================================================================================
void CScene2DUV::Update(void)
{
}

//=================================================================================================
//　　　2Dポリゴン描画処理                                     
//=================================================================================================
void CScene2DUV::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	CreateVertexAffine(D3DCOLOR_RGBA(255, 255, 255, 255));


	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_2D));

	//レンダーステートの設定
	//αブレンドを行う
	//SRC...今から描くもの、つまりポリゴンに描画されている部分
	//DEST...すでに描画されている画面の部分
	//SRC_RGB * SRC_α +DEST_RGB * ( 1 - SRC_α )
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);                   //

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	

	//FVF(今から使用する頂点情報)の設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ貼り付ける
	pDevice->SetTexture(0, m_pTexture);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	

	pDevice->DrawPrimitive(                 //重要
		D3DPT_TRIANGLEFAN, 0,			    //描画のモード
		2);                                  //ポリゴン数
	
	//アルファブレンドOFF
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CScene2DUV::DrawWithOutTexture(int nAlpha = 255)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	CreateVertexAffine(D3DCOLOR_RGBA(255, 255, 255, nAlpha));

	//設定のアルファで設定する
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);

	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_2D));

	//レンダーステートの設定
	//αブレンドを行う
	//SRC...今から描くもの、つまりポリゴンに描画されている部分
	//DEST...すでに描画されている画面の部分
	//SRC_RGB * SRC_α +DEST_RGB * ( 1 - SRC_α )
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);                   //

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	

	//FVF(今から使用する頂点情報)の設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	pDevice->DrawPrimitive(                 //重要
		D3DPT_TRIANGLEFAN, 0,			    //描画のモード
		2);                                  //ポリゴン数

	//アルファブレンドOFF
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

//=================================================================================================
//　　　2Dポリゴンクラスのインスタンス生成                                    
//=================================================================================================
CScene2DUV * CScene2DUV::Create(int nPriority, std::string stFileName)
{
	CScene2DUV *Scene2DUV = new CScene2DUV(nPriority, stFileName);
	Scene2DUV->Init();
	return Scene2DUV;
}

//=================================================================================================
//　　　2DポリゴンのテクスチャUVの設定                                
//=================================================================================================
void CScene2DUV::SetTextureUV(float U0, float V0, float U1, float V1)
{
	m_fU0 = U0;
	m_fV0 = V0;
	m_fU1 = U1;
	m_fV1 = V1;
}


//=================================================================================================
//　　　頂点バッファ処理                                   
//=================================================================================================
void CScene2DUV::CreateVertexAffine(D3DCOLOR color)
{
	float dx = m_vePosition.x;
	float dy = m_vePosition.y;

	int tw = m_D3DTextureInfo.Width;
	int th = m_D3DTextureInfo.Height;

	int dw = m_D3DTextureInfo.Width * m_fU1;
	int dh = m_D3DTextureInfo.Height * m_fV1;

	dw *= m_veScale.x;
	dh *= m_veScale.y;

	float u0 = m_fU0;
	float v0 = m_fV0;
	float u1 = m_fU1;
	float v1 = m_fV1;

	VERTEX_2D* pV;
	m_pVertexBuffer->Lock(0, 0,			//頂点バッファロック(始まる、領域、voidのポイントポイント（つまり擬似アドレス）) 
		(void**)&pV,					//頂点バッファロック(voidのポイントポイント（つまり擬似アドレス）) 
		D3DLOCK_DISCARD);
	
	/*
	float x   = (    -m_veScaleOffset.x) * m_veScale.x + m_veScale.x;
	float x_w = (tcw - m_veScaleOffset.x) * m_veScale.x + m_veScale.x;
	float y   = (    -m_veScaleOffset.y) * m_veScale.y + m_veScale.y;
	float y_h = (tch - m_veScaleOffset.y) * m_veScale.y + m_veScale.y;

	float fPolygonRotationOffSetX = (m_veScaleOffset.x - m_veScaleOffset.x) * m_veScale.x;
	float fPolygonRotationOffSetY = (m_veScaleOffset.y - m_veScaleOffset.y) * m_veScale.y;

	x -= fPolygonRotationOffSetX;
	x_w -= fPolygonRotationOffSetX;
	y -= fPolygonRotationOffSetY;
	y_h -= fPolygonRotationOffSetY;

	dx += fPolygonRotationOffSetX - 0.5f;
	dy += fPolygonRotationOffSetY - 0.5f;

	pV[0].pos = D3DXVECTOR4(
		dx + x*cosf(m_fRotationAngle) - y*sinf(m_fRotationAngle),
		dy + x*sinf(m_fRotationAngle)+y*cosf(m_fRotationAngle),
		m_vePosition.z, 1.0f);
	pV[1].pos = D3DXVECTOR4(
		dx + x_w*cosf(m_fRotationAngle) - y*sinf(m_fRotationAngle),
		dy + x_w*sinf(m_fRotationAngle) + y*cosf(m_fRotationAngle),
		m_vePosition.z, 1.0f);
	pV[2].pos = D3DXVECTOR4(
		dx + x_w*cosf(m_fRotationAngle) - y_h*sinf(m_fRotationAngle),
		dy + x_w*sinf(m_fRotationAngle) + y_h*cosf(m_fRotationAngle),
		m_vePosition.z, 1.0f);
	pV[3].pos = D3DXVECTOR4(
		dx + x*cosf(m_fRotationAngle) - y_h*sinf(m_fRotationAngle),
		dy + x*sinf(m_fRotationAngle) + y_h*cosf(m_fRotationAngle),
		m_vePosition.z, 1.0f);
	*/

	pV[0].pos = D3DXVECTOR4(dx + 0.0f - 0.5f, dy + 0.0f - 0.5f, m_vePosition.z, 1.0f);
	pV[1].pos = D3DXVECTOR4(dx + dw - 0.5f, dy + 0.0f - 0.5f, m_vePosition.z, 1.0f);
	pV[2].pos = D3DXVECTOR4(dx + dw - 0.5f, dy + dh - 0.5f, m_vePosition.z, 1.0f);
	pV[3].pos = D3DXVECTOR4(dx + 0.0f - 0.5f, dy + dh - 0.5f, m_vePosition.z, 1.0f);

	pV[0].color = color;
	pV[1].color = color;
	pV[2].color = color;
	pV[3].color = color;

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u1, v1);
	pV[3].texcoord = D3DXVECTOR2(u0, v1);

	m_pVertexBuffer->Unlock();                                            //頂点バッファアンロック
}


