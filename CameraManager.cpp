#include "stdafx.h"
#include "CameraManager.h"
#include <cmath>

POINT CameraManager::GetCamPos()
{
	return mObjectPos;
}

// 보간 적용
void CameraManager::MovePos(POINT& destPos, float durTime, eDir dir)
{

	mStartPos = mObjectPos;

	switch (dir)
	{
	case eDir::Right:
		mElapsedTime += DELTA_TIME;
		if (mObjectPos.x >= -TILE_SIZE * TILE_COUNT_X)
		{
			mObjectPos.x = mStartPos.x - fabs(destPos.x - mStartPos.x) * mElapsedTime / durTime;
		}
		cout << "mObjectPos.x : " << mObjectPos.x << endl;
		
		if (mElapsedTime >= durTime)
		{
			mObjectPos.x = destPos.x;
			mElapsedTime = 0.0f;
		}
		cout << "mRivisedDurTimeX : " << durTime << endl;
		cout << "Distance : " << fabs(destPos.x - mStartPos.x) << endl;
		break;
	case eDir::Left:
		mElapsedTime += DELTA_TIME;
		if (mObjectPos.x <= 0)
		{
			mObjectPos.x = mStartPos.x + fabs(destPos.x - mStartPos.x) * mElapsedTime / durTime;
		}

		if (mElapsedTime >= durTime)
		{
			mObjectPos.x = destPos.x;
			mElapsedTime = 0.0f;
		}

		cout << "mRivisedDurTimeX : " << durTime << endl;
		cout << "Distance : " << fabs(destPos.x - mStartPos.x) << endl;
		break;
	case eDir::Up:
		mElapsedTime += DELTA_TIME;
		if (mObjectPos.y <= 0)
		{
			mObjectPos.y = mStartPos.y + fabs(destPos.y - mStartPos.y) * mElapsedTime / durTime;
			cout << "mObjectPos.y : " << mObjectPos.y << endl;
		}

		if (mElapsedTime >= durTime)
		{
			mObjectPos.y = destPos.y;
			mElapsedTime = 0.0f;
		}
		cout << "mRivisedDurTimeY : " << durTime << endl;
		cout << "Distance : " << fabs(mStartPos.y - destPos.y) << endl;
		break;
	case eDir::Down:
		mElapsedTime += DELTA_TIME;
		if (mObjectPos.y >= -TILE_SIZE * TILE_COUNT_Y)
		{
			mObjectPos.y = mStartPos.y - fabs(destPos.y - mStartPos.y) * mElapsedTime / durTime;
			cout << "mObjectPos.y : " << mObjectPos.y << endl;
		}

		if (mElapsedTime >= durTime)
		{
			mObjectPos.y = destPos.y;
			mElapsedTime = 0.0f;
		}
		cout << "mRivisedDurTimeY : " << durTime << endl;
		cout << "Distance : " << fabs(destPos.y - mStartPos.y) << endl;
		break;
	}

	//while (mElapsedTime <= durTime)
	//{
	//	mElapsedTime += DELTA_TIME;
	//	mObjectPos.x = mStartPos.x + (mDestPos.x - mStartPos.x) * mElapsedTime / durTime;
	//	mObjectPos.y = mStartPos.y + (mDestPos.y - mStartPos.y) * mElapsedTime / durTime;
	//	cout << mElapsedTime << endl;
	//}
	
}

void CameraManager::SetPos(POINT& movePos)
{
	mObjectPos = movePos;
}
