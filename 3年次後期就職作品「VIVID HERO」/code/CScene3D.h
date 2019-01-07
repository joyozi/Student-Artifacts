//��-------------------------------------------------------------------------��
//
//	File:CScene3D�̃w�b�_�[�t�@�C��[CScene3D.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CSCENE3D_H_
#define _CSCENE3D_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "CScene.h"

class CScene3D;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = 8);
	virtual ~CScene3D();

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

	static CScene3D *Create(LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,float TexWidth,float TexHeight);
	static CScene3D *Create(int Priority,LPCTSTR TextureName,D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,float TexWidth,float TexHeight);

	virtual VERTEX_3D GetVERTEXPos(int num);
	virtual void SetColor(D3DXCOLOR Color);

protected:
	D3DXVECTOR3					m_Pos;
	D3DXVECTOR3					m_Rot;
	D3DXVECTOR3					m_Scl;
	LPDIRECT3DTEXTURE9			m_Texture;
	LPDIRECT3DVERTEXBUFFER9			m_VtxBuffer;

	VERTEX_3D*					m_pVtx;		//�摜�̍��W�̃|�C���^
	LPCTSTR						m_TexName;
	float						m_TexWidth;
	float						m_TexHeight;
	D3DXMATRIX					m_mtxProjection;					//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX					m_mtxView;						//�r���[�}�g���b�N�X
	D3DXMATRIX					m_mtxWorld;						//���[���h�}�g���b�N�X

private:
	D3DXVECTOR3					m_VtxPos0;
	D3DXVECTOR3					m_VtxPos1;
	D3DXVECTOR3					m_VtxPos2;
	D3DXVECTOR3					m_VtxPos3;
};

#endif