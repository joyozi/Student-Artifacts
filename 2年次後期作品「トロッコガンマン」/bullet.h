//��-------------------------------------------------------------------------��
//
//	File	:�o���b�g�t�@�C��[bullet.h]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void BULLET_HITJUDGE(void);

#define BULLET_MAX (300)						//�^�}�̍ő唭�˗�
#define BULLET_SPEED (MODEL_MOVE + 30.0f)		//�^�}�̃X�s�[�h
#define BULLET_LANGE (3000.0f)					//�^�}�̎˒�����

#define BAEM_TEXTURE_NUM	(10)	//�e�ۂ̃r�[�������ɗp����e�N�X�`������
#define BULLET_SIZE			(10.0f)	//�^�}�̃T�C�Y�i�����͔{�j

#define BULLET_KANKAKU		(8)					//�e�𔭎˂���Ԋu

//_CRT_SECURE_NO_DEPRECATE		���ׂȂ���
