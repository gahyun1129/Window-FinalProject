#include "stdafx.h"

void Boss::Jump()
{
	if (isJumping)
	{
		if (position.y > jumpStartPos.y - jumpSpeed * 10 && jumpUp)
			position.y -= jumpSpeed;
		else
		{
			jumpUp = false;

			if (position.y <= jumpStartPos.y - jumpSpeed && !jumpUp)
				position.y += jumpSpeed;
			else
				isJumping = false;
		}
	}
}

void Boss::SetDirection(const POINT towardPosition)
{
	if (position.x < towardPosition.x)
	{
		dir = RIGHT;
	}
	else if (position.x >= towardPosition.x)
	{
		dir = LEFT;
	}
}

void Boss::MoveTo(const POINT whereToMove)
{
	if (position.x < whereToMove.x - 100 || position.x > whereToMove.x + 200)
	{
		if (dir == RIGHT) {
			position.x += velocityX;
		}
		else {
			position.x -= velocityX;
		}

		if (imgIndex == 0) {
			imgIndex = 1;
		}
		else {
			imgIndex = 0;
		}
	}
}

void Boss::Draw(HDC hDC, int sceneX)
{
	if (dir == LEFT) {
		img.Draw(hDC, position.x - sceneX, position.y,					// 윈도우에 그릴 위치
					  offsetX * 1.5, offsetY * 1.5,				// 윈도우에 그려질 크기(가로,세로)
					  offsetX * 2 + offsetX * imgIndex, 420,	// 이미지 상에서 가져올 위치
					  offsetX, offsetY);						// 이미지 상에서 가져올 크기(가로,세로)
	}
	else {
		img.Draw(hDC, position.x - sceneX, position.y,
					  offsetX * 1.5, offsetY * 1.5,
					  offsetX * 4 + offsetX * imgIndex, 420,
					  offsetX, offsetY);
	}
}

void Boss::DyingUpdate()
{
	if (position.y >= 0) {
		vy += GRAVITY;
		position.y += vy;
	}
}
