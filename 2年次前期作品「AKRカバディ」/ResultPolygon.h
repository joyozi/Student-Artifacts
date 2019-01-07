//◇-------------------------------------------------------------------------◇
//
//	リザルトポリゴンhファイル[ResultPolygon.h]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇
#ifndef _RESULT_POLYGON_H_
#define _RESULT_POLYGON_H_

#define RESULT_POLYGON_NUM (8)			//表示する三角形ポリゴンの数
#define TYOUTEN_NUM (8)					//頂点の個数
#define POLYGON_ZOOM	 (150)			//ポリゴンの拡大縮小の量

void InitResultPolygon(void);
void UninitResultPolygon(void);
void UpdateResultPolygon(void);
void DrawResultPolygon(void);


#endif