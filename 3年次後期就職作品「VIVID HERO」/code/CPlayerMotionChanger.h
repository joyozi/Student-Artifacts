//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionChanger�̃w�b�_�[�t�@�C��[CPlayerMotionChanger.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONCHANGER_H_
#define _CPLAYERMOTIONCHANGER_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include <Windows.h>

class CPlayerMotionPattern;
class CPlayerModel;
class CSceneModelMotion;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionChanger
{
public:
	CPlayerMotionChanger(CPlayerMotionPattern *pPattern);
	virtual ~CPlayerMotionChanger();

	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion);
	
	virtual void ChangedPattern(CPlayerMotionPattern *pPattern);



private:
	CPlayerMotionPattern *m_pPatternNow;
};


#endif
