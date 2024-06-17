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
	cloud.Load(L"Image/purple_cloud.png");
	startTime = chrono::high_resolution_clock::now();
	prevJumpingTime = -1;

	koopaImage.Load(L"Image/koopa_image.png");
	marioImage.Load(L"Image/mario_image.png");
	luigiImage.Load(L"Image/luigi_image.png");
	lifeImage.Load(L"Image/life.png");

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

	lastMarioAttackTime = -1;
	lastLuigiAttackTime = -1;

	//// Init Boss ////
	boss = new Boss;

	boss->img.Load(L"Image/Enemy.png");
	boss->imgIndex = 2;

	boss->offsetX = 872 / 11;
	boss->offsetY = 66;

	boss->position.x = 750;
	boss->position.y = 670;
	boss->dir = LEFT;
	boss->velocityX = 5.f;

	boss->isJumping = false;
	boss->jumpUp = false;
	boss->jumpSpeed = 5.f;

	boss->hp = 100;

	//// �ӽ� ////
	bossStartPos.y = boss->position.y;
	bossEndPos.x = 400;
	bossEndPos.y = boss->position.y;
}

void BossGameScene::Update(const float frameTime)
{
	// �÷��� �ð�(��) ���
	auto currTime = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = currTime - startTime;

	//// ���� ////
	if (mario->life == 0 && luigi->life == 0)
	{
		if (gameEndingTime == -1)
		{
			gameEndingTime = (int)elapsed.count();
		}
		else if (gameEndingTime <= (int)elapsed.count())
		{
			Framework.mainCamera->pos.x = 0;
			Scene* scene = Framework.CurScene;   // ���� ���� tmp�� �ְ� ������
			Framework.CurScene = new GameOverScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = OVER;
			delete scene;
		}
		return;
	}
	else if (boss->hp <= 0)
	{
		if (gameEndingTime == -1)
		{
			gameEndingTime = (int)elapsed.count();
		}
		else if (gameEndingTime <= (int)elapsed.count())
		{
			Framework.mainCamera->pos.x = 0;
			Scene* scene = Framework.CurScene;   // ���� ���� tmp�� �ְ� ������
			Framework.CurScene = new ClearScene;
			Framework.CurScene->Init();
			Framework.SceneIndex = CLEAR;
			delete scene;
		}
		return;
	}
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
			if (Framework.mainCamera->pos.x < 600) {
				Framework.mainCamera->pos.x = gapX;
			}
			else {

			}
		}
	}
	//// Update Player ////
	if (mario->life > 0)
	{
		mario->Move();

		mario->CheckFloor();

		mario->PlayAnimation();
	}
	else
	{
		mario->isDying = true;
		mario->DyingUpdate();
	}
	if (luigi->life > 0)
	{
		luigi->Move();

		luigi->CheckFloor();

		luigi->PlayAnimation();
	}
	else
	{
		luigi->isDying = true;
		luigi->DyingUpdate();
	}

	//// Update Balls ////	
	for (auto it = balls.begin(); it != balls.end(); )
	{
		auto b = *it;
		// Ball <-> Boss
		RECT ballR = { b->position.x - b->halfSize, b->position.y - b->halfSize, b->position.x + b->halfSize, b->position.y + b->halfSize };
		RECT bossR = { boss->position.x, boss->position.y, boss->position.x + boss->offsetX, boss->position.y + boss->offsetY };
		RECT intersection;
		if (IntersectRect(&intersection, &ballR, &bossR)) {
			b->vx = 0;
			boss->hp -= 5;
			if (boss->hp <= 0) {
				boss->hp = 0;
				boss->isDying = true;
			}
		}

		if (b->startTime == -1) {
			b->startTime = (int)elapsed.count();
			if (b->playerName == "mario")
				lastMarioAttackTime = (int)elapsed.count();
			else if (b->playerName == "luigi")
				lastLuigiAttackTime = (int)elapsed.count();
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
		// ������ jumpTerm(��)���� ���� ���
		if ((int)elapsed.count() % boss->jumpTerm == 0 && (int)elapsed.count() > prevJumpingTime)
		{
			boss->isJumping = true;
			boss->jumpUp = true;
			boss->jumpStartPos = boss->position;
			prevJumpingTime = (int)elapsed.count();
		}
		boss->Jump();

		// ������ attackTerm(��)���� fireBall ����
		if ((int)elapsed.count() % boss->attackTerm == 0 && (int)elapsed.count() > prevAttackTime)
		{
			AddFireBall();
			prevAttackTime = (int)elapsed.count();
		}

		// ������ skillTerm(��)���� Ray ����
		if ((int)elapsed.count() % boss->skillTerm == 0 && (int)elapsed.count() > prevSkillTime)
		{
			for (int i = 0; i < 3; i++)
			{
				AddRay();
			}
			prevSkillTime = (int)elapsed.count();
			Framework.mainCamera->isShake = true;
		}

		// ���� �̵�
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
			if (fb->position.x > Framework.size.right + Framework.mainCamera->pos.x)
				fb->velocity = 0;
		}

		// Player <-> Fire Ball
		RECT marioR = { mario->position.x, mario->position.y, mario->position.x + mario->imgWidth, mario->position.y + mario->imgHeight };
		RECT luigiR = { luigi->position.x, luigi->position.y, luigi->position.x + luigi->imgWidth, luigi->position.y + luigi->imgHeight };
		RECT fireR = { fb->position.x, fb->position.y, fb->position.x + fb->offsetX, fb->position.y + fb->offsetY };
		RECT intersection;
		if (IntersectRect(&intersection, &marioR, &fireR)) {
			fb->velocity = 0;
			if (!mario->isHero)
				mario->life--;
		}
		if (IntersectRect(&intersection, &luigiR, &fireR)) {
			fb->velocity = 0;
			if (!luigi->isHero)
				luigi->life--;
		}

		if (fb->imgIndex == 0) {
			fb->imgIndex = 1;
		}
		else {
			fb->imgIndex = 0;
		}

		if (fb->velocity == 0) {
			it = fireBalls.erase(it); // velocity�� 0�� ��� ���Ϳ��� ����
		}
		else {
			++it; // velocity�� 0�� �ƴ� ��� ���� ��ҷ� �̵�
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
					POINT particlePos = { mario->position.x, mario->position.y };
					newParticle->Init(mario->position);
					newParticle->prevTime = (int)elapsed.count();
					particles.push_back(newParticle);
				}
				if (!mario->isHero)
					mario->life--;
			}
			if (IntersectRect(&intersection, &luigiR, &rayR)) {
				for (int i = 0; i < 3; i++)
				{
					Particle* newParticle = new Particle;
					POINT particlePos = { luigi->position.x, luigi->position.y };
					newParticle->Init(luigi->position);
					newParticle->prevTime = (int)elapsed.count();
					particles.push_back(newParticle);
				}
				if (!luigi->isHero)
					luigi->life--;
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
	Rectangle(hDC, Framework.size.left, Framework.size.top, Framework.size.right + Framework.mainCamera->pos.x, Framework.size.bottom);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	background.Draw(hDC, 0, 0, Framework.size.right + Framework.mainCamera->pos.x, Framework.size.bottom, 0, Framework.mainCamera->pos.y, 800 + Framework.mainCamera->pos.x, 600);
	DrawClouds(hDC);
	DrawPlayerHP(hDC);
	DrawTime(hDC);

	//floorImg.Draw(hDC, mario->position.x, mario->position.y,
	//	mario->imgWidth, mario->imgHeight,
	//	mario->imgWidth * mario->imgIndex, mario->imgHeight * mario->animIndex,
	//	mario->imgWidth, mario->imgHeight);

	// �÷��̾� �浹 �ڽ�
	/*RECT marioR = { mario->position.x, mario->position.y, mario->position.x + mario->imgWidth, mario->position.y + mario->imgHeight };
	RECT luigiR = { luigi->position.x, luigi->position.y, luigi->position.x + luigi->imgWidth, luigi->position.y + luigi->imgHeight };
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, marioR.left, marioR.top, marioR.right, marioR.bottom);
	DeleteObject(hBrush);*/

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
	// �÷��� �ð�(��) ���
	auto currTime = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = currTime - startTime;

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
			if ((int)elapsed.count() - lastMarioAttackTime >= 1)
			{
				AddPlayerBall("mario");
			}
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
		else if (wParam == VK_M) {
			if ((int)elapsed.count() - lastLuigiAttackTime >= 1)
			{
				AddPlayerBall("luigi");
			}
		}
		else if (wParam == VK_K) {
			mario->isHero = !mario->isHero;
			luigi->isHero = !luigi->isHero;
		}
		else if (wParam == VK_1) {
			boss->hp = 5;
		}
		break;
	}
	case WM_LBUTTONDOWN: {
		int mx = LOWORD(lParam); //--- ���콺 ��ǥ��: (mx, my)
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

void BossGameScene::AddPlayerBall(const string name)
{
	if (name == "mario")
	{
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
		newBall->Init(newP, mario->dir, -1, name);
		balls.push_back(newBall);
	}
	else if (name == "luigi")
	{
		Ball* newBall = new Ball;
		POINT newP;
		if (luigi->dir == LEFT) {
			newP.x = luigi->position.x;
			newP.y = luigi->position.y + luigi->imgHeight / 2;
		}
		else {
			newP.x = luigi->position.x + luigi->imgWidth;
			newP.y = luigi->position.y + luigi->imgHeight / 2;
		}
		newBall->Init(newP, luigi->dir, -1, name);
		balls.push_back(newBall);
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
		newFireBall->position.x = boss->position.x - newFireBall->offsetX;
	}
	else {
		newFireBall->position.x = boss->position.x + boss->offsetX * 1.5;
	}
	newFireBall->position.y = boss->position.y + 20;
	newFireBall->velocity = 10;

	fireBalls.push_back(newFireBall);
}

void BossGameScene::AddRay()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<> disX(Framework.size.left + Framework.mainCamera->pos.x, Framework.size.right + Framework.mainCamera->pos.x);
	static std::uniform_real_distribution<> disW(30, 50);

	Ray* newRay = new Ray;
	newRay->positionX = disX(gen);
	newRay->width = disW(gen);
	ray.push_back(newRay);
}

