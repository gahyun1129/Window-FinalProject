#pragma once
class EasyGameScene : public Scene
{

public:
	Player* mario;
	Player* luigi;

	CImage backgroud;

	vector<Obstacle> obs;

	Obstacle switchStick;
	Obstacle switchElevator;
	Obstacle buttonDown;
	Obstacle buttonUp;
	Obstacle buttonElevator;
	Obstacle box;

	int timeM;
	int timeS;

public:
	void InitPlayer();
	void InitObstacles();
	void CollisionCheck();
	void GameEnd();
	void DrawTime(HDC hDC);
public:
	virtual ~EasyGameScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;
};

