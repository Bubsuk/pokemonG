#include "stdafx.h"
#include "Config.h"
#include "Jiwoo.h"
#include "Image.h"

HRESULT Jiwoo::Init()
{
    mImage = IMG_MGR->FindImage(eImageTag::Jiwoo_idle);
    mImageRunRL = IMG_MGR->FindImage(eImageTag::Jiwoo_moveRL);
    mImageRunUD = IMG_MGR->FindImage(eImageTag::Jiwoo_moveUD);

    if (mImage == nullptr || mImageRunRL == nullptr || mImageRunUD == nullptr)
    {
        return E_FAIL;
    }


    mPos.x = WIN_SIZE_X / 2 - 32;
    mPos.y = WIN_SIZE_Y / 2;

    mState = eDir::Idle;

    return S_OK;
}

void Jiwoo::Update()
{
    if (KEY_MGR->IsStayKeyDown(VK_DOWN))
    {
      /*  mElapsedCount += DELTA_TIME;
        if (mElapsedCount >= MAX_ANIM_TIME)
        {
            mElapsedCount -= MAX_ANIM_TIME;

        }*/
        mState = eDir::Down;
    }
    else if (KEY_MGR->IsOnceKeyDown(VK_UP))
    {
        mState = eDir::Up;
    }
    else if (KEY_MGR->IsOnceKeyDown(VK_LEFT))
    {
        mState = eDir::Left;
    }
    else if (KEY_MGR->IsOnceKeyDown(VK_RIGHT))
    {
        mState = eDir::Right;
    }
}

void Jiwoo::Render(HDC hdc)
{
    
    switch (mState)
    {
    case eDir::Idle:
        mImage->Render(hdc, mPos.x, mPos.y, frameX + 1, frameY);
        break;
    case eDir::Up:
        mImageRunUD->Render(hdc, mPos.x, mPos.y, frameX, frameY + 1);
        break;
    case eDir::Down:
        mImageRunUD->Render(hdc, mPos.x, mPos.y, frameX, frameY);
        break;
    case eDir::Right:
        mImageRunRL->Render(hdc, mPos.x, mPos.y, frameX, frameY);
        break;
    case eDir::Left:
        mImageRunRL->Render(hdc, mPos.x, mPos.y, frameX, frameY + 1);
        break;
    }
    
}


void Jiwoo::Release()
{
    GameObject::Release();
}
