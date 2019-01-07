//��-------------------------------------------------------------------------��
//
//	�^���ÃE�B���h�E[main.h]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��

#define DIRECTINPUT_VERSION (0x0800)	//�G���[����̂���

#ifndef _MAIN_H_
#define _MAIN_H_

#include"dinput.h"
#include<windows.h>
#include "d3dx9.h"		//�`�揈���ɕK�v
#include "xaudio2.h"	//XAudio2�֘A�̃t�@�C�����T�E���h�Đ��ɕK�v
#include <time.h>
#include <stdlib.h>

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//��L�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g�ɕK�v
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

#define SCREEN_WIDTH (800)			//��ʂ̕�
#define SCREEN_HEIGHT (800)			//��ʂ̍���
#define CLASS_NAME	"�\�����܂�"	//(�E�B���h�E�N���X�̖��O)
#define WINDOW_NAME	"�i�w���@�~�@�c���搶�j�@AKR�J�o�f�B�I"		//(�E�B���h�E�̖��O)
//���_�̃t�H�[�}�b�g
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define RESULT_END_TIME	(300)			//���U���g��ʂ̐�������


//��L�̃t�H�[�}�b�g�ɍ��킹���\����
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//�e�N�X�e���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

typedef enum
{
	MODE_TITTLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;

LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif	//����ɒǉ