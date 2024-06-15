#include "stdafx.h"

extern GameFramework Framework;

BossGameScene::~BossGameScene()
{
	delete(boss);
	delete(mario);
	delete(luigi);

	for (FireBall* fireBall : fireBalls) {
		if (fireBall != nullptr) {
			delete fireBall;
		}
	}
	fireBalls.clear();
}

void BossGameScene::Init()
{
	//// Init Scene ////
	background.Load(L"Image/Stage-ground.png");
	startTime = chrono::high_resolution_clock::now();
	prevJumpingTime = -1;

	//// Init Player ////
	mario = new Player;
	luigi = new Player;

	mario->img.Load(L"Image/BigMario.png");
	luigi->img.Load(L"Image/Luigi.png");

	mario->imgFrameW = 8;
	luigi->imgFrameW = 8;

	mario->imgFrameH = 4;
	luigi->imgFrameH = 4;

	mario->imgWidth = mario->img.GetWidth() / mario->imgFrameW;
	mario->imgHeight = mario->img.GetHeight() / mario->imgFrameH;

	luigi->imgWidth = luigi->img.GetWidth() / luigi->imgFrameW;
	luigi->imgHeight = luigi->img.GetHeight() / luigi->imgFrameH;

	//// Init Boss ////
	boss = new Boss;

	boss->img.Load(L"Image/Enemy.png");

	boss->offsetX = 872 / 11;
	boss->offsetY = 66;

	boss->position.x = 10;
	boss->position.y = 700;
	boss->velocityX = 5.f;

	boss->isJumping = false;
	boss->jumpUp = false;
	boss->jumpSpeed = 5.f;

	//// Init Fire Ball ////
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
	bossEndPos.x = 400;
	bossEndPos.y = boss->position.y;
}

void BossGameScene::Update(const float frameTime)
{
	//// Update Player ////
	mario->imgIndex += 1;
	if (mario->imgIndex == mario->imgFrameW) {
		mario->imgIndex = 0;
	}
	if (mario->isJump) {
		if (mario->jumpTime < 10) {
			mario->position.y -= 10;
			mario->jumpTime += 1;
		}
		else {
			mario->position.y += 10;
			mario->jumpTime += 1;

			if (mario->jumpTime == 20) {
				mario->isJump = false;
				mario->jumpTime = 0;
			}
		}
	}
	if (luigi->isJump) {
		if (luigi->jumpTime < 10) {
			luigi->position.y -= 10;
			luigi->jumpTime += 1;
		}
		else {
			luigi->position.y += 10;
			luigi->jumpTime += 1;

			if (luigi->jumpTime == 20) {
				luigi->isJump = false;
				luigi->jumpTime = 0;
			}
		}
	}

	//// Update Boss ////
	// 플레이 시간(초) 계산
	auto currTime = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = currTime - startTime;
	// 보스의 jumpTerm(초)마다 점프 재생
	if ((int)elapsed.count() % boss->jumpTerm == 0 && (int)elapsed.count() > prevJumpingTime)
	{
		boss->isJumping = true;
		boss->jumpUp = true;
		prevJumpingTime = (int)elapsed.count();
	}
	// 보스의 attackTerm(초)마다 fireBall 생성
	if ((int)elapsed.count() % boss->attackTerm == 0 && (int)elapsed.count() > prevAttackTime)
	{
		FireBall* newFireBall = new FireBall;

		newFireBall->img.Load(L"Image/Enemy.png");

		newFireBall->dir = boss->dir;
		
		newFireBall->offsetX = 60;
		newFireBall->offsetY = 22;

		if (boss->dir == LEFT)
			newFireBall->position.x = boss->position.x - 100;
		else
			newFireBall->position.x = boss->position.x + 100;
		newFireBall->position.y = boss->position.y;

		newFireBall->velocity = 10;

		fireBalls.push_back(newFireBall);
		prevAttackTime = (int)elapsed.count();
	}
	// 보스 점프
	if (boss->isJumping)
	{
		if (boss->position.y > bossStartPos.y - boss->jumpSpeed * 10 && boss->jumpUp)
			boss->position.y -= boss->jumpSpeed;
		else
		{
			boss->jumpUp = false; 

			if (boss->position.y < bossStartPos.y - boss->jumpSpeed && !boss->jumpUp)
				boss->position.y += boss->jumpSpeed;
			else
				boss->isJumping = false;
		}
	}
	// 보스 방향 설정
	if (boss->position.x < mario->position.x)
		boss->dir = RIGHT;
	else
		boss->dir = LEFT;
	// 보스 이동 (mario 위치로 이동)
	if (boss->position.x < mario->position.x - 100 || boss->position.x > mario->position.x + 100)
	{
		if (boss->dir == RIGHT)
			boss->position.x += boss->velocityX;
		else
			boss->position.x -= boss->velocityX;
	}

	//// Update Fire Ball ////
	for (auto it = fireBalls.begin(); it != fireBalls.end(); ) {
		auto fb = *it;
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

		if (fb->velocity == 0) {
			it = fireBalls.erase(it); // velocity가 0인 경우 벡터에서 제거
		}
		else {
			++it; // velocity가 0이 아닌 경우 다음 요소로 이동
		}
	}
}

void BossGameScene::Draw(HDC hDC)
{
	//// Scene ////
	//SetBkColor(hDC, RGB(0, 0, 0));
	//Rectangle(hDC, Framework.size.left, Framework.size.top, Framework.size.right, Framework.size.bottom);

	background.Draw(hDC, 0, 0, Framework.size.right, Framework.size.bottom, 0, 0, 800, 600);

	//// Player /////
	mario->img.Draw(hDC, mario->position.x + 100, mario->position.y,
		mario->imgWidth, mario->imgHeight,
		mario->imgWidth * mario->imgIndex, mario->imgHeight * mario->animIndex,
		mario->imgWidth, mario->imgHeight);
	luigi->img.Draw(hDC, luigi->position.x, luigi->position.y,
		luigi->imgWidth, luigi->imgHeight,
		luigi->imgWidth * luigi->imgIndex, luigi->imgHeight * luigi->animIndex,
		luigi->imgWidth, luigi->imgHeight);

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
							  200 + fb->offsetX * fb->imgIndex, 500,
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
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_W) {
			mario->isJump = true;
		}
		else if (wParam == VK_A) {
			mario->position.x -= 5;
			if (mario->position.x <= 0) {
				mario->position.x += 5;
			}
		}
		else if (wParam == VK_D) {
			mario->position.x += 5;
			if (mario->position.x + 64 >= 1100) {
				mario->position.x -= 5;
			}
		}
		else if (wParam == VK_LEFT) {
			luigi->position.x -= 5;
			if (luigi->position.x <= 0) {
				luigi->position.x += 5;
			}
		}
		else if (wParam == VK_RIGHT) {
			luigi->position.x += 5;
			if (luigi->position.x + 64 >= 1100) {
				luigi->position.x -= 5;
			}
		}
		else if (wParam == VK_UP) {
			luigi->isJump = true;
		}
		break;
	}
	case WM_LBUTTONDOWN: {
		int mx = LOWORD(lParam); //--- 마우스 좌표값: (mx, my)
		int my = HIWORD(lParam);

		break;
	}
	}
}

POINT BossGameScene::GetPosToMove(POINT p1, POINT p2, float t)
{
	POINT newPos;
	newPos.x = p1.x + t * (p2.x - p1.x);
	newPos.y = p1.y + t * (p2.y - p1.y);

	return newPos;
}
