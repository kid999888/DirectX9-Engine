//=================================================================================================
//                                                        
//�@�@�@�}�b�v�N���X�v���O����[Map.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.23      
//                                                        
//=================================================================================================
#ifndef _CMAP_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CMAP_H_
#include "Scene.h"
#include "Scene2D.h"
#include "Enemy.h"
#include "Player.h"
class CEnemy;

//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CMap : public CScene
{
public:
	CMap(CEnemy* pEnemy,int nPriority);											//�}�b�v�R���X�g���N�^
	~CMap();														//�}�b�v�f�X�g���N�^
	bool Init(void);												//�}�b�v��������
	void Uninit(void);												//�}�b�v�I������
	void Update(void);												//�}�b�v�X�V����
	void Draw(void);												//�}�b�v�`�揈��
	static CMap * Create(CEnemy* pEnemy);										//�}�b�v�̃C���X�^���X����
private:
	CScene2D* m_pScene2DMap;									//�}�b�v���̊Ǘ�����A�h���X
	CScene2D* m_pScene2DBlock;								//�}�b�v�I�u�W�F�N�g�Ǘ�����A�h���X
	CEnemy* m_pEnemy;										//
};

#endif