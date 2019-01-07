//��-------------------------------------------------------------------------��
//
//	File:CMeshHitCheckBall�̃w�b�_�[�t�@�C��[CMeshHitCheckBall.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CMESHHITCHECKBALL_H_
#define _CMESHHITCHECKBALL_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CMeshBasisClass.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CMeshHitCheckBall : public CMeshBasisClass
{
public:
	CMeshHitCheckBall(int nPriority = 80);
	virtual ~CMeshHitCheckBall();

	virtual HRESULT Init(void);
	virtual void Draw(void);

	virtual void SetBallRadius(float Radius);

	static CMeshHitCheckBall *Create();

private:
	static const int	CHECKBALL_DANSUU = 5;
	static const int	CHECLBALL_ONEVTX = 6;							//��̉��̍L����ɂ��钸�_��
	static const int	CHECKBALL_VTXNUM = CHECKBALL_DANSUU * CHECLBALL_ONEVTX;

	float				m_BallRadius;
	D3DXVECTOR3			m_BallVtxVec[CHECKBALL_VTXNUM];
};


#endif
