//��-------------------------------------------------------------------------��
//
//	File:�}�l�[�W���̃t�@�C��[CManager.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CMANAGER_H_
#define _CMANAGER_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"

class CRenderer;
class CCamera;
class CLight;
class CTextureManager;
class CDebugProc;
class CInput;
class CPhaseChange;
class CPhaseGame;
class CXFileManager;
class CJoystick;
class CPhase;

//#define JOYSTIKON

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void);

	static CTextureManager *GetTextureManagerPointer(void);		//�e�N�X�`���̃|�C���^���Q�b�g����
	static CXFileManager *GetXFileManagerPointer(void);		//X�t�@�C���̃|�C���^���Q�b�g����
	static CCamera *GetCameraPointer(void);						//�J�����̃|�C���^���Q�b�g����
	static CPhaseChange *GetPhaseChangePointer(void);
	
	static void SetMainCameraPointer(CCamera *pCamera);				//�r���{�[�h�̂��߂Ɏ�ς̃J�����������Ă���

private:
	static CRenderer *m_Renderer;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CTextureManager *m_pTexManager;
	static CInput *m_pInput;
	static CPhase *m_pPhase;
	static CPhaseChange *m_pPhaseChange;
	static CXFileManager *m_pXFileManager;

	static CJoystick *m_pJoystick;
};



#endif
