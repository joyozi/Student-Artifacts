//◇-------------------------------------------------------------------------◇
//
//	ゲーム背景hファイル[GameBG.h]
//	Author : touma yoshihiro
//
//◇-------------------------------------------------------------------------◇
void InitGameBG(void);
void UninitGameBG(void);
void UpdateGameBG(void);
void DrawGameBG(void);

#define BG_NUM (1)	//背景画像の枚数。増やしたらグローバル変数のNULも増やす