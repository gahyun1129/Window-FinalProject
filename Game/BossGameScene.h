#pragma once
class BossGameScene : public Scene
{

public:
	Player* p1;
	Player* p2;

	Boss* boss;
	POINT bossStartPos;
	POINT bossEndPos;
	float moveT;
	vector<FireBall*> fireBalls;

	CImage background;

public:
	virtual ~BossGameScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;

private:
	POINT GetPosToMove(POINT p1, POINT p2, float t);
};

