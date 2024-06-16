#include "stdafx.h"

extern GameFramework Framework;

LobbyScene::~LobbyScene()
{
	delete(p1);
}

void LobbyScene::Init()
{
	background.Load(L"Image/lobby.png");
	titleText.Load(L"Image/text.png");

	p1 = new Player;

	p1->img.Load(L"Image/BigMario.png");

	p1->imgFrameW = 8;

	p1->imgWidth = p1->img.GetWidth() / p1->imgFrameW;

	p1->position = { 50, 680 };
}

void LobbyScene::Update(const float frameTime)
{
	title_coolTime++;
	if (title_coolTime == 3) {
		title_coolTime = 0;
		if (title_index == 0) {
			title_index = 1;
		}
		else {
			title_index = 0;
		}
	}

	p1->imgIndex++;
	if (p1->imgIndex == p1->imgFrameW) {
		p1->imgIndex = 0;
	}
	p1->position.x += 10;
	if (p1->position.x >= 1000) {
		p1->position.x = 50;
	}
}

void LobbyScene::Draw(HDC hDC)
{
	HBRUSH hBrush, oldBrush;

	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC, 0, 0, Framework.size.right, Framework.size.bottom);
	background.Draw(hDC, 40, 30, 1000, 800, 0, 0, 800, 600);

	titleText.Draw(hDC, 500, 40, 545, 227, 545 * title_index, 0, 545, 227);

	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);

	p1->img.Draw(hDC, p1->position.x, p1->position.y,
		p1->imgWidth, 64,
		p1->imgWidth * p1->imgIndex, 64,
		p1->imgWidth, 64);
}

void LobbyScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_E) {
			Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
			Framework.CurScene = new EasyGameScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = EASY;
			delete scene;
		}
		if (wParam == VK_B) {
			Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
			Framework.CurScene = new BossGameScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = HARD;
			delete scene;
		}
		if (wParam == VK_H) {
			Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
			Framework.CurScene = new HardGameScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = NORMAL;
			delete scene;
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

