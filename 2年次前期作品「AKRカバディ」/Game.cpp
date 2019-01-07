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
#include "GameBG.h"
#include "GamePlayer.h"
#include "input.h"
#include "enemy.h"
#include "fade.h"
#include "Game_Countdown.h"
#include "score.h"
#include "pause.h"
#include "gakutyou.h"
#include "explosion.h"
#include "sound.h"

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

float musicTime;

//��-------------------------------------------------------------------------��
//�Q�[������������
//��-------------------------------------------------------------------------��
void InitGame(void)
{
	g_bPause = false;

	musicTime = 0;

	InitGameBG();			//�Q�[���̔w�i�̏���������
	InitGamePolygon();		//�Q�[���̃|���S������������
	InitMasaru();
	InitEnemy();
	InitExplosion();
	InitScore();			//�X�R�A�̏���������
	InitCountdown();
	InitPause();

	PlaySound(SOUND_LABEL_GAME_MAIN);
}

//��---------------------------------��
//�Q�[���̏I������
//��---------------------------------��
void UninitGame(void)
{
	//QUIT�ŏI��������|�[�Y���j���[���I��������
	g_bPause = false;

	StopSound(SOUND_LABEL_GAME_MAIN);

	UninitGameBG();			//�Q�[���̔w�i�̏I������
	UninitGamePolygon();	//�Q�[���̃|���S���I������
	UninitMasaru();
	UninitEnemy();
	UninitExplosion();
//	UninitScore();			//�X�R�A�̏I������  RESULT�ł��邩�炢��Ȃ�
	UninitCountdown();
	UninitPause();
}
//��---------------------------------��
//�Q�[���̍X�V����
//��---------------------------------��
void UpdateGame(void)
{
	//������~���[�W�b�N���[�v
	musicTime+=1.0f;
	if(musicTime >= 60.0f*60.3f)
	{
		StopSound(SOUND_LABEL_GAME_MAIN);
		PlaySound(SOUND_LABEL_GAME_MAIN);

		musicTime = 0.0f;
	}


	//�|�[�Y����
	if(GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause?false : true;
		//�|�[�Y���j���[�̑I���������ɖ߂�
	}

	if(g_bPause == true)
	{
		UpdatePause();
	}
	else
	{
		//�J�E���g�_�E���̓t�F�C�h�C�����I�����Ă���n�߂Ă��炢�܂�
		if(GetFade() == FADE_NONE)
		{
			UpdateCountdown();	//�J�E���g�_�E������
		}

		UpdateGameBG();			//�Q�[���̔w�i�̍X�V����
		UpdateMasaru();
		UpdateGamePolygon();	//�Q�[���̃|���S���X�V����
		UpdateEnemy();
		UpdateExplosion();
		UpdateScore();			//�X�R�A�A�b�v�f�[�g
	
	}
}

//��---------------------------------��
//�Q�[���̕`�揈��
//��---------------------------------��
void DrawGame(void)
{
	DrawGameBG();			//�Q�[���̔w�i�̕`�揈��
	DrawCountdown();		//�J�E���g�_�E���̕`�揈��
	DrawMasaru();
	DrawGamePolygon();		//�Q�[���̃|���S���`�揈��
	DrawExplosion();
	DrawScore();			//�X�R�A�̕`�揈��
	DrawEnemy();

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