#pragma once
#include "GameEntity.h"

class MapEditor;
class MapScene : public GameEntity
{
private:
	MapEditor* mMapEditor;

public:

	HRESULT Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
};

