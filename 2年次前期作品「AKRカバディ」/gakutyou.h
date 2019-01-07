//��-------------------------------------------------------------------------��
//
//	�w���w�b�_�[�t�@�C��[gakutyou.h]
//	AT12A271�@�����D�O
//
//��-------------------------------------------------------------------------��
void InitMasaru(void);
void UninitMasaru(void);
void UpdateMasaru(void);
void DrawMasaru(void);

#define GAKUTYOU_TEXTURE_NUM		(50)
#define GAKUTYOU_TYOUTEN_NUM		(GAKUTYOU_TEXTURE_NUM * 4)
#define GAKUTYOU_POLYGON_NUM		(GAKUTYOU_TEXTURE_NUM * 4)
#define GAKUTYOU_POLYGON_YOKOLONG	(80)
#define GAKUTYOU_POLYGON_TATELONG	(80)
#define GAKUTYOU_BEAM_NOBI_SPEED	(8)		//�w����PHAZE2�̃r�[���̐L�т̃X�s�[�h
#define GAKUTYOU_BEAM_TAME_TIME		(60)	//�w���C�̗��߂̎���
#define GAKUTYOU_BEAM_ROLL_SPEED	(10)	//�w���C�̉�]�X�s�[�h�@���炷�Ƒ����Ȃ�
#define GAKUTYOU_BEAM_LONG			(900)	//�r�[���̒���
#define GAKUTYOU_BEAM_DELETE_SPEED	(30)

bool GetBeam(void);
void SetBeam(bool gakutyouJudge);