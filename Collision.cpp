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
#include"Camera.h"

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

//=================================================================================================
//�@�@�@���ƃJ�v�Z������                                    
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
//		�֐����F	GetSqDistancePoint2Segment
//		�����@�F	�_(point)�A�����n�_(start)�A�����I�_(end)
//		�߂�l�F	�_�Ɛ����̋����̓��(float)
//		�����@�F	���������Z�o���Ȃ���
//		�����̒[�_��A,B	�_��C�Ƃ��āA
//		�@AB�x�N�g����AC�x�N�g���̓��ς����̎��A�_A���_C�̍ŋߖT�ł���
//		�ABA�x�N�g����BC�x�N�g���̓��ς����̎��A�_B���_C�̍ŋߖT�ł���
//		�B�@�@�A�A�ɊY�����Ȃ��ꍇ�A�_C�̎ˉe��AC�̓����ɑ��݂��邽�߁A���̓_���ŋߖT�ł���
//=================================================================================================
float CCollision::GetSqDistancePoint2Segment(const D3DXVECTOR3 & point, const D3DXVECTOR3 & start, const D3DXVECTOR3 & end)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	D3DXVECTOR3 SegmentSub;
	D3DXVECTOR3 SegmentPoint;
	D3DXVECTOR3 CP;

	// �����̎n�_����I�_�ւ̃x�N�g��
	SegmentSub = end - start;

	// �����̎n�_����_�ւ̃x�N�g��
	SegmentPoint = point - start;
	if (D3DXVec3Dot(&SegmentSub, &SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̎n�_���ŋߖT
		return 	D3DXVec3Dot(&SegmentPoint, &SegmentPoint);
	}

	// �_��������̏I�_�ւ̃x�N�g��
	SegmentPoint = end - point;
	if (D3DXVec3Dot(&SegmentSub, &SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̏I�_���ŋߖT
		return 	D3DXVec3Dot(&SegmentPoint, &SegmentPoint);
	}

	// ��L�̂ǂ���ɂ��Y�����Ȃ��ꍇ�A������ɗ��Ƃ����ˉe���ŋߖT
	// (�{���Ȃ�T�C���ŋ��߂邪�A�O�ς̑傫��/�����̃x�N�g���̑傫���ŋ��܂�)
	D3DXVec3Cross(&CP, &SegmentSub, &SegmentPoint);

	return D3DXVec3Dot(&CP, &CP) / D3DXVec3Dot(&SegmentSub, &SegmentSub);
}
