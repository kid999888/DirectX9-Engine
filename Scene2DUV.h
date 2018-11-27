//=================================================================================================
//                                                        
//�@�@�@2D�|���S���v���O����[Scene2D.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE2DUV_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENE2DUV_H_
#include "Scene.h"
#include<string>

//=================================================================================================
//�@�@�@2D�|���S���N���X                                       
//=================================================================================================
class CScene2DUV : public CScene
{
public:
	CScene2DUV(int nPriority, std::string stFileName);																	//2D�|���S���R���X�g���N�^
	~CScene2DUV();															//2D�|���S���f�X�g���N�^
	bool Init(void);														//2D�|���S����������
	void Uninit(void);														//2D�|���S���I������
	void Update(void);														//2D�|���S���X�V����
	void Draw(void);														//2D�|���S���`�揈��
	void DrawWithOutTexture(int nAlpha);											//2D�|���S���`�揈��(�e�N�X�`���ݒ�Ȃ�)
	static CScene2DUV * Create(int nPriority, std::string stFileName);		//2D�|���S���̃C���X�^���X����
	void SetTextureUV(float U0, float V0, float U1, float V1);				//2D�|���S���̃e�N�X�`��UV�̐ݒ�
	float GetU0(void) { return m_fU0; };
	float GetV0(void) { return m_fV0; };
	float GetU1(void) { return m_fU1; };
	float GetV1(void) { return m_fV1; };
	int Get2DObjectHeight(void)												//�e�N�X�`���̍��x���擾
	{
		return m_D3DTextureInfo.Height;
	};
	int Get2DObjectWidth(void)												//�e�N�X�`���̕����擾
	{
		return m_D3DTextureInfo.Width;
	};

private:
	int m_nAlpha;															//
	D3DXIMAGE_INFO m_D3DTextureInfo;										//�e�N�X�`�����̊Ǘ�������
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;								//���_�o�b�t�@�Ǘ����郁����
	void CreateVertexAffine(D3DCOLOR color);				//���_�o�b�t�@����
	std::string stFileNameModel;											//�t�@�C���p�X�̊Ǘ�������
	float m_fU0;
	float m_fV0;
	float m_fU1;
	float m_fV1;
};

#endif