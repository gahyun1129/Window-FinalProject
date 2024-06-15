#include "stdafx.h"

extern GameFramework Framework;

void EasyGameScene::InitPlayer()
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
	luigi->position = { 20, 670 };

	mario->type = MARIO;
	luigi->type = LUIGI;
}

void EasyGameScene::InitObstacles()
{
	Obstacle o;

	////////////////////////////////////////////////////////

	o.size = { 300, 435, 346, 450 };
	o.type = BUTTON1;
	obs.push_back(o); // 0

	buttonDown.size = { 300, 435, 346, 450 };
	buttonDown.img.Load(L"image/button.png");

	o.size = { 820, 315, 866, 330 };
	o.type = BUTTON2;
	obs.push_back(o); // 1

	buttonUp.size = { 820, 315, 866, 330 };
	buttonUp.img.Load(L"image/button.png");

	/////////////////////////////////////////////////////////
	o.size = { 0, 730, 350, 735 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 2

	o.size = { 0, 715, 350, 720 };
	o.type = WALL_TOP;
	obs.push_back(o); // 1


	o.size = { 970, 770, 980, 840 };
	o.type = WALL_RIGHT;
	obs.push_back(o); // 2


	o.size = { 990, 740, 1100, 745 };
	o.type = WALL_TOP;
	obs.push_back(o); // 3

	o.size = { 450, 670, 930, 675 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 4

	o.size = { 450, 655, 940, 660 };
	o.type = WALL_TOP;
	obs.push_back(o); // 5

	o.size = { 0, 610, 450, 615 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 6

	o.size = { 0, 595, 450, 600 };
	o.type = WALL_TOP;
	obs.push_back(o); // 7

	o.size = { 140, 465, 500, 470 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 8

	o.size = { 140, 450, 560, 455 };
	o.type = WALL_TOP;
	obs.push_back(o); // 9

	o.size = { 530, 495, 900, 500 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 10

	o.size = { 910, 530, 940, 535 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 11

	o.size = { 990, 585, 1100, 590 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 12

	o.size = { 560, 475, 1100, 480 };
	o.type = WALL_TOP;
	obs.push_back(o); // 13

	o.size = { 0, 345, 780, 350 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 14

	o.size = { 800, 375, 940, 380 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 15

	o.size = { 160, 330, 550, 335 };
	o.type = WALL_TOP;
	obs.push_back(o); // 16

	o.size = { 550, 270, 750, 275 };
	o.type = WALL_TOP;
	obs.push_back(o); // 17

	o.size = { 800, 330, 940, 335 };
	o.type = WALL_TOP;
	obs.push_back(o); // 18

	o.size = { 0, 210, 160, 215 };
	o.type = WALL_TOP;
	obs.push_back(o); // 19

	o.size = { 330, 260, 470, 265 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 20

	o.size = { 470, 200, 1100, 205 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 21

	o.size = { 270, 140, 300, 145 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 22

	o.size = { 275, 120, 355, 125 };
	o.type = WALL_TOP;
	obs.push_back(o); // 23

	o.size = { 385, 150, 420, 155 };
	o.type = WALL_TOP;
	obs.push_back(o); // 24

	o.size = { 445, 180, 1100, 185 };
	o.type = WALL_TOP;
	obs.push_back(o); // 25

	o.size = { 0, 830, 1100, 835 };
	o.type = WALL_TOP;
	obs.push_back(o); // 26

	////////////////////////////////////////////////////////

	o.size = { 530, 825, 600, 880 };
	o.type = MARIO;
	obs.push_back(o); // 27

	o.size = { 750, 825, 820, 880 };
	o.type = LUIGI;
	obs.push_back(o); // 28


	o.size = { 700, 650, 770, 660 };
	o.type = BOTH;
	obs.push_back(o); // 29

	////////////////////////////////////////////////////////

	o.size = { 225, 570, 297, 599 };
	o.type = SWITCHSTICK;
	obs.push_back(o); // 30

	switchStick.size = { 225, 570, 297, 599 };
	switchStick.img.Load(L"image/key.png");

	////////////////////////////////////////////////////////

	o.size = { 35, 450, 120, 475 };
	o.type = WALL_TOP;
	o.minLv = 450;
	o.maxLv = 530;
	obs.push_back(o); // 33

	switchElevator.size = { 35, 450, 120, 475 };
	switchElevator.img.Load(L"image/elevator.png");
	switchElevator.minLv = 450;
	switchElevator.maxLv = 530;

	o.size = { 950, 350, 1035, 375 };
	o.type = WALL_TOP;
	o.minLv = 350;
	o.maxLv = 430;
	obs.push_back(o); // 34

	buttonElevator.size = { 950, 350, 1035, 375 };
	buttonElevator.img.Load(L"image/elevator.png");
	buttonElevator.minLv = 350;
	buttonElevator.maxLv = 430;

	o.size = { 160, 210, 240, 215 };
	o.type = WALL_TOP;
	obs.push_back(o);

	box.size = { 160, 210, 280, 215 };
	box.img.Load(L"image/box.png");

	///////////////////////////////////////////////

	o.size = { 240, 210, 245, 330 };
	o.type = WALL_LEFT;
	obs.push_back(o);

	o.size = { 330, 170, 335, 260 };
	o.type = WALL_RIGHT;
	obs.push_back(o);

	o.size = { 460, 200, 465, 260 };
	o.type = WALL_RIGHT;
	obs.push_back(o);


	o.size = { 550, 280, 555, 330 };
	o.type = WALL_LEFT;
	obs.push_back(o);

	////////////////////////////////////////////////

	o.size = { 990, 100, 1030, 180 };
	o.type = MARIO_END;
	obs.push_back(o);

	o.size = { 890, 100, 930, 180 };
	o.type = LUIGI_END;
	obs.push_back(o);
}

void EasyGameScene::CollisionCheck()
{
	RECT marioR = {mario->position.x, mario->position.y, mario->position.x + mario->imgWidth, mario->position.y + mario->imgHeight};
	RECT luigiR = {luigi->position.x, luigi->position.y, luigi->position.x + luigi->imgWidth, luigi->position.y + luigi->imgHeight};
	RECT tmp;

	buttonDown.index = 0;
	buttonUp.index = 0;
	buttonElevator.isDown = false;
	buttonElevator.isUp = true;
	obs[34].isUp = true;
	obs[34].isDown = false;

	for (Obstacle& o : obs) {
		if (IntersectRect(&tmp, &marioR, &o.size)) {
			mario->CheckWithWall(o);
			if (o.type == SWITCHSTICK) {
				switchStick.index = o.index;
				if (switchStick.index == 1) {
					switchElevator.isUp = false;
					switchElevator.isDown = true;
					obs[33].isUp = false;
					obs[33].isDown = true;
				}
				else if (switchStick.index == 0) {
					switchElevator.isUp = true;
					switchElevator.isDown = false;
					obs[34].isUp = true;
					obs[34].isDown = false;
				}
			}
			else if (o.type == BUTTON1) {
				buttonDown.index = 1;
				buttonElevator.isDown = true;
				buttonElevator.isUp = false;
				obs[34].isUp = false;
				obs[34].isDown = true;
			}
			else if (o.type == BUTTON2) {
				buttonUp.index = 1;
				buttonElevator.isDown = true;
				buttonElevator.isUp = false;
				obs[34].isUp = false;
				obs[34].isDown = true;
			}
		}
	}
	for (Obstacle& o : obs) {
		if (IntersectRect(&tmp, &luigiR, &o.size)) {
			luigi->CheckWithWall(o);
			if (o.type == SWITCHSTICK) {
				switchStick.index = o.index;
				if (switchStick.index == 1) {
					switchElevator.isUp = false;
					switchElevator.isDown = true;
					obs[33].isUp = false;
					obs[33].isDown = true;
				}
				else if (switchStick.index == 0) {
					switchElevator.isUp = true;
					switchElevator.isDown = false;
					obs[33].isUp = true;
					obs[33].isDown = false;
				}
			}
			else if (o.type == BUTTON1) {
				buttonDown.index = 1;
				buttonElevator.isDown = true;
				buttonElevator.isUp = false;
				obs[34].isUp = false;
				obs[34].isDown = true;
			}
			else if (o.type == BUTTON2) {
				buttonUp.index = 1;
				buttonElevator.isDown = true;
				buttonElevator.isUp = false;
				obs[34].isUp = false;
				obs[34].isDown = true;
			}
		}
	}
}

void EasyGameScene::GameEnd()
{
	if (mario->isEnd && luigi->isEnd) {
		Scene* scene = Framework.CurScene;   // 현재 씬을 tmp에 넣고 지워줌
		Framework.CurScene = new HardGameScene;
		Framework.CurScene->Init();
		Framework.SceneIndex = NORMAL;
		delete scene;
	}
}

void EasyGameScene::DrawTime(HDC hDC)
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
	wsprintf(str, L"%02d : %02d", timeM, timeS /17);
	TextOut(hDC, 480, 0, str, lstrlen(str));

	SelectObject(hDC, oldFont);
	DeleteObject(hFont);
}

EasyGameScene::~EasyGameScene()
{
	delete(mario);
	delete(luigi);
}

void EasyGameScene::Init()
{
	backgroud.Load(L"Image/easy.png");

	InitPlayer();
	InitObstacles();

}

void EasyGameScene::Update(const float frameTime)
{

	timeS ++;
	mario->Move();
	luigi->Move();

	mario->CheckFloor();
	luigi->CheckFloor();

	mario->PlayAnimation();
	luigi->PlayAnimation();

	CollisionCheck();

	switchElevator.MoveElevator();
	obs[33].MoveElevator();

	buttonElevator.MoveElevator();
	obs[34].MoveElevator();

	GameEnd();

}

void EasyGameScene::Draw(HDC hDC)
{
	backgroud.Draw(hDC, 0, 0, Framework.size.right, Framework.size.bottom, 0, 0, 800, 600);
	mario->img.Draw(hDC, mario->position.x, mario->position.y, 
						mario->imgWidth, mario->imgHeight, 
						mario->imgWidth * mario->imgIndex, mario->imgHeight * mario->animIndex,
						mario->imgWidth, mario->imgHeight);
	luigi->img.Draw(hDC, luigi->position.x, luigi->position.y,
		luigi->imgWidth, luigi->imgHeight,
		luigi->imgWidth * luigi->imgIndex, luigi->imgHeight * luigi->animIndex,
		luigi->imgWidth, luigi->imgHeight);

	//for (Obstacle o : obs) {
	//	Rectangle(hDC, o.size.left, o.size.top, o.size.right, o.size.bottom);
	//}

	switchStick.img.Draw(hDC, switchStick.size.left, switchStick.size.top, 72, 29, 72 * switchStick.index, 0, 72, 29);
	switchElevator.img.Draw(hDC, switchElevator.size.left, switchElevator.size.top, 85, 20, 0, 0, 85, 20);
	
	if (buttonDown.index == 0) {
		buttonDown.img.Draw(hDC, buttonDown.size.left, buttonDown.size.top, 46, 15, 0, 0, 46, 15);
	}

	buttonElevator.img.Draw(hDC, buttonElevator.size.left, buttonElevator.size.top, 85, 20, 0, 0, 85, 20);
	
	if (buttonUp.index == 0) {
		buttonUp.img.Draw(hDC, buttonUp.size.left, buttonUp.size.top, 46, 15, 0, 0, 46, 15);
	}

	box.img.Draw(hDC, box.size.left, box.size.top, 43, 43, 0, 0, 43, 43);
	box.img.Draw(hDC, box.size.left, box.size.top + 42, 43, 43, 0, 0, 43, 43);
	box.img.Draw(hDC, box.size.left, box.size.top + 42 * 2, 43, 43, 0, 0, 43, 43);

	box.img.Draw(hDC, box.size.left + 42, box.size.top, 43, 43, 0, 0, 43, 43);
	box.img.Draw(hDC, box.size.left + 42, box.size.top + 42, 43, 43, 0, 0, 43, 43);
	box.img.Draw(hDC, box.size.left + 42, box.size.top + 42 * 2, 43, 43, 0, 0, 43, 43);

	DrawTime(hDC);
}

void EasyGameScene::ProcessKey(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_W) {
			if ( !mario->isJump && !mario->isFalling)
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

