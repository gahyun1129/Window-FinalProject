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

	floorImg.Load(L"Image/floorblock.png");
	drawSceneX = 0;

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

	mario->position = { 70, 700 };
	luigi->position = { 20, 700 };

	//// Init Boss ////
	boss = new Boss;

	boss->img.Load(L"Image/Enemy.png");
	boss->imgIndex = 2;

	boss->offsetX = 872 / 11;
	boss->offsetY = 66;

	boss->position.x = 10;
	boss->position.y = 670;
	boss->velocityX = 5.f;

	boss->isJumping = false;
	boss->jumpUp = false;
	boss->jumpSpeed = 5.f;

	boss->hp = 100;

	//// 임시 ////
	bossStartPos.y = boss->position.y;
	bossEndPos.x = 400;
	bossEndPos.y = boss->position.y;
}

void BossGameScene::Update(const float frameTime)
{
	// 플레이 시간(초) 계산
	auto currTime = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = currTime - startTime;

	//// Camera Moving ////
	vector<float> positionXs;
	positionXs.push_back(mario->position.x);
	positionXs.push_back(luigi->position.x);
	positionXs.push_back(boss->position.x);
	if (!positionXs.empty()) {
		auto maxElement = max_element(positionXs.begin(), positionXs.end());
		auto minElement = min_element(positionXs.begin(), positionXs.end());
		float sceneCenterX = *minElement + (*maxElement - *minElement) / 2.f;
		float gapX = sceneCenterX - Framework.size.right / 2;
		if (gapX > 0) {
			if (drawSceneX + 800 <= 1986) {
				drawSceneX = gapX;
				//Framework.mainCamera->pos.x = gapX;
			}
		}
	}

	//// Update Player ////
	mario->Move();
	luigi->Move();

	mario->CheckFloor();
	luigi->CheckFloor();

	mario->PlayAnimation();
	luigi->PlayAnimation();

	for (auto it = balls.begin(); it != balls.end(); )
	{
		auto b = *it;
		RECT ballR = { b->position.x - b->halfSize, b->position.y - b->halfSize, b->position.x + b->halfSize, b->position.y + b->halfSize };
		RECT bossR = { boss->position.x, boss->position.y, boss->position.x + boss->offsetX, boss->position.y + boss->offsetY };
		RECT intersection;
		if (IntersectRect(&intersection, &ballR, &bossR)) {
			b->vx = 0;
			boss->hp -= 20;
			if (boss->hp <= 0)
				boss->isDying = true;
		}

		if (b->startTime == -1) {
			b->startTime = (int)elapsed.count();
		}

		if (b->startTime + 3 <= (int)elapsed.count() || b->vx == 0) {
			it = balls.erase(it);
		}
		else {
			b->Update();
			++it;
		}
	}

	//// Update Boss ////
	if (!boss->isDying)
	{
		// 보스의 jumpTerm(초)마다 점프 재생
		if ((int)elapsed.count() % boss->jumpTerm == 0 && (int)elapsed.count() > prevJumpingTime)
		{
			boss->isJumping = true;
			boss->jumpUp = true;
			boss->jumpStartPos = boss->position;
			prevJumpingTime = (int)elapsed.count();
		}
		boss->Jump();

		// 보스의 attackTerm(초)마다 fireBall 생성
		if ((int)elapsed.count() % boss->attackTerm == 0 && (int)elapsed.count() > prevAttackTime)
		{
			AddFireBall();
			prevAttackTime = (int)elapsed.count();
		}

		if ((int)elapsed.count() % boss->skillTerm == 0 && (int)elapsed.count() > prevSkillTime)
		{
			Ray* newRay = new Ray;
			newRay->positionX = 100;
			newRay->width = 40;
			ray.push_back(newRay);
			prevSkillTime = (int)elapsed.count();
			Framework.mainCamera->isShake = true;
		}

		// 보스 이동
		POINT pPos = { mario->position.x, mario->position.y };
		boss->SetDirection(pPos);
		boss->MoveTo(pPos);
	}
	else
	{
		boss->DyingUpdate();
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

		// Player <-> Fire Ball
		RECT marioR = { mario->position.x, mario->position.y, mario->position.x + mario->imgWidth, mario->position.y + mario->imgHeight };
		RECT luigiR = { luigi->position.x, luigi->position.y, luigi->position.x + luigi->imgWidth, luigi->position.y + luigi->imgHeight };
		RECT fireR = { fb->position.x, fb->position.y, fb->position.x + fb->offsetX, fb->position.y + fb->offsetY };
		RECT intersection;
		if (IntersectRect(&intersection, &marioR, &fireR)) {
			fb->velocity = 0;
		}
		if (IntersectRect(&intersection, &luigiR, &fireR)) {
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

	for (auto it = particles.begin(); it != particles.end(); )
	{
		auto p = *it;
		p->imgIndex--;

		if (p->imgIndex < 0) {
			it = particles.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto it = ray.begin(); it != ray.end(); )
	{
		auto r = *it;
		r->width--;

		if (r->width <= 0) {
			// Player <-> Ray
			RECT marioR = { mario->position.x, mario->position.y, mario->position.x + mario->imgWidth, mario->position.y + mario->imgHeight };
			RECT luigiR = { luigi->position.x, luigi->position.y, luigi->position.x + luigi->imgWidth, luigi->position.y + luigi->imgHeight };
			RECT rayR = { r->positionX - 5, 0, r->positionX + 5, 750 };
			RECT intersection;
			if (IntersectRect(&intersection, &marioR, &rayR)) {
				for (int i = 0; i < 3; i++)
				{
					Particle* newParticle = new Particle;
					POINT particlePos = { r->positionX, 700 };
					newParticle->Init(particlePos);
					newParticle->prevTime = (int)elapsed.count();
					particles.push_back(newParticle);
				}
			}
			if (IntersectRect(&intersection, &luigiR, &rayR)) {
				for (int i = 0; i < 3; i++)
				{
					Particle* newParticle = new Particle;
					POINT particlePos = { r->positionX, 700 };
					newParticle->Init(particlePos);
					newParticle->prevTime = (int)elapsed.count();
					particles.push_back(newParticle);
				}
			}
			it = ray.erase(it);
		}
		else {
			++it;
		}
	}
}

void BossGameScene::Draw(HDC hDC)
{
	//// Scene ////
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	hBrush = CreateSolidBrush(RGB(10, 10, 10));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(10, 10, 10));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	Rectangle(hDC, Framework.size.left, Framework.size.top, Framework.size.right, Framework.size.bottom);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	background.Draw(hDC, 0, 0, 1986, Framework.size.bottom, 0, 0, 1986, 600);

	//floorImg.Draw(hDC, mario->position.x, mario->position.y,
	//	mario->imgWidth, mario->imgHeight,
	//	mario->imgWidth * mario->imgIndex, mario->imgHeight * mario->animIndex,
	//	mario->imgWidth, mario->imgHeight);

	// 플레이어 충돌 박스
	RECT marioR = { mario->position.x, mario->position.y, mario->position.x + mario->imgWidth, mario->position.y + mario->imgHeight };
	RECT luigiR = { luigi->position.x , luigi->position.y, luigi->position.x + luigi->imgWidth, luigi->position.y + luigi->imgHeight };
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, marioR.left, marioR.top, marioR.right, marioR.bottom);
	DeleteObject(hBrush);

	//// Ray ////
	for (const auto r : ray)
	{
		r->Draw(hDC);
	}

	//// Player /////
	mario->img.Draw(hDC, mario->position.x, mario->position.y,
		mario->imgWidth, mario->imgHeight,
		mario->imgWidth * mario->imgIndex, mario->imgHeight * mario->animIndex,
		mario->imgWidth, mario->imgHeight);
	luigi->img.Draw(hDC, luigi->position.x, luigi->position.y,
		luigi->imgWidth, luigi->imgHeight,
		luigi->imgWidth * luigi->imgIndex, luigi->imgHeight * luigi->animIndex,
		luigi->imgWidth, luigi->imgHeight);

	for (const auto b : balls)
	{
		b->Draw(hDC, 0);
	}

	//// Boss ////
	boss->Draw(hDC, 0);
	DrawBossHP(hDC, boss->hp);
	
	//// Fire Balls ////
	for (const auto fb : fireBalls)
	{
		fb->Draw(hDC, 0);
	}
	//// Particle ////
	for (const auto p : particles)
	{
		p->Draw(hDC, 0);
	}
}

void BossGameScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_W) {
			if (!mario->isJump && !mario->isFalling)
			{
				mario->isJump = true;
				if (mario->dir == LEFT) {
					mario->animIndex = 2;
				}
				else {
					mario->animIndex = 3;
				}
			}
		}
		else if (wParam == VK_A) {
			mario->dir = LEFT;
			mario->isLeft = true;
			mario->animIndex = 0;
		}
		else if (wParam == VK_D) {
			mario->dir = RIGHT;
			mario->isRight = true;
			mario->animIndex = 1;
		}
		else if (wParam == VK_Z) {
			Ball* newBall = new Ball;
			POINT newP;
			if (mario->dir == LEFT) {
				newP.x = mario->position.x;
				newP.y = mario->position.y + mario->imgHeight / 2;
			}
			else {
				newP.x = mario->position.x + mario->imgWidth;
				newP.y = mario->position.y + mario->imgHeight / 2;
			}
			newBall->Init(newP, mario->dir, -1);
			balls.push_back(newBall);
		}
		else if (wParam == VK_UP) {
			if (!luigi->isJump && !luigi->isFalling) {
				luigi->isJump = true;
				if (luigi->dir == LEFT) {
					luigi->animIndex = 2;
				}
				else {
					luigi->animIndex = 3;
				}
			}
		}
		else if (wParam == VK_LEFT) {
			luigi->dir = LEFT;
			luigi->isLeft = true;
			luigi->animIndex = 0;
		}
		else if (wParam == VK_RIGHT) {
			luigi->dir = RIGHT;
			luigi->isRight = true;
			luigi->animIndex = 1;
		}
		break;
	}
	case WM_LBUTTONDOWN: {
		int mx = LOWORD(lParam); //--- 마우스 좌표값: (mx, my)
		int my = HIWORD(lParam);

		break;
	}
	case WM_KEYUP:
	{
		if (wParam == VK_A) {
			mario->isLeft = false;
		}
		else if (wParam == VK_D) {
			mario->isRight = false;
		}
		else if (wParam == VK_LEFT) {
			luigi->isLeft = false;
		}
		else if (wParam == VK_RIGHT) {
			luigi->isRight = false;
		}
		break;
	}
	}
}

void BossGameScene::AddFireBall()
{
	FireBall* newFireBall = new FireBall;

	newFireBall->img.Load(L"Image/Enemy.png");

	newFireBall->dir = boss->dir;

	newFireBall->offsetX = 60;
	newFireBall->offsetY = 22;

	if (boss->dir == LEFT) {
		newFireBall->position.x = boss->position.x - 100;
	}
	else {
		newFireBall->position.x = boss->position.x + 100;
	}
	newFireBall->position.y = boss->position.y;

	newFireBall->velocity = 10;

	fireBalls.push_back(newFireBall);
}

void BossGameScene::DrawBossHP(HDC hDC, const int hp)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	float hpWidth = Framework.size.right / 8 * 4;
	float currHpWidth = Framework.size.right / 8 * 4 * hp / 100;

	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	RoundRect(hDC, Framework.size.right / 8 * 2, Framework.size.top + 15, Framework.size.right / 8 * 2 + hpWidth, Framework.size.top + 15 + 20, 20, 20);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	RoundRect(hDC, Framework.size.right / 8 * 2, Framework.size.top + 15, Framework.size.right / 8 * 2 + currHpWidth, Framework.size.top + 15 + 20, 20, 20);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}
