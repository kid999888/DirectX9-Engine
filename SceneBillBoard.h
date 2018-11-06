//=================================================================================================
//                                                        
//　　　ビルボードクラスプログラム[SceneBillBoard.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.07.09      
//                                                        
//=================================================================================================
#ifndef _SCENEBILLBOARD_H_                                                 //2重インクルード防止のマクロ定義
#define _SCENEBILLBOARD_H_
#include "Scene.h"
#include "Camera.h"

//=================================================================================================
//　　　ビルボードクラス                                       
//=================================================================================================
class CSceneBillBoard : public CScene
{
public:
	CSceneBillBoard(CCamera* pCamera,int nPriority);							//ビルボードクラスコンストラクタ
	~CSceneBillBoard();										//ビルボードクラスデストラクタ
	bool Init(void);										//ビルボードクラス初期処理
	void Uninit(void);										//ビルボードクラス終了処理
	void Update(void);										//ビルボードクラス更新処理
	void Draw(void);										//ビルボードクラス描画処理
	static CSceneBillBoard * Create(CCamera* pCamera);					//ビルボードのインスタンス生成

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//頂点バッファ管理するメモ帳
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//インデックスバッファ管理するメモ
	D3DXMATRIX m_mtxTranspose;								//ビュー行列の転置行列
	CCamera* m_pCamera;										//
};

#endif