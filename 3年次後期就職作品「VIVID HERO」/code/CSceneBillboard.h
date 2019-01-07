//��-------------------------------------------------------------------------��
//
//	File:CScene3D�̃w�b�_�[�t�@�C��[CScene3D.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CSCENEBILLBOARD_H_
#define _CSCENEBILLBOARD_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CScene.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CSceneBillboard : public CScene
{
public:
	CSceneBillboard(int nPriority = /*9*/50);
	virtual ~CSceneBillboard();

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

	static CSceneBillboard *Create(void);
	static CSceneBillboard *CSceneBillboard::Create(LPCTSTR TextureName,float PosX,float PosY,float PosZ,float TexWidth,float TexHeight);

	virtual void SetColor(D3DXCOLOR Color);

protected:
	LPDIRECT3DTEXTURE9			m_Texture;
	LPDIRECT3DVERTEXBUFFER9		m_VtxBuffer;

	D3DXVECTOR3					m_Pos;
	D3DXVECTOR3					m_Rot;
	D3DXVECTOR3					m_Scl;

	VERTEX_3D*					m_pVtx;						//�摜�̍��W�̃|�C���^
	
	D3DXMATRIX					m_mtxProjection;				//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX					m_mtxView;						//�r���[�}�g���b�N�X
	D3DXMATRIX					m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXMATRIX					m_mtxViewreturn;				//�t�s��p�̃r���[�}�g���b�N�X

	float						TextureWidth;
	float						TextureHeight;
	LPCTSTR						m_TextureName;
};


#endif