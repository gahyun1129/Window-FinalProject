#include "stdafx.h"

void Player::Move()
{
	if (isLeft) {
		position.x -= 7;
		if (position.x <= 20) {
			position.x += 7;
		}
		if (position.x <= leftMax) {
			isFlying = false;
			isFalling = true;
			if (dir == LEFT) {
				animIndex = 0;
			}
			else {
				animIndex = 1;
			}
		}
	}
	else if (isRight) {
		position.x += 7;
		if (position.x + imgWidth >= 1070) {
			position.x -= 7;
		}
		if (position.x + imgWidth >= rightMax) {
			isFlying = false;
			isFalling = true;
			if (dir == LEFT) {
				animIndex = 0;
			}
			else {
				animIndex = 1;
			}
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

void Player::CheckWithWall(Obstacle& o)
{
	switch (o.type)
	{
	case WALL_BOTTOM: {
		isFalling = true;
		isFlying = false;
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
		break;
	}
	case WALL_LEFT: {
		position.x = o.size.right;
		break;
	}
	case MARIO: {
		if (type == LUIGI) {
			position = spawnPoint;
		}
		break;
	}	
	case LUIGI: {
		if (type == MARIO) {
			position = spawnPoint;
		}
		break;
	}
	case BOTH: {
		position = spawnPoint;
		break;
	}
	case SWITCHSTICK: {
		if (dir == LEFT && o.index == 0) {
			o.index = 1;
		}
		if (dir == RIGHT && o.index == 1) {
			o.index = 0;
		}
		break;
	}
	case MARIO_END: {
		if (type == MARIO) {
			isEnd = true;
		}
		break;
	}
	case LUIGI_END: {
		if (type == LUIGI) {
			isEnd = true;
		}
		break;
	}
	case JUMPSTEP: {
		isFlying = true;
		leftMax = o.size.left;
		rightMax = o.size.right;
		if (dir == LEFT) {
			animIndex = 2;
		}
		else {
			animIndex = 3;
		}
		break;
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

void Player::Flying()
{
	if (isFlying) {
		position.y -= 9;
	}
}


