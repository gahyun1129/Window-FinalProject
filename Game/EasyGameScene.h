#pragma once
class EasyGameScene : public Scene
{

public:
	Player* p1;
	Player* p2;

	CImage backgroud;

	
public:
	virtual ~EasyGameScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;
};

