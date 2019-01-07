#ifndef _CSCENE_H_
#define _CSCENE_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"

//��-----------------------------------��
//�}�N����`
//��-----------------------------------��
#define PRIORITY_NUM (128)

/*/------�v���C�I���e�B�[���C�u����(�v���C�I���e�B�̏��Ԃɂ���)------

�O�`�T : ��(�f�o�b�O�p�A�����p��)
�U�`�Q�O : CScene�̊�{�N���X
�Q�P�`�R�O : �Q�[���̊�b�ƂȂ���̂����낢��
�R�P�`�S�O : Mesh�n
�T�O�`PRIORITY_NUM : ���̑�

���ʘg
CFade : PRIORITY_NUM - 1 �Ō�ɕ`�悵��������



//--------------------------------------------------------------------*/

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CScene
{
public:
	//PRIORITY�Ƃ́A�`�悷�鏇�Ԃł���B�ŏ����珇�ɕ`�悵�Ă����āA�`�揇�Ԃ��킩��₷�����邽�߂ɕK�v�ł���
	//CScene(int nPriority = 0):m_nPriority(nPriority){}
	CScene(int nPriority = 6);
	virtual ~CScene();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//���Ԑ������
	virtual void  SetPosition(float x,float y,float z) = 0;
	virtual void  SetPosition(D3DXVECTOR3 pos) = 0;

	virtual D3DXVECTOR3  GetPosition(void) = 0;

	virtual void SetRotation(float x,float y,float z) = 0;
	virtual void SetRotation(D3DXVECTOR3 pos) = 0;
	virtual D3DXVECTOR3 GetRotation(void) = 0;

	virtual void SetType(int nType) = 0;
	
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	void Release(void);

	void LinkList(void);
	void UnlinkList(void);
	
	static CScene *SearchLinkList(CScene *irekoScene[],int searchType);

	virtual void CollisionHitCheckCircle(CScene *Scene);
	virtual float GetCollisionRadius(int Num);
	virtual D3DXVECTOR3 GetCollisionCenterPos(int Num);
	virtual bool CollisionTargetSheet(CLASS_TYPE Type);

	virtual void CollisionAction(CLASS_TYPE Type,int Num);		//�ǂ̃^�C�v���Ɖ��Ԗڂ̂�����ʒu������������

	virtual void SetCollisionHitNum(int HitNum);
	virtual int GetCollisionHitNum(void);

	static void CollisionHitLoop(void);

private:
	static CScene*		m_pTop[PRIORITY_NUM];	// ���X�g�̐擪�|�C���^
	static CScene*		m_pCur[PRIORITY_NUM];	// ���X�g�̖���
	CScene*				m_pPrev;						// ���g�̑O�ւ̃|�C���^
	CScene*				m_pNext;						// ���g�̎��ւ̃|�C���^

	int					m_nPriority;
	int					m_CollisionHitNum;

protected:
	bool				m_DeleteFlag;
	CLASS_TYPE			m_Type;						//�Z�b�g�^�C�v�Ŏg���ϐ�
	bool				m_CollisionHitJudge;
};



#endif
