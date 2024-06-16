#include "stdafx.h"

extern GameFramework Framework;

ClearScene::~ClearScene()
{
}

void ClearScene::Init()
{
	EndingImage.Load(L"Image/gameclear.png");
}

void ClearScene::Update(const float frameTime)
{
}

void ClearScene::Draw(HDC hDC)
{
	//// Scene ////
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	hBrush = CreateSolidBrush(RGB(10, 10, 10));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(10, 10, 10));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	Rectangle(hDC, Framework.size.left, Framework.size.top, Framework.size.right, Framework.size.bottom);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	EndingImage.Draw(hDC, (Framework.size.right - Framework.size.bottom) / 2, 0, Framework.size.bottom, Framework.size.bottom, 0, 0, 500, 500);

	HFONT hFont, oldFont;
	hFont = CreateFont(
		30,                   // 높이
		0,                    // 너비
		0,                    // 기울기 각도
		0,                    // 기본 방향 각도
		FW_BOLD,              // 굵기
		FALSE,                // 기울임
		FALSE,                // 밑줄
		FALSE,                // 취소선
		DEFAULT_CHARSET,      // 문자 집합
		OUT_DEFAULT_PRECIS,   // 출력 정밀도
		CLIP_DEFAULT_PRECIS,  // 클리핑 정밀도
		DEFAULT_QUALITY,      // 출력 품질
		DEFAULT_PITCH | FF_SWISS,  // 글꼴과 피치
		TEXT("Arial"));       // 글꼴 이름

	oldFont = (HFONT)SelectObject(hDC, hFont);

	TCHAR modeTxt[100];
	SetBkColor(hDC, RGB(10, 10, 10));
	SetTextColor(hDC, RGB(255, 255, 255));  // 흰색 텍스트
	wsprintf(modeTxt, L"Press 'R' to restart");

	SIZE textSize;
	GetTextExtentPoint32(hDC, modeTxt, lstrlen(modeTxt), &textSize);

	int x = (Framework.size.right - textSize.cx) / 2;
	int y = (Framework.size.bottom - textSize.cy) / 4 * 3;

	TextOut(hDC, x, y, modeTxt, lstrlen(modeTxt));

	DeleteObject(hFont);
}

void ClearScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_R) {
			Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
			Framework.CurScene = new LobbyScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = LOBBY;
			delete scene;
		}
		break;
	}
	case WM_LBUTTONDOWN: {
		int mx = LOWORD(lParam); //--- 마우스 좌표값: (mx, my)
		int my = HIWORD(lParam);

		break;
	}
	case WM_KEYUP:
	{
		
		break;
	}
	}
}
