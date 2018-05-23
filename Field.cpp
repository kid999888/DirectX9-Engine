//=================================================================================================
//                                                        
//�@�@�@3D�L���[�u�N���X�v���O����[Scene3D.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"Field.h"
#include"main.h"
#include<d3d9.h>
#include<d3dx9.h>
#include"Renderer.h"

//=================================================================================================
//		�}�N����`                                        
//=================================================================================================
//FVF�̐錾
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)    //3D�|���S���̒��_���
//�e�N�X�`���t�@�C���p�X
#define TEXTUREFILENAME000	        "Data\\Texture\\Ground.png"	

#define MESH_FILEDX (4)
#define MESH_FILEDY (4)
//=================================================================================================
//�@�@�@�O���[�o���ϐ�                                    
//=================================================================================================

//=================================================================================================
//�@�@�@�\���̒�`                                         
//=================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;            //XYZW���W
	D3DXVECTOR3 fs;				//�@��
	D3DCOLOR color;             //�F���
	D3DXVECTOR2 texcoord;       //�e�N�X�`�����W
}VERTEX_3D;

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�f�X�g���N�^                                     
//=================================================================================================
CField::~CField()
{
}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X��������                                     
//=================================================================================================
bool CField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	m_pTexture = new LPDIRECT3DTEXTURE9[1];

	HRESULT hr[2];


	hr[0] = D3DXCreateTextureFromFile(
		pDevice,
		TEXTUREFILENAME000,
		m_pTexture);

	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "�t�B�[���h�̃e�N�X�`�����ǂݍ��߂Ȃ��B", "�G���[", MB_OK);					//�e�N�X�`�����ǂݍ��߃G���[���b�Z�[�W
		return false;
	}



	float fSizeX = 1.0f, fSizeZ = 1.0f;
	float fStartX = -fSizeX * (MESH_FILEDX / 2), fStartY = 0.0f, fStartZ = fSizeZ * (MESH_FILEDY / 2);

	int nCx = MESH_FILEDX + 1, nCy = MESH_FILEDY + 1;
	int nX, nZ;
	int nCount = 0;

	m_FiledPosNumber = nCx * nCy;														//���_��
	m_FiledIndexNumber = (nCx * 2 + 1) * (nCy - 1) + ((nCy - 2) * 1);										//�C���f�b�N�X��
	m_FiledPrimitiveNumber = m_FiledIndexNumber - 2;								//Primitive��


	VERTEX_3D vMeshFiledPos[2048] = {};

	for (nZ = 0;nZ < nCy;nZ++)
	{
		for (nX = 0;nX < nCx;nX++)
		{
			vMeshFiledPos[nCount] = {
				D3DXVECTOR3(fStartX + (fSizeX * nX), fStartY, fStartZ - (fSizeZ * nZ)), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2((fSizeX * nX),(fSizeZ * nZ))
			};
			nCount++;
		}
	}

	//2X2�̃C���f�b�N�X
	/*static WORD index[] = {
	3,0,4,1,5,2,2,6,6,3,7,4,8,5
	};*/

	int nS = 0, nF = 0, nC = 2 * nCx, nD = 2 * nCx + 1;
	static WORD index[1024];
	for (nCount = 0;nCount < m_FiledIndexNumber;nCount++)
	{
		//�C���f�b�N�X�����Ԃ̏k��
		if (nCount == nC)
		{
			index[nCount] = index[nCount - 1];
			nC += (2 * (nCx + 1));
			continue;
		}
		//�C���f�b�N�X������
		if (nCount % 2 == 0)
		{
			index[nCount] = nCx + nS;
			nS++;
		}
		//�C���f�b�N�X��Ԃ̏k��
		if (nCount == nD)
		{
			index[nCount] = nCx + nS;
			nD += (2 * (nCx + 1));
			continue;
		}
		//�C���f�b�N�X���
		if (nCount % 2 == 1)
		{
			index[nCount] = nF;
			if (nCount == ((nC * nCx) - 1))
			{
				index[nCount] = nF;
				continue;
			}
			else
			{
				nF++;
			}
		}
	}

	//���_Vertex�o�b�t�@�����
	hr[0] = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_FiledPosNumber,						//���_���̈�m��
		D3DUSAGE_WRITEONLY,							//�g�p�p�r(��������ł���)
		FVF_VERTEX_3D,								//FVF�A�O�ł����v
		D3DPOOL_MANAGED,							//���_�o�b�t�@�̊Ǘ����@(Device�ɊǗ�����)
		&m_pVertexBuffer,							//�Ǘ��҂̃������ꏊ
		NULL);

	//�C���f�b�N�X�o�b�t�@�����
	hr[1] = pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_FiledIndexNumber,							//���[���h�s����̈�m��
		D3DUSAGE_WRITEONLY,							//�g�p�p�r(��������ł���)
		D3DFMT_INDEX16,								//FMT,DWORD�̏ꍇ��D3DFMT_INDEX32
		D3DPOOL_MANAGED,							//���_�o�b�t�@�̊Ǘ����@(Device�ɊǗ�����)
		&m_pIndexBuffer,							//�C���f�b�N�X�o�b�t�@�Ǘ����郁����
		NULL);

	//���_�o�b�t�@NULL�`�F�b�N
	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "���b�V���t�B-���h���_�o�b�t�@�����Ȃ�", "�G���[", MB_OK);							//���_�o�b�t�@�G���[���b�Z�[�W
		return false;
	}

	//�C���f�b�N�X�o�b�t�@NULL�`�F�b�N
	if (FAILED(hr[1]))
	{
		MessageBox(NULL, "���b�V���t�B-���h�C���f�b�N�X�o�b�t�@�����Ȃ�", "�G���[", MB_OK);							//���_�o�b�t�@�G���[���b�Z�[�W
		return false;
	}

	VERTEX_3D* pV;
	m_pVertexBuffer->Lock(0, 0,						//���_�o�b�t�@���b�N(�n�܂�A�̈�Avoid�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		(void**)&pV,								//���_�o�b�t�@���b�N(void�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		D3DLOCK_DISCARD);

	//���_����pV�ɏ��������
	//�@���܂ł̔z����g�p�cPV��V�̓��e�R�s�[����B�imemcpy�g�p���āj
	memcpy(&pV[0], &vMeshFiledPos[0], sizeof(VERTEX_3D) * m_FiledPosNumber);

	//�A���ڏ���

	m_pVertexBuffer->Unlock();


	LPWORD pIndex;
	m_pIndexBuffer->Lock(0, 0,						//���_�o�b�t�@���b�N(�n�܂�A�̈�Avoid�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		(void**)&pIndex,							//���_�o�b�t�@���b�N(void�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		D3DLOCK_DISCARD);

	//�C���f�b�N�X��pIndex�ɏ��������
	//�@���܂ł̔z����g�p�cPV��V�̓��e�R�s�[����B�imemcpy�g�p���āj
	memcpy(&pIndex[0], &index[0], sizeof(WORD) * m_FiledIndexNumber);
	//�A���ڏ���^

	m_pIndexBuffer->Unlock();


	return true;
}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�I������                                     
//=================================================================================================
void CField::Uninit(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_DELETE_ARRAY(m_pTexture);

}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�X�V����                                     
//=================================================================================================
void CField::Update(void)
{
	/*g_fRotX[nCount] += rx;
	g_fRotY[nCount] += ry;
	g_fRotZ[nCount] += rz;*/
}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�`�揈��                                     
//=================================================================================================
void CField::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	//�g��k���s������
	D3DXMatrixScaling(&m_mtxWorldS, 1.0f, 1.0f, 1.0f);

	//��]�s������
	D3DXMatrixRotationX(&m_mtxWorldRX, m_fRotX);
	D3DXMatrixRotationY(&m_mtxWorldRY, m_fRotY);
	D3DXMatrixRotationZ(&m_mtxWorldRZ, m_fRotZ);

	//��]�s�������	
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldRX, &m_mtxWorldRY);
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldR, &m_mtxWorldRZ);

	//���s�ړ��s��̍���
	D3DXMatrixTranslation(&m_mtxWorldT, m_vePosition.x, m_vePosition.y, m_vePosition.z);

	//�s��	
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorldR);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);

	pDevice->SetStreamSource(0,
		m_pVertexBuffer, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_pIndexBuffer);


	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���C�gON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//���[���h�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�T���v���[�X�e�[�g�̐ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);			//�e�N�X�`��U���W�傫�ȏꍇ��,WRAP�͉摜�𑝂���B

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);			//�e�N�X�`��V���W�傫�ȏꍇ��,WRAP�͉摜�𑝂���B

	//�e�N�X�`���\��t����
	pDevice->SetTexture(0, *m_pTexture);


	//�o�b�t�@�g����
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,			//Primitive�`��^�C�v
		0,
		0,								//�C���f�b�N�X�̍ŏ��l	
		m_FiledPosNumber,				//���_�̐�
		0,
		m_FiledPrimitiveNumber);		//�`�悷��̃|���S���i�O�p�`�j�̐�
}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�̃C���X�^���X����                                   
//=================================================================================================
CField * CField::Create(void)
{
	CField *Field = new CField(2);
	Field->Init();
	return Field;
}