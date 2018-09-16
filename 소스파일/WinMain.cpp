#include <windows.h>
#include "System.h"
#include "MainProc.h"

#define TEXT	"Sprite"

HWND g_hWnd;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		return OnCreate(hWnd, wParam, lParam);

	case WM_TIMER:
		return OnTimer(hWnd, wParam, lParam);

	case WM_MOUSEMOVE:
		return OnMouseMove(hWnd, wParam, lParam);

	case WM_CLOSE:
	case WM_DESTROY:
		return OnDestroy(hWnd, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	RECT rtSystemSize = {0, 0, WIDTH, HEIGHT};

	WinInit(TEXT);

	g_hWnd = WinCreate(TEXT, TEXT, hInst, WS_OVERLAPPEDWINDOW, rtSystemSize);

	return GameLoop();
}