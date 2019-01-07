//◇-------------------------------------------------------------------------◇
//
//	爆発hファイル[explosion.h]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

void SetExplosion(bool enemy_Judge,D3DXVECTOR3 pos,int RendouCnt);

#define EXPLOSION_HANKEI (80)	//爆発の大きさ
#define EXPLOSION_TIME (60)	//爆発の時間


