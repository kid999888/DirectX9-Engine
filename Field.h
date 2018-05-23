//=================================================================================================
//                                                        
//　　　フィールドプログラム[Field.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _CFIELD_H_                                                 //2重インクルード防止のマクロ定義
#define _CFIELD_H_
#include"Scene.h"

//=================================================================================================
//　　　フィールドクラス                                       
//=================================================================================================
class CField: public CScene
{
public:
	CField(int nPriority) : CScene(nPriority)
	{
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fRotX = 0.0f;
		m_fRotY = 0.0f;
		m_fRotZ = 0.0f;
		m_pTexture = nullptr;
		m_pVertexBuffer = NULL;
		m_pIndexBuffer = NULL;
	};												//フィールドコンストラクタ
	~CField();										//フィールドデストラクタ
	bool Init(void);								//フィールド初期処理
	void Uninit(void);								//フィールド終了処理
	void Update(void);								//フィールド更新処理
	void Draw(void);								//フィールド描画処理
	static CField * Create(void);					//フィールドのインスタンス生成

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//頂点バッファ管理するメモ帳
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//インデックスバッファ管理するメモ
	int m_FiledPosNumber;									//頂点数
	int m_FiledIndexNumber;									//インデックス数
	int m_FiledPrimitiveNumber;								//Primitive数
};

#endif
