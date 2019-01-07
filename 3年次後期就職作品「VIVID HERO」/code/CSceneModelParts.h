//��-------------------------------------------------------------------------��
//
//	File:CSceneModelParts�̃w�b�_�[�t�@�C��[CXFileManager.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CSCENEMODELPARTS_H_
#define _CSCENEMODELPARTS_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CScene.h"
#include "CSceneModelMotion.h"
#include "CXFileManager.h"

class CSceneModelParts;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CSceneModelParts : public CScene
{
public:
	CSceneModelParts(int nPriority = 11);
	virtual ~CSceneModelParts();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void MatrixUpdate();

	virtual void SetPosition(float x,float y,float z);
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual D3DXVECTOR3 GetPosition(void);

	virtual void SetRotation(float x,float y,float z);
	virtual void SetRotation(D3DXVECTOR3 pos);
	virtual D3DXVECTOR3 GetRotation(void);

	virtual void SetType(int nType);

	static CSceneModelParts *Create(LPCTSTR ModelTxtName,D3DXVECTOR3 Pos);

protected:
	XFILE_INFO			m_XFile_Info[256];
	LPDIRECT3DTEXTURE9	m_Texture[256];
	
	D3DXVECTOR3			m_Pos;
	D3DXVECTOR3			m_Rot;
	D3DXVECTOR3			m_Scl;
	
	D3DXMATRIX			m_mtxProjection;				//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX			m_mtxView;						//�r���[�}�g���b�N�X
	D3DXMATRIX			*m_pmtxWorld;						//���[���h�}�g���b�N�X

	D3DXVECTOR3			m_MotionParentPartsRot;
	PART_INFO*			m_pModelParts;
	CSceneModelMotion*	m_pSceneModelMotion;
	LPCTSTR				m_ModelTxtName;
};




#endif