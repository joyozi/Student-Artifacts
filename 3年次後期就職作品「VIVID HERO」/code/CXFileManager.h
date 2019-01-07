//��-------------------------------------------------------------------------��
//
//	File:CXFileManager�̃w�b�_�[�t�@�C��[CXFileManager.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CXFileManager_H_
#define _CXFileManager_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"

//��-----------------------------------��
//�\���̒�`
//��-----------------------------------��
typedef struct
{
	LPDIRECT3DTEXTURE9			XFile;
	LPDIRECT3DVERTEXBUFFER9		VtxBuffer;
	LPD3DXMESH					Mesh;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER				BuffMat;		//�}�e���A�����ւ̃|�C���^
	DWORD						numMat;			//�}�e���A���̐�
}XFILE_INFO;

//struct�̏ꍇ�́Apublic�Ƃ������Ȃ������ꍇ�́Apublic�ɂȂ�
struct XFileData
{
	XFILE_INFO			XFile_Info;
	static const int	XFILE_FILENAME_MAX = 256;
	char				XFileName[XFILE_FILENAME_MAX];
};

class CXFileManager;

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CXFileManager
{
public:
	CXFileManager();
	virtual ~CXFileManager();

	int Load(const char* pXFileName);

	void Init(int nMax);
	void Uninit(void);

	XFILE_INFO GetXFile(int nId);

private:
	LPDIRECT3DTEXTURE9		m_XFile;
	int						m_nXFileMax;
	int						m_nXFileCount;
	XFileData*				m_pXFileData;
};


#endif