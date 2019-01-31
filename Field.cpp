//=================================================================================================
//                                                        
//�@�@�@�t�B�[���h�N���X�v���O����[Scene3D.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include "Field.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>
#include <tchar.h>
#include "Renderer.h"
#include "input.h"

using namespace std;

//=================================================================================================
//		�}�N����`                                        
//=================================================================================================
//FVF�̐錾
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)    //3D�|���S���̒��_���
//�e�N�X�`���t�@�C���p�X
#define TEXTUREFILENAME000	        "Data\\Texture\\Ground.png"	
#define NOISEFILENAME000	        "Data\\Texture\\noise.png"	

//=================================================================================================
//�@�@�@�O���[�o���ϐ�                                    
//=================================================================================================

CField::CField(int nPriority, int nNumX, int nNumZ, float fScaleX, float fScaleZ, bool bNeat) : CScene(nPriority)
{
	m_veScale = D3DXVECTOR3(fScaleX, 1.0f, fScaleZ);
	m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pTexture = nullptr;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	m_fheightScale = 0.005f;
	m_nNumX = nNumX;
	m_nNumZ = nNumZ;
	m_bDraw = true;
	m_bNeat = bNeat;
};
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

	HRESULT hr[2];

	hr[0] = D3DXCreateTextureFromFile(
		pDevice,
		TEXTUREFILENAME000,
		&m_pTexture);

	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "�t�B�[���h�̃e�N�X�`�����ǂݍ��߂Ȃ��B", "�G���[", MB_OK);					//�e�N�X�`�����ǂݍ��߃G���[���b�Z�[�W
		return false;
	}

	float fSizeX = 1.0f, fSizeZ = 1.0f;
	fSizeX *= m_veScale.x;
	fSizeZ *= m_veScale.z;
	float fStartX = -fSizeX * (m_nNumX / 2), fStartY = 0.0f, fStartZ = fSizeZ * (m_nNumZ / 2);

	int nCx = m_nNumX + 1, nCy = m_nNumZ + 1;
	int nX, nZ;
	int nCount = 0;

	m_nFiledPosNumber = nCx * nCy;													//���_��
	m_nFiledIndexNumber = (nCx * 2 + 1) * (nCy - 1) + ((nCy - 2) * 1);				//�C���f�b�N�X��
	m_nFiledPrimitiveNumber = m_nFiledIndexNumber - 2;								//Primitive��

	//���_���Ǘ��������̃C���X�^���X����
	m_pvMeshFiledPos = new VERTEX_3D[m_nFiledPosNumber];

	//���x�̏��Ǘ��������i���j
	vector<vector<float>> vaFieldHeight(nCx);
	for (nCount = 0; nCount < nCx; nCount++)
	{
		vaFieldHeight[nCount].resize(nCy);
	}
	//���_���Ǘ�������������
	nCount = 0;
	for (nZ = 0;nZ < nCy;nZ++)
	{
		for (nX = 0;nX < nCx;nX++)
		{
			vaFieldHeight[nX][nZ] = 0.0f;
		}
	}





	//���x�}��ǂݕ���
	ifstream InFile;
	InFile.open(NOISEFILENAME000, ios::binary);				//��i�̕����Ƀf�[�^��ǂݍ���

	InFile.seekg(0, ios::end);								//�|�C���^�Ƀt�@�C�����[���ړ�
	vector<BYTE>vaInData(InFile.tellg());					//<BYTE>�^��Vector�z��inData��錾
	int nSize = vaInData.size();
	InFile.seekg(ios::beg);									//�|�C���^�Ƀt�@�C����[���ړ�
	InFile.read((char*)&vaInData[0], vaInData.size());		//�t�@�C����ǂݍ���
	InFile.close();											//�t�@�C�������

	//���x�t�@�C�������
	//ofstream OutFile;
	//OutFile.open("Data\\HeightMessage.txt", ios::out);
	///*OutFile.write("0.0", 3);*/

	//for (int i = 0;i < (int)vaInData.size(); i++)
	//{
	//	OutFile << (vaInData[i] * 0.005f);
	//	OutFile.write("\n", 2);
	//}

	//OutFile.close();


	//�t�@�C���̍��x���ɍ��x�̃������ɓ����
	nCount = 0;
	for (nZ = 0;nZ < nCy;nZ++)
	{
		for (nX = 0;nX < nCx;nX++)
		{
			vaFieldHeight[nX][nZ] = (vaInData[nCount] * 0.005f);
			nCount++;
		}
	}
	//Vector�z��inData�̏���
	vaInData.clear();
	if (m_bNeat)
	{
		nCount = 0;
		for (nZ = 0;nZ < nCy;nZ++)
		{
			for (nX = 0;nX < nCx;nX++)
			{
				m_pvMeshFiledPos[nCount] = {
					D3DXVECTOR3(fStartX + (fSizeX * nX), fStartY, fStartZ - (fSizeZ * nZ)), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2((fSizeX * nX),(fSizeZ * nZ))
				};
				m_pvMeshFiledPos[nCount].pos.y = 0.0f;

				nCount++;
			}
		}
	}
	else
	{
		nCount = 0;
		for (nZ = 0;nZ < nCy;nZ++)
		{
			for (nX = 0;nX < nCx;nX++)
			{
				m_pvMeshFiledPos[nCount] = {
					D3DXVECTOR3(fStartX + (fSizeX * nX), fStartY, fStartZ - (fSizeZ * nZ)), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2((fSizeX * nX),(fSizeZ * nZ))
				};
				m_pvMeshFiledPos[nCount].pos.y = vaFieldHeight[nX][nZ];

				nCount++;
			}
		}
	}


	//Vector�z��vaFieldHeight�̏���
	vaFieldHeight.clear();


	//�@���̉��ʂƂ��Ď����v�Z
	for (nZ = 1;nZ < (nCy - 1);nZ++)
	{
		for (nX = 1;nX < (nCx - 1);nX++)
		{
			D3DXVECTOR3 vx, nx, vz, nz, n;
			vx = m_pvMeshFiledPos[nZ * nCx + (nX + 1)].pos - m_pvMeshFiledPos[nZ * nCx + (nX - 1)].pos;
			nx.x = -vx.y;
			nx.y = vx.x;
			nx.z = 0.0f;

			vz = m_pvMeshFiledPos[nX * nCy + (nZ + 1)].pos - m_pvMeshFiledPos[nX * nCy + (nZ - 1)].pos;
			nz.x = 0.0f;
			nz.y = vz.z;
			nz.z = vz.y;

			n = nx + nz;

			D3DXVec3Normalize(&n, &n);
			m_pvMeshFiledPos[nZ * nCx + (nX + 1)].fs = n;
		}
	}

	/*for (nZ = 1;nZ < (nCy - 1);nZ++)
	{
		for (nX = 1;nX < (nCx - 1);nX++)
		{
			D3DXVECTOR3 vx, vx0, nx, nx0, vz, vz0, nz, nz0, n;
			vx = m_pvMeshFiledPos[nZ * nCx + (nX + 1)].pos - m_pvMeshFiledPos[nZ * nCx + (nX - 1)].pos;
			nx.x = -vx.y;
			nx.y = vx.x;
			nx.z = 0.0f;

			vx0 = m_pvMeshFiledPos[nZ * nCx + (nX - 1)].pos - m_pvMeshFiledPos[nZ * nCx + (nX + 1)].pos;
			nx0.x = -vx.y;
			nx0.y = -vx.x;
			nx0.z = 0.0f;

			vz = m_pvMeshFiledPos[nX * nCy + (nZ + 1)].pos - m_pvMeshFiledPos[nX * nCy + (nZ - 1)].pos;
			nz.x = 0.0f;
			nz.y = vz.z;
			nz.z = vz.y;

			vz0 = m_pvMeshFiledPos[nX * nCy + (nZ - 1)].pos - m_pvMeshFiledPos[nX * nCy + (nZ + 1)].pos;
			nz0.x = 0.0f;
			nz0.y = -vz.z;
			nz0.z = vz.y;

			n = nx + nz + nx0 + nz0;

			D3DXVec3Normalize(&n, &n);
			m_pvMeshFiledPos[nZ * nCx + (nX + 1)].fs = n;
		}
	}*/

	//2X2�̃C���f�b�N�X
	/*static WORD index[] = {
	3,0,4,1,5,2,2,6,6,3,7,4,8,5
	};*/

	int nS = 0, nF = 0, nC = 2 * nCx, nD = 2 * nCx + 1;
	static WORD *index;
	index = new WORD[m_nFiledIndexNumber];
	for (nCount = 0;nCount < m_nFiledIndexNumber;nCount++)
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
		sizeof(VERTEX_3D) * m_nFiledPosNumber,		//���_���̈�m��
		D3DUSAGE_WRITEONLY,							//�g�p�p�r(��������ł���)
		FVF_VERTEX_3D,								//FVF�A�O�ł����v
		D3DPOOL_MANAGED,							//���_�o�b�t�@�̊Ǘ����@(Device�ɊǗ�����)
		&m_pVertexBuffer,							//�Ǘ��҂̃������ꏊ
		NULL);

	//�C���f�b�N�X�o�b�t�@�����
	hr[1] = pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nFiledIndexNumber,			//���[���h�s����̈�m��
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
	memcpy(&pV[0], &m_pvMeshFiledPos[0], sizeof(VERTEX_3D) * m_nFiledPosNumber);



	//�A���ڏ���

	m_pVertexBuffer->Unlock();


	LPWORD pIndex;
	m_pIndexBuffer->Lock(0, 0,						//���_�o�b�t�@���b�N(�n�܂�A�̈�Avoid�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		(void**)&pIndex,							//���_�o�b�t�@���b�N(void�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		D3DLOCK_DISCARD);

	//�C���f�b�N�X��pIndex�ɏ��������
	//�@���܂ł̔z����g�p�cPV��V�̓��e�R�s�[����B�imemcpy�g�p���āj
	memcpy(&pIndex[0], &index[0], sizeof(WORD) * m_nFiledIndexNumber);

	//���_���Ǘ��������i���j�̏���
	SAFE_DELETE_ARRAY(index);

	//�A���ڏ���^

	m_pIndexBuffer->Unlock();

	//�}�e���A���̃C���X�^���X����&�ݒ�
	m_Material = new CMaterial();
	/*m_Material->SetAmbient(0.9f, 0.1f, 0.1f, 1.0f);*/

	return true;
}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�I������                                     
//=================================================================================================
void CField::Uninit(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_Material);
	//���_���Ǘ��������̏���
	SAFE_DELETE_ARRAY(m_pvMeshFiledPos);

}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�X�V����                                     
//=================================================================================================
void CField::Update(void)
{
	//m_veRotation.x += 0.0f;
	//m_veRotation.y += 0.01f;
	//m_veRotation.z += 0.0f;
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
	D3DXMatrixRotationX(&m_mtxWorldRX, D3DXToRadian(m_veRotation.x));
	D3DXMatrixRotationY(&m_mtxWorldRY, D3DXToRadian(m_veRotation.y));
	D3DXMatrixRotationZ(&m_mtxWorldRZ, D3DXToRadian(m_veRotation.z));

	//��]�s�������	
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldRX, &m_mtxWorldRY);
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldR, &m_mtxWorldRZ);

	//���s�ړ��s��̍���
	D3DXMatrixTranslation(&m_mtxWorldT, m_vePosition.x, m_vePosition.y, m_vePosition.z);

	//�s�񍇐� 	
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

	//�}�e���A���̍X�V
	m_Material->Update();

	//�e�N�X�`���\��t����
	pDevice->SetTexture(0, m_pTexture);

	//�����`��ON
	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//�o�b�t�@�g����
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,			//Primitive�`��^�C�v
		0,
		0,								//�C���f�b�N�X�̍ŏ��l	
		m_nFiledPosNumber,				//���_�̐�
		0,
		m_nFiledPrimitiveNumber);		//�`�悷��̃|���S���i�O�p�`�j�̐�

	//�����`��OFF
	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�̃C���X�^���X����                                   
//=================================================================================================
CField * CField::Create(int nNumX, int nNumZ, float fScaleX, float fScaleZ, bool bNeat)
{
	CField *Field = new CField(2, nNumX, nNumZ, fScaleX, fScaleZ, bNeat);
	Field->Init();
	return Field;
}