void BossGameScene::DrawBossHP(HDC hDC, const int hp)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	float imageSize = 80;
	float drawY = 10 + 50;

	float hpWidth = Framework.size.right / 10 * 6;
	float hpHeight = 20;
	float currHpWidth = hpWidth * hp / 100;
	float gap = -imageSize/2 - hpHeight/2;

	// hp
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	RoundRect(hDC, hpWidth / 6 * 2 + Framework.mainCamera->pos.x, drawY + imageSize + gap, hpWidth / 6 * 2 + hpWidth + Framework.mainCamera->pos.x, drawY + imageSize + gap + hpHeight, 20, 20);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	RoundRect(hDC, hpWidth / 6 * 2 + Framework.mainCamera->pos.x, drawY + imageSize + gap, hpWidth / 6 * 2 + currHpWidth + Framework.mainCamera->pos.x, drawY + imageSize + gap + hpHeight, 20, 20);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	// koopa image
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	RoundRect(hDC, Framework.mainCamera->pos.x + Framework.size.right / 2 - imageSize / 2, drawY, imageSize + Framework.mainCamera->pos.x + Framework.size.right / 2 - imageSize / 2, drawY + imageSize, 10, 10);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	koopaImage.Draw(hDC, Framework.mainCamera->pos.x + Framework.size.right / 2 - imageSize / 2, drawY, imageSize, imageSize, 0, 0, 595, 595);
}

