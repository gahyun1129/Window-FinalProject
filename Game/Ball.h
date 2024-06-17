#pragma once
class Ball
{
public:
	string playerName;
	POINT position;
	float vx, vy;
	float halfSize = 5;
	COLORREF color;

	// �߷� ���ӵ�
	const float GRAVITY = 1.0f;

	// �ݻ� ��� (0�� 1 ������ ��, 1�� ���� ź�� �浹)
	const float BOUNCE_FACTOR = 0.7f;

	int startTime;

public:
	void Init(const POINT position, const DIRECTION dir, const int currTime, const string name);
	void Update();
	void Draw(HDC hDC, int sceneX);
};

