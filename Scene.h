//=================================================================================================
//                                                        
//　　　オブジェクト処理クラス プログラム[Scene.h]
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE_H_                                                 //2重インクルード防止のマクロ定義
#define _SCENE_H_
#include"main.h"
#include"Material.h"

//=================================================================================================
//　　　列挙体                                      
//=================================================================================================
enum SCENE_TYPE
{
	SCENE_TYPE_NONE,
	SCENE_TYPE_2D,
	SCENE_TYPE_3D,
	SCENE_TYPE_PLAYER,
	SCENE_TYPE_ENEMY,
	SCENE_TYPE_BULLET,
};

//=================================================================================================
//　　　オブジェクト処理クラス                                       
//=================================================================================================
class CScene
{
public:
	CScene(int nPriorty);
	CScene(void);
	virtual ~CScene() {};
	virtual bool Init(void) { return true; };			//オブジェクト初期処理
	virtual void Uninit(void) = 0;						//オブジェクト終了処理
	virtual void Update(void) = 0;						//オブジェクト更新処理
	virtual void Draw(void) = 0;						//オブジェクト描画処理

	void SetScale(D3DXVECTOR3 veScale);					//オブジェクトの拡縮倍率設定
	void SetScaleX(float fX);							//オブジェクトの拡縮倍率X設定
	void SetScaleY(float fY);							//オブジェクトの拡縮倍率Y設定
	void SetScaleZ(float fZ);							//オブジェクトの拡縮倍率Z設定
	void SetRotation(D3DXVECTOR3 veRotation);			//オブジェクトの軸回転値設定
	void SetRotationX(float fX);						//オブジェクトのX軸回転値設定
	void SetRotationY(float fY);						//オブジェクトのY軸回転値設定
	void SetRotationZ(float fZ);						//オブジェクトのZ軸回転値設定
	void SetPosition(D3DXVECTOR3 vePosition);			//オブジェクトの位置設定
	void SetPositionX(float fX);						//オブジェクトの位置X設定
	void SetPositionY(float fY);						//オブジェクトの位置Y設定
	void SetPositionZ(float fZ);						//オブジェクトの位置Z設定

	D3DXVECTOR3 GetScale(void);							//オブジェクトの拡縮倍率取得
	float GetScaleX(void);								//オブジェクトの拡縮倍率X取得
	float GetScaleY(void);								//オブジェクトの拡縮倍率Y得
	float GetScaleZ(void);								//オブジェクトの拡縮倍率Z得
	D3DXVECTOR3 GetRotation(void);						//オブジェクトの軸回転値取得
	float GetRotationX(void);							//オブジェクトのX軸回転値取得
	float GetRotationY(void);							//オブジェクトのY軸回転値取得
	float GetRotationZ(void);							//オブジェクトのZ軸回転値取得
	D3DXVECTOR3 GetPosition(void);						//オブジェクトの位置取得
	float GetPositionX(void);							//オブジェクトの位置X取得
	float GetPositionY(void);							//オブジェクトの位置Y取得
	float GetPositionZ(void);							//オブジェクトの位置Z取得
	
	void Release(void);									//オブジェクトのリリース
	static void UpdateAll(void);						//オブジェクト全体更新処理
	static void DrawAll(void);							//オブジェクト全体描画処理	
	static void ReleaseAll(void);						//オブジェクトの全体リリース処理
	static CScene *m_Scene[3][30];						//シーンの管理メンバー関数
	SCENE_TYPE m_Type;
	SCENE_TYPE GetType(void)
	{
		return this->m_Type;
	};

protected:
	D3DXVECTOR3 m_veScale;								//オブジェクトの拡縮倍率
	D3DXVECTOR3 m_veRotation;							//オブジェクトの軸回転
	D3DXVECTOR3 m_vePosition;							//オブジェクトの位置
	LPDIRECT3DTEXTURE9* m_pTexture;						//テクスチャ管理するメモ帳
	CMaterial *m_Material;								//マテリアルの管理するメモ帳
	D3DXMATRIX m_mtxWorld;								//オブジェクトワールド行列変数
	D3DXMATRIX m_mtxWorldR;								//オブジェクトワールド キューブの回転行列
	D3DXMATRIX m_mtxWorldRX;							//オブジェクトワールド キューブのX方向回転行列
	D3DXMATRIX m_mtxWorldRY;							//オブジェクトワールド キューブのY方向回転行列
	D3DXMATRIX m_mtxWorldRZ;							//オブジェクトワールド キューブのZ方向回転行列
	D3DXMATRIX m_mtxWorldT;								//オブジェクトワールド キューブの平行移動行列
	D3DXMATRIX m_mtxWorldS;								//オブジェクトワールド キューブの平行移動行列
	bool m_bDraw;										//オブジェクト描画判断変数
};

#endif