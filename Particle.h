//=================================================================================================
//                                                        
//�@�@�@�p�[�e�B�N���N���X�v���O����[Particle.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.09      
//                                                        
//=================================================================================================
#ifndef _CPARTICLE_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CPARTICLE_H_
#include "Scene.h"
#include "SceneBillBoard.h"

//=================================================================================================
//�@�@�@�\���̒�`                                         
//=================================================================================================
typedef struct
{
	int status;					//���
	D3DXVECTOR3 vePos;			//���݂̍��W
	D3DXVECTOR3 veMov;			//���x�x�N�g��
	D3DXVECTOR3 veAcc;			//�����x�x�N�g��
	int nLife;					//����
}PARTICLE;

#define PARTICLE_NUM (200)

//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CParticle : public CScene
{
public:
	CParticle(int nPriority) : CScene(nPriority)						//�p�[�e�B�N���R���X�g���N�^
	{
		m_veScale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fSpeed = 1.0f;
		m_nLifeLimit = 100;
	};
	~CParticle();													//�p�[�e�B�N���f�X�g���N�^
	bool Init(void);												//�p�[�e�B�N����������
	void Uninit(void);												//�p�[�e�B�N���I������
	void Update(void);												//�p�[�e�B�N���X�V����
	void Draw(void);												//�p�[�e�B�N���`�揈��
	static CParticle * Create(CSceneBillBoard* pBillBoard,
		D3DXVECTOR3 vePosition, float fSpeed, int nLife,int GenerateTime,bool bGravity = false);			//�p�[�e�B�N���̃C���X�^���X����
	static void LoadBillBoard(CSceneBillBoard* pBillBoard);			//�p�[�e�B�N���̃r���{�[�h��ǂݍ���


private:
	PARTICLE m_Particle[PARTICLE_NUM];								//�p�[�e�B�N�����̊Ǘ�
	static CSceneBillBoard* m_pBillBoard;							//�p�[�e�B�N���r���{�[�h�Ǘ�����A�h���X
	static D3DXVECTOR3 m_vePosition;								//�p�[�e�B�N�������̈ʒu�𐺖�����
	static float m_fSpeed;											//�p�[�e�B�N���̈ړ��X�r�[�g�𐺖�����
	static int m_nLifeLimit;										//�p�[�e�B�N���̎������E�𐺖�����
	int m_nGenerateTime;											//�p�[�e�B�N���̐�������
	static int m_nGenerateTimeLimit;								//�p�[�e�B�N���̎������E�𐺖�����
	static bool m_bGravityType;										//�p�[�e�B�N�����d�͂̉e�����󂯂邩
};

#endif