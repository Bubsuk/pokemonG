#include "stdafx.h"
#include "Config.h"
#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::Empty;
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);

	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height,
	bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::File;
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height,
		LR_LOADFROMFILE);

	imageInfo->hMemDc = CreateCompatibleDC(hdc);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(g_hWnd, hdc);

	this->isTransparent = isTrans;
	this->transColor = transColor;

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
	bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::File;
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height,
		LR_LOADFROMFILE);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(g_hWnd, hdc);

	this->isTransparent = isTrans;
	this->transColor = transColor;

	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->currFrameX = 0;
	imageInfo->currFrameY = 0;
	imageInfo->frameWidth = width / maxFrameX;
	imageInfo->frameHeight = height / maxFrameY;

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDc, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDc);

		delete imageInfo;
		imageInfo = nullptr;
	}
}

void Image::Render(HDC hdc)
{
	BitBlt(hdc,				// ???? ?????? DC
		0,					// ?????? ???????? ???? ???? x
		0,					// ?????? ???????? ???? ???? y
		imageInfo->width,	// ???? ?????? ???? ????
		imageInfo->height,	// ???? ?????? ???? ????
		imageInfo->hMemDc,	// ???? DC
		0,					// ???? ?????? ???? ???? ???? x
		0,					// ???? ?????? ???? ???? ???? y
		SRCCOPY);			// ???? ????
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (isTransparent)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDc,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor
		);
	}
	else
	{
		BitBlt(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDc,
			0,
			0,
			SRCCOPY);
	}

}

void Image::Render(HDC hdc, int destX, int destY, float scale)
{
	StretchBlt(hdc,
		destX - (imageInfo->width * scale / 2),
		destY - (imageInfo->height * scale / 2),
		imageInfo->width * scale,
		imageInfo->height * scale,
		imageInfo->hMemDc,
		0, 0,
		imageInfo->width,
		imageInfo->height,
		SRCCOPY);

	//if (isTransparent)
	//{
	//	GdiTransparentBlt(
	//		hdc,
	//		destX - (imageInfo->width / 2),
	//		destY - (imageInfo->height / 2),
	//		imageInfo->width * scale,
	//		imageInfo->height * scale,	// ???? ?????? ??
	//
	//		imageInfo->hMemDc,
	//		imageInfo->width,
	//		imageInfo->height,
	//		0, 0,
	//		transColor
	//	);
	//}
	//else
	//{
	//	BitBlt(hdc,
	//		destX - (imageInfo->width / 2),
	//		destY - (imageInfo->height / 2),
	//		imageInfo->width * scale,
	//		imageInfo->height * scale,
	//		imageInfo->hMemDc,
	//		0,
	//		0,
	//		SRCCOPY);
	//}
}

void Image::Render(HDC hdc, int destX, int destY, int frameX, int frameY, float scale/* = 1.0f*/)
{
	if (isTransparent)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->frameWidth / 2),
			destY - (imageInfo->frameHeight / 2),
			imageInfo->frameWidth * scale,
			imageInfo->frameHeight * scale,	// ???? ?????? ??

			imageInfo->hMemDc,
			imageInfo->frameWidth * frameX,
			imageInfo->frameHeight * frameY,
			imageInfo->frameWidth, imageInfo->frameHeight,
			transColor
		);
	}
	else
	{
		BitBlt(hdc,
			destX - (imageInfo->frameWidth / 2),
			destY - (imageInfo->frameHeight / 2),
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDc,
			imageInfo->frameWidth * frameX,
			imageInfo->frameHeight * frameY,
			SRCCOPY);
	}
}

// ??????
void Image::CameraRender(HDC hdc, int destX, int destY, int renderStartX, int renderStartY, int rendersizeX, int renderSizeY)
{

}
