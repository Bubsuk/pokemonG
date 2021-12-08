#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

#pragma comment(lib, "winmm.lib")


#define WIN_START_POS_X	100
#define WIN_START_POS_Y	100
#define WIN_SIZE_X	1600 //640
#define WIN_SIZE_Y	960 //576

#define PI 3.14159265357989
#define PI2 (3.14159265357989 * 2)

#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }
#define SAFE_UPDATE(p) { if (p) { p->Update(); } }
#define SAFE_RENDER(p) { if (p) { p->Render(hdc); } }

#include "Header.h"
#include "Macro.h"
#include "Enum.h"
#include "TimerManager.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

#define TIMER_MGR TimerManager::GetSingleton()
#define KEY_MGR KeyManager::GetSingleton()
#define SCENE_MGR SceneManager::GetSingleton()
#define IMG_MGR ImageManager::GetSingleton()

#define DELTA_TIME TIMER_MGR->GetDeltaTime()

#define TILE_START_POS_X ((WIN_SIZE_X - (TILE_SIZE * TILE_COUNT_X)) / 2)
#define TILE_START_POS_Y ((WIN_SIZE_Y - (TILE_SIZE * TILE_COUNT_Y)) / 2)

#define RANDOM(min, max) (rand() % ((max) - (min) + 1) + (min))

#define SAMPLE_TILE_SIZE 40
#define TILE_SIZE	64
#define TILE_MAP_TOOL_X 1600
#define TILE_MAP_TOOL_Y 960
#define TILE_COUNT_X	130
#define TILE_COUNT_Y	40
#define SAMPLE_TILE_COUNT_X	15
#define SAMPLE_TILE_COUNT_Y	15



extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
