#include "stdafx.h"

void Player::Move()
{
	if (isLeft) {
		position.x -= 7;
		if (position.x <= 0) {
			position.x += 7;
		}
		if (position.x <= leftMax) {
			isFalling = true;
		}
	}
	else if (isRight) {
		position.x += 7;
		if (position.x + imgWidth >= 1070) {
			position.x -= 7;
		}
		if (position.x + imgWidth >= rightMax) {
			isFalling = true;
		}
	}
	if (isJump) {
		if (jumpTime < jumpCoolTime) {
			position.y -= 12;
			jumpTime += 1;
		}
		else {
			position.y += 12;
			jumpTime += 1;

			if (jumpTime >= jumpCoolTime * 2) {
				isJump = false;
				jumpTime = 0;
				jumpCoolTime = 10;
				if (dir == LEFT) {
					animIndex = 0;
				}
				else {
					animIndex = 1;
				}
			}
		}
	}
}

void Player::PlayAnimation()
{
	imgCoolTime++;
	if (imgCoolTime == 3) {
		imgIndex++;
		if (imgIndex == imgFrameW) {
			imgIndex = 0;
		}
		imgCoolTime = 0;
	}
}

void Player::CheckWithWall(Obstacle o)
{
	switch (o.type)
	{
	case WALL_BOTTOM: {
		isFalling = true;
		isJump = false;
		jumpTime = 0;
		jumpCoolTime = 10;
		if (dir == LEFT) {
			animIndex = 0;
		}
		else {
			animIndex = 1;
		}
		break;
	}
	case WALL_TOP: {
		position.y = o.size.top - imgHeight;
		isFalling = false;
		leftMax = o.size.left;
		rightMax = o.size.right;
		break;
	}
	case WALL_RIGHT: {
		position.x = o.size.left - imgWidth;
	}
	}
}

void Player::CheckFloor()
{
	if(isFalling)
	{
		position.y += 9;
	}
}
