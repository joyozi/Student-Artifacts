//◇-------------------------------------------------------------------------◇
//
//	File	:モデル処理[model.h]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//プロトタイプ宣言
//◇-------------------------------------------------------------------------◇
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

void ModelHITJUDGE(void);

D3DXVECTOR3 Getg_posModel(void);
D3DXVECTOR3 Getg_rotModel(void);

D3DXMATRIX GetTranslate_juuL(void);
D3DXMATRIX GetTranslate_juuR(void);

float GetModel_SpeedUP(void);

//◇-------------------------------------------------------------------------◇
//マクロ定義
//◇-------------------------------------------------------------------------◇
#define MODEL_NUM	(9)				//モデルのパーツ数

#define MODEL_MOVE (15.0f)			//キャラの移動量
#define MODE_WHEEL_ROT (0.2f)		//ホイールの回転の速度
#define MODEL_KOMA_SAYUU (5)		//モデルの左右移動が何コマのアニメーションをするか

#define MODEL_GOAL		(60000.0f-300.0f)		//ゴールの座標

//プレイヤーの構造体はmain.hに移動しました

//構造体の後に定義する
PLAYER_MODE GetModelOriginal(void);