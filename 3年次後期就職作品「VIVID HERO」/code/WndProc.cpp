//◇-------------------------------------------------------------------------◇
//
//	File:classnameのファイル[classname.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "Renderer.h"

//◇----------------------------------◇
//ウィンドウプロシージャ
//◇----------------------------------◇
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
							"終了しますか？",
							"GAME END",
							MB_YESNO);
			if(nID == IDYES)
			{
				DestroyWindow(hWnd);
				break;
			}
		}
	case WM_SYSKEYDOWN:     // Alt + 特殊キーの処理に使う
		switch(wParam)
		{
			case VK_RETURN:     // Alt + Enterを押すと切り替え
			break;
		}
	default:
		break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
