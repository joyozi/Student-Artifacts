//◇-------------------------------------------------------------------------◇
//
//	ゲームポリゴンhファイル[GamePolygon.h]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇
#ifndef _GAME_POLYGON_H_
#define _GAME_POLYGON_H_

#define POLYGON_NUM (GamePlayer_texturenum * 2)			//表示する三角形ポリゴンの数
#define TYOUTEN_NUM (8)			//頂点の個数
#define IDOURYOU	(20)		//ランイングマンの移動量
#define POLYGON_YOKO (SCREEN_WIDTH / 2)		//ポリゴンの初期の中心x座標
#define POLYGON_TATE (SCREEN_HEIGHT / 2)	//ポリゴンの初期の中心y座標
#define POLYGON_YOKOLONG (200)	//ポリゴンの横の長さ
#define POLYGON_TATELONG (60)	//ポリゴンの縦の長さ
#define POLYGON_ZOOM	 (150)	//ポリゴンの拡大縮小の量
#define POLYGON_HANKEI	 (150)
#define GamePlayer_texturenum (1)	//このcppの画像の枚数
#define GAMEPLAYER_SPEED	(80)		//先生のスピード
#define GAMEPLAYER_TATE_SPEED_S	(120)	//後退スピード
#define GAMEPLAYER_TATE_SPEED	(12)

void InitGamePolygon(void);
void UninitGamePolygon(void);
void UpdateGamePolygon(void);
void DrawGamePolygon(void);


#endif