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
	// ������ ���� Ÿ�� ��ǥ��ǥ
	POINT mDestPos;
	// ī�޶�
	POINT mMovePixel;
	// �巡�׷� Ÿ�� ����
	POINT mClickStart;
	POINT mCLickEnd;
	// �巡�� ���ð��� ���밪
	POINT mClickArea;
	// ����Ÿ�Ͽ��� ���õ� Ÿ���� ��ǥ��
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

