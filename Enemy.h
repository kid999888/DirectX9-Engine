//=================================================================================================
//                                                        
//�@�@�@�G�N���X�v���O����[Enemy.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.16      
//                                                        
//=================================================================================================
#ifndef _CENEMY_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CENEMY_H_
#include "Scene.h"
#include "Scene3D.h"
#include "SceneModel.h"
#include "Player.h"
class CPlayer;
//=================================================================================================
//�@�@�@�\���̒�`                                         
//=================================================================================================
typedef enum
{
	ENEMY_TYPES_ZAKU,				//�U�O�G�^
	ENEMY_TYPES_BULIDING,			//�����G�^
}ENEMY_TYPES_ID;


typedef struct
{
	int status;					//���
	D3DXVECTOR3 vePos;			//���݂̍��W
	D3DXVECTOR3 veMov;			//���x�x�N�g��
	int nLife;					//����
	ENEMY_TYPES_ID EnemyType;	//�G�^
	CSceneModel* SceneModel;
	D3DXVECTOR3 veScale;
}ENEMY;

#define ENEMY_NUM (100)



//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CEnemy : public CScene
{
public:
	CEnemy(int nPriority);														//�G�R���X�g���N�^
	~CEnemy();														//�G�f�X�g���N�^
	bool Init(void);												//�G��������
	void Uninit(void);												//�G�I������
	void Update(void);												//�G�X�V����
	void Draw(void);												//�G�`�揈��
	static CEnemy * Create(void);									//�G�̃C���X�^���X����
	void Generate(ENEMY_TYPES_ID EnemyType, D3DXVECTOR3 vePosition,
		CSceneModel* pSceneModel, D3DXVECTOR3 veScale);				//�V�����G�𐶐�
	void Destory(int nNum);									//�G��p������
	void SetEnemyLife(int nNum, int nLife);					//�GHP��ݒ�
	void SetEnemyPosition(int nNum, D3DXVECTOR3 vePos);					//�GHP��ݒ�
	ENEMY GetEnemyManager(int nNum)							//�i���o�[�̓G�̏�������
	{
		return m_Enemy[nNum];
	};
	void SetPlayer(CPlayer* Player);
private:
	ENEMY m_Enemy[ENEMY_NUM];								//�G���̊Ǘ�
	D3DXVECTOR3 GetMovePattern(int nNum);					//�G�ړ��p�^�[��
	CPlayer* m_Player;
};

#endif