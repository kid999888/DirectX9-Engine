//=================================================================================================
//                                                        
//　　　衝突クラスプログラム[Collision.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _COLLISION_H_                                                 //2重インクルード防止のマクロ定義
#define _COLLISION_H_
#include "main.h"
#include "Field.h"

//=================================================================================================
//　　　衝突クラス                                      
//=================================================================================================
class CCollision
{
public:
	static bool BallJudgement(D3DXVECTOR3 vBall1, D3DXVECTOR3 vBall2, float r1, float r2);					//フィールドの高度を取得
	static float GetFieldHeight(VERTEX_3D *m_pvMeshFiledPos,D3DXVECTOR3 Position, int NumX, int NumZ);		//3Dボール衝突判定
	static bool CheckSphereAndCapsule(D3DXVECTOR3 Spherecenter, float r1,									//球とカプセル判定
								D3DXVECTOR3 Capsulecenter, float lenght, float r2);
	static float GetSqDistancePoint2Segment(const D3DXVECTOR3& point,										//点と線分の距離の二乗を取得
								const D3DXVECTOR3& start, const D3DXVECTOR3& end);
	static D3DXVECTOR3* CalcScreenToXZ(D3DXVECTOR3* pout,int Sx,int Sy,
	int Screen_w,int Screen_h,D3DXMATRIX* View,D3DXMATRIX* Prj);
	static D3DXVECTOR3* CalcScreenToWorld(D3DXVECTOR3* pout, int Sx, int Sy, float fZ,
	int Screen_w, int Screen_h, D3DXMATRIX* View, D3DXMATRIX* Prj);
	

private:
	
};
#endif