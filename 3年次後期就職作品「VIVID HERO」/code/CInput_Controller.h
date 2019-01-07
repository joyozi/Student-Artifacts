//��-------------------------------------------------------------------------��
//
//	File:CInput_Controller�̃w�b�_�[�t�@�C��[CInput_Controller.h]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��
#ifndef _CINPUTCONTROLLER_H_
#define _CINPUTCONTROLLER_H_

//��-----------------------------------��
//�C���N���[�h�t�@�C��
//��-----------------------------------��
#include "main.h"

//��-----------------------------------��
//�N���X�݌v
//��-----------------------------------��
class CInput_Controller
{
public:
	CInput_Controller();
	virtual ~CInput_Controller();

	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	
	BOOL CALLBACK EnumJoyCallback( const DIDEVICEINSTANCE* pdidInstance,VOID* pContext);

private:
	LPDIRECTINPUT8 g_pDInput;				//DirectInput�C���^�t�F�[�X�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 g_pDIDevController;	//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^


};


#endif
