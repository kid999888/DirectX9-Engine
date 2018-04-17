//=================================================================================================
//                                                        
//　　　2Dポリゴンプログラム[Scene2D.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#include "Scene2D.h"

//=================================================================================================
//		マクロ定義                                        
//=================================================================================================
//FVF定義
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )			//2Dポリゴンの頂点情報
//テクスチャファイルパス
#define TEXTUREFILENAME000	        "Data\\Texture\\kobeni.png"	

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================
typedef struct
{
	D3DXVECTOR4 pos;            //XYZW座標
	D3DCOLOR color;				//頂点色
	D3DXVECTOR2 texcoord;       //テクスチャ座標

}VERTEX_2D;

//=================================================================================================
//　　　2Dポリゴンコンストラクタ                                       
//=================================================================================================
CScene2D::CScene2D()
{
	m_Position = D3DXVECTOR3(100.0f, 100.0f, 1.0f);
	m_Texture = NULL;
}

//=================================================================================================
//　　　2Dポリゴンデストラクタ                                     
//=================================================================================================
CScene2D::~CScene2D()
{
}

//=================================================================================================
//　　　2Dポリゴン初期処理                                     
//=================================================================================================
bool CScene2D::Init(void)
{
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	hr = D3DXCreateTextureFromFile(
		pDevice,
		TEXTUREFILENAME000,
		&m_Texture);

	if (FAILED(hr))
	{
		MessageBox(NULL, "エラー", "テクスチャが読み込めない。", MB_OK);
		return false;
	}

	return true;
}

//=================================================================================================
//　　　2Dポリゴン終了処理                                     
//=================================================================================================
void CScene2D::Uninit(void)
{
	SAFE_RELEASE(m_Texture);
}

//=================================================================================================
//　　　2Dポリゴン更新処理                                     
//=================================================================================================
void CScene2D::Update(void)
{
}

//=================================================================================================
//　　　2Dポリゴン描画処理                                     
//=================================================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	VERTEX_2D vtx[] = {
	//頂点座標情報
	{ D3DXVECTOR4(m_Position.x, m_Position.y, m_Position.z,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f) },          //X座標、Y座標、Z座標、光W分量(必ず1.0fに入れる)、色
	{ D3DXVECTOR4(m_Position.x + 300.0f, m_Position.y, m_Position.z,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f) },
	{ D3DXVECTOR4(m_Position.x + 300.0f, m_Position.y + 300.0f, m_Position.z,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f) },
	{ D3DXVECTOR4(m_Position.x, m_Position.y + 300.0f, m_Position.z,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f) },
	};

	//FVF(今から使用する頂点情報)の設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ貼り付ける
	pDevice->SetTexture(0, m_Texture);

	pDevice->DrawPrimitiveUP(			//重要
		D3DPT_TRIANGLEFAN,				//描画のモード
		2,								//ポリゴン数
		&vtx[0],						//座標情報
		sizeof(VERTEX_2D));				//座標情報のメモリ長さ
}


