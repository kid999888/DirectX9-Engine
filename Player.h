//=================================================================================================
//                                                        
//�@�@�@�v���[���[�N���X�v���O����[Player.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.23      
//                                                        
//=================================================================================================
#ifndef _CPLAYER_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CPLAYER_H_
#include"Scene.h"
#include"SceneModel.h"


#include"Camera.h"
#include"Bullet.h"

//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CPlayer : public CScene
{
public:
	CPlayer(int nPriority) : CScene(nPriority)
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePlayerFront = D3DXVECTOR3(m_vePosition.x, m_vePosition.y, (m_vePosition.z - 1.0f));
		m_veFrontTemporary = m_vePlayerFront;
		m_fMoveSpeed = 0.2f;
		m_fRotYSpeed = 5.0f;
		m_fRotOnce = 0.0f;
		m_fRotYExactly = 0;
		m_pTexture = nullptr;
	};												//�v���[���[�R���X�g���N�^
	~CPlayer();										//�v���[���[�f�X�g���N�^
	bool Init(void);								//�v���[���[��������
	void Uninit(void);								//�v���[���[�I������
	void Update(void);								//�v���[���[�X�V����
	void Draw(void);								//�v���[���[�`�揈��
	static CPlayer * Create(D3DXVECTOR3 vePosition);//�v���[���[�̃C���X�^���X����
	bool BallJudgement(D3DXVECTOR3 vBall1, D3DXVECTOR3 vBall2, float r1, float r2);
	D3DXVECTOR3 GetPlayerFront(void)				//�v���[���[�̌����x�N�g�����擾
	{
		return m_veFrontTemporary;
	};
	float GetPlayerRotY(void)
	{
		return m_veRotation.y;
	}

private:
	CSceneModel * m_pPlayer;							//�v���[���[�̃��f�����O�Ǘ�����A�h���X
	CBullet * m_pBullet;								//�Ǘ�����A�h���X
	CCamera *m_Camera;									//�J�����Ǘ����郁���o�[�A�h���X
	D3DXVECTOR3 m_vePlayerFront;						//�v���[���[�̌����x�N�g��
	D3DXVECTOR3 m_veFrontTemporary;
	float m_fMoveSpeed;									//�ړ��X�r�[�g
	float m_fRotYSpeed;									//��]�X�r�[�g
	float m_fRotOnce;									//�v���[���[����]�p�x
	int m_fRotYExactly;									//��]���E
};

#endif