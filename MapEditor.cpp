#include "stdafx.h"
#include "MapEditor.h"
#include "CameraManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Jiwoo.h"
#include <cmath>

HRESULT MapEditor::Init()
{
	SetWindowSize(40, 40, TILE_MAP_TOOL_X, TILE_MAP_TOOL_Y);

	mSampleTileImage = IMG_MGR->FindImage(eImageTag::SampleTile);
	mDrawTileImage = IMG_MGR->FindImage(eImageTag::DrawTile);
	mBackground = IMG_MGR->FindImage(eImageTag::Background);


	mTestJiwoo = new Jiwoo;
	mTestJiwoo->Init();

	mMoveSpeed = 300;
	mMovePixel = { 0,0 };

	mOneTileTime = 1.0f;
	
	if (mSampleTileImage == nullptr)
	{
		cout << "SmapleTile �ε� ����" << '\n';
		return E_FAIL;
	}

	// �׸����� ��ü(1Ÿ�ϴ� 64�ȼ�)
	for (int i = 0; i < TILE_COUNT_Y; ++i)
	{
		for (int j = 0; j < TILE_COUNT_X; ++j)
		{
			SetRect(&(mTileInfo[i * TILE_COUNT_X + j].Rc),
				j * TILE_SIZE + CAM_MGR->GetCamPos().x,
				i * TILE_SIZE + CAM_MGR->GetCamPos().y,
				TILE_SIZE + j * TILE_SIZE + CAM_MGR->GetCamPos().x,
				TILE_SIZE + i * TILE_SIZE + CAM_MGR->GetCamPos().y);

			mTileInfo[i * TILE_COUNT_X + j].TilePos.x = 11;
			mTileInfo[i * TILE_COUNT_X + j].TilePos.y = 2;

			mTileInfo[i * TILE_COUNT_X + j].Terrain = eTerrain::Close;
		}

	}
	

	// ������ ��� ���ÿ���(1Ÿ�ϴ� 40�ȼ�)
	for (int i = 0; i < SAMPLE_TILE_COUNT_Y; ++i)
	{
		for (int j = 0; j < SAMPLE_TILE_COUNT_X; ++j)
		{
			SetRect(&(mSampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].Rc),
				TILE_MAP_TOOL_X - mSampleTileImage->GetWidth() + j * SAMPLE_TILE_SIZE,
				i * SAMPLE_TILE_SIZE,
				TILE_MAP_TOOL_X - mSampleTileImage->GetWidth() + j * SAMPLE_TILE_SIZE + SAMPLE_TILE_SIZE,
				i * SAMPLE_TILE_SIZE + SAMPLE_TILE_SIZE);

			mSampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].TilePos.x = j;
			mSampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].TilePos.y = i;

			// Ÿ�Ϻ� �Ӽ� ����
			if (0 <= (i * SAMPLE_TILE_COUNT_X + j) && (i * SAMPLE_TILE_COUNT_X + j) <= 7 || (i * SAMPLE_TILE_COUNT_X + j) == 9
				|| (i * SAMPLE_TILE_COUNT_X + j) == 24 || (i * SAMPLE_TILE_COUNT_X + j) == 25 || 50 <= (i * SAMPLE_TILE_COUNT_X + j)
				&& (i * SAMPLE_TILE_COUNT_X + j) <= 52 || (i * SAMPLE_TILE_COUNT_X + j) == 58 || (i * SAMPLE_TILE_COUNT_X + j) == 77
				|| (i * SAMPLE_TILE_COUNT_X + j) == 78 || (i * SAMPLE_TILE_COUNT_X + j) == 80 || (i * SAMPLE_TILE_COUNT_X + j) == 158
				|| (i * SAMPLE_TILE_COUNT_X + j) == 159 || 176 <= (i * SAMPLE_TILE_COUNT_X + j) || (i * SAMPLE_TILE_COUNT_X + j) <= 178
				|| 191 <= (i * SAMPLE_TILE_COUNT_X + j) && (i * SAMPLE_TILE_COUNT_X + j) <= 193 || 206 <= (i * SAMPLE_TILE_COUNT_X + j)
				|| (i * SAMPLE_TILE_COUNT_X + j) <= 208 || (i * SAMPLE_TILE_COUNT_X + j) == 211)
			{
				mSampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].Terrain = eTerrain::Open;
			}
			else if ((i * SAMPLE_TILE_COUNT_X + j) == 8) 
			{
				mSampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].Terrain = eTerrain::Grass;
			}
			else if ((21 <= (i * SAMPLE_TILE_COUNT_X + j) && (i * SAMPLE_TILE_COUNT_X + j) <= 23 || (i * SAMPLE_TILE_COUNT_X + j) == 112
					|| (i * SAMPLE_TILE_COUNT_X + j) == 162))
			{
				mSampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].Terrain = eTerrain::Door;
			}
			else if ((i * SAMPLE_TILE_COUNT_X + j) == 16 || (i * SAMPLE_TILE_COUNT_X + j) == 17)
			{
				mSampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].Terrain = eTerrain::BottomBlock;
			}
			else if ((i * SAMPLE_TILE_COUNT_X + j) == 18)
			{
				mSampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].Terrain = eTerrain::RightBlock;
			}
			else if ((i * SAMPLE_TILE_COUNT_X + j) == 15)
			{
				mSampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].Terrain = eTerrain::LeftBlock;
			}
			else
			{
				mSampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].Terrain = eTerrain::Close;
			}

		}
	}

	// ���ÿ��� ũ��(1Ÿ�ϴ� 40�ȼ�)
	mSampleArea.left = TILE_MAP_TOOL_X - mSampleTileImage->GetWidth();
	mSampleArea.top = 0;
	mSampleArea.right = TILE_MAP_TOOL_X;
	mSampleArea.bottom = mSampleTileImage->GetHeight();

	// �׸����� ũ��(1Ÿ�ϴ� 64�ȼ�)
	mDrawArea.left = 0;
	mDrawArea.top = 0;
	mDrawArea.right = TILE_SIZE * 15; // 960
	mDrawArea.bottom = TILE_SIZE * 15; //960

	mSaveIndex = 0;


	
	return S_OK;
}

