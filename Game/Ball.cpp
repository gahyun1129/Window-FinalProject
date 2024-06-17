#include "stdafx.h"

extern GameFramework Framework;

void Ball::Init(const POINT pos, const DIRECTION dir, const int currTime, const string name)
{
    playerName = name;
	position.x = pos.x;
	position.y = pos.y;
	if (dir == LEFT) {
		vx = -10;
	}
	else {
		vx = 10;
	}
	vy = -10;
    startTime = currTime;
    if (name == "mario")
        color = RGB(255, 102, 0);
    else if (name == "luigi")
        color = RGB(0, 204, 51);
}

void Ball::Update()
{
    // �߷� ����
    vy += GRAVITY;

    // ��ġ ������Ʈ
    position.x += vx;
    position.y += vy;

    // �ٿ ó��
    if (position.y > 750) {
        position.y = 750;
        vy *= -BOUNCE_FACTOR;
    }

    if (position.x > Framework.size.right + Framework.mainCamera->pos.x) {
        position.x = Framework.size.right + Framework.mainCamera->pos.x;
        vx *= -BOUNCE_FACTOR;
    }

    if (position.x < 0) {
        position.x = 0;
        vx *= -BOUNCE_FACTOR;
    }

    if (position.y < 0) {
        position.y = 0;
        vy *= -BOUNCE_FACTOR;
    }
}

void Ball::Draw(HDC hDC, int sceneX)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	hBrush = CreateSolidBrush(color);
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, color);
	oldPen = (HPEN)SelectObject(hDC, hPen);
	Ellipse(hDC, position.x - sceneX - halfSize, position.y - halfSize, position.x - sceneX + halfSize, position.y + halfSize);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}
