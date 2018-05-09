//=================================================================================================
//                                                        
//　　　オブジェクト処理クラス プログラム[Scene.h]
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE_H_                                                 //2重インクルード防止のマクロ定義
#define _SCENE_H_
#include"main.h"
//=================================================================================================
//　　　マクロ定義                                        
//=================================================================================================

//=================================================================================================
//　　　オブジェクト処理クラス                                       
//=================================================================================================
class CScene
{
public:
	CScene() {};
	virtual ~CScene() {};
	virtual bool Init(void) { return true; };			//オブジェクト初期処理
	virtual void Uninit(void) = 0;						//オブジェクト終了処理
	virtual void Update(void) = 0;						//オブジェクト更新処理
	virtual void Draw(void) = 0;						//オブジェクト描画処理
	void SetPosition(D3DXVECTOR3 vePosition);			//オブジェクトの位置設定
	void Release(void);									//オブジェクトのリリース

protected:
	D3DXVECTOR3 m_vePosition;							//オブジェクトの位置
	LPDIRECT3DTEXTURE9* m_pTexture;						//テクスチャ管理するメモ帳
	D3DXMATRIX m_mtxWorld;								//オブジェクトワールド行列変数
	D3DXMATRIX m_mtxWorldR;								//オブジェクトワールド キューブの回転行列
	D3DXMATRIX m_mtxWorldRX;							//オブジェクトワールド キューブのX方向回転行列
	D3DXMATRIX m_mtxWorldRY;							//オブジェクトワールド キューブのY方向回転行列
	D3DXMATRIX m_mtxWorldRZ;							//オブジェクトワールド キューブのZ方向回転行列
	D3DXMATRIX m_mtxWorldT;								//オブジェクトワールド キューブの平行移動行列
	D3DXMATRIX m_mtxWorldS;								//オブジェクトワールド キューブの平行移動行列
	float m_fRotX;										//オブジェクトのX回転
	float m_fRotY;										//オブジェクトのY回転
	float m_fRotZ;										//オブジェクトのZ回転
};

#endif