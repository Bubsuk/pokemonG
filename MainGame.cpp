#include "Config.h"
#include "MainGame.h"
#include "Image.h"
#include "CommonFunction.h"
#include "TestScene.h"
#include "MapScene.h"

#define TILETOOL

HRESULT MainGame::Init()
{
	KEY_MGR->Init();
	IMG_MGR->Init();
	TIMER_MGR->Init();
	SCENE_MGR->Init();

	SCENE_MGR->AddScene(eSceneTag::TestScene, new TestScene);
	SCENE_MGR->AddScene(eSceneTag::MapToolScene, new MapScene);

	srand((unsigned int)time(nullptr));

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	mousePosX = 0;
	mousePosY = 0;
	clickedMousePosX = 0;
	clickedMousePosY = 0;

	// 백버퍼 맥스사이즈 다시보기
	backBuffer = new Image();

#ifdef TILETOOL
	SCENE_MGR->ChangeScene(eSceneTag::MapToolScene);
	int maxSizeX = TILE_MAP_TOOL_X;
	int maxSizeY = TILE_MAP_TOOL_Y;

#else
	SCENE_MGR->ChangeScene(eSceneTag::TestScene);
	int maxSizeX = WIN_SIZE_X;
	int maxSizeY = WIN_SIZE_Y;
#endif // TILETOOL

	backBuffer->Init("Image/mapImage.bmp", maxSizeX, maxSizeY);

	return S_OK;
}

void MainGame::Update()
{
	TIMER_MGR->Update();
	SCENE_MGR->Update();
	KEY_MGR->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	//PatBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, WHITENESS);
	HDC hBackBufferDC = backBuffer->GetMemDC();

	SCENE_MGR->Render(hBackBufferDC);
	TIMER_MGR->Render(hBackBufferDC);

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	TIMER_MGR->Release();
	TIMER_MGR->ReleaseSingleton();

	KEY_MGR->Release();
	KEY_MGR->ReleaseSingleton();

	SCENE_MGR->Release();
	SCENE_MGR->ReleaseSingleton();



	KillTimer(g_hWnd, 0);
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_SIZE:
		SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y);
		break;
	case WM_LBUTTONDOWN:
		clickedMousePosX = LOWORD(lParam);
		clickedMousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
