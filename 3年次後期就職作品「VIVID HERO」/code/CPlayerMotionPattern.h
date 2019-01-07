//��-------------------------------------------------------------------------��
//
//	File:CPlayerMotionPattern�̃w�b�_�[�t�@�C��[CPlayerMotionPattern.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CPLAYERMOTIONPATTERN_BASIC_H_
#define _CPLAYERMOTIONPATTERN_BASIC_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include <Windows.h>
#include "sound.h"

class CPlayerModel;
class CSceneModelMotion;

//��-----------------------------------��
//�񋓌^
//��-----------------------------------��

typedef enum{
	PMOVE_NUTORAL = 0,
	PMOVE_MOVE,
	PMOVE_SHOT,
	PMOVE_SWORDACCEL,
	PMOVE_SWORDATTACK,
	PMOVE_HOMINGMISSILE,
	PMOVE_DAMAGE,
	PMOVE_RAPIDUP,
	PMOVE_RAPIDDOWN,

	PMOVE_SHOTMOVE_L,
	PMOVE_SHOTMOVE_R,

	PMOVE_SWORDATTACK_2ND,

	PMOVE_MAX
}PLAYER_MOTION;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CPlayerMotionPattern
{
public:
	CPlayerMotionPattern(){}
//	virtual ~CPlayerMotionPattern() = 0{}
	virtual void Update(CPlayerModel *pPlayer,CSceneModelMotion *pModelMotion) = 0;
};


#endif
