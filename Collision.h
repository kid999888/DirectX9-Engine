//=================================================================================================
//                                                        
//�@�@�@�Փ˃N���X�v���O����[Collision.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _COLLISION_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _COLLISION_H_
#include "main.h"
#include "Field.h"

//=================================================================================================
//�@�@�@�Փ˃N���X                                      
//=================================================================================================
class CCollision
{
public:
	static bool BallJudgement(D3DXVECTOR3 vBall1, D3DXVECTOR3 vBall2, float r1, float r2);					//�t�B�[���h�̍��x���擾
	static float GetFieldHeight(VERTEX_3D *m_pvMeshFiledPos,D3DXVECTOR3 Position, int NumX, int NumZ);		//3D�{�[���Փ˔���
	static bool CheckSphereAndCapsule(D3DXVECTOR3 Spherecenter, float r1,									//���ƃJ�v�Z������
								D3DXVECTOR3 Capsulecenter, float lenght, float r2);
	static float GetSqDistancePoint2Segment(const D3DXVECTOR3& point,										//�_�Ɛ����̋����̓����擾
								const D3DXVECTOR3& start, const D3DXVECTOR3& end);
	static D3DXVECTOR3* CalcScreenToXZ(D3DXVECTOR3* pout,int Sx,int Sy,
	int Screen_w,int Screen_h,D3DXMATRIX* View,D3DXMATRIX* Prj);
	static D3DXVECTOR3* CalcScreenToWorld(D3DXVECTOR3* pout, int Sx, int Sy, float fZ,
	int Screen_w, int Screen_h, D3DXMATRIX* View, D3DXMATRIX* Prj);
	

private:
	
};
#endif