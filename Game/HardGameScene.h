#pragma once
class HardGameScene : public Scene
{
public:
	Player* mario;
	Player* luigi;

	CImage backgroud, mario_life, luigi_life;
	CImage mario_img, luigi_img, life_img;

	vector<Obstacle> obs;
	vector<Obstacle> hearts;

	int timeM;
	int timeS;


public:
	void InitPlayer();
	void InitObstacles();
	void InitHearts();
	void CollisionCheck();
	void GameEnd();
	void DrawTime(HDC hDC);
	void DrawUI(HDC hDC);

public:
	virtual ~HardGameScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;
};

