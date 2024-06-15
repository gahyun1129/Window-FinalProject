#include "stdafx.h"

void Ray::Draw(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	hBrush = CreateSolidBrush(RGB(255, 255, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	Rectangle(hDC, positionX - width - 2, 0, positionX + width + 2, 750);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	Rectangle(hDC, positionX - width, 0, positionX + width, 750);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}
