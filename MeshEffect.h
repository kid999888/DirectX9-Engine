//=================================================================================================
//                                                        
//　　　ポリコンメッシュエフェクトプログラム[MeshEffect.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.10.31      
//                                                        
//=================================================================================================
#pragma once
#include "Scene.h"
class CMeshEffect : public CScene
{
public:
	CMeshEffect();
	~CMeshEffect();
	bool Init(void);										//メッシュエフェクト初期処理
	void Uninit(void);										//メッシュエフェクト終了処理
	void Update(void);										//メッシュエフェクト更新処理
	void Draw(void);										//メッシュエフェクト描画処理
	static CMeshEffect * Create(void);						//メッシュエフェクトのインスタンス生成
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//頂点バッファ管理するメモ帳
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//インデックスバッファ管理するメモ
};

