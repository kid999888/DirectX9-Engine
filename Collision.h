//=================================================================================================
//                                                        
//�@�@�@�Փ˃N���X�v���O����[Collision.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _COLLISION_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _COLLISION_H_
#include"main.h"
#include"Field.h"

//=================================================================================================
//�@�@�@DirectX�������N���X                                      
//=================================================================================================
class CCollision
{
public:
	static bool BallJudgement(D3DXVECTOR3 vBall1, D3DXVECTOR3 vBall2, float r1, float r2);					//�t�B�[���h�̍��x���擾
	static float GetFieldHeight(VERTEX_3D *m_pvMeshFiledPos,D3DXVECTOR3 Position, int NumX, int NumZ);		//3D�{�[���Փ˔���
	

private:
	
};
#endif