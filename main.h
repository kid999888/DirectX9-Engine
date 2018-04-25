//=================================================================================================
//                                                        
//�@�@�@�Q�[���t���[�����[�N���C���v���O����[main.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.13      
//                                                        
//=================================================================================================
#ifndef _MAIN_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _MAIN_H_

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include<d3d9.h>
#include<d3dx9.h>
#include"Renderer.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

//=================================================================================================
//�@�@�@�}�N����`                                        
//=================================================================================================
#define SAFE_RELEASE(p)			if(p){ p->Release(); p=NULL; }					//���S�����[�X�}�N��
#define SAFE_DELETE(p)			if(p){ delete      (p); (p) = nullptr; }		//���S�����}�N��
#define SAFE_DELETE_ARRAY(p)	if(p){ delete[]    (p); (p) = nullptr; }		//���S�z������}�N��
#define SCREEN_WIDTH		(800)							//�X�N���[���̕�
#define SCREEN_HEIGHT		(600)							//�X�N���[���̍���
//�f�t�H���g�x�N�g��
static const D3DXVECTOR4 v4One(1, 1, 1, 1);
static const D3DXVECTOR3 v3One(1, 1, 1);
static const D3DXVECTOR2 v2One(1, 1);
static const D3DXVECTOR3 v3Right(1, 0, 0);
static const D3DXVECTOR3 v3Down(0, -1, 0);
static const D3DXVECTOR3 v3In(0, 0, 1);
static const D3DXVECTOR3 v3Left(-1, 0, 0);
static const D3DXVECTOR3 v3Up(0, 1, 0);
static const D3DXVECTOR3 v3Out(0, 0, -1);
static const D3DXVECTOR2 v2Right(1, 0);
static const D3DXVECTOR2 v2Down(0, 1);
static const D3DXVECTOR2 v2Left(-1, 0);
static const D3DXVECTOR2 v2Up(0, -1);
static const D3DXVECTOR4 v4Zero(0, 0, 0, 0);
static const D3DXVECTOR3 v3Zero(0, 0, 0);
static const D3DXVECTOR2 v2Zero(0, 0);

#endif		//_MAIN_H_