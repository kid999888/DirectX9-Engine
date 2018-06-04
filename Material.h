//=================================================================================================
//                                                        
//�@�@�@�}�e���A���N���X�v���O����[Material.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _MATERIAL_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _MATERIAL_H_
#include"main.h"

//=================================================================================================
//�@�@�@3D�|���S���N���X                                       
//=================================================================================================
class CMaterial
{
public:
	CMaterial();												//�}�e���A���N���X�R���X�g���N�^
	~CMaterial();												//�}�e���A���N���X�f�X�g���N�^
	void Update(void);											//�}�e���A���N���X�X�V����
	void SetAmbient(float r, float g, float b, float a);		//�}�e���A�������i�e�Ɍ����F�j�F�̐ݒ�
	void SetDiffuse(float r, float g, float b, float a);		//�}�e���A���g�U���i���̃��C���F�j�F�̐ݒ�
	void SetSpecular(float r, float g, float b, float a);		//�}�e���A�����ˌ��̐ݒ�
	void MatCopy(D3DMATERIAL9 MatCpy);							//�}�e���A�����ˌ��̐ݒ�

private:
	D3DMATERIAL9 m_Mat;											//DirectX�̃}�e���A�����
};
#endif