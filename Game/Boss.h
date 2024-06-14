#pragma once
class Boss
{
public:

	CImage img;
	DIRECTION dir = RIGHT;
	int imgIndex = 0;
	int offsetX;
	int offsetY;

	POINT position;

	// Boss Movement
	float velocityX;
	float velocityY;
	int jumpTerm = 3;
	int attackTerm = 1;
	bool isJumping;
	bool jumpUp;

	float jumpSpeed;

public:

};