
//��-------------------------------------------------------------------------��
//
//	File:�f�o�b�O���b�N�̃t�@�C��[CDebugProc.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CDebugProc.h"
#include<vector>

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��
LPD3DXFONT CDebugProc::m_D3DXFont = NULL;
char CDebugProc::m_aStr[] = {NULL};

std::string g_strMoji;

//��-----------------------------------��
//�f�o�b�O���b�N�̃R���X�g���N�^
//��-----------------------------------��
CDebugProc::CDebugProc()
{

}

//��-----------------------------------��
//�f�o�b�O���b�N�̃f�X�g���N�^
//��-----------------------------------��
CDebugProc::~CDebugProc()
{

}

//��-----------------------------------��
//�f�o�b�O���b�N�̏���������
//��-----------------------------------��
HRESULT CDebugProc::Init(void)
{
#ifndef _DEBUG_

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	D3DXCreateFont(pDevice,18,0,FW_ULTRALIGHT,NULL,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Terminal",&m_D3DXFont);
	
#endif
	return S_OK;
}

//��-----------------------------------��
//�f�o�b�O���b�N�̏I������
//��-----------------------------------��
void CDebugProc::Uninit(void)
{
	if(m_D3DXFont != NULL)
	{
		m_D3DXFont -> Release();
		m_D3DXFont = NULL;
	}
}

//��-----------------------------------��
//�f�o�b�O���b�N�̍X�V����
//��-----------------------------------��
void CDebugProc::Update(void)
{

}

//��-----------------------------------��
//�f�o�b�O���b�N�̕`�揈��
//��-----------------------------------��
void CDebugProc::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

#ifdef _DEBUG
	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

	//�e�L�X�g�̕`��
	m_D3DXFont->DrawText(NULL,g_strMoji.c_str(),-1,&rect,DT_LEFT,D3DCOLOR_RGBA(255,255,255,255));
#endif

	std::string a;
	g_strMoji = a;
}

//��-----------------------------------��
//�f�o�b�O���b�N�̃v�����g����
//
//fmt : �\�������������A�ϊ������Ȃ�
//%d�Ő��l��9���܂ł����\���ł��܂���
//
//��-----------------------------------��
void CDebugProc::Print(const char *fmt,...)
{
#ifdef _DEBUG

	//���X�g�̊J�n
	va_list list;

	int i;
	char *cp;			//fmt������

	double x_float;
	int x_int;
	char *c_char;

	char c[256];		//256�����܂łȂ牽�Ƃ��ł���

	va_start(list,fmt);

	//fmt�̐����Ԃ�������
	for(cp = (char *)fmt,i = 0;*cp != '\0';cp++,i++)
	{
		if(*cp == '%')
		{
			switch(*(cp + 1))
			{
			case 's':
				c_char = va_arg(list,char*);	//�ψ����̕���������
				g_strMoji += c_char;

				break;

			case 'd':
				x_int = va_arg(list,int);
				_itoa(x_int,c,10);

				g_strMoji += c;
				cp++;

				break;

			case 'f':
				x_float = va_arg(list,double);
				_gcvt(x_float,6,c);

				g_strMoji += c;
				cp++;

				break;
			}
		}
		else
		{
			g_strMoji += *cp;
		}
	}




	va_end(list);

#endif
}




