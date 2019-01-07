//��-------------------------------------------------------------------------��
//
//	�Q�[���|���S��h�t�@�C��[GamePolygon.h]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��
#ifndef _GAME_POLYGON_H_
#define _GAME_POLYGON_H_

#define POLYGON_NUM (GamePlayer_texturenum * 2)			//�\������O�p�`�|���S���̐�
#define TYOUTEN_NUM (8)			//���_�̌�
#define IDOURYOU	(20)		//�����C���O�}���̈ړ���
#define POLYGON_YOKO (SCREEN_WIDTH / 2)		//�|���S���̏����̒��Sx���W
#define POLYGON_TATE (SCREEN_HEIGHT / 2)	//�|���S���̏����̒��Sy���W
#define POLYGON_YOKOLONG (200)	//�|���S���̉��̒���
#define POLYGON_TATELONG (60)	//�|���S���̏c�̒���
#define POLYGON_ZOOM	 (150)	//�|���S���̊g��k���̗�
#define POLYGON_HANKEI	 (150)
#define GamePlayer_texturenum (1)	//����cpp�̉摜�̖���
#define GAMEPLAYER_SPEED	(80)		//�搶�̃X�s�[�h
#define GAMEPLAYER_TATE_SPEED_S	(120)	//��ރX�s�[�h
#define GAMEPLAYER_TATE_SPEED	(12)

void InitGamePolygon(void);
void UninitGamePolygon(void);
void UpdateGamePolygon(void);
void DrawGamePolygon(void);


#endif