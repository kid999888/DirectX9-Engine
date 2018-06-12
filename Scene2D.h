//=================================================================================================
//                                                        
//�@�@�@2D�|���S���v���O����[Scene2D.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE2D_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENE2D_H_
#include"Scene.h"

//=================================================================================================
//�@�@�@2D�|���S���N���X                                       
//=================================================================================================
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority, int nNx, int nNy) : CScene(nPriority)
	{
		m_veScale = D3DXVECTOR3(0.25f, 0.25f, 1.0f);
		/*m_veScaleOffset = D3DXVECTOR2(0.0f, 0.0f);
		m_veRotationOffset = D3DXVECTOR2(0.0f, 0.0f);
		m_fRotationAngle = 0.0f;*/
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		
		m_npTLimitNum.x = nNx;
		m_npTLimitNum.y = nNy;
		m_pTexture = nullptr;
		m_pVertexBuffer = NULL;
	};												//2D�|���S���R���X�g���N�^
	~CScene2D();									//2D�|���S���f�X�g���N�^
	bool Init(void);								//2D�|���S����������
	void Uninit(void);								//2D�|���S���I������
	void Update(void);								//2D�|���S���X�V����
	void Draw(void);								//2D�|���S���`�揈��
	static CScene2D * Create(int nNx, int nNy);		//2D�|���S���̃C���X�^���X����

private:
	/*D3DXVECTOR2 m_veScaleOffset;
	D3DXVECTOR2 m_veRotationOffset;
	float m_fRotationAngle;*/
	Point2DI m_npTLimitNum;
	D3DXIMAGE_INFO m_D3DTextureInfo;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;						//���_�o�b�t�@�Ǘ����郁����
	void CreateVertexAffine(D3DCOLOR color, int tCx, int tCy);		//���_�o�b�t�@
};

#endif