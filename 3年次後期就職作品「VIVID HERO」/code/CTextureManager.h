//��-------------------------------------------------------------------------��
//
//	File:CXFileManager�̃w�b�_�[�t�@�C��[CXFileManager.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CTEXTUREMANAGER_H_
#define _CTEXTUREMANAGER_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CTextureManager
{
public:
	CTextureManager();
	~CTextureManager();
	
	//�Ǘ��ԍ��@�ǂݍ��߂Ȃ�������[�P
	int Load(const char* pTextureFileName);
	
	void Init(int nMax);
	void Uninit(void);
	LPDIRECT3DTEXTURE9 GetTexture(int nId);

private:
	int m_nTextureMax;
	int m_nTextureCount;


	//struct�̏ꍇ�́Apublic�Ƃ������Ȃ������ꍇ�́Apublic�ɂȂ�
	struct TextureData
	{
		LPDIRECT3DTEXTURE9 pTexture;
		static const int TEXTURE_FILENAME_MAX = 256;
		char m_fileName[TEXTURE_FILENAME_MAX];
	};
	TextureData* m_pTextureData;
};

#endif
