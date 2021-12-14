#pragma once
#include "Config.h"
#include "Singleton.h"

class CameraManager : public Singleton<CameraManager>
{
private:
	POINT mObjectPos = {};
	POINT mMaxPos = {};
	// 보간에서 이동거리
	POINT mStartPos;
	POINT mDestPos;
	// 보정 시간값
	float mRivisedDurTimeX = {};
	float mRivisedDurTimeY = {};
	float mElapsedTime = {};

public:	
	// 전체 오브젝트들 위치이동으로 카메라효과
	POINT GetCamPos();

	void MovePos(POINT& destPos, float durTime, eDir dir);

	// 워프
	void SetPos(POINT& warfPos);

};

