//=================================================================================================
//                                                        
//�@�@�@�G�N���X�v���O����[Enemy.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.16      
//                                                        
//=================================================================================================
#ifndef _CENEMY_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CENEMY_H_
#include"Scene.h"
#include"Scene3D.h"
#include"Player.h"


typedef struct
{
	int status;					//���
	D3DXVECTOR3 vePos;			//���݂̍��W
	D3DXVECTOR3 veMov;			//���x�x�N�g��
	int nLife;					//����
}ENEMY;

#define ENEMY_NUM (100)

//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CEnemy : public CScene
{
public:
	CEnemy(int nPriority) : CScene(nPriority)						//�G�R���X�g���N�^
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_bDraw = true;
	};
	~CEnemy();														//�G�f�X�g���N�^
	bool Init(void);												//�G��������
	void Uninit(void);												//�G�I������
	void Update(void);												//�G�X�V����
	void Draw(void);												//�G�`�揈��
	static CEnemy * Create(CScene3D* pScene3D);						//�G�̃C���X�^���X����
	static void Load(CScene3D* pScene3D);							//�G�̎��̂�ǂݍ���
	static void Generate(D3DXVECTOR3 vePosition);					//�V�����G�𐶐�
	static void Destory(int nNum);									//�G��p������
	static void SetEnemyLife(int nNum, int nLife);					//�GHP��ݒ�
	static ENEMY GetEnemyManager(int nNum)							//�i���o�[�̓G�̏�������
	{
		return m_Enemy[nNum];
	};
private:
	static ENEMY m_Enemy[ENEMY_NUM];								//�G���̊Ǘ�
	static CScene3D* m_pScene3D;									//�G�̎��̊Ǘ�����A�h���X
	static D3DXVECTOR3 GetMovePattern(int nNum);					//�G�ړ��p�^�[��
};

#endif