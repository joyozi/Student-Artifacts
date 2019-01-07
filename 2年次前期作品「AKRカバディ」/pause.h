//◇-------------------------------------------------------------------------◇
//
//	pauseヘッダーファイル[pause.h]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#define PAUSE_TEXTURE_NUM	(6)
#define PAUSE_TYOUTEN_NUM	(PAUSE_TEXTURE_NUM * 4)
#define PAUSE_POLYGON_NUM	(PAUSE_TEXTURE_NUM * 2)

typedef enum
{
	PAUSE_MENU_CONTINUE,
	PAUSE_MENU_RETRY,
	PAUSE_MENU_QUIT,
	PAUSE_MENU_MAX
}PAUSE_MENU;

void ResetPauseMenu(void);

