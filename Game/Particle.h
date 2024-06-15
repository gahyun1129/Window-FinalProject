#pragma once
class Particle
{
public:
	CImage img;
	int imgIndex = 2;
	int offsetX;
	int offsetY;
	int prevTime;

	POINT position;

public:
	void Init(const POINT center);
	void Draw(HDC hDC, int sceneX);
};

