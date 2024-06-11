#include "stdafx.h"

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

	p1->dir = RIGHT;
}

void EasyGameScene::Update(const float frameTime)
{
}

void EasyGameScene::Draw(HDC hDC)
{
	if (p1->dir == LEFT) {
		p1->img.Draw(hDC, 10, 10, p1->offset, 64, p1->imgIndex, 0, p1->offset, 64);
	}
	else {
		p1->img.Draw(hDC, 10, 10, p1->offset, 64, p1->offset * 13 - p1->imgIndex, 0, p1->offset, 64);
	}
	// p2->img.Draw(hDC, 10, 10, 810 / 14, 64, 0, 0, 810 / 14, 64);
}

void EasyGameScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		break;
	}
	case WM_LBUTTONDOWN: {
		int mx = LOWORD(lParam); //--- 마우스 좌표값: (mx, my)
		int my = HIWORD(lParam);

		break;
	}
	}
}