void MapEditor::Update()
{
	SAFE_UPDATE(mTestJiwoo);


	if (Input::GetButton(VK_DOWN))
	{
		mDir = eDir::Down;
		mMovePixel.y -= mMoveSpeed * DELTA_TIME;
		CAM_MGR->SetPos(mMovePixel);

		mbNeedRevise = false;

		if (mMovePixel.y >= TILE_SIZE * TILE_COUNT_X)
		{
			mMovePixel.y = -TILE_SIZE * TILE_COUNT_X;
			mDestPos.y = -TILE_SIZE * TILE_COUNT_X;
		}
		else
		{
			mDestPos.y = mMovePixel.y - TILE_SIZE - (mMovePixel.y % TILE_SIZE);
		}

		cout << "mStartPosY : " << mMovePixel.y << endl;
		cout << "mDestPosY : " << mDestPos.y << endl;
		cout << "mCurPosY : " << mMovePixel.y << endl;
	}
	if (Input::GetButtonUp(VK_DOWN))
	{
		mbNeedRevise = true;
	}
	if (Input::GetButton(VK_UP))
	{
		mDir = eDir::Up;
		mMovePixel.y += mMoveSpeed * DELTA_TIME;
		CAM_MGR->SetPos(mMovePixel);

		mbNeedRevise = false;

		if (mMovePixel.y >= 0)
		{
			mDestPos.y = 0;
			mMovePixel.y = 0;
		}
		else
		{
			mDestPos.y = mMovePixel.y + TILE_SIZE - (TILE_SIZE + (mMovePixel.y % TILE_SIZE));
		}

		cout << "mStartPosY : " << mMovePixel.y << endl;
		cout << "mDestPosY : " << mDestPos.y << endl << endl;
	}
	if (Input::GetButtonUp(VK_UP))
	{
		mbNeedRevise = true;
	}
	if (Input::GetButton(VK_LEFT))
	{
		mDir = eDir::Left;
		mMovePixel.x += mMoveSpeed * DELTA_TIME;
		CAM_MGR->SetPos(mMovePixel);

		mbNeedRevise = false;

		if (mMovePixel.x >= 0)
		{
			mDestPos.x = 0;
			mMovePixel.x = 0;
		}
		else
		{
			mDestPos.x = mMovePixel.x + TILE_SIZE - (TILE_SIZE + (mMovePixel.x % TILE_SIZE));
		}

		cout << "mStartPosX : " << mMovePixel.x << endl;
		cout << "mDestPosX : " << mDestPos.x << endl;
		cout << "mCurPosX : " << mMovePixel.x << endl;
	}
	if (Input::GetButtonUp(VK_LEFT))
	{
		mbNeedRevise = true;
	}
	if (Input::GetButton(VK_RIGHT))
	{
		mDir = eDir::Right;
		mMovePixel.x -= mMoveSpeed * DELTA_TIME;
		CAM_MGR->SetPos(mMovePixel);

		mbNeedRevise = false;
		
		if (mMovePixel.x >= TILE_SIZE * TILE_COUNT_X)
		{
			mMovePixel.x = -TILE_SIZE * TILE_COUNT_X;
			mDestPos.x = -TILE_SIZE * TILE_COUNT_X;
		}
		else
		{
			mDestPos.x = mMovePixel.x - TILE_SIZE - (mMovePixel.x % TILE_SIZE);
		}

		cout << "mStartPosX : " << mMovePixel.x << endl;
		cout << "mDestPosX : " << mDestPos.x << endl;
		cout << "mCurPosX : " << mMovePixel.x << endl;
	} 
	if (Input::GetButtonUp(VK_RIGHT))
	{
		mbNeedRevise = true;
	}

	if (mbNeedRevise == true)
	{
		CAM_MGR->MovePos(mDestPos, 1.0f, mDir);
		mMovePixel = CAM_MGR->GetCamPos();

		if (mDir == eDir::Right && mMovePixel.x <= mDestPos.x)
		{
			mbNeedRevise = false;
		}
		if (mDir == eDir::Left && mMovePixel.x >= mDestPos.x)
		{
			mbNeedRevise = false;
		}
		else if (mDir == eDir::Up && mMovePixel.y >= mDestPos.y)
		{
			mbNeedRevise = false;
		}
		else if (mDir == eDir::Down && mMovePixel.y <= mDestPos.y)
		{
			mbNeedRevise = false;
		}
	}
	


	// ���� �κ�, ���� ��
	if (Input::GetButtonDown(VK_CONTROL))
	{
		if (Input::GetButton('1'))
		{
			mSaveIndex = '1';
			cout << "\"" << mSaveIndex << "\"" << "�� ����˴ϴ�" << '\n';
		}

	}

	// �巡�� ����
	if (Input::GetButton(VK_LBUTTON))
	{
		if (PtInRect(&(mSampleArea), g_ptMouse))
		{
			mbIsClick = true;
			// ���ÿ��� Ŭ�� ������ǥ
			mClickStart.x = (g_ptMouse.x - mSampleArea.left) / SAMPLE_TILE_SIZE;
			mClickStart.y = g_ptMouse.y / SAMPLE_TILE_SIZE;
			// Ŭ�� �巡�� ���� ���۰� 1�� ����
			mClickArea.x = 1;
			mClickArea.y = 1;

		}
	}
	// �巡�� ��
	if (Input::GetButtonUp(VK_LBUTTON))
	{
		if (PtInRect(&(mSampleArea), g_ptMouse) && mbIsClick == true)
		{
			// Ŭ�� ����� ��ǥ
			mCLickEnd = POINT{ (g_ptMouse.x - mSampleArea.left) / SAMPLE_TILE_SIZE, (g_ptMouse.y - mSampleArea.top) / SAMPLE_TILE_SIZE };
			// �巡�� ���� ��ǥ
			mClickArea.x = fabs(mClickStart.x -  mCLickEnd.x);
			mClickArea.y= fabs(mClickStart.y - mCLickEnd.y);
		}
		mbIsClick = false;
	}

	// �׸��� ���� Ÿ������ ������Ʈ
	if (Input::GetButton(VK_LBUTTON))
	{
		if (PtInRect(&(mDrawArea), g_ptMouse))
		{
			// �׸��� ���� �� ��ǥ
			POINT clickPos
				= { (g_ptMouse.x - CAM_MGR->GetCamPos().x) / TILE_SIZE,
				(g_ptMouse.y - CAM_MGR->GetCamPos().y) / TILE_SIZE };

			for (int i = 0; i <= mClickArea.y; ++i)
			{
				for (int j = 0; j <= mClickArea.x; ++j)
				{
					// Ŭ�� ��ǥ�� ���������� ������ �Ѿ ��� ����ó��
					if ((clickPos.x + j + 1) > (mDrawArea.right + CAM_MGR->GetCamPos().x / TILE_SIZE)) break;

					mTileInfo[(clickPos.y + i) * TILE_COUNT_X + (clickPos.x + j)].TilePos.x = mClickStart.x + j;
					mTileInfo[(clickPos.y + i) * TILE_COUNT_X + (clickPos.x + j)].TilePos.y = mClickStart.y + i;
					mTileInfo[(clickPos.y + i) * TILE_COUNT_X + (clickPos.x + j)].Terrain =
						mSampleTileInfo[(mClickStart.y + i) * SAMPLE_TILE_COUNT_X + (mClickStart.x + j)].Terrain;

				}
			}

			
		}
	}

	/*cout << "Tile Barometer X : " << mTileBarometerPos.x / TILE_SIZE << endl;
	cout << "Tile Barometer Y : " << mTileBarometerPos.y / TILE_SIZE << endl;
	cout << "To Tile X : " << (mTileBarometerPos.x + TILE_SIZE) / TILE_SIZE << endl;*/
	/*cout << "To Tile Y : " << (mTileBarometerPos.y + TILE_SIZE) / TILE_SIZE << endl;*/
	//cout << "X : " << CAM_MGR->GetCamPos().x << endl;
	//cout << "Y : " << CAM_MGR->GetCamPos().y << endl << endl;
	//cout << "SampleX : " << mClickStart.x << endl;
	//cout << "SampleY : " << mClickStart.y << endl;
	//cout << "�巡�� : " << mClickArea.x << endl;
	//cout << "�巡�� : " << mClickArea.y << endl;


}

