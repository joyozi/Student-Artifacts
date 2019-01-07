//��-------------------------------------------------------------------------��
//
//	�Q�[��cpp�t�@�C��[game.cpp]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "pause.h"
#include "box.h"

#include "field.h"
#include "model.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "billboard.h"
#include "shadow.h"
#include "meshsky.h"
#include "meshcave.h"
#include "obstacle.h"
#include "model_rail.h"
#include "bullet.h"
#include "gameUI.h"
#include "explosion.h"
#include "taimatsu.h"
#include "enemy_01.h"
#include "barricade.h"

#include "sound.h"
#include "score.h"
#include "UI_modelpos.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
bool g_bPause = false;		//true�̂Ƃ��|�[�Y

//��-------------------------------------------------------------------------��
//�Q�[������������
//��-------------------------------------------------------------------------��
void InitGame(void)
{
	PlaySound(SOUND_LABEL_GAMEBGM);

	g_bPause = false;

	InitLight();
	InitCamera();
	InitPause();

	InitObstacle();

	InitModel();
	InitRail();
	InitTaimatsu();
	InitEnemy01();

	InitBullet();
	InitExplosion();

	InitBarricade();

	InitMeshfield();
	InitMeshCave();
	InitBox();

	InitGameUI();
	InitUI_modelpos();
	InitScore();
}

//��---------------------------------��
//�Q�[���̏I������
//��---------------------------------��
void UninitGame(void)
{
	//QUIT�ŏI��������|�[�Y���j���[���I��������
	g_bPause = false;


	UninitLight();
	UninitCamera();
	UninitPause();

	UninitObstacle();

	UninitModel();
	UninitRail();
	UninitTaimatsu();
	UninitEnemy01();

	UninitBullet();	
	UninitExplosion();

	UninitBarricade();

	UninitMeshfield();
	UninitMeshCave();
	UninitBox();
	
	UninitGameUI();
	UninitUI_modelpos();
	UninitScore();

	StopSound(SOUND_LABEL_GAMEBGM);
}
//��---------------------------------��
//�Q�[���̍X�V����
//��---------------------------------��
void UpdateGame(void)
{
	if(GetFade() == FADE_NONE)
	{
		//�|�[�Y����
		if(GetKeyboardTrigger(DIK_P) == true)
		{
			g_bPause = g_bPause?false : true;
			//�|�[�Y���j���[�̑I���������ɖ߂�
		}
	}

	if(g_bPause == true)
	{
		UpdatePause();
	}
	else
	{
		UpdateLight();
		UpdateCamera();

		UpdateObstacle();

		UpdateModel();
		UpdateRail();
		UpdateTaimatsu();
		UpdateEnemy01();

		UpdateBullet();
		UpdateExplosion();

		UpdateBarricade();
		UpdateBox();

		UpdateMeshfield();
		UpdateMeshCave();

		BULLET_HITJUDGE();
		ModelHITJUDGE();

		UpdateGameUI();
		UpdateUI_modelpos();
		UpdateScore();
	}

}

//��---------------------------------��
//�Q�[���̕`�揈��
//��---------------------------------��
void DrawGame(void)
{
	DrawLight();
	SetCamera();

	DrawObstacle();
	DrawModel();
	DrawRail();
	DrawTaimatsu();
	DrawEnemy01();

	DrawBullet();
	DrawExplosion();
	
	DrawBarricade();

	DrawMeshfield();
	DrawMeshCave();
//	DrawBox();

	DrawGameUI();
	DrawUI_modelpos();
	DrawScore();

	if(g_bPause == true)
	{
		DrawPause();
	}

}

//��---------------------------------��
//�|�[�Y����
//��---------------------------------��
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

bool GetPause(void)
{
	return g_bPause;
}
