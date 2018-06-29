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
	CBullet(int nPriority) : CScene(nPriority)						//�o���b�g�R���X�g���N�^
	{
		m_veScale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_veMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_nLife = 0;
	};												
	~CBullet();														//�o���b�g�f�X�g���N�^
	bool Init(void);												//�o���b�g��������
	void Uninit(void);												//�o���b�g�I������
	void Update(void);												//�o���b�g�X�V����
	void Draw(void);												//�o���b�g�`�揈��
	static CBullet * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 At);		//�o���b�g�̃C���X�^���X����
	static int GeTBullerLife(void) { return m_nLife; };				//�o���b�g�̎��������炤

private:
	CSceneModel * m_pBullet;										//�o���b�g���f�����O�Ǘ�����A�h���X
	static D3DXVECTOR3 m_vePosition;								//�o���b�g�̈ʒu�𐺖�����
	static D3DXVECTOR3 m_veMove;									//�o���b�g�̉����x�𐺖�����
	static int m_nLife;												//�o���b�g�̎���

};

#endif