void MapEditor::Render(HDC hdc)
{
	mBackground->Render(hdc);

	// �׸��� ���� ǥ��
	Rectangle(hdc, 0, 0, SAMPLE_TILE_COUNT_X * TILE_SIZE, SAMPLE_TILE_COUNT_X * TILE_SIZE);

	//Ÿ�� �׸���
	
	for (int i = 0; i < TILE_COUNT_Y; ++i)
	{
		for (int j = 0; j < TILE_COUNT_X; ++j)
		{
			
			if (mTileInfo[i * TILE_COUNT_X + j].Rc.right + CAM_MGR->GetCamPos().x <= (SAMPLE_TILE_COUNT_X) * TILE_SIZE
				&& mTileInfo[i * TILE_COUNT_X + j].Rc.bottom + CAM_MGR->GetCamPos().y <= (SAMPLE_TILE_COUNT_Y) * TILE_SIZE)
			{
				Rectangle(hdc, j * TILE_SIZE + CAM_MGR->GetCamPos().x,
					i * TILE_SIZE + +CAM_MGR->GetCamPos().y,
					TILE_SIZE + j * TILE_SIZE + CAM_MGR->GetCamPos().x,
					TILE_SIZE + i * TILE_SIZE + CAM_MGR->GetCamPos().y);

				mDrawTileImage->Render(hdc,
					mTileInfo[i * TILE_COUNT_X + j].Rc.left + TILE_SIZE / 2 + CAM_MGR->GetCamPos().x,
					mTileInfo[i * TILE_COUNT_X + j].Rc.top + TILE_SIZE / 2 + CAM_MGR->GetCamPos().y,
					mTileInfo[i * TILE_COUNT_X + j].TilePos.x,
					mTileInfo[i * TILE_COUNT_X + j].TilePos.y);

				Rectangle(hdc, (SAMPLE_TILE_COUNT_X - 1) * TILE_SIZE, 0, SAMPLE_TILE_COUNT_X * TILE_SIZE, SAMPLE_TILE_COUNT_Y * TILE_SIZE);
				Rectangle(hdc, 0, (SAMPLE_TILE_COUNT_Y - 1) * TILE_SIZE, SAMPLE_TILE_COUNT_X * TILE_SIZE, SAMPLE_TILE_COUNT_Y * TILE_SIZE);
			}
			
		}
	}

	// ��ü ���� ����
	mSampleTileImage->Render(hdc, TILE_MAP_TOOL_X - mSampleTileImage->GetWidth() + mSampleTileImage->GetWidth() / 2,
		mSampleTileImage->GetWidth() / 2);

	// ���� Ÿ�� ǥ�ÿ���
	for (int i = 0; i <= mClickArea.y ; ++i)
	{
		for (int j = 0; j <= mClickArea.x; ++j)
		{
			mSampleTileImage->Render(hdc, TILE_MAP_TOOL_X - mSampleTileImage->GetWidth() + mSampleTileImage->GetWidth() / 2 + j * SAMPLE_TILE_SIZE,
				mSampleTileImage->GetHeight() + mSampleTileImage->GetFrameHeight() / 2 + 50 + i * SAMPLE_TILE_SIZE,
				mClickStart.x + j, mClickStart.y + i);
		}
	}

	// ���� Ÿ�� �ε��� ǥ��
	/*wsprintf(mSampleText, "Sample Tile index : %d, %d", mClickStart.x, mClickStart.y);
	TextOut(hdc, WIN_SIZE_X - mSampleTileImage->GetWidth(), mSampleTileImage->GetHeight() + 120, mSampleText, strlen(mSampleText));*/
	// ����Ÿ�ϳѹ�
	wsprintf(mSampleText, "Sample Tile index : %d", mClickStart.y * SAMPLE_TILE_COUNT_X + mClickStart.x);
	TextOut(hdc, WIN_SIZE_X - mSampleTileImage->GetWidth(), mSampleTileImage->GetHeight() + 120, mSampleText, strlen(mSampleText));
	// ���� Ÿ�� �Ӽ� ǥ��
	wsprintf(mSampleText, "Sample Tile Terrain : %d", mSampleTileInfo[mClickStart.y * SAMPLE_TILE_COUNT_X + mClickStart.x].Terrain);
	TextOut(hdc, WIN_SIZE_X - mSampleTileImage->GetWidth(), mSampleTileImage->GetHeight() + 160, mSampleText, strlen(mSampleText));

	// �׽�Ʈ ����
	mTestJiwoo->Render(hdc);
}

