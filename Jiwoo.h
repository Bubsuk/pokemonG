#pragma once
#include "GameObject.h"

class Jiwoo : public GameObject
{
private:
	Image* mImageRunRL = nullptr;
	Image* mImageRunUD = nullptr;

	eDir mState;

	int frameX = 0;
	int frameY = 0;

	const float MAX_ANIM_TIME = 0.1f;
	float mElapsedCount = 0.0f;

public:
	virtual ~Jiwoo() {}
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

};

