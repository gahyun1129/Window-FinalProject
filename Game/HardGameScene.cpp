#include "stdafx.h"

extern GameFramework Framework;

void HardGameScene::InitPlayer()
{
	mario = new Player;
	luigi = new Player;

	mario->img.Load(L"Image/BigMario.png");
	luigi->img.Load(L"Image/Luigi.png");

	mario->imgFrameW = 8;
	luigi->imgFrameW = 8;

	mario->imgFrameH = 4;
	luigi->imgFrameH = 4;

	mario->imgIndex = 3;

	mario->imgWidth = mario->img.GetWidth() / mario->imgFrameW;
	mario->imgHeight = mario->img.GetHeight() / mario->imgFrameH;

	luigi->imgWidth = luigi->img.GetWidth() / luigi->imgFrameW;
	luigi->imgHeight = luigi->img.GetHeight() / luigi->imgFrameH;

	mario->position = { 20, 770 };
	luigi->position = { 1000, 770 };

	mario->type = MARIO;
	luigi->type = LUIGI;

	luigi->animIndex = 0;
	luigi->dir = LEFT;

	mario->spawnPoint = mario->position;
	luigi->spawnPoint = luigi->position;
}

void HardGameScene::InitObstacles()
{
	Obstacle o;
	o.size = { 0, 830, 1100, 835 };
	o.type = WALL_TOP;
	obs.push_back(o); // 1 floor

	o.size = { 470, 740, 610, 745 };
	o.type = WALL_TOP;
	obs.push_back(o); // 2 floor

	o.size = { 85, 655, 440, 660 };
	o.type = WALL_TOP;
	obs.push_back(o); // 3 floor - 1

	o.size = { 640, 655, 995, 660 };
	o.type = WALL_TOP;
	obs.push_back(o); // 3 floor - 2

	o.size = { 30, 670, 440, 675 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 3 floor_bottom - 1

	o.size = { 640, 670, 1050, 675 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 3 floor_bottom - 2

	o.size = { 0, 595, 85, 600 };
	o.type = WALL_TOP;
	obs.push_back(o); // 4 floor - 1

	o.size = { 995, 595, 1100, 600 };
	o.type = WALL_TOP;
	obs.push_back(o); // 4 floor - 2

	o.size = { 80, 600, 85, 670 };
	o.type = WALL_LEFT;
	obs.push_back(o); // 4 floor - left

	o.size = { 995, 600, 1000, 670 };
	o.type = WALL_RIGHT;
	obs.push_back(o); // 4 floor - right

	o.size = { 155, 535, 925, 540 };
	o.type = WALL_TOP;
	obs.push_back(o); // 5 floor

	o.size = { 155, 555, 925, 560 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 5 floor_bottom

	o.size = { 255, 140, 260, 535 };
	o.type = WALL_RIGHT;
	obs.push_back(o); // 5 floor - right_out

	o.size = { 825, 140, 830, 535 };
	o.type = WALL_LEFT;
	obs.push_back(o); // 5 floor - left_out


	o.size = { 270, 140, 275, 535 };
	o.type = WALL_LEFT;
	obs.push_back(o); // 5 floor - left_in

	o.size = { 805, 140, 810, 535 };
	o.type = WALL_RIGHT;
	obs.push_back(o); // 5 floor - right_in

	o.size = { 0, 445, 170, 450 };
	o.type = WALL_TOP;
	obs.push_back(o); // 6 floor - 1

	o.size = { 915, 445, 1100, 450 };
	o.type = WALL_TOP;
	obs.push_back(o); // 6 floor - 2

	o.size = { 0, 470, 170, 475 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 6 floor_bottom - 1

	o.size = { 915, 470, 1100, 475 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 6 floor_bottom - 2


	o.size = { 275, 390, 390, 395 };
	o.type = WALL_TOP;
	obs.push_back(o); // 7 floor - 1

	o.size = { 690, 390, 805, 395 };
	o.type = WALL_TOP;
	obs.push_back(o); // 7 floor - 2

	o.size = { 275, 410, 390, 415 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 7 floor_bottom - 1

	o.size = { 690, 410, 805, 415 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 7 floor_bottom - 2

	o.size = { 115, 120, 500, 125 };
	o.type = WALL_TOP;
	obs.push_back(o); // 8 floor - 1

	o.size = { 585, 120, 940, 125 };
	o.type = WALL_TOP;
	obs.push_back(o); // 8 floor - 2

	o.size = { 115, 145, 500, 150 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 8 floor_bottom - 1

	o.size = { 585, 145, 940, 150 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 8 floor_bottom - 2

	o.size = { 520, 240, 565, 245 };
	o.type = WALL_TOP;
	obs.push_back(o); // 9 floor - inner

	o.size = { 500, 380, 585, 385 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 9 floor_bottom - inner

	o.size = { 530, 385, 535, 535 };
	o.type = WALL_RIGHT;
	obs.push_back(o); // 9 floor - right_in

	o.size = { 550, 385, 555, 535 };
	o.type = WALL_LEFT;
	obs.push_back(o); // 9 floor - left_in

	o.size = { 0, 30, 1100, 35 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // top

	//////////////////////////////////////////////////

	o.size = { 310, 455, 360, 535 };
	o.type = MARIO_END;
	obs.push_back(o);

	o.size = { 725, 455, 775, 535 };
	o.type = LUIGI_END;
	obs.push_back(o);

	///////////////////////////////////////////////////

	o.size = { 30, 120, 120, 450 };
	o.type = JUMPSTEP;
	obs.push_back(o);

	o.size = { 965, 120, 1055, 450 };
	o.type = JUMPSTEP;
	obs.push_back(o);

	//////////////////////////////////////////////////

	o.size = { 200, 825, 360, 880 };
	o.type = MARIO;
	obs.push_back(o); 


	o.size = { 725, 825, 885, 880 };
	o.type = LUIGI;
	obs.push_back(o);

	o.size = { 725, 650, 885, 665 };
	o.type = MARIO;
	obs.push_back(o);

	o.size = { 200, 650, 360, 665 };
	o.type = LUIGI;
	obs.push_back(o);

	o.size = { 310, 385, 360, 400 };
	o.type = MARIO;
	obs.push_back(o);

	o.size = { 725, 385, 775, 400 };
	o.type = LUIGI;
	obs.push_back(o);

}

void HardGameScene::InitHearts()
{
	mario_life.Load(L"Image/mario_life.png");
	luigi_life.Load(L"Image/luigi_life.png");

	Obstacle o;

	o.size = { 300, 785, 330, 820 };
	o.type = MARIO_HEART;
	hearts.push_back(o);

	o.size = { 750, 785, 780, 820 };
	o.type = LUIGI_HEART;
	hearts.push_back(o);

	o.size = { 650, 620, 680, 655 };
	o.type = LUIGI_HEART;
	hearts.push_back(o);

	o.size = { 400, 620, 430, 655 };
	o.type = MARIO_HEART;
	hearts.push_back(o);

	o.size = { 340, 345, 370, 380 };
	o.type = MARIO_HEART;
	hearts.push_back(o);

	o.size = { 725, 345, 775, 380 };
	o.type = LUIGI_HEART;
	hearts.push_back(o);
}

void HardGameScene::CollisionCheck()
{
	RECT marioR = { mario->position.x, mario->position.y, mario->position.x + mario->imgWidth, mario->position.y + mario->imgHeight };
	RECT luigiR = { luigi->position.x, luigi->position.y, luigi->position.x + luigi->imgWidth, luigi->position.y + luigi->imgHeight };
	RECT tmp;

	for (Obstacle& o : obs) {
		if (IntersectRect(&tmp, &marioR, &o.size)) {
			mario->CheckWithWall(o);
		}
		if (IntersectRect(&tmp, &luigiR, &o.size)) {
			luigi->CheckWithWall(o);
		}
	}

	for (int i = 0; i < hearts.size(); ++i) {
		if (IntersectRect(&tmp, &marioR, &hearts[i].size)) {
			if (hearts[i].type == MARIO_HEART) {
				mario->CheckHearts(hearts[i]);
				hearts.erase(hearts.begin() + i);
			}
			break;
		}
		if (IntersectRect(&tmp, &luigiR, &hearts[i].size)) {
			if (hearts[i].type == LUIGI_HEART) {
				luigi->CheckHearts(hearts[i]);
				hearts.erase(hearts.begin() + i);
			}
			break;
		}
	}
}

void HardGameScene::GameEnd()
{
	if (mario->isEnd && luigi->isEnd) {
		Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
		Framework.CurScene = new BossGameScene;
		Framework.CurScene->Init();
		dynamic_cast<BossGameScene*>(Framework.CurScene)->mario->life = mario->life;
		dynamic_cast<BossGameScene*>(Framework.CurScene)->luigi->life = luigi->life;
		Framework.SceneIndex = HARD;
		delete scene;
	}
}

void HardGameScene::DrawTime(HDC hDC)
{
	HFONT hFont, oldFont;
	hFont = CreateFont(
		50,                        // 폰트 높이
		0,                         // 폰트 너비
		0,                         // 문자 기울기 각도
		0,                         // 베이스라인 기울기 각도
		FW_BOLD,                   // 폰트 두께
		TRUE,                     // 이탤릭체 여부
		FALSE,                     // 밑줄 여부
		FALSE,                     // 취소선 여부
		DEFAULT_CHARSET,           // 문자 집합
		OUT_DEFAULT_PRECIS,        // 출력 정확도
		CLIP_DEFAULT_PRECIS,       // 클리핑 정확도
		DEFAULT_QUALITY,           // 출력 품질
		DEFAULT_PITCH | FF_SWISS,  // 피치와 가족
		L"Times New Roman"                   // 폰트 이름
	);
	oldFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, RGB(255, 255, 0));
	TCHAR str[100];
	if (timeS / 17 == 61) {
		timeM += 1;
		timeS = 0;
	}
	wsprintf(str, L"%02d : %02d", timeM, timeS / 17);
	TextOut(hDC, 480, 0, str, lstrlen(str));

	SelectObject(hDC, oldFont);
	DeleteObject(hFont);
}

void HardGameScene::DrawUI(HDC hDC)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	float imageSize = 50;
	float lifeSize = 40;
	float drawY = 40;

	// mario
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	RoundRect(hDC, Framework.mainCamera->pos.x, drawY, imageSize + Framework.mainCamera->pos.x, drawY + imageSize, 10, 10);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	mario_img.Draw(hDC, Framework.mainCamera->pos.x, drawY, imageSize, imageSize, 0, 0, 1682, 1682);

	for (int i = 0; i < mario->life; i++)
	{
		life_img.Draw(hDC, imageSize + 10 + lifeSize * i + Framework.mainCamera->pos.x, drawY + imageSize / 2 - lifeSize / 2, lifeSize, lifeSize, 0, 0, 120, 120);
	}

	// luigi
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	RoundRect(hDC, Framework.mainCamera->pos.x + Framework.size.right - imageSize, drawY, Framework.size.right + Framework.mainCamera->pos.x, drawY + imageSize, 10, 10);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	luigi_img.Draw(hDC, Framework.mainCamera->pos.x + Framework.size.right - imageSize, drawY, imageSize, imageSize, 0, 0, 1494, 1494);

	for (int i = 0; i < luigi->life; i++)
	{
		life_img.Draw(hDC, Framework.mainCamera->pos.x + Framework.size.right - imageSize - 10 - lifeSize * i - lifeSize, drawY + imageSize / 2 - lifeSize / 2, lifeSize, lifeSize, 0, 0, 120, 120);
	}
}

////////////////////////////////////////////////////////////////////

HardGameScene::~HardGameScene()
{
	delete(mario);
	delete(luigi);
}

void HardGameScene::Init()
{
	backgroud.Load(L"Image/hard.png");

	mario_img.Load(L"Image/mario_image.png");
	luigi_img.Load(L"Image/luigi_image.png");
	life_img.Load(L"Image/life.png");

	InitPlayer();
	InitObstacles();
	InitHearts();
}

void HardGameScene::Update(const float frameTime)
{
	timeS++;
	mario->Move();
	luigi->Move();

	mario->CheckFloor();
	luigi->CheckFloor();

	mario->Flying();
	luigi->Flying();

	mario->PlayAnimation();
	luigi->PlayAnimation();

	CollisionCheck();

	GameEnd();
}

void HardGameScene::Draw(HDC hDC)
{
	backgroud.Draw(hDC, 0, 0, Framework.size.right, Framework.size.bottom, 0, 0, 800, 600);
	
	//for (Obstacle o : obs) {
	//	Rectangle(hDC, o.size.left, o.size.top, o.size.right, o.size.bottom);
	//}

	for (const Obstacle& o : hearts) {
		if (o.type == LUIGI_HEART) {
			luigi_life.Draw(hDC, o.size.left, o.size.top, 30, 34, 0, 0, 30, 34);
		}
		else {
			mario_life.Draw(hDC, o.size.left, o.size.top, 30, 34, 0, 0, 30, 34);
		}
	}

	DrawUI(hDC);

	DrawTime(hDC);


	mario->img.Draw(hDC, mario->position.x, mario->position.y,
		mario->imgWidth, mario->imgHeight,
		mario->imgWidth * mario->imgIndex, mario->imgHeight * mario->animIndex,
		mario->imgWidth, mario->imgHeight);
	luigi->img.Draw(hDC, luigi->position.x, luigi->position.y,
		luigi->imgWidth, luigi->imgHeight,
		luigi->imgWidth * luigi->imgIndex, luigi->imgHeight * luigi->animIndex,
		luigi->imgWidth, luigi->imgHeight);


}

void HardGameScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
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
		if (wParam == VK_B) {
			Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
			Framework.CurScene = new BossGameScene;
			Framework.CurScene->Init();
			dynamic_cast<HardGameScene*>(Framework.CurScene)->mario->life = mario->life;
			dynamic_cast<HardGameScene*>(Framework.CurScene)->luigi->life = luigi->life;
			Framework.SceneIndex = HARD;
			delete scene;
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
