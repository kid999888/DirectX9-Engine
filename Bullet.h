//=================================================================================================
//                                                        
//�@�@�@�o���b�g�N���X�v���O����[Bullet.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.23      
//                                                        
//=================================================================================================
#ifndef _CBULLET_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CBULLET_H_
#include"Scene.h"
#include"SceneModel.h"

//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CBullet : public CScene
{
public:
	CBullet(int nPriority) : CScene(nPriority)
	{
		m_veScale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_veMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_nLife = 0;
	};												//�v���[���[�R���X�g���N�^
	~CBullet();										//�v���[���[�f�X�g���N�^
	bool Init(void);								//�v���[���[��������
	void Uninit(void);								//�v���[���[�I������
	void Update(void);								//�v���[���[�X�V����
	void Draw(void);								//�v���[���[�`�揈��
	static CBullet * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 At);					//�v���[���[�̃C���X�^���X����
	/*static bool BallJudgement(D3DXVECTOR3 vBall1, D3DXVECTOR3 vBall2, float r1, float r2);*/

private:
	CSceneModel * m_pBullet;							//�v���[���[�̃��f�����O�Ǘ�����A�h���X
	static D3DXVECTOR3 m_vePosition;
	static D3DXVECTOR3 m_veMove;								//
	int m_nLife;

};

#endif