void BossGameScene::DrawPlayerHP(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	float imageSize = 80;
	float lifeSize = 40;
	float drawY = 70 + 50;

	// mario
	if (mario->isHero) {
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		oldPen = (HPEN)SelectObject(hDC, hPen);
	}
	else {
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		oldPen = (HPEN)SelectObject(hDC, hPen);
	}
	RoundRect(hDC, Framework.mainCamera->pos.x, drawY, imageSize + Framework.mainCamera->pos.x, drawY + imageSize, 10, 10);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	marioImage.Draw(hDC, Framework.mainCamera->pos.x, drawY, imageSize, imageSize, 0, 0, 1682, 1682);

	for (int i = 0; i < mario->life; i++)
	{
		lifeImage.Draw(hDC, imageSize + 10 + lifeSize * i + Framework.mainCamera->pos.x, drawY + imageSize / 2 - lifeSize / 2, lifeSize, lifeSize, 0, 0, 120, 120);
	}
	
	// luigi
	if (mario->isHero) {
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		oldPen = (HPEN)SelectObject(hDC, hPen);
	}
	else {
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		oldPen = (HPEN)SelectObject(hDC, hPen);
	}
	RoundRect(hDC, Framework.mainCamera->pos.x + Framework.size.right - imageSize, drawY, Framework.size.right + Framework.mainCamera->pos.x, drawY + imageSize, 10, 10);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	luigiImage.Draw(hDC, Framework.mainCamera->pos.x + Framework.size.right - imageSize, drawY, imageSize, imageSize, 0, 0, 1494, 1494);

	for (int i = 0; i < luigi->life; i++)
	{
		lifeImage.Draw(hDC, Framework.mainCamera->pos.x + Framework.size.right - imageSize - 10 - lifeSize * i - lifeSize, drawY + imageSize / 2 - lifeSize / 2, lifeSize, lifeSize, 0, 0, 120, 120);
	}
}

