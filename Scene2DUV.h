//=================================================================================================
//                                                        
//　　　2Dポリゴンプログラム[Scene2D.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE2DUV_H_                                                 //2重インクルード防止のマクロ定義
#define _SCENE2DUV_H_
#include "Scene.h"
#include<string>

//=================================================================================================
//　　　2Dポリゴンクラス                                       
//=================================================================================================
class CScene2DUV : public CScene
{
public:
	CScene2DUV(int nPriority, std::string stFileName);																	//2Dポリゴンコンストラクタ
	~CScene2DUV();															//2Dポリゴンデストラクタ
	bool Init(void);														//2Dポリゴン初期処理
	void Uninit(void);														//2Dポリゴン終了処理
	void Update(void);														//2Dポリゴン更新処理
	void Draw(void);														//2Dポリゴン描画処理
	void DrawWithOutTexture(int nAlpha);											//2Dポリゴン描画処理(テクスチャ設定なし)
	static CScene2DUV * Create(int nPriority, std::string stFileName);		//2Dポリゴンのインスタンス生成
	void SetTextureUV(float U0, float V0, float U1, float V1);				//2DポリゴンのテクスチャUVの設定
	float GetU0(void) { return m_fU0; };
	float GetV0(void) { return m_fV0; };
	float GetU1(void) { return m_fU1; };
	float GetV1(void) { return m_fV1; };
	int Get2DObjectHeight(void)												//テクスチャの高度を取得
	{
		return m_D3DTextureInfo.Height;
	};
	int Get2DObjectWidth(void)												//テクスチャの幅を取得
	{
		return m_D3DTextureInfo.Width;
	};

private:
	int m_nAlpha;															//
	D3DXIMAGE_INFO m_D3DTextureInfo;										//テクスチャ情報の管理メモ帳
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;								//頂点バッファ管理するメモ帳
	void CreateVertexAffine(D3DCOLOR color);				//頂点バッファ処理
	std::string stFileNameModel;											//ファイルパスの管理メモ帳
	float m_fU0;
	float m_fV0;
	float m_fU1;
	float m_fV1;
};

#endif