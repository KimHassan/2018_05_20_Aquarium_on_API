#ifndef _MAIN_PROC_H_
#define _MAIN_PROC_H_

#include <windows.h>
#include <math.h>
#include "stdio.h"
class Fish
{
public:
	HBITMAP bit; // ºñÆ®¸Ê ÀÌ¹ÌÁö
	float x;// ÁÂÇ¥
	float y;

	int maxWidth ;
	int maxHeight;
	
	HDC hdc; // dc¿µ¿ª

	int frameX;
	int frameY;

	int maxFrameX;
	int maxFrameY;
	
	float width ;
	float height;

	float moveX; // ÀÌµ¿ÇÒ ÁÂÇ¥
	float moveY;
	float speed;
	float angle;
	bool rev;
	bool attack;
	int count;
	bool dead;
	int start_count;
	HRESULT init(HINSTANCE hInstance, HDC ScreenDC, LPCSTR str, int FrameX, int FrameY, int Width, int Height);

	void start();
	void SwampStart();
	void update();
	void headMove();

		void move();
		void render(HDC MemoryDC, int r, int g, int b); // Ä³¸¯ÅÍ¸¦ Ä¥ÇØÁÜ
		void render(HDC MemoryDC, int r, int g, int b, float scale);
		float getAngle();
	
};

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);

int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam);

int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam);

void Run();

#endif