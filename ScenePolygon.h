//=================================================================================================
//                                                        
//　　　3Dポリゴンクラスプログラム[ScenePolygon.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.06.08      
//                                                        
//=================================================================================================
#ifndef _SCENEPOLYGON_H_                                                 //2重インクルード防止のマクロ定義
#define _SCENEPOLYGON_H_
#include"Scene.h"

//=================================================================================================
//　　　3Dポリゴンクラス                                       
//=================================================================================================
class CScenePolygon : public CScene
{
public:
	CScenePolygon(int nPriority) : CScene(nPriority)
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pTexture = nullptr;
		m_pVertexBuffer = NULL;
		m_pIndexBuffer = NULL;
	};														//3Dポリゴンクラスコンストラクタ
	~CScenePolygon();										//3Dポリゴンクラスデストラクタ
	bool Init(void);										//3Dポリゴンクラス初期処理
	void Uninit(void);										//3Dポリゴンクラス終了処理
	void Update(void);										//3Dポリゴンクラス更新処理
	void Draw(void);										//3Dポリゴンクラス描画処理
	static CScenePolygon * Create(void);					//3Dポリゴンのインスタンス生成

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//頂点バッファ管理するメモ帳
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//インデックスバッファ管理するメモ
};

#endif
