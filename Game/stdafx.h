#pragma once

// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#define _CRT_SECURE_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <atlimage.h>
#include <mmsystem.h>

// C 런타임 헤더 파일입니다.
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
#include "Ray.h"
#include "Particle.h"
#include "Obstacle.h"
#include "Player.h"
#include "Ball.h"
#include "Scene.h"
#include "BossGameScene.h"
#include "HardGameScene.h"
#include "EasyGameScene.h"
#include "LobbyScene.h"
#include "GameOverScene.h"
#include "ClearScene.h"
#include "GameFramework.h"



// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
