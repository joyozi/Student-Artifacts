void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

//-------------------------------------------------------------
//
//爆発をセットする関数
//Explosion_Pos : 爆発する位置
//BULLETNUM		 : 爆発させる番号をバレットと同期させる番号
//JUDGE			 : 爆発を表示する判定 trueで表示
//LRJudge		 : 左右どっちに傾いてるか
//
//-------------------------------------------------------------
void SetExplosion(D3DXVECTOR3 Explosion_Pos,int BULLETNUM,bool JUDGE,int LRJudge);

