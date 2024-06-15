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
		img.Draw(hDC, position.x - sceneX, position.y,					// �����쿡 �׸� ��ġ
					  offsetX * 1.5, offsetY * 1.5,				// �����쿡 �׷��� ũ��(����,����)
					  offsetX * 2 + offsetX * imgIndex, 420,	// �̹��� �󿡼� ������ ��ġ
					  offsetX, offsetY);						// �̹��� �󿡼� ������ ũ��(����,����)
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
