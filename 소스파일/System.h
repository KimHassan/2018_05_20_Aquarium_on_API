#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <windows.h>

#define	WIDTH	640
#define	HEIGHT	480

BOOL WinInit(char* pWinName);

HWND WinCreate(char* pClassName, char* pWindowName, HINSTANCE hInst, int nWindowStyle, RECT rtWindowSize);

VOID MsgLoop();

int GameLoop();


#endif