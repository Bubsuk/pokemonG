#pragma once
#include "GameEntity.h"


typedef struct TagTile
{
	eTerrain Terrain;
	RECT Rc;
	POINT TilePos;

} TILE_INFO, SAMPLE_TILE_INFO;

class Jiwoo;
class Image;
class MapEditor : public GameEntity
{
public:
	struct SampleMouse
	{
		POINT start = {};
		POINT end = {};
	};	


protected:
	Jiwoo* mTestJiwoo;

	Image* mSampleTileImage;
	Image* mDrawTileImage;
	Image* mBackground;

	RECT mSampleArea;
	RECT mDrawArea;

	TILE_INFO mTileInfo[TILE_COUNT_X * TILE_COUNT_Y];
	SAMPLE_TILE_INFO mSampleTileInfo[SAMPLE_TILE_COUNT_X * SAMPLE_TILE_COUNT_Y];
	SAMPLE_TILE_INFO mSelectedTile;
	
	eDir mDir;

	bool mbControl  = {};
	bool mbIsClick = {};
	bool mbNeedRevise = {};

	float mRivisedDurTime = {};
	float mOneTileTime = {};

	int mMoveSpeed;
	// 보간을 위한 타일 목표좌표
	POINT mDestPos;
	// 카메라
	POINT mMovePixel;
	// 드래그로 타일 선택
	POINT mClickStart;
	POINT mCLickEnd;
	// 드래그 선택값의 절대값
	POINT mClickArea;
	// 샘플타일에서 선택된 타일의 좌표값
	POINT mClickIndex;


	string mSaveIndex = {};
	char mSave[10] = {};
	char mSampleText[256];

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void SaveMap(string index);
	void LoadMap(string index);

	

};

