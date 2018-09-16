#include "MainProc.h"
#include "System.h"
#include "stdio.h"
#include <time.h>
extern BOOL bIsActive;

HDC ScreenDC;
HDC MemoryDC;

HBITMAP hBM;
HDC BackgroundDC;
HBITMAP hbmBackground;

Fish Character[5];
Fish Big[3];
Fish Swamp;
Fish Head;
HDC CharacterDC;
HDC CharacterDC2;
HDC CharacterDC3;
HDC CharacterDC4;
HDC CharacterDC5;

HBITMAP hbmCharacter;

HBITMAP hbmCharacter2;

HBITMAP hbmCharacter3;

HBITMAP hbmCharacter4;

HBITMAP hbmCharacter5;
POINT ptMouse;
int nFPS;
int nCount;


bool Atk;
HRESULT Fish::init(HINSTANCE hInstance,HDC ScreenDC, LPCSTR str,int FrameX,int FrameY, int Width, int Height)
{
	bit = (HBITMAP)LoadImage(hInstance, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hdc = CreateCompatibleDC(ScreenDC);
	SelectObject(hdc, bit);


	frameX = 0;
	frameY = 0;

	maxFrameX = FrameX;
	maxFrameX = FrameY;

	maxWidth = Width;
	maxHeight = Height;

	width  = Width / FrameX;
	height = Height / FrameY;

	dead = false;
	count = 0;
	return S_OK;
}

void Fish::SwampStart()
{
	count++;
	if (count % 50==0)
	{
		frameX--;
		
	}
}
void Fish::start()
{
	count++;
	if (count < start_count)
	{
		frameX = -1;
	}
	else
	{
		if (count % 50 == 0)
		{
			frameX++;
			x += 5;

		}
	}
}
void Fish::update()
{
	count++;
	if (count % 100 == 0) // FRAME 변경
	{
		
		
		if (frameY == 3)
		{
			frameX--;
			if (frameX <= 0)
			{
				frameY = 0;
			}

		}
		else
		{
			frameX++;
			if (frameX > maxFrameX)
			{
				frameX = 0;
			}
			if (frameY == 1)
			{
				if (frameX >= maxFrameX)
				{
					frameY = 2;
				}

			}
		}
	}
	move();
}


void Fish::move()
{
	x += cosf(angle) * 0.1;
	y += -sinf(angle) * 0.1;

	float PI = 3.141592654f;
	if ((frameY == 0) || (frameY == 2))
	{
		if (angle > PI / 2 && angle < PI / 2 * 3)
		{
			frameY = 0;
		}
		else
		{
			frameY = 2;
		}
	}

	if (x > 560)
	{
		//x = 100;
		//y = 100;
		float PI = 3.141592654f;
		if (angle >= PI)
		{
			angle = angle - PI / 2;
		}
		if (angle <= PI)
		{
			angle = PI / 2 + angle;
		}
		frameY = 3;
		frameX = maxFrameX - 1;


	}
	if (x < 0)
	{

		float PI = 3.141592654f;
		if (angle >= PI)
		{
			angle = PI / 2 - angle;

		}
		if (angle <= PI)
		{
			angle = PI / 2 + angle;
		}

		frameY = 1;
		frameX = 0;
	}
	if (y > 400)
	{
		float PI = 3.141592654f;
		if (angle >= PI)
		{
			angle = PI / 2 - angle;
	
		}
		if (angle <= PI) // ↘↗
		{
			angle = PI / 2 + angle;

		}

	}
	if (y < 0)
	{
		float PI = 3.141592654f;
		if (angle >= PI)//↖↙
		{
			angle = PI / 2 - angle;
			frameY = 0;
		}
		if (angle <= PI)
		{
			angle = PI / 2 + angle;

		}
	}


}
void Fish::headMove()
{
	count++;

	if (count > 200)
	{
		float PI = 3.141592654f;
		if (y < 100)
		{
			attack = true;

		}
		if (attack == false)
		{
			angle = PI / 4;
			frameX = 0;
		}
		else
		{
			angle = PI / 4 * 7;
			frameX = 1;
		}
		x += cosf(angle) * 1;
		y += -sinf(angle) * 1;
	}
	else
	{
		frameX = -1;
	}
}
void Fish::render(HDC MemoryDC, int r, int g, int b) // 캐릭터를 칠해줌
{
	if (dead)
	{
	}
	else
		TransparentBlt(MemoryDC, x, y, width, height, hdc, frameX * width, frameY * height, width, height, RGB(r, g, b));

	//char ch[128];
	//sprintf(ch, "%f/%f", x,y);
	//TextOut(MemoryDC, x, y, ch, strlen(ch));
}

void Fish::render(HDC MemoryDC, int r, int g, int b, float scale)
{
	TransparentBlt(MemoryDC, x, y, width * scale, height * scale, hdc, frameX * width, frameY * height, width, height, RGB(r, g, b));
}

float Fish::getAngle()
{
	float aX = moveX - x;
	float aY = moveY - y;

	float distance = sqrtf(aX * aX + aY * aY);

	float angle = acosf(aX / distance);

	float PI2 = 3.141592654f * 2;// 360

	if (moveY > y)
	{
		angle = PI2 - angle;

		if (angle >= PI2) angle -= PI2;
	}

	return angle;
}



int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	ScreenDC = GetDC(hWnd);

	MemoryDC = CreateCompatibleDC(ScreenDC);
	hBM = CreateCompatibleBitmap(ScreenDC, WIDTH, HEIGHT);
	SelectObject(MemoryDC, hBM);

	BackgroundDC = CreateCompatibleDC(ScreenDC); // DC를 받아온다
	hbmBackground = (HBITMAP)LoadImage(hInstance, "Background.bmp",IMAGE_BITMAP, 0,0,LR_LOADFROMFILE); // 이미지를 불러온다
	SelectObject(BackgroundDC, hbmBackground); // DC에 추가한다

	srand((unsigned int)time(NULL));

	Character[0].init(hInstance,ScreenDC, "6.bmp", 10, 4, 800, 320);
	Character[1].init(hInstance,ScreenDC, "7.bmp", 10, 4, 800, 320);
	Character[2].init(hInstance,ScreenDC, "8.bmp", 10, 4, 800, 320);
	Character[3].init(hInstance,ScreenDC, "9.bmp", 10, 4, 800, 320);
	Character[4].init(hInstance,ScreenDC, "5.bmp", 10, 4, 800, 320);

	//Big[0].init(hInstance, ScreenDC, "b_bottom.bmp", 17, 1, 5695, 151);


	Swamp.init(hInstance, ScreenDC, "b_bottom.bmp", 17, 1, 5695, 151);
	Swamp.x = 0;
	Swamp.y = 300;
	Swamp.frameX = 17;
	for (int i = 0; i < 3; i++)
	{
		Big[i].init(hInstance, ScreenDC, "b_under.bmp", 8, 1, 1160, 188);
		Big[i].count = 0;
		Big[i].start_count = i * 100 + 200;
		Big[i].x = 150 + i * 100;
		Big[i].y = 480 - Big[i].height - 40;
	}
	Big[3].start_count = 350;

	Head.init(hInstance, ScreenDC, "head.bmp", 2, 1, 788, 251);
	Head.attack = false;
	Head.x = -100;
	Head.y = 200;
	Head.count = 0;

	bIsActive = true;

	SetTimer(hWnd, 0, 1000, NULL);

	for (int i = 0; i < 5; i++)
	{
		Character[i].x = i* 100;
		Character[i].y = i * 100;
		Character[i].moveX = rand() % WIDTH;
		Character[i].moveY = rand() % HEIGHT;
		Character[i].speed = 0.1;
		Character[i].angle = Character[i].getAngle();
		Character[i].rev = false;
		Character[i].count = 0;
		float PI = 3.141592654f;
		if (Character[i].angle > PI / 2 && Character[i].angle < PI / 2 * 3)
		{
			Character[i].frameY = 0;
		}
		else
		{
			Character[i].frameY = 2;
		}
	}
	Atk = false;
	return 1;
}

int OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	nFPS = nCount;
	nCount = 0;

	return 1;
}

int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	ptMouse.x = LOWORD(lParam);
	ptMouse.y = HIWORD(lParam);

	return 1;
}

int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	DeleteObject(hbmCharacter);
	DeleteObject(hbmBackground);
	DeleteObject(hBM);
	DeleteDC(CharacterDC);
	DeleteDC(BackgroundDC);
	DeleteDC(MemoryDC);
	DeleteDC(ScreenDC);

	bIsActive = false;

	PostQuitMessage(0);

	return 1;
}

#pragma comment (lib, "Msimg32.lib")

void Run()
{
	char strBuffer[16];
	RECT rtImg = {0, 0, 640, 480};

	BitBlt(MemoryDC, rtImg.left, rtImg.top, rtImg.right, rtImg.bottom, BackgroundDC, 0, 0, SRCCOPY);
	SetBkMode(MemoryDC, TRANSPARENT);
	char str[128];
	sprintf(str, "물고기가 싫으시다면 SPACE를 누르세요");
	TextOut(MemoryDC, 150, 70, str, strlen(str));
	if (GetAsyncKeyState(VK_SPACE))
	{
		
		Swamp.x = 0;
		Swamp.y = 300;
		Swamp.frameX = 17;
		for (int i = 0; i < 3; i++)
		{
			Big[i].count = 0;
			Big[i].start_count = i * 100 + 200;
			Big[i].x = 150 + i * 100;
			Big[i].y = 480 - Big[i].height - 40;
		}
		Big[3].start_count = 350;
		Head.attack = false;
		Head.x = -100;
		Head.y = 200;
		Head.count = 0;
		Atk = true;
	}
	if (Atk == true)
	{
		Swamp.SwampStart();
		Swamp.render(MemoryDC, 255, 255, 255, 2);
	}
	for (int i = 0; i < 5; i++)
	{
		Character[i].update();

		Character[i].render(MemoryDC, 0, 0, 0);

		
	}
	if(Atk == true)
	{
		if (Head.y < 200)
		{
			for (int i = 0; i < 5; i++)
			{

				if (Character[i].y > 200)
				{
					Character[i].dead = true;
				}

			}
		}
		Head.headMove();
		Head.render(MemoryDC, 255, 255, 255, 1.5);

		for (int i = 0; i < 3; i++)
		{
			Big[i].start();
			Big[i].render(MemoryDC, 255, 255, 255);
		}
	}
	if (Head.y > 500)
	{
		Atk = false;
	}

	sprintf(strBuffer, "FPS = %3d", nFPS);
	TextOut(MemoryDC, 0, 0, strBuffer, strlen(strBuffer)); 
	if (Atk)
	{
		if(nCount %2==0)
			BitBlt(ScreenDC, -10, 0, WIDTH, HEIGHT, MemoryDC, 0, 0, SRCCOPY);
		else
			BitBlt(ScreenDC, 10, 0, WIDTH, HEIGHT, MemoryDC, 0, 0, SRCCOPY);
	}
	else
	{
		BitBlt(ScreenDC, 0, 0, WIDTH, HEIGHT, MemoryDC, 0, 0, SRCCOPY);
	}
	nCount++;


}

