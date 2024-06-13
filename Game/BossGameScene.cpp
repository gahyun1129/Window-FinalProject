#include "stdafx.h"

BossGameScene::~BossGameScene()
{
	delete(boss);

	for (FireBall* fireBall : fireBalls) {
		if (fireBall != nullptr) {
			delete fireBall;
		}
	}
	fireBalls.clear();
}

void BossGameScene::Init()
{
	//// Boss ////
	boss = new Boss;

	boss->img.Load(L"Image/Enemy.png");

	boss->offsetX = 872 / 11;
	boss->offsetY = 66;

	boss->position.x = 10;
	boss->position.y = 700;

	//// Fire Ball ////
	FireBall* newFireBall = new FireBall;

	newFireBall->img.Load(L"Image/Enemy.png");

	newFireBall->offsetX = 60;
	newFireBall->offsetY = 22;

	if (boss->dir == LEFT)
		newFireBall->position.x = boss->position.x - 50;
	else
		newFireBall->position.x = boss->position.x + 50;
	newFireBall->position.y = 700;

	newFireBall->velocity = 10;

	fireBalls.push_back(newFireBall);

	//// 임시 ////
	bossStartPos.y = boss->position.y;
	bossEndPos.x = 200;
	bossEndPos.y = 700;
}

void BossGameScene::Update(const float frameTime)
{
	for (auto fb : fireBalls)
	{
		if (fb->dir == LEFT) {
			fb->position.x -= fb->velocity;
			if (fb->position.x < 0)
				fb->velocity = 0;
		}
		else {
			fb->position.x += fb->velocity;
			if (fb->position.x > 1100)
				fb->velocity = 0;
		}

		if (fb->imgIndex == 0) {
			fb->imgIndex = 1;
		}
		else {
			fb->imgIndex = 0;
		}
	}
	boss->position = GetPosToMove(bossStartPos, bossEndPos, moveT);
	//if (moveT < 1.f)
	//	moveT += 0.1f;	// 두 점 사이를 보간하는 t값 증가
}

void BossGameScene::Draw(HDC hDC)
{
	//// Boss ////
	if (boss->dir == LEFT) {
		boss->img.Draw(hDC, boss->position.x, boss->position.y,			// 윈도우에 그릴 위치
							boss->offsetX * 1.5, boss->offsetY * 1.5,	// 윈도우에 그려질 크기(가로,세로)
							0, 420,										// 이미지 상에서 가져올 위치
							boss->offsetX, boss->offsetY);				// 이미지 상에서 가져올 크기(가로,세로)
	}
	else {
		boss->img.Draw(hDC, boss->position.x, boss->position.y,
							boss->offsetX * 1.5, boss->offsetY * 1.5,
							boss->offsetX * 4, 420,
							boss->offsetX, boss->offsetY);
	}
	//// Fire Balls ////
	for (const auto fb : fireBalls)
	{
		if (fb->dir == LEFT) {
			fb->img.Draw(hDC, fb->position.x, fb->position.y,
							  fb->offsetX * 1.5, fb->offsetY * 1.5,
							  0, 420 + 64,
							  fb->offsetX, fb->offsetY);
		}
		else {
			fb->img.Draw(hDC, fb->position.x, fb->position.y,
							  fb->offsetX * 1.5, fb->offsetY * 1.5,
							  320 + fb->offsetX * fb->imgIndex, 500,
							  fb->offsetX, fb->offsetY);
		}
	}
}

void BossGameScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
}

POINT BossGameScene::GetPosToMove(POINT p1, POINT p2, float t)
{
	POINT newPos;
	newPos.x = p1.x + t * (p2.x - p1.x);
	newPos.y = p1.y + t * (p2.y - p1.y);

	return newPos;
}
