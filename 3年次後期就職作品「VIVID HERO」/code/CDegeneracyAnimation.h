//��-------------------------------------------------------------------------��
//
//	File:CDegeneracyAnimation�̃w�b�_�[�t�@�C��[CDegeneracyAnimation.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CDEGENERACYANIMATION_H_
#define _CDEGENERACYANIMATION_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CDegeneracyPolygon.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CDegeneracyAnimation : public CDegeneracyPolygon
{
public:
	CDegeneracyAnimation(int nPriority = 52);
	virtual ~CDegeneracyAnimation();

	virtual HRESULT Init(void);
	virtual void SetOnlyInit(void);
	virtual void Uninit(void);
	virtual void Update(void);
	
	static CDegeneracyAnimation *Create(LPCTSTR TexName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,int DivideNumX,int DivideNumY,int AnimTime);
	
private:
	static const int DEGENERACYANIMATION_MAX = 1000;
	
protected:
	int m_Anim_TexDivide_NumX;		//�e�N�X�`�������������邩
	int m_Anim_TexDivide_NumY;

	int m_AnimTime;					//���b�����ăA�j���[�V�������邩
	int *m_pAnimTimeCnt;			//�k�ރ|���S�����ꂼ��̃J�E���g


	bool m_AnimationLoopJudge;
};


#endif
