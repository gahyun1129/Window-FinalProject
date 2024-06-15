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
	luigi->position = { 20, 500 };

	mario->type = MARIO;
	luigi->type = LUIGI;
}

void EasyGameScene::InitObstacles()
{
	Obstacle o;
	o.size = { 0, 730, 350, 735 };
	o.type = WALL_BOTTOM;
	obs.push_back(o); // 0

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
	obs.push_back(o); // 31

	switchElevator.size = { 35, 450, 120, 475 };
	switchElevator.img.Load(L"image/elevator.png");
	switchElevator.minLv = 450;
	switchElevator.maxLv = 530;


}

void EasyGameScene::CollisionCheck()
{
	RECT marioR = {mario->position.x, mario->position.y, mario->position.x + mario->imgWidth, mario->position.y + mario->imgHeight};
	RECT luigiR = {luigi->position.x, luigi->position.y, luigi->position.x + luigi->imgWidth, luigi->position.y + luigi->imgHeight};
	RECT tmp;

	for (Obstacle& o : obs) {
		if (IntersectRect(&tmp, &marioR, &o.size)) {
			mario->CheckWithWall(o);
			if (o.type == SWITCHSTICK) {
				switchStick.index = o.index;
				if (switchStick.index == 1) {
					switchElevator.isUp = false;
					switchElevator.isDown = true;
					obs[31].isUp = false;
					obs[31].isDown = true;
				}
				else if (switchStick.index == 0) {
					switchElevator.isUp = true;
					switchElevator.isDown = false;
					obs[31].isUp = true;
					obs[31].isDown = false;
				}
			}
			break;
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
					obs[31].isUp = false;
					obs[31].isDown = true;
				}
				else if (switchStick.index == 0) {
					switchElevator.isUp = true;
					switchElevator.isDown = false;
					obs[31].isUp = true;
					obs[31].isDown = false;
				}
			}
			break;
		}
	}
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
	mario->Move();
	luigi->Move();

	mario->CheckFloor();
	luigi->CheckFloor();

	mario->PlayAnimation();
	luigi->PlayAnimation();

	CollisionCheck();

	switchElevator.MoveElevator();
	obs[31].MoveElevator();
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

	for (Obstacle o : obs) {
		Rectangle(hDC, o.size.left, o.size.top, o.size.right, o.size.bottom);
	}

	switchStick.img.Draw(hDC, switchStick.size.left, switchStick.size.top, 72, 29, 72 * switchStick.index, 0, 72, 29);
	switchElevator.img.Draw(hDC, switchElevator.size.left, switchElevator.size.top, 85, 20, 0, 0, 85, 20);
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

