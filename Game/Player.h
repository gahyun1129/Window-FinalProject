#pragma once
class Player
{
public:

	CImage img;
	DIRECTION dir = LEFT;
	int imgIndex = 0;
	int offset;

	POINT position = {10, 700};

	bool isJump;
	int jumpTime;

public:

};

