//=================================================================================================
//                                                        
//　　　2Dポリゴンプログラム[Scene2D.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE2D_H_                                                 //2重インクルード防止のマクロ定義
#define _SCENE2D_H_
#include "Scene.h"
#include<string>

//=================================================================================================
//　　　2Dポリゴンクラス                                       
//=================================================================================================
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority, std::string stFileName, int nNx, int nNy);																	//2Dポリゴンコンストラクタ
	~CScene2D();															//2Dポリゴンデストラクタ
	bool Init(void);														//2Dポリゴン初期処理
	void Uninit(void);														//2Dポリゴン終了処理
	void Update(void);														//2Dポリゴン更新処理
	void Draw(void);														//2Dポリゴン描画処理
	void DrawWithOutTexture(int nAlpha);											//2Dポリゴン描画処理(テクスチャ設定なし)
	static CScene2D * Create(int nPriority, std::string stFileName, int nNx, int nNy);		//2Dポリゴンのインスタンス生成
	void SetTextureNum(int nX, int nY);										//2Dポリゴンのテクスチャナンバーの設定
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
	Point2DI m_nTextureNumber;												//2Dポリゴンの現在UV（枚数）
	Point2DI m_npTLimitNum;													//2DポリゴンのUV分け
	D3DXIMAGE_INFO m_D3DTextureInfo;										//テクスチャ情報の管理メモ帳
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;								//頂点バッファ管理するメモ帳
	void CreateVertexAffine(D3DCOLOR color, int tCx, int tCy);				//頂点バッファ処理
	std::string stFileNameModel;											//ファイルパスの管理メモ帳
};

#endif