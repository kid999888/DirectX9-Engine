//=================================================================================================
//                                                        
//�@�@�@�Փ˃N���X�v���O����[Collision.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"Collision.h"

//=============================================================================================
//		�֐����F	BallJudgement
//		�����@�F	�{�[��1�̈ʒu(vBall1),�{�[��2�̈ʒu(vBall2),
//					�{�[��1�̔��a(r1),�{�[��2�̔��a(r2)
//		�߂�l�F	�Փ˔����bool�^����
//		�����@�F	3D�{�[���Փ˔���
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
//		�֐����F	GetFieldHeight
//		�����@�F	�t�B�[���h�̒��_���(m_pvMeshFiledPos),�I�u�W�F�N�g�̈ʒu(Position)
//					X�����u���b�N��(NumX),Z�����u���b�N��(NumZ)
//		�߂�l�F	�t�B�[���h�̍��x(float)
//		�����@�F	�t�B�[���h�̍��x���擾
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
			//�����|���S���Փ˔���
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
				//���������߂�
				D3DXVec3Cross(&n, &V01, &V12);
				Position.y = m_pvMeshFiledPos[P0].pos.y - (n.x * (Position.x - m_pvMeshFiledPos[P0].pos.x) + n.z * (Position.z - m_pvMeshFiledPos[P0].pos.z)) / n.y;
			}



			//�E���|���S���Փ˔���
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
				//���������߂�
				D3DXVec3Cross(&n, &V01, &V12);
				Position.y = m_pvMeshFiledPos[P0].pos.y - (n.x * (Position.x - m_pvMeshFiledPos[P0].pos.x) + n.z * (Position.z - m_pvMeshFiledPos[P0].pos.z)) / n.y;
			}
		}
	}

	return Position.y;
}
