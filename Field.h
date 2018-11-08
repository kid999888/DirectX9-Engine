//=================================================================================================
//                                                        
//　　　フィールドプログラム[Field.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _CFIELD_H_                                                 //2重インクルード防止のマクロ定義
#define _CFIELD_H_
#include "main.h"
#include "Scene.h"

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;            //XYZW座標
	D3DXVECTOR3 fs;				//法線
	D3DCOLOR color;             //色情報
	D3DXVECTOR2 texcoord;       //テクスチャ座標
}VERTEX_3D;

//=================================================================================================
//　　　フィールドクラス                                       
//=================================================================================================
class CField: public CScene
{
public:
	CField(int nPriority, int nNumX, int nNumZ, bool bNeat = false);														//フィールドコンストラクタ
	~CField();												//フィールドデストラクタ
	bool Init(void);										//フィールド初期処理
	void Uninit(void);										//フィールド終了処理
	void Update(void);										//フィールド更新処理
	void Draw(void);										//フィールド描画処理
	static CField * Create(int nNumX, int nNumZ, bool bNeat = false);			//フィールドのインスタンス生成
	int GetBlockNumX(void)									//フィールドX方向ブロック数を取得
	{
		return m_nNumX;
	};
	int GetBlockNumZ(void)									//フィールドZ方向ブロック数を取得
	{
		return m_nNumZ;
	};
	VERTEX_3D* GetFiledPos(void)							//頂点情報管理メモ帳を取得
	{
		return m_pvMeshFiledPos;
	};							

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//頂点バッファ管理するメモ帳
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//インデックスバッファ管理するメモ
	VERTEX_3D *m_pvMeshFiledPos;							//頂点情報管理メモ帳
	int m_nFiledPosNumber;									//頂点数
	int m_nFiledIndexNumber;								//インデックス数
	int m_nFiledPrimitiveNumber;							//Primitive数
	int m_nNumX;											//フィールドのXブロック数
	int m_nNumZ;											//フィールドのZブロック数
	float m_fheightScale;									//ファイル高度情報縮小係数
	bool m_bNeat;											//
};

#endif
