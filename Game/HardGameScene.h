#pragma once
class HardGameScene : public Scene
{
public:
	Player* mario;
	Player* luigi;

	CImage backgroud;

	vector<Obstacle> obs;

	int timeM;
	int timeS;

public:
	void InitPlayer();
	void InitObstacles();
	void CollisionCheck();
	void GameEnd();
	void DrawTime(HDC hDC);
public:
	virtual ~HardGameScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;
};

