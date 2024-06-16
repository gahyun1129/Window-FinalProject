#include "stdafx.h"

void FireBall::Draw(HDC hDC, int sceneX)
{
	if (dir == LEFT) {
		img.Draw(hDC, position.x + sceneX, position.y,
					  offsetX, offsetY,
					  200 + offsetX * imgIndex, 500,
					  offsetX, offsetY);
	}
	else {
		img.Draw(hDC, position.x + sceneX, position.y,
					  offsetX, offsetY,
					  320 + offsetX * imgIndex, 500,
					  offsetX, offsetY);
	}
}
