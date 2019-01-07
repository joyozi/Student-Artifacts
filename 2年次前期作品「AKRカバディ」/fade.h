//��-------------------------------------------------------------------------��
//
//	�t�F�C�h�w�b�_�[�t�@�C��[fade.h]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _FADE_H_
#define _FADE_H_

typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
}FADE;


void InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(FADE fade);
FADE GetFade(void);
void SetFade_2(FADE fade,MODE modeNext);	//0924�ɍ쐬�@���Ԃ�������_2

#define FADE_TIME	(0.01f)	//�t�F�C�h�C���t�F�C�h�A�E�g�̎���

#endif