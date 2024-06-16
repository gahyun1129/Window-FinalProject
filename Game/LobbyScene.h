#pragma once
class LobbyScene : public Scene
{

	CImage background, titleText;
	int title_index = 0;
	int title_coolTime = 0;
	Player* p1;
public:
	virtual ~LobbyScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;
};

