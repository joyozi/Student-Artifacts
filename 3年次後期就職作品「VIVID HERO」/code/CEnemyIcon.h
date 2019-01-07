//��-------------------------------------------------------------------------��
//
//	File:CEnemyIcon�̃w�b�_�[�t�@�C��[CEnemyIcon.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CEnemyIcon_H_
#define _CEnemyIcon_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CScene2D.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CEnemyIcon : public CScene2D
{
public:
	CEnemyIcon(int nPriority = 71);
	virtual ~CEnemyIcon();

	virtual void Draw(void)override;
	virtual void SetDrawJudge(bool Judge){m_DrawJudge = Judge;}

	static CEnemyIcon *Create(LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Size);

private:
	bool m_DrawJudge;
};


#endif
