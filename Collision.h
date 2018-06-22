//=================================================================================================
//                                                        
//　　　衝突クラスプログラム[Collision.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _COLLISION_H_                                                 //2重インクルード防止のマクロ定義
#define _COLLISION_H_
#include"main.h"
#include"Field.h"

//=================================================================================================
//　　　DirectX初期化クラス                                      
//=================================================================================================
class CCollision
{
public:
	static bool BallJudgement(D3DXVECTOR3 vBall1, D3DXVECTOR3 vBall2, float r1, float r2);					//フィールドの高度を取得
	static float GetFieldHeight(VERTEX_3D *m_pvMeshFiledPos,D3DXVECTOR3 Position, int NumX, int NumZ);		//3Dボール衝突判定
	

private:
	
};
#endif