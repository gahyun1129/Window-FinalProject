#include "stdafx.h"

extern GameFramework Framework;

void Ball::Init(const POINT pos, const DIRECTION dir, const int currTime)
{
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
}

void Ball::Update()
{
    // 중력 적용
    vy += GRAVITY;

    // 위치 업데이트
    position.x += vx;
    position.y += vy;

    // 바운스 처리
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

	hBrush = CreateSolidBrush(RGB(0, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	Ellipse(hDC, position.x - sceneX - halfSize, position.y - halfSize, position.x - sceneX + halfSize, position.y + halfSize);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}
