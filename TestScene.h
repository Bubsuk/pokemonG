#pragma once
#include "GameEntity.h"

class Jiwoo;
class Image;
class TestScene : public GameEntity
{
private:
	Jiwoo* mJiwoo;

	Image* mBackGround = nullptr;
public:
	HRESULT Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
};