//◇-------------------------------------------------------------------------◇
//
//	File	:バレットファイル[bullet.h]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void BULLET_HITJUDGE(void);

#define BULLET_MAX (300)						//タマの最大発射量
#define BULLET_SPEED (MODEL_MOVE + 30.0f)		//タマのスピード
#define BULLET_LANGE (3000.0f)					//タマの射程距離

#define BAEM_TEXTURE_NUM	(10)	//弾丸のビーム処理に用いるテクスチャ枚数
#define BULLET_SIZE			(10.0f)	//タマのサイズ（実物は倍）

#define BULLET_KANKAKU		(8)					//弾を発射する間隔

//_CRT_SECURE_NO_DEPRECATE		調べなさい
