#pragma once
class Ball
{
public:
	string playerName;
	POINT position;
	float vx, vy;
	float halfSize = 5;
	COLORREF color;

	// 중력 가속도
	const float GRAVITY = 1.0f;

	// 반사 계수 (0과 1 사이의 값, 1은 완전 탄성 충돌)
	const float BOUNCE_FACTOR = 0.7f;

	int startTime;

public:
	void Init(const POINT position, const DIRECTION dir, const int currTime, const string name);
	void Update();
	void Draw(HDC hDC, int sceneX);
};

