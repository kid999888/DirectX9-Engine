//=================================================================================================
//                                                        
//　　　カメラクラスプログラム[Camera.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _CAMERA_H_                                                 //2重インクルード防止のマクロ定義
#define _CAMERA_H_
#include "main.h"
//=================================================================================================
//　　　マクロ定義                                        
//=================================================================================================

//=================================================================================================
//　　　3Dポリゴンクラス                                       
//=================================================================================================
class CCamera
{
public:
	CCamera();											//カメラクラスコンストラクタ
	~CCamera();											//カメラクラスデストラクタ
	void Update(void);									//カメラクラス更新処理
	void SetCameraPos(D3DXVECTOR3 veEyePos);			//カメラ位置の設定
	void SetCameraAtPos(D3DXVECTOR3 veAtPos);			//カメラ注視点の設定
	D3DXVECTOR3 GetCameraPos(void)				//カメラ位置の取得
	{ return m_eye; };									
	D3DXVECTOR3 GetCameraAtPos(void)				//カメラ注視点の取得
	{ return m_at; };
	static D3DXMATRIX GetCameraProjection(void)			//カメラプロジェクション行列の取得
	{
		return m_mtxProjection;
	};
	static D3DXMATRIX GetCameraView(void)			//カメラビュー行列の取得
	{
		return m_mtxView;
	};
private:
	static D3DXVECTOR3 m_eye;							//カメラ場所を声明
	static D3DXVECTOR3 m_at;							//カメラ注視点を声明
	static D3DXVECTOR3 m_up;							//上の場所を声明
	static D3DXMATRIX m_mtxView;						//ビュー行列
	static D3DXMATRIX m_mtxProjection;					//プロジェクション行列
};
#endif