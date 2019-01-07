//-------------------------------------------------------------------------
//
//	^Cgcppt@C[tittle.cpp]
//	AT12A271@DO
//
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//CN[ht@C
//-------------------------------------------------------------------------
#include "main.h"
#include "tittle.h"
#include "TittleBG.h"
#include "TittlePolygon.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//-------------------------------------------------------------------------
//}Nè`
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//vg^Cvé¾
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//O[oÏ
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//^Cgú»
//-------------------------------------------------------------------------
void InitTittle(void)
{
	InitTittleBG();					//^CgÌwiÌú»
	InitTittlePolygon();			//^CgÌ|Sú»

	PlaySound(SOUND_LABEL_TITLE_BGM);
}
//---------------------------------
//^CgÌI¹
//---------------------------------
void UninitTittle(void)
{
	UninitTittleBG();					//^CgÌwiÌI¹
	UninitTittlePolygon();				//^CgÌ|SI¹

	StopSound(SOUND_LABEL_TITLE_BGM);
}
//---------------------------------
//^CgÌXV
//---------------------------------
void UpdateTittle(void)
{
	UpdateTittleBG();					//^CgÌwiÌXV
	UpdateTittlePolygon();				//^CgÌ|SXV

}
//---------------------------------
//^CgÌ`æ
//---------------------------------
void DrawTittle(void)
{
	DrawTittleBG();					//^CgÌwiÌ`æ
	DrawTittlePolygon();			//^CgÌ|S`æ
}

