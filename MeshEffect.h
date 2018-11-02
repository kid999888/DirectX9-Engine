//=================================================================================================
//                                                        
//�@�@�@�|���R�����b�V���G�t�F�N�g�v���O����[MeshEffect.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.10.31      
//                                                        
//=================================================================================================
#pragma once
#include "Scene.h"
class CMeshEffect : public CScene
{
public:
	CMeshEffect();
	~CMeshEffect();
	bool Init(void);										//���b�V���G�t�F�N�g��������
	void Uninit(void);										//���b�V���G�t�F�N�g�I������
	void Update(void);										//���b�V���G�t�F�N�g�X�V����
	void Draw(void);										//���b�V���G�t�F�N�g�`�揈��
	static CMeshEffect * Create(void);						//���b�V���G�t�F�N�g�̃C���X�^���X����
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//���_�o�b�t�@�Ǘ����郁����
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//�C���f�b�N�X�o�b�t�@�Ǘ����郁��
};