void MapEditor::Release()
{
	SAFE_RELEASE(mTestJiwoo);	
}

void MapEditor::SaveMap(int index)
{
	string saveFileName = "Save/saveMapData_" + (to_string(index)) + ".map";


	HANDLE hFile = CreateFile(saveFileName.c_str(),
		GENERIC_WRITE,
		NULL, NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD mapSaveTileInfo = sizeof(TagTile) * TILE_COUNT_X * TILE_COUNT_Y;

	DWORD writtenByte;
	if (WriteFile(hFile,
		mTileInfo,
		mapSaveTileInfo,
		&writtenByte,
		NULL) == false)
	{
		MessageBox(g_hWnd, "�� ������ ���忡 �����߽��ϴ�.", "����", MB_OK);
	}

	CloseHandle(hFile);
}

void MapEditor::LoadMap(int index)
{
	string loadFileName = "Save/saveMapData_" + to_string(index);
	loadFileName += ".map";
	DWORD mapSaveTileInfo = sizeof(TagTile) * TILE_COUNT_X * TILE_COUNT_Y;

	HANDLE hFile = CreateFile(loadFileName.c_str(),
		GENERIC_READ,
		0, NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD readByte;
	if (ReadFile(hFile, mTileInfo, mapSaveTileInfo,
		&readByte, NULL) == false)
	{
		MessageBox(g_hWnd, "�� ������ �ε忡 �����߽��ϴ�.", "����", MB_OK);
	}

	CloseHandle(hFile);
}
