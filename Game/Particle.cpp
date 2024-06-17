#include "stdafx.h"

void Particle::Init(const POINT center)
{
	img.Load(L"Image/Enemy.png");

	offsetX = 58;
	offsetY = 58;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> disX(center.x - 20, center.x + 20);
	std::uniform_real_distribution<> disY(center.y - 20, center.y + 20);

	position.x = disX(gen);
	position.y = disY(gen);
}

void Particle::Draw(HDC hDC, int sceneX)
{
	img.Draw(hDC, position.x - sceneX - offsetX * 1.5f / 2, position.y - offsetY * 1.5f / 2,	// �����쿡 �׸� ��ġ
				  offsetX * 1.5f, offsetY * 1.5f,						// �����쿡 �׷��� ũ��(����,����)
				  698 + offsetX * imgIndex, offsetY * 6,				// �̹��� �󿡼� ������ ��ġ
				  offsetX, offsetY);									// �̹��� �󿡼� ������ ũ��(����,����)
}
