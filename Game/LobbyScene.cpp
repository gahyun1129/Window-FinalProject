#include "stdafx.h"

extern GameFramework Framework;

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init()
{
}

void LobbyScene::Update(const float frameTime)
{
}

void LobbyScene::Draw(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(100, 100, 100));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, 200, 175, 900, 375);
	HFONT hFont, oldFont;
	hFont = CreateFont(
		100,                   // ����
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
	SetBkColor(hDC, RGB(100, 100, 100));
	wsprintf(modeTxt, L"INVERSUS");
	TextOut(hDC, 330, 235, modeTxt, lstrlen(modeTxt));

	DeleteObject(hFont);
	hFont = CreateFont(
		50,                   // ����
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

	SelectObject(hDC, hFont);

	DeleteObject(hBrush);
	hBrush = CreateSolidBrush(RGB(100, 120, 150));
	SelectObject(hDC, hBrush);
	Rectangle(hDC, 300, 450, 800, 550);
	SetBkColor(hDC, RGB(100, 120, 150));
	TextOut(hDC, 450, 475, L"Easy Mode", lstrlen(L"Easy Mode"));

	DeleteObject(hBrush);
	hBrush = CreateSolidBrush(RGB(150, 150, 110));
	SelectObject(hDC, hBrush);
	Rectangle(hDC, 300, 575, 800, 675);
	SetBkColor(hDC, RGB(150, 150, 110));
	TextOut(hDC, 425, 600, L"Normal Mode", lstrlen(L"Normal Mode"));

	DeleteObject(hBrush);
	hBrush = CreateSolidBrush(RGB(150, 100, 100));
	SelectObject(hDC, hBrush);
	Rectangle(hDC, 300, 700, 800, 800);
	SetBkColor(hDC, RGB(150, 100, 100));
	TextOut(hDC, 450, 725, L"Hard Mode", lstrlen(L"Hard Mode"));

	SelectObject(hDC, oldFont);

	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);
	DeleteObject(hFont);

}

void LobbyScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_E) {
			Scene* scene = Framework.CurScene;   // ���� ���� tmp�� �ְ� ������
			Framework.CurScene = new EasyGameScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = EASY;
			delete scene;
		}
		if (wParam == VK_B) {
			Scene* scene = Framework.CurScene;   // ���� ���� tmp�� �ְ� ������
			Framework.CurScene = new BossGameScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = HARD;
			delete scene;
		}
		if (wParam == VK_H) {
			Scene* scene = Framework.CurScene;   // ���� ���� tmp�� �ְ� ������
			Framework.CurScene = new HardGameScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = NORMAL;
			delete scene;
		}
		break;
	}
	case WM_LBUTTONDOWN: {
		int mx = LOWORD(lParam); //--- ���콺 ��ǥ��: (mx, my)
		int my = HIWORD(lParam);

		break;
	}
	}
}

