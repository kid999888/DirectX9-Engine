//=================================================================================================
//                                                        
//�@�@�@�r���{�[�h�N���X�v���O����[SceneBillBoard.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.09      
//                                                        
//=================================================================================================
#ifndef _SCENEBILLBOARD_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENEBILLBOARD_H_
#include "Scene.h"

//=================================================================================================
//�@�@�@�r���{�[�h�N���X                                       
//=================================================================================================
class CSceneBillBoard : public CScene
{
public:
	CSceneBillBoard(int nPriority) : CScene(nPriority)
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(-90.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pTexture = nullptr;
		m_pVertexBuffer = NULL;
		m_pIndexBuffer = NULL;
	};														//�r���{�[�h�N���X�R���X�g���N�^
	~CSceneBillBoard();										//�r���{�[�h�N���X�f�X�g���N�^
	bool Init(void);										//�r���{�[�h�N���X��������
	void Uninit(void);										//�r���{�[�h�N���X�I������
	void Update(void);										//�r���{�[�h�N���X�X�V����
	void Draw(void);										//�r���{�[�h�N���X�`�揈��
	static CSceneBillBoard * Create(void);					//�r���{�[�h�̃C���X�^���X����

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//���_�o�b�t�@�Ǘ����郁����
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//�C���f�b�N�X�o�b�t�@�Ǘ����郁��
	D3DXMATRIX m_mtxTranspose;								//�r���[�s��̓]�u�s��
};

#endif