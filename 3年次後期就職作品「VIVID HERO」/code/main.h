//��-------------------------------------------------------------------------��
//
//	File:�^���ÃE�B���h�E[main.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#define DIRECTINPUT_VERSION (0x0800)	//�G���[����̂���
#define _CRT_SECURE_NO_WARNINGS 1

//�N���G�C�g�e�N�X�`���̒����̂�����悤�ɂ���}�N����`
//�`�����F�N���e�N�̑O�Ƀu���|�C���g��u���Ď��s���̂�����?
#define D3D_DEBUG_INFO

//2�d�C���N���[�h�h�~
#ifndef _MAIN_H_
#define _MAIN_H_

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)	{if(p){delete (p);(p) = NULL;}}
#endif

#ifndef SAFE_DELETE_ARRY
#define SAFE_DELETE_ARRY(p)	{if(p){delete[] (p);(p) = NULL;}}
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)	{if(p){(p)->Release();(p) = NULL;}}
#endif

//===================
//���������[�N�̃t�@�C��
//===================
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include"dinput.h"
#include<windows.h>
#include "d3dx9.h"		//�`�揈���ɕK�v
#include "xaudio2.h"	//XAudio2�֘A�̃t�@�C�����T�E���h�Đ��ɕK�v
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")			//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		//��L�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g�ɕK�v
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//��������Ă�������ADXTrace(�H�H�H�H�H);�������Ɖ����̃_�C�A���O���o��
#pragma comment(lib,"dxerr.lib")
#include"dxerr.h"
//#pragma once
//�܂���������
//��-----------------------------------��
//�������������[�N�̏���
//��-----------------------------------��
#ifndef _DEBUG_
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

//��-----------------------------------��
//�}�N����`
//��-----------------------------------��
#define SCREEN_WIDTH (1280)				//��ʂ̕�
#define SCREEN_HEIGHT (720)				//��ʂ̍���

//��-----------------------------------��
//2D�̏���
//��-----------------------------------��
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
typedef struct
{
	D3DXVECTOR3		pos;		//���_���W
	float			rhw;		//�e�N�X�e���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR		col;		//���_�J���[
	D3DXVECTOR2		tex;		//�e�N�X�`�����W
}VERTEX_2D;



//��-----------------------------------��
//3D�����̒ǉ�
//��-----------------------------------��
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

typedef struct
{
	D3DXVECTOR3		pos;
	D3DXVECTOR3		nor;
	D3DCOLOR		col;
	D3DXVECTOR2		tex;
}VERTEX_3D;

//��-----------------------------------��
//���ꂼ��̕��̂̃^�C�v�ݒ�
//��-----------------------------------��
enum CLASS_TYPE
{
	CTYPE_NONE =0,
	CTYPE_SCENE,
	CTYPE_SCENE2D,
	CTYPE_SCENE3D,
	CTYPE_SCENEX,
	CTYPE_SCENEBILLBOARD,
	CTYPE_MESHSKY,
	CTYPE_BULLET,
	CTYPE_EXPLOSION,
	CTYPE_SCORE,
	CTYPE_TIMER,
	CTYPE_FADE,
	CTYPE_SCENEMODELMOTION,
	CTYPE_SCENEMODELPARTS,
	CTYPE_SCENESTENCILSHADOW,
	CTYPE_SCENEMESHORBIT,
	CTYPE_MESHBESISCLASS,
	CTYPE_PARTICLESYSTEM,
	CTYPE_DEGENERACYPOLYGON,
	CTYPE_DEGENERACYSTAR,

	CTYPE_PLAYERMODEL,
	CTYPE_BULLET000,
	CTYPE_BULLETHOMING,

	CTYPE_ENEMY,

	CTYPE_ENEMYBULLET000,
	CTYPE_ENEMYBULLET001,
	
	CTYPE_GAMESTART,

	CTYPE_MAX
};

//��-----------------------------------��
//�f�o�C�X���擾����֐�
//��-----------------------------------��
LPDIRECT3DDEVICE9 GetDevice(void);

#endif