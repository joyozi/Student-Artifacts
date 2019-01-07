//◇-------------------------------------------------------------------------◇
//
//	学長ヘッダーファイル[gakutyou.h]
//	AT12A271　当摩好弘
//
//◇-------------------------------------------------------------------------◇
void InitMasaru(void);
void UninitMasaru(void);
void UpdateMasaru(void);
void DrawMasaru(void);

#define GAKUTYOU_TEXTURE_NUM		(50)
#define GAKUTYOU_TYOUTEN_NUM		(GAKUTYOU_TEXTURE_NUM * 4)
#define GAKUTYOU_POLYGON_NUM		(GAKUTYOU_TEXTURE_NUM * 4)
#define GAKUTYOU_POLYGON_YOKOLONG	(80)
#define GAKUTYOU_POLYGON_TATELONG	(80)
#define GAKUTYOU_BEAM_NOBI_SPEED	(8)		//学長のPHAZE2のビームの伸びのスピード
#define GAKUTYOU_BEAM_TAME_TIME		(60)	//学長砲の溜めの時間
#define GAKUTYOU_BEAM_ROLL_SPEED	(10)	//学長砲の回転スピード　減らすと早くなる
#define GAKUTYOU_BEAM_LONG			(900)	//ビームの長さ
#define GAKUTYOU_BEAM_DELETE_SPEED	(30)

bool GetBeam(void);
void SetBeam(bool gakutyouJudge);