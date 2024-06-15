#pragma once
class Player
{
public:
	CImage img;				// image
	int imgWidth;			// image width
	int imgHeight;			// image height

	int imgIndex = 0;		// image index
	int animIndex = 1;		// animation index  
							// 0: left walk 1: right walk 2: left jump 3: right jump
	int imgCoolTime = 0;
	
	int imgFrameW = 0;		// image index max value
	int imgFrameH = 0;		// animation index max value

	POINT position = {0, 0};
	DIRECTION dir = RIGHT;

	int leftMax = 0;
	int rightMax = 1070;
public:
	bool isJump;
	int jumpTime;
	int jumpCoolTime = 10;

	bool isLeft;
	bool isRight;

	bool isFalling;

public:
	void Move();
	void PlayAnimation();
	void CheckWithWall(Obstacle o);
	void CheckFloor();
};

