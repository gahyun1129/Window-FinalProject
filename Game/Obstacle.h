#pragma once
class Obstacle
{
public:
	RECT size;
	TYPE type;

	CImage img;
	int index = 0;

	bool isUp;
	bool isDown;

	int maxLv;
	int minLv;
public:
	void MoveElevator();
};

