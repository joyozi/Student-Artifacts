//��-------------------------------------------------------------------------��
//
//	File:CScore�̃w�b�_�[�t�@�C��[CScore.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CSCORE_H_
#define _CSCORE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CScene.h"
#include "CScene2D.h"

#define SCORE_KETA_MAX (16)		//�X�R�A�̍ő包��

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CScore : public CScene
{
public:
	CScore(int nPriority = 70);
	virtual ~CScore();
	
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void  SetPosition(float x,float y,float z);
	virtual void  SetPosition(D3DXVECTOR3 pos);

	virtual D3DXVECTOR3 GetPosition(void);

	virtual void SetRotation(float x,float y,float z);
	virtual void SetRotation(D3DXVECTOR3 pos);

	virtual D3DXVECTOR3 GetRotation(void);

	virtual void SetType(int nType);

	static CScore *Create(LPCTSTR TextureName,int KetaNum,float Pos_Right,float Pos_Up,float TexWidth,float TexHeight,int StartScore);
	void PlusScore(int score);
	void ResetScore(int score);

protected:
	int				SCORE_KETA_NUM;				//�X�R�A�̌��̐�
	float			SCORE_POS_RIGHT;			//�X�R�A�̍��[�̈ʒu
	float			SCORE_POS_UP;				//�X�R�A�̈�ԏ�̈ʒu
	float			SCORE_POS_HEIGHT;			//�X�R�A�̏c��
	float			SCORE_POS_WIDTH;			//��̃X�R�A�̉���

	D3DXVECTOR3		m_Pos;
	D3DXVECTOR3		m_Rot;

	LPCTSTR			m_ScoreTextureName;
	CScene2D*		m_pNumber[SCORE_KETA_MAX];

	int				m_Score;					//���v�̐��l�B
	int				m_NowScore;					//�ϓ����̃X�R�A �\���p

};

#endif