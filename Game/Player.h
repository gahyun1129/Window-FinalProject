#pragma once
class Player
{
public:
	CImage img;				// image
	int imgWidth;			// image width
	int imgHeight;			// image height

	int imgIndex = 0;		// image index
	int amimIndex = 1;		// animation index  
							// 0: left walk 1: right walk 2: left jump 3: right jump
	
	int imgFrameW = 0;		// image index max value
	int imgFrameH = 0;		// animation index max value

	POINT position = {10, 700};

public:
	bool isJump;
	int jumpTime;

public:

};

