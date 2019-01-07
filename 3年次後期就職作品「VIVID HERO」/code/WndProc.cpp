//��-------------------------------------------------------------------------��
//
//	File:classname�̃t�@�C��[classname.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "Renderer.h"

//��----------------------------------��
//�E�B���h�E�v���V�[�W��
//��----------------------------------��
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int nID;

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
			break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(NULL,
							"�I�����܂����H",
							"GAME END",
							MB_YESNO);
			if(nID == IDYES)
			{
				DestroyWindow(hWnd);
				break;
			}
		}
	case WM_SYSKEYDOWN:     // Alt + ����L�[�̏����Ɏg��
		switch(wParam)
		{
			case VK_RETURN:     // Alt + Enter�������Ɛ؂�ւ�
			break;
		}
	default:
		break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
