//��-------------------------------------------------------------------------��
//
//	�^���ÃE�B���h�E[main.h]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��

#define DIRECTINPUT_VERSION (0x0800)	//�G���[����̂���

#ifndef _MAIN_H_
#define _MAIN_H_
#include<windows.h>

#include "d3dx9.h"	//�`�揈���ɕK�v

#include"dinput.h"
#include<windows.h>
#include "d3dx9.h"		//�`�揈���ɕK�v
#include "xaudio2.h"	//XAudio2�֘A�̃t�@�C�����T�E���h�Đ��ɕK�v
#include <time.h>
#include <stdlib.h>

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")			//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		//��L�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g�ɕK�v
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

#define SCREEN_WIDTH (1200)				//��ʂ̕�
#define SCREEN_HEIGHT (760)				//��ʂ̍���
#define RESULT_END_TIME	(300)			//���U���g��ʂ̐�������

#define SCREEN_CHANGE (TRUE)			//�E�B���h�E�A�t���X�N���[���̃`�F���W

LPDIRECT3DDEVICE9 GetDevice(void);

//*** 2D�̏��� ***
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//�e�N�X�e���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;


/*** 3D�����̒ǉ� ***/
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR    col;
	D3DXVECTOR2 tex;
}VERTEX_3D;

//===================���[�h�̐ݒ�=======================
typedef enum
{
	MODE_TITTLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;

void SetMode(MODE mode);
MODE GetMode(void);
//======================================================

//�v���C���[�̏�Ԃ�ۑ�����\����
typedef struct
{
	D3DXVECTOR3 MOTO_pos;		//�o���b�g�𔭎˂������̃v���C���[�̈ʒu�B�����蔻��̂Ƃ��Ɏg��
	bool Jump_Judge;			//�W�����v���Ă邩�ۂ��̔���
	int LR_Judge;				//���E�ɌX���Ă邩�̔���@1�����@2���^�񒆁@3���E�ɌX���Ă�
	int GUN_under;				//�r�̏�Ԃ�ۑ����� 1�Řr����ɂ����Ă����ԁ@2�Řr�����ɂ��낵�Ă����ԁ@3��
	bool Thing_exist;			//���̂����݂��邩�ǂ����B true�ŕ\������
	int Model_Muteki;			//���f���̖��G��Ԃɂ��ā@1�A�ʏ��ԁ@�Q�A�_���[�W���󂯂ĂЂ��ł��ԁ@�R�A���G��ԁ@�e�����Ă�
	int Enemy_Damage;			//�Ă���HP�B0�ɂȂ�Ə��ł���
}PLAYER_MODE;


#endif 	//����ɒǉ