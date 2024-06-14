#pragma once
class BossGameScene : public Scene
{

public:
	Player* mario;
	Player* luigi;

	Boss* boss;
	POINT bossStartPos;
	POINT bossEndPos;
	vector<FireBall*> fireBalls;

	CImage background;

	// Timer
	chrono::high_resolution_clock::time_point startTime;
	int prevJumpingTime;	// 직전 점프 시각(초)
	int prevAttackTime;		// 직전 공격 시각(초)
public:
	virtual ~BossGameScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;

private:
	POINT GetPosToMove(POINT p1, POINT p2, float t);
};

