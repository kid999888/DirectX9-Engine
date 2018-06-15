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
		m_fMoveSpeed = 0.2f;
		m_pTexture = nullptr;
	};												//�v���[���[�R���X�g���N�^
	~CPlayer();										//�v���[���[�f�X�g���N�^
	bool Init(void);								//�v���[���[��������
	void Uninit(void);								//�v���[���[�I������
	void Update(void);								//�v���[���[�X�V����
	void Draw(void);								//�v���[���[�`�揈��
	static CPlayer * Create(D3DXVECTOR3 vePosition);					//�v���[���[�̃C���X�^���X����

private:
	CSceneModel * m_pPlayer;
	CCamera *m_Camera;
	float m_fMoveSpeed;
};

#endif