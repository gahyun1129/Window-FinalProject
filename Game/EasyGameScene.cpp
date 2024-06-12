#include "stdafx.h"

extern GameFramework Framework;

EasyGameScene::~EasyGameScene()
{
	delete(p1);
	delete(p2);
}

void EasyGameScene::Init()
{
	p1 = new Player;
	p2 = new Player;

	p1->img.Load(L"Image/BigMario.png");
	p2->img.Load(L"Image/FireMario.png");

	p1->offset = 810 / 14;
	p2->offset = 810 / 14;

	backgroud.Load(L"Image/Background.png");

}

void EasyGameScene::Update(const float frameTime)
{
	if (p1->isJump) {
		if (p1->jumpTime < 10) {
			p1->position.y -= 10;
			p1->jumpTime += 1;
		}
		else {
			p1->position.y += 10;
			p1->jumpTime += 1;

			if (p1->jumpTime == 20) {
				p1->isJump = false;
				p1->jumpTime = 0;
			}
		}
	}
	if (p2->isJump) {
		if (p2->jumpTime < 10) {
			p2->position.y -= 10;
			p2->jumpTime += 1;
		}
		else {
			p2->position.y += 10;
			p2->jumpTime += 1;

			if (p2->jumpTime == 20) {
				p2->isJump = false;
				p2->jumpTime = 0;
			}
		}
	}
}

void EasyGameScene::Draw(HDC hDC)
{
	backgroud.Draw(hDC, 0, 0, Framework.size.right, Framework.size.bottom, 0, 0, 800, 600);

	if (p1->dir == LEFT) {
		p1->img.Draw(hDC, p1->position.x, p1->position.y,  p1->offset, 64, 0, 0, p1->offset, 64);
	}
	else {
		//p1->img.Draw(hDC, 10, 10, p1->offset, 64, p1->offset * 13 - p1->imgIndex, 0, p1->offset, 64);
	}
	p2->img.Draw(hDC, p2->position.x, p2->position.y, 810 / 14, 64, 0, 0, 810 / 14, 64);
}

void EasyGameScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_W) {
			p1->isJump = true;
		}
		else if (wParam == VK_A) {
			p1->position.x -= 5;
			if (p1->position.x <= 0) {
				p1->position.x += 5;
			}
		}
		else if (wParam == VK_D) {
			p1->position.x += 5;
			if (p1->position.x + 64 >= 1100) {
				p1->position.x -= 5;
			}
		}
		else if (wParam == VK_LEFT) {
			p2->position.x -= 5;
			if (p2->position.x <= 0) {
				p2->position.x += 5;
			}
		}
		else if (wParam == VK_RIGHT) {
			p2->position.x += 5;
			if (p2->position.x + 64 >= 1100) {
				p2->position.x -= 5;
			}
		}
		else if (wParam == VK_UP) {
			p2->isJump = true;
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
