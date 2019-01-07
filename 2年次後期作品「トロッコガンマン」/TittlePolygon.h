//◇-------------------------------------------------------------------------◇
//
//	タイトルポリゴンhファイル[TittlePolygon.h]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇
#ifndef _TITTLE_POLYGON_H_
#define _TITTLE_POLYGON_H_

#define TITTLE_POLYGON_NUM (2)			//表示する三角形ポリゴンの数
#define TITTLE_TYOUTEN_NUM (4)			//頂点の個数
#define TITTLE_IDOURYOU	(10)			//ランイングマンの移動量
#define TITTLE_POLYGON_YOKO (80)		//ポリゴンの初期の中心x座標
#define TITTLE_POLYGON_TATE (340)		//ポリゴンの初期の中心y座標
#define TITTLE_POLYGON_YOKOLONG (270)	//ポリゴンの横の長さ
#define TITTLE_POLYGON_TATELONG (550)	//ポリゴンの縦の長さ
#define TITTLE_POLYGON_ZOOM	 (150)		//ポリゴンの拡大縮小の量
#define TENMETU_TIME			(30)	//プレスエンターが点滅する間隔
#define TENMETU_TIME_FADEOUT	(5)	//プレスエンターが点滅する間隔


void InitTittlePolygon(void);
void UninitTittlePolygon(void);
void UpdateTittlePolygon(void);
void DrawTittlePolygon(void);


#endif