//��-------------------------------------------------------------------------��
//
//	����h�t�@�C��[explosion.h]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

void SetExplosion(bool enemy_Judge,D3DXVECTOR3 pos,int RendouCnt);

#define EXPLOSION_HANKEI (80)	//�����̑傫��
#define EXPLOSION_TIME (60)	//�����̎���


