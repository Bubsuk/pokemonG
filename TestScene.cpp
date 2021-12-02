#include "TestScene.h"
#include "Image.h"
#include "Jiwoo.h"

HRESULT TestScene::Init()
{
    mBackGround = IMG_MGR->FindImage(eImageTag::StartRoom);

    mJiwoo = new Jiwoo;
    mJiwoo->Init();


    return S_OK;
}

void TestScene::Update()
{
    SAFE_UPDATE(mJiwoo);
}

void TestScene::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, WHITENESS);

    if (mBackGround)
    {
        mBackGround->Render(hdc);
    }
    
    mJiwoo->Render(hdc);
}

void TestScene::Release()
{
    SAFE_RELEASE(mJiwoo);
}
