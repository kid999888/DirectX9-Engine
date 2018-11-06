//=================================================================================================
//                                                        
//�@�@�@�r���{�[�h�N���X�v���O����[SceneBillBoard.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.09      
//                                                        
//=================================================================================================
#ifndef _SCENEBILLBOARD_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENEBILLBOARD_H_
#include "Scene.h"
#include "Camera.h"

//=================================================================================================
//�@�@�@�r���{�[�h�N���X                                       
//=================================================================================================
class CSceneBillBoard : public CScene
{
public:
	CSceneBillBoard(CCamera* pCamera,int nPriority);							//�r���{�[�h�N���X�R���X�g���N�^
	~CSceneBillBoard();										//�r���{�[�h�N���X�f�X�g���N�^
	bool Init(void);										//�r���{�[�h�N���X��������
	void Uninit(void);										//�r���{�[�h�N���X�I������
	void Update(void);										//�r���{�[�h�N���X�X�V����
	void Draw(void);										//�r���{�[�h�N���X�`�揈��
	static CSceneBillBoard * Create(CCamera* pCamera);					//�r���{�[�h�̃C���X�^���X����

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//���_�o�b�t�@�Ǘ����郁����
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//�C���f�b�N�X�o�b�t�@�Ǘ����郁��
	D3DXMATRIX m_mtxTranspose;								//�r���[�s��̓]�u�s��
	CCamera* m_pCamera;										//
};

#endif