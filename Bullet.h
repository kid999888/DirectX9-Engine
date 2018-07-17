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

typedef struct
{
	int status;					//���
	D3DXVECTOR3 vePos;			//���݂̍��W
	D3DXVECTOR3 veMov;			//���x�x�N�g��
	int nLife;					//����
}BULLET;

#define BULLET_NUM (100)

//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CBullet : public CScene
{
public:
	CBullet(int nPriority) : CScene(nPriority)						//�o���b�g�R���X�g���N�^
	{
		m_veScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_bDraw = true;
	};												
	~CBullet();														//�o���b�g�f�X�g���N�^
	bool Init(void);												//�o���b�g��������
	void Uninit(void);												//�o���b�g�I������
	void Update(void);												//�o���b�g�X�V����
	void Draw(void);												//�o���b�g�`�揈��
	static CBullet * Create(CSceneModel* pBullet);									//�o���b�g�̃C���X�^���X����
	static void Load(CSceneModel* pBullet);											//�p�[�e�B�N���̃r���{�[�h��ǂݍ���
	static void Shoot(D3DXVECTOR3 vePosition, D3DXVECTOR3 veVec);					//
	static BULLET GetBulletManager(int nNum)
	{
		return m_Bullet[nNum];
	};
private:
	static BULLET m_Bullet[BULLET_NUM];								//�p�[�e�B�N�����̊Ǘ�
	static CSceneModel* m_pBullet;											//�o���b�g���f�����O�Ǘ�����A�h���X

};

#endif