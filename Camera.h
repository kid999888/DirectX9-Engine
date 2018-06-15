//=================================================================================================
//                                                        
//　　　カメラクラスプログラム[Camera.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _CAMERA_H_                                                 //2重インクルード防止のマクロ定義
#define _CAMERA_H_
#include"main.h"
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
	static void SetCameraPos(D3DXVECTOR3 veEyePos);		//
	static void SetCameraAtPos(D3DXVECTOR3 veAtPos);	//
	static D3DXVECTOR3 GetCameraPos(void) 
	{ return m_eye; };									//
	static D3DXVECTOR3 GetCameraAtPos(void) 
	{ return m_at; };									//

private:
	static D3DXVECTOR3 m_eye;									//カメラの場所
	static D3DXVECTOR3 m_at;									//注視点
	static D3DXVECTOR3 m_up;									//上の場所
	D3DXMATRIX m_mtxView;								//ビュー行列
	D3DXMATRIX m_mtxProjection;							//プロジェクション行列
};
#endif