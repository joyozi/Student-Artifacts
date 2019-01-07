//��-------------------------------------------------------------------------��
//
//	File:CSceneModelMotion�̃w�b�_�[�t�@�C��[CSceneModelMotion.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CSCENEMODELMOTION_H_
#define _CSCENEMODELMOTION_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CItemList.h"
#include "CScene.h"

//��-----------------------------------��
//�\����
//��-----------------------------------��
//���f���̃j���[�g�������
typedef struct
{
	char		ModelName[256];
	char		TexName[256];
	int			ModelNumber;
	int			ParentNumber;
	int			IndexNumber;

	D3DXVECTOR3	Pos;
	D3DXVECTOR3	Rot;
	D3DXVECTOR3	Scl;
}PART_INFO;

// �L�[�f�[�^�̒�`
typedef struct
{
	D3DXVECTOR3 keyPos;
	D3DXVECTOR3 keyRot;
}KEY_DATA;

// �A�j���[�V�����f�[�^�̒�`
typedef struct
{
	int			loopjudge;
	int			num_key;
	int			frame;
	KEY_DATA*	key;
}KEY_ANIME;

typedef enum
{
	MODELACT_NEUTRAL = 0,
	MODELACT_WALK,
	MODELACT_RUN,
	MODELACT_PUNCH,
	MODELACT_KICK,
	MODELACT_HEADBUTT,
	MODELACT_MAX
}MODELACT;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CSceneModelMotion : public CScene
{
public:
	CSceneModelMotion(int nPriority = 10);
	virtual ~CSceneModelMotion();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void SetPosition(float x,float y,float z);
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual D3DXVECTOR3 GetPosition(void);

	virtual void SetRotation(float x,float y,float z);
	virtual void SetRotation(D3DXVECTOR3 pos);
	virtual D3DXVECTOR3 GetRotation(void);

	virtual void SetType(int nType);

	virtual PART_INFO *GetPart_Info(void);
	virtual int GetNowMotionNum();
	virtual bool GetMotionEndJudge(void){return m_MotionEndJudge;}
	static CSceneModelMotion *Create(LPCTSTR ModelTxtName);

	virtual void SetActCommand(int Act){m_ModelAct = Act;}
	virtual int GetActCommand(){return m_ModelAct;}
	
	int GetPart_Num(void);

private:
	D3DXVECTOR3				m_Pos;
	D3DXVECTOR3				m_Rot;
	LPCTSTR					m_ModelTxtName;
	PART_INFO*				m_pModel;						//���f���̊�{���
	PART_INFO*				m_pModelMove;					//���f���̃L�[�t���[�����
	KEY_DATA*				m_pModelStandard;					//���f���̉������ĂȂ��Ƃ��̃|�[�Y�̏��ۊǏꏊ
	KEY_ANIME				*m_pAnime;

	int						m_ModelPartsNum;
	int						m_ModelAct;
	int						m_MotionNum_deleted;					//�f���[�g�Ŏg���p
	
	//���`��ԗp�̂��낢��Ȑ��l
	float					m_Time;							//�v�Z�p
	int						m_ModelActNow;						//�O��Ƃ̔�r����悤
	int						m_MotionNumStart;					//���[�V�����̎n�܂�̐��l
	KEY_DATA*				m_pKeyInterpolation;				//���`��Ԃ��钆�Ԃ̏��
	bool					m_KeyInfterpolationjudge;				//���`��Ԃ����Ă��邩���Ă��Ȃ���
	bool					m_MotionEndJudge;
};

#endif