void BossGameScene::DrawClouds(HDC hDC)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<> disX(0, 1500);
	static std::uniform_real_distribution<> disY(250, 350);

	static const int cloudNum = 10;

	static float randomX[cloudNum] = { -1 };
	static float randomY[cloudNum] = { -1 };
	
	if (randomX[0] == -1)
	{
		for (int i = 0; i < cloudNum; i++)
		{
			randomX[i] = disX(gen);
			randomY[i] = disY(gen);
		}
	}

	for (int i = 0; i < cloudNum; i++)
	{
		cloud.Draw(hDC, randomX[i], randomY[i], 100, 100, 0, 0, 500, 500);
	}
}

void BossGameScene::DrawTime(HDC hDC)
{
	// �÷��� �ð�(��) ���
	auto currTime = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = currTime - startTime;
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(elapsed);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed) - std::chrono::duration_cast<std::chrono::seconds>(minutes);

	HFONT hFont, oldFont;
	hFont = CreateFont(
		50,                        // ��Ʈ ����
		0,                         // ��Ʈ �ʺ�
		0,                         // ���� ���� ����
		0,                         // ���̽����� ���� ����
		FW_BOLD,                   // ��Ʈ �β�
		TRUE,                     // ���Ÿ�ü ����
		FALSE,                     // ���� ����
		FALSE,                     // ��Ҽ� ����
		DEFAULT_CHARSET,           // ���� ����
		OUT_DEFAULT_PRECIS,        // ��� ��Ȯ��
		CLIP_DEFAULT_PRECIS,       // Ŭ���� ��Ȯ��
		DEFAULT_QUALITY,           // ��� ǰ��
		DEFAULT_PITCH | FF_SWISS,  // ��ġ�� ����
		L"Times New Roman"                   // ��Ʈ �̸�
	);
	oldFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, RGB(255, 255, 0));
	TCHAR str[100];
	wsprintf(str, L"%02d : %02d", (int)minutes.count(), (int)seconds.count());
	TextOut(hDC, 480 + Framework.mainCamera->pos.x, 0, str, lstrlen(str));

	SelectObject(hDC, oldFont);
	DeleteObject(hFont);
}
