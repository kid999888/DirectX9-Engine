//=================================================================================================
//                                                        
//�@�@�@3D���f���N���X�v���O����[SceneModel.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"SceneModel.h"
#include"main.h"
#include"Material.h"
#include"Renderer.h"

//=================================================================================================
//		�}�N����`                                        
//=================================================================================================
//���f���t�@�C���p�X
#define MODELFILENAME000	        "Data\\Model\\cart.x"	

//=================================================================================================
//�@�@�@�O���[�o���ϐ�                                    
//=================================================================================================
static CMaterial *g_Material;

//=================================================================================================
//�@�@�@3D���f���N���X�f�X�g���N�^                                     
//=================================================================================================
CSceneModel::~CSceneModel()
{

}

//=================================================================================================
//�@�@�@3D���f���N���X��������                                     
//=================================================================================================
bool CSceneModel::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	//�����o�[�ϐ������� 
	
	m_pMesh = NULL;
	m_nMaterialNum = 0;
	m_pMaterial = NULL;
	m_nMaterialPointNum = 0;

	LPD3DXBUFFER pAdjacencyBuffer;
	HRESULT hr;

	hr = D3DXLoadMeshFromX(MODELFILENAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_pMaterial,
		NULL,
		&m_nMaterialNum,
		&m_pMesh);



	if (FAILED(hr))
	{
		MessageBox(NULL, "3D���b�V����ǂݍ��߂Ȃ�", "�G���[", MB_OK);							//���_�o�b�t�@�G���[���b�Z�[�W
		return false;
	}

	if (pDevice == NULL)
	{
		return false;
	}


	//X���f���̃}�e���A������ǂݍ���
	LPD3DXMATERIAL pMaterial = (LPD3DXMATERIAL)m_pMaterial->GetBufferPointer();
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nMaterialNum];

	int nCount = 0;
	for (nCount = 0; nCount < m_nMaterialNum;nCount++)
	{
		pDevice->SetMaterial(&pMaterial->MatD3D);
		hr = D3DXCreateTextureFromFile(
			pDevice,
			pMaterial->pTextureFilename,
			&m_pTexture[nCount]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "3D���f�����O�e�N�X�`�����ǂݍ��߂Ȃ��B", "�G���[", MB_OK);					//�e�N�X�`�����ǂݍ��߃G���[���b�Z�[�W
			return false;
		}
		pMaterial++;
	}
	m_nMaterialPointNum = m_nMaterialPointNum + m_nMaterialNum;

	LPD3DXMESH pTempMesh;

	hr = m_pMesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pAdjacencyBuffer->GetBufferPointer(),
		NULL, NULL, NULL);

	SAFE_RELEASE(pAdjacencyBuffer);

	LPD3DVERTEXELEMENT9 pElements = NULL;
	m_pMesh->GetDeclaration(pElements);
	hr = m_pMesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,
		pElements,
		pDevice,
		&pTempMesh);

	SAFE_RELEASE(m_pMesh);
	m_pMesh = pTempMesh;

	if (FAILED(hr))
	{
		MessageBox(NULL, "���b�V���œK���ł��Ȃ�", "�G���[", MB_OK);			//���b�V���œK���G���[���b�Z�[�W
		return false;
	}

	//�C���X�^���X����
	g_Material = new CMaterial();

	return true;
}

//=================================================================================================
//�@�@�@3D���f���N���X�I������                                     
//=================================================================================================
void CSceneModel::Uninit(void)
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMaterial);
	SAFE_DELETE_ARRAY(m_pTexture);
	delete g_Material;
}

//=================================================================================================
//�@�@�@3D���f���N���X�X�V����                                     
//=================================================================================================
void CSceneModel::Update(void)
{
	g_Material->Update();
	//m_fRotX += 0.0f;
	m_fRotY -= 0.01f;
	//m_fRotZ += 0.0f;
}

//=================================================================================================
//�@�@�@3D���f���N���X�`�揈��                                     
//=================================================================================================
void CSceneModel::Draw(void)
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

	//���[���h�s��
	D3DXMATRIX Vec;
	D3DXMatrixTranslation(&Vec, v3In.x, v3In.y, v3In.z);
	D3DXMatrixMultiply(&Vec, &Vec, &m_mtxWorld);

	m_XmodelAt = D3DXVECTOR3(Vec._41, Vec._42, Vec._43);

	//���[���h�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�}�e���A���ƌ��̐ݒ�
	//MaterialSet(FCOLOR{ 0.8f,0.8f,0.8f,1.0f }, FCOLOR{ 0.8f,0.8f,0.8f,1.0f });
	//LightSet(D3DXVECTOR3(1.0f, -1.0f, 0.0f), FCOLOR{ 0.8f,0.8f,0.8f,1.0f }, FCOLOR{ 0.8f,0.8f,0.8f,1.0f }, FCOLOR{ 0.3f,0.3f,0.3f,1.0f });

	//�`��
	int nCount = 0;
	for (nCount = 0;nCount < m_nMaterialNum;nCount++)
	{
		//�e�N�X�`���\��t����
		pDevice->SetTexture(0, m_pTexture[nCount]);
		//�}�e���A���ݒ�i�e�N�X�`���܂ށj
		m_pMesh->DrawSubset(nCount);
	}
	
}

//=================================================================================================
//�@�@�@3D���f���N���X�̃C���X�^���X����                                    
//=================================================================================================
CSceneModel * CSceneModel::Create(void)
{
	CSceneModel *SceneModel = new CSceneModel(1);
	SceneModel->Init();
	return SceneModel;
}
