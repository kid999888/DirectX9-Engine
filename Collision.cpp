//=================================================================================================
//                                                        
//　　　衝突クラスプログラム[Collision.cpp]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include"Collision.h"
#include"Camera.h"

//=============================================================================================
//		関数名：	BallJudgement
//		引数　：	ボール1の位置(vBall1),ボール2の位置(vBall2),
//					ボール1の半径(r1),ボール2の半径(r2)
//		戻り値：	衝突判定のbool型結果
//		説明　：	3Dボール衝突判定
//=============================================================================================
bool CCollision::BallJudgement(D3DXVECTOR3 vBall1, D3DXVECTOR3 vBall2, float r1, float r2)
{
	float x = vBall1.x - vBall2.x;
	float y = vBall1.y - vBall2.y;
	float z = vBall1.z - vBall2.z;
	float l = x * x + y * y + z * z;
	return l < (r1 + r2) * (r1 + r2);
}

//=============================================================================================
//		関数名：	GetFieldHeight
//		引数　：	フィールドの頂点情報(m_pvMeshFiledPos),オブジェクトの位置(Position)
//					X方向ブロック数(NumX),Z方向ブロック数(NumZ)
//		戻り値：	フィールドの高度(float)
//		説明　：	フィールドの高度を取得
//=============================================================================================
float CCollision::GetFieldHeight(VERTEX_3D * m_pvMeshFiledPos, D3DXVECTOR3 Position, int NumX, int NumZ)
{
	int nCx = NumX, nCz = NumZ;
	int nX, nZ;
	int nCount = 0;
	D3DXVECTOR3 V01, V12, V20, V0P, V1P, V2P, n;
	float C0, C1, C2;
	int P0, P1, P2;
	D3DXVECTOR3 T0, T1, T2;


	for (nZ = 0;nZ < nCz;nZ++)
	{
		for (nX = 0;nX < nCx;nX++)
		{
			//左側ポリゴン衝突判定
			P0 = (nZ + 1) * nCx + (1 * nZ) + 1 + nX;
			P1 = nZ * nCx + (1 * nZ) + nX;
			P2 = nZ * nCx + (1 * nZ) + (nX + 1);
			T0 = m_pvMeshFiledPos[P0].pos;
			T1 = m_pvMeshFiledPos[P1].pos;
			T2 = m_pvMeshFiledPos[P2].pos;

			V01 = m_pvMeshFiledPos[P1].pos - m_pvMeshFiledPos[P0].pos;
			V12 = m_pvMeshFiledPos[P2].pos - m_pvMeshFiledPos[P1].pos;
			V20 = m_pvMeshFiledPos[P0].pos - m_pvMeshFiledPos[P2].pos;

			V0P = Position - m_pvMeshFiledPos[P0].pos;
			V1P = Position - m_pvMeshFiledPos[P1].pos;
			V2P = Position - m_pvMeshFiledPos[P2].pos;



			C0 = V01.x * V0P.z - V01.z * V0P.x;
			C1 = V12.x * V1P.z - V12.z * V1P.x;
			C2 = V20.x * V2P.z - V20.z * V2P.x;

			if (C0 <= 0.0f && C1 <= 0.0f && C2 <= 0.0f)
			{
				//高さを求める
				D3DXVec3Cross(&n, &V01, &V12);
				Position.y = m_pvMeshFiledPos[P0].pos.y - (n.x * (Position.x - m_pvMeshFiledPos[P0].pos.x) + n.z * (Position.z - m_pvMeshFiledPos[P0].pos.z)) / n.y;
			}



			//右側ポリゴン衝突判定
			P0 = (nZ + 1) * nCx + (1 * nZ) + 1 + nX;
			P1 = nZ * nCx + (1 * nZ) + (nX + 1);
			P2 = (nZ + 1) * nCx + (1 * nZ) + 1 + (nX + 1);
			T0 = m_pvMeshFiledPos[P0].pos;
			T1 = m_pvMeshFiledPos[P1].pos;
			T2 = m_pvMeshFiledPos[P2].pos;

			V01 = m_pvMeshFiledPos[P1].pos - m_pvMeshFiledPos[P0].pos;
			V12 = m_pvMeshFiledPos[P2].pos - m_pvMeshFiledPos[P1].pos;
			V20 = m_pvMeshFiledPos[P0].pos - m_pvMeshFiledPos[P2].pos;

			V0P = Position - m_pvMeshFiledPos[P0].pos;
			V1P = Position - m_pvMeshFiledPos[P1].pos;
			V2P = Position - m_pvMeshFiledPos[P2].pos;

			C0 = V01.x * V0P.z - V01.z * V0P.x;
			C1 = V12.x * V1P.z - V12.z * V1P.x;
			C2 = V20.x * V2P.z - V20.z * V2P.x;

			if (C0 <= 0.0f && C1 <= 0.0f && C2 <= 0.0f)
			{
				//高さを求める
				D3DXVec3Cross(&n, &V01, &V12);
				Position.y = m_pvMeshFiledPos[P0].pos.y - (n.x * (Position.x - m_pvMeshFiledPos[P0].pos.x) + n.z * (Position.z - m_pvMeshFiledPos[P0].pos.z)) / n.y;
			}
		}
	}

	return Position.y;
}

