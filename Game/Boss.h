#pragma once
class Boss
{
public:

	CImage img;
	DIRECTION dir = RIGHT;
	int imgIndex = 0;
	int offsetX;
	int offsetY;

	int hp;

	POINT position;

	// Boss Movement
	float velocityX;
	float velocityY;
	int jumpTerm = 5;
	int attackTerm = 3;
	int skillTerm = 15;
	bool isJumping;
	bool jumpUp;
	POINT jumpStartPos;
	float jumpSpeed;

	// dying
	bool isDying = false;
	const float GRAVITY = 1.0f;
	const float BOUNCE_FACTOR = 0.7f;
	float vy = -10;

public:
	void Jump();
	void SetDirection(const POINT towardPosition);
	void MoveTo(const POINT whereToMove);

	void Draw(HDC hDC, int sceneX);

	void DyingUpdate();
};