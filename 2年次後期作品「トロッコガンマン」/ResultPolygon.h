//◇-------------------------------------------------------------------------◇
//
//	リザルトポリゴンhファイル[ResultPolygon.h]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇
#ifndef _RESULT_POLYGON_H_
#define _RESULT_POLYGON_H_

#define POLYGON_NUM (8)			//表示する三角形ポリゴンの数
#define TYOUTEN_NUM (8)			//頂点の個数
#define IDOURYOU	(10)		//ランイングマンの移動量
#define POLYGON_YOKO (80)		//ポリゴンの初期の中心x座標
#define POLYGON_TATE (340)		//ポリゴンの初期の中心y座標
//#define POLYGON_YOKOLONG (270)	//ポリゴンの横の長さ
//#define POLYGON_TATELONG (550)	//ポリゴンの縦の長さ
#define POLYGON_ZOOM	 (150)	//ポリゴンの拡大縮小の量

void InitResultPolygon(bool Judge);
void UninitResultPolygon(void);
void UpdateResultPolygon(void);
void DrawResultPolygon(void);


#endif