#pragma once
class ClearScene : public Scene
{
public:
	CImage EndingImage;
public:
	virtual ~ClearScene() override;
	virtual void Init() override;
	virtual void Update(const float frameTime) override;
	virtual void Draw(HDC hDC) override;
	virtual void ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam) override;
};

