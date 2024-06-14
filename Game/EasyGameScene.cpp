#include "stdafx.h"

extern GameFramework Framework;

EasyGameScene::~EasyGameScene()
{
	delete(mario);
	delete(luigi);
}

void EasyGameScene::Init()
{
	backgroud.Load(L"Image/Background.png");

	mario = new Player;
	luigi = new Player;

	mario->img.Load(L"Image/BigMario.png");
	luigi->img.Load(L"Image/Luigi.png");

	mario->imgFrameW = 8;
	luigi->imgFrameW = 8;

	mario->imgFrameH = 4;
	luigi->imgFrameH = 4;

	mario->imgWidth = mario->img.GetWidth() / mario->imgFrameW;
	mario->imgHeight = mario->img.GetHeight() / mario->imgFrameH;

	luigi->imgWidth = luigi->img.GetWidth() / luigi->imgFrameW;
	luigi->imgHeight = luigi->img.GetHeight() / luigi->imgFrameH;
}

void EasyGameScene::Update(const float frameTime)
{
	mario->imgIndex += 1;
	if (mario->imgIndex == mario->imgFrameW) {
		mario->imgIndex = 0;
	}
	if (mario->isJump) {
		if (mario->jumpTime < 10) {
			mario->position.y -= 10;
			mario->jumpTime += 1;
		}
		else {
			mario->position.y += 10;
			mario->jumpTime += 1;

			if (mario->jumpTime == 20) {
				mario->isJump = false;
				mario->jumpTime = 0;
			}
		}
	}
	if (luigi->isJump) {
		if (luigi->jumpTime < 10) {
			luigi->position.y -= 10;
			luigi->jumpTime += 1;
		}
		else {
			luigi->position.y += 10;
			luigi->jumpTime += 1;

			if (luigi->jumpTime == 20) {
				luigi->isJump = false;
				luigi->jumpTime = 0;
			}
		}
	}
}

void EasyGameScene::Draw(HDC hDC)
{
	backgroud.Draw(hDC, 0, 0, Framework.size.right, Framework.size.bottom, 0, 0, 800, 600);
	mario->img.Draw(hDC, mario->position.x + 100, mario->position.y, 
						mario->imgWidth, mario->imgHeight, 
						mario->imgWidth * mario->imgIndex, mario->imgHeight * mario->amimIndex,
						mario->imgWidth, mario->imgHeight);
	luigi->img.Draw(hDC, luigi->position.x, luigi->position.y,
		luigi->imgWidth, luigi->imgHeight,
		luigi->imgWidth * luigi->imgIndex, luigi->imgHeight * luigi->amimIndex,
		luigi->imgWidth, luigi->imgHeight);
}

void EasyGameScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_W) {
			mario->isJump = true;
		}
		else if (wParam == VK_A) {
			mario->position.x -= 5;
			if (mario->position.x <= 0) {
				mario->position.x += 5;
			}
		}
		else if (wParam == VK_D) {
			mario->position.x += 5;
			if (mario->position.x + 64 >= 1100) {
				mario->position.x -= 5;
			}
		}
		else if (wParam == VK_LEFT) {
			luigi->position.x -= 5;
			if (luigi->position.x <= 0) {
				luigi->position.x += 5;
			}
		}
		else if (wParam == VK_RIGHT) {
			luigi->position.x += 5;
			if (luigi->position.x + 64 >= 1100) {
				luigi->position.x -= 5;
			}
		}
		else if (wParam == VK_UP) {
			luigi->isJump = true;
		}
		break;
	}
	case WM_LBUTTONDOWN: {
		int mx = LOWORD(lParam); //--- 마우스 좌표값: (mx, my)
		int my = HIWORD(lParam);

		break;
	}
	}
}
