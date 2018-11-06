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
#define PI				(3.141592f)			// 円周率

#define	VIEW_ANGLE				(45.0f)					// 視野角(45.0f)	
#define	VIEW_NEAR_Z				(10.0f)					// ビュー平面のNearZ値(10.0f)	
#define	VIEW_FAR_Z				(100000.0f)				// ビュー平面のFarZ値(100000.0f)	

#define	VALUE_MOVE				(0.2f)					// カメラの移動量
#define	VALUE_ROTATE			(PI * 0.01f)			// カメラの回転量
#define	VALUE_MOVE_DRAG			(0.30f)					// マウスドラッグ時の移動量
#define	VALUE_ROTATE_MOUSE		(0.003f)				// マウスによる回転量

#define	CAM_LENGTH_RATE			(20.0f)					// 視点から注視点までの距離の比率
#define	CAM_LENGTH_LIMIT_MIN	(10.0f)					// 視点から注視点までの距離最小値
#define	CAM_LENGTH_LIMIT_MAX	(1600.0f)				// 視点から注視点までの距離最大値

#define	LENGTH_REF_MOVE			(60.0f)					// プレイヤーに対する注視点の距離(移動中)
#define	LENGTH_REF_STOP			(30.0f)					// プレイヤーに対する注視点の距離(停止中)
#define	HEIGTH_REF				(40.0f)					// プレイヤーに対する注視点の高さ

#define	LENGTH_POS_MOVE			(300.0f)				// プレイヤーに対する視点の距離(移動中)
#define	LENGTH_POS_STOP			(300.0f)				// プレイヤーに対する視点の距離(停止中)
#define	HEIGTH_POS				(80.0f)					// プレイヤーに対する視点の高さ

#define	ADJUST_ROT				(0.010f)				// 視点の回転角補正係数

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
	D3DXVECTOR3 GetCameraPos(void)						//カメラ位置の取得
	{ return m_eye; };									
	D3DXVECTOR3 GetCameraAtPos(void)					//カメラ注視点の取得
	{ return m_at; };
	D3DXMATRIX GetCameraProjection(void)				//カメラプロジェクション行列の取得
	{
		return m_mtxProjection;
	};
	D3DXMATRIX GetCameraView(void)						//カメラビュー行列の取得
	{
		return m_mtxView;
	};
	void CameraViewFlag(bool bFlag)						//視点操作フラッグ
	{
		m_bViewChange = bFlag;
	}

private:
	D3DXVECTOR3 m_eye;							//カメラ場所を声明
	D3DXVECTOR3 m_at;							//カメラ注視点を声明
	D3DXVECTOR3 m_up;							//上の場所を声明
	D3DXVECTOR3 m_rot;							//カメラの向き
	D3DXMATRIX m_mtxView;						//ビュー行列
	D3DXMATRIX m_mtxProjection;					//プロジェクション行列
	bool m_bViewChange;							//視点操作フラッグ
	float m_fLengthInterval;							// 視点から注視点までの距離
	float m_fLengthIntervalXZ;							// 視点から注視点までの距離(XZ平面)
	void ViewChange(void);								//視点操作
};
#endif