//=================================================================================================
//　　　球とカプセル判定                                    
//=================================================================================================
bool CCollision::CheckSphereAndCapsule(D3DXVECTOR3 Spherecenter, float r1, D3DXVECTOR3 Capsulecenter, float lenght, float r2)
{
	D3DXVECTOR3 start = Capsulecenter - v3Up * (lenght + r2);
	D3DXVECTOR3 end = Capsulecenter + v3Up * (lenght + r2);
	float distance = GetSqDistancePoint2Segment(Spherecenter, start, end);
	float R = r1 + r2;
	if (distance > R*R)
	{
		return false;
	}
	return true;
}

//=================================================================================================
//		関数名：	GetSqDistancePoint2Segment
//		引数　：	点(point)、線分始点(start)、線分終点(end)
//		戻り値：	点と線分の距離の二乗(float)
//		説明　：	平方根を算出しない版
//		線分の端点をA,B	点をCとして、
//		①ABベクトルとACベクトルの内積が負の時、点Aが点Cの最近傍である
//		②BAベクトルとBCベクトルの内積が負の時、点Bが点Cの最近傍である
//		③　①、②に該当しない場合、点Cの射影がACの内側に存在するため、その点が最近傍である
//=================================================================================================
float CCollision::GetSqDistancePoint2Segment(const D3DXVECTOR3 & point, const D3DXVECTOR3 & start, const D3DXVECTOR3 & end)
{
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値
	D3DXVECTOR3 SegmentSub;
	D3DXVECTOR3 SegmentPoint;
	D3DXVECTOR3 CP;

	// 線分の始点から終点へのベクトル
	SegmentSub = end - start;

	// 線分の始点から点へのベクトル
	SegmentPoint = point - start;
	if (D3DXVec3Dot(&SegmentSub, &SegmentPoint) < epsilon)
	{// ２ベクトルの内積が負なら、線分の始点が最近傍
		return 	D3DXVec3Dot(&SegmentPoint, &SegmentPoint);
	}

	// 点から線分の終点へのベクトル
	SegmentPoint = end - point;
	if (D3DXVec3Dot(&SegmentSub, &SegmentPoint) < epsilon)
	{// ２ベクトルの内積が負なら、線分の終点が最近傍
		return 	D3DXVec3Dot(&SegmentPoint, &SegmentPoint);
	}

	// 上記のどちらにも該当しない場合、線分上に落とした射影が最近傍
	// (本来ならサインで求めるが、外積の大きさ/線分のベクトルの大きさで求まる)
	D3DXVec3Cross(&CP, &SegmentSub, &SegmentPoint);

	return D3DXVec3Dot(&CP, &CP) / D3DXVec3Dot(&SegmentSub, &SegmentSub);
}
