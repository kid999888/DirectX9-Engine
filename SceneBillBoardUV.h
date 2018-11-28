//=================================================================================================
//                                                        
//　　　ビルボードクラスプログラム[SceneBillBoard.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.07.09      
//                                                        
//=================================================================================================
#ifndef _SCENEBILLBOARDUV_H_                                                 //2重インクルード防止のマクロ定義
#define _SCENEBILLBOARDUV_H_
#include "Scene.h"
#include "Camera.h"
#include<string>

//=================================================================================================
//　　　ビルボードクラス                                       
//=================================================================================================
class CSceneBillBoardUV : public CScene
{
public:
	CSceneBillBoardUV(CCamera* pCamera,int nPriority, std::string stFileName);							//ビルボードクラスコンストラクタ
	~CSceneBillBoardUV();										//ビルボードクラスデストラクタ
	bool Init(void);										//ビルボードクラス初期処理
	void Uninit(void);										//ビルボードクラス終了処理
	void Update(void);										//ビルボードクラス更新処理
	void Draw(void);										//ビルボードクラス描画処理
	static CSceneBillBoardUV * Create(CCamera* pCamera, std::string stFileName);					//ビルボードのインスタンス生成
	void SetTextureUV(float U0, float V0, float U1, float V1);				//ビルボードのテクスチャUVの設定
	float GetU0(void) { return m_fU0; };
	float GetV0(void) { return m_fV0; };
	float GetU1(void) { return m_fU1; };
	float GetV1(void) { return m_fV1; };

private:
	std::string stFileNameModel;											//ファイルパスの管理メモ帳
	D3DXIMAGE_INFO m_D3DTextureInfo;										//テクスチャ情報の管理メモ帳
	void CreateVertexAffine(D3DCOLOR color);
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//頂点バッファ管理するメモ帳
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//インデックスバッファ管理するメモ
	D3DXMATRIX m_mtxTranspose;								//ビュー行列の転置行列
	CCamera* m_pCamera;										//
	float m_fU0;
	float m_fV0;
	float m_fU1;
	float m_fV1;
};

#endif