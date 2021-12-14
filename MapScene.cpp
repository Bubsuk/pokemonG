#include "stdafx.h"
#include "MapScene.h"
#include "MapEditor.h"
#include "CommonFunction.h"

HRESULT MapScene::Init()
{
    SetWindowSize(40, 40, TILE_MAP_TOOL_X, TILE_MAP_TOOL_Y);

    mMapEditor = new MapEditor;
    mMapEditor->Init();

    if (mMapEditor == nullptr)
    {
        cout << "aa" << '\n';
        return E_FAIL;
    }

    return S_OK;
}

void MapScene::Update()
{
    mMapEditor->Update();
}

void MapScene::Render(HDC hdc)
{
    mMapEditor->Render(hdc);
}

void MapScene::Release()
{
    SAFE_RELEASE(mMapEditor);
}
