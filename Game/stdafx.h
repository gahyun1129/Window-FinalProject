#pragma once

// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ Ư�� ���� ������ ��� �ִ�
// ���� �����Դϴ�.
//

#define _CRT_SECURE_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
#include <atlimage.h>
#include <mmsystem.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
#include <windef.h>
#include <assert.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::chrono;

#include "define.h"
#include "Camera.h"
#include "Boss.h"
#include "FireBall.h"
#include "Obstacle.h"
#include "Player.h"
#include "Scene.h"
#include "BossGameScene.h"
#include "EasyGameScene.h"
#include "LobbyScene.h"
#include "GameFramework.h"



// ���⼭ ���α׷��� �ʿ��� �߰� ����� �����մϴ�.
