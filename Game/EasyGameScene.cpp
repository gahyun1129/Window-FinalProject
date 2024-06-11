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
}

void EasyGameScene::Update(const float frameTime)
{
}

void EasyGameScene::Draw(HDC hDC)
{
	if (p1->dir == LEFT) {
		p1->img.Draw(hDC, p1->position.x, p1->position.y,  p1->offset, 64, 0, 0, p1->offset, 64);
	}
	else {
		//p1->img.Draw(hDC, 10, 10, p1->offset, 64, p1->offset * 13 - p1->imgIndex, 0, p1->offset, 64);
	}
	p2->img.Draw(hDC, 100, 10, 810 / 14, 64, 0, 0, 810 / 14, 64);
}

void EasyGameScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_W) {
			p1->position.y -= 5;
			if (p1->position.y <= 0) {
				p1->position.y += 5;
			}
		}
		else if (wParam == VK_A) {
			p1->position.x -= 5;
			if (p1->position.x <= 0) {
				p1->position.x += 5;
			}
		}
		else if (wParam == VK_D) {
			p1->position.x += 5;
			if (p1->position.x + p1->offset >= Framework.size.right) {
				p1->position.x -= 5;
			}
		}
		else if (wParam == VK_S) {
			p1->position.y += 5;
			if (p1->position.y + 64 >= 800) {
				p1->position.y -= 5;
			}
		}
		else if (wParam == VK_LEFT) {

		}
		else if (wParam == VK_RIGHT) {

		}
		else if (wParam == VK_UP) {

		}
		else if (wParam == VK_DOWN) {

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
