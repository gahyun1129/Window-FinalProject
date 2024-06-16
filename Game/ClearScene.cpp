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
		30,                   // ����
		0,                    // �ʺ�
		0,                    // ���� ����
		0,                    // �⺻ ���� ����
		FW_BOLD,              // ����
		FALSE,                // �����
		FALSE,                // ����
		FALSE,                // ��Ҽ�
		DEFAULT_CHARSET,      // ���� ����
		OUT_DEFAULT_PRECIS,   // ��� ���е�
		CLIP_DEFAULT_PRECIS,  // Ŭ���� ���е�
		DEFAULT_QUALITY,      // ��� ǰ��
		DEFAULT_PITCH | FF_SWISS,  // �۲ð� ��ġ
		TEXT("Arial"));       // �۲� �̸�

	oldFont = (HFONT)SelectObject(hDC, hFont);

	TCHAR modeTxt[100];
	SetBkColor(hDC, RGB(10, 10, 10));
	SetTextColor(hDC, RGB(255, 255, 255));  // ��� �ؽ�Ʈ
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
			Scene* scene = Framework.CurScene;   // ���� ���� tmp�� �ְ� ������
			Framework.CurScene = new LobbyScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = LOBBY;
			delete scene;
		}
		break;
	}
	case WM_LBUTTONDOWN: {
		int mx = LOWORD(lParam); //--- ���콺 ��ǥ��: (mx, my)
		int my = HIWORD(lParam);

		break;
	}
	case WM_KEYUP:
	{
		
		break;
	}
	}
}
