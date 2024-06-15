#pragma once
class EasyGameScene : public Scene
{

public:
	Player* mario;
	Player* luigi;

	CImage backgroud;

	vector<Obstacle> obs;

public:
	void InitPlayer();
	void InitObstacles();
	void CollisionCheck();
public:
	virtual ~EasyGameScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;
};

