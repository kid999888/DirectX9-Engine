//=================================================================================================
//                                                        
//�@�@�@�}�b�v�N���X�v���O����[Map.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.23      
//                                                        
//=================================================================================================
#ifndef _CMAP_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CMAP_H_
#include"Scene.h"
#include"Scene2D.h"
#include"Enemy.h"
#include"Player.h"

//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CMap : public CScene
{
public:
	CMap(int nPriority) : CScene(nPriority)						//�}�b�v�R���X�g���N�^
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_bDraw = true;
	};
	~CMap();														//�}�b�v�f�X�g���N�^
	bool Init(void);												//�}�b�v��������
	void Uninit(void);												//�}�b�v�I������
	void Update(void);												//�}�b�v�X�V����
	void Draw(void);												//�}�b�v�`�揈��
	static CMap * Create(void);										//�}�b�v�̃C���X�^���X����
private:
	static CScene2D* m_pScene2DMap;									//�}�b�v���̊Ǘ�����A�h���X
	static CScene2D* m_pScene2DBlock;								//�}�b�v�I�u�W�F�N�g�Ǘ�����A�h���X
	static CEnemy* m_pEnemy;										//
};

#endif