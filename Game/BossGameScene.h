#pragma once
class BossGameScene : public Scene
{

public:
	CImage floorImg;

	Player* mario;
	Player* luigi;
	vector<Ball*> balls;

	Boss* boss;
	POINT bossStartPos;
	POINT bossEndPos;
	vector<FireBall*> fireBalls;
	vector<Ray*> ray;
	vector<Particle*> particles;

	CImage background;

	float drawSceneX = 0;

	// Timer
	chrono::high_resolution_clock::time_point startTime;
	int prevJumpingTime;	// 직전 점프 시각(초)
	int prevAttackTime;		// 직전 공격 시각(초)
	int prevSkillTime;
	int prevParticleTime;
public:
	virtual ~BossGameScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;

private:
	void AddFireBall();
	void AddParticle();
	void DrawBossHP(HDC hDC, const int hp);
};

