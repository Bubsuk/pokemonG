#include "stdafx.h"
#include "Config.h"
#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
	// 캐릭터
	AddImage(eImageTag::Jiwoo_idle, "Image/Jiwoo_idle.bmp", 128, 128, 2, 2, true, RGB(255, 0, 255));
	AddImage(eImageTag::Jiwoo_moveUD, "Image/character_run_UD.bmp", 224, 128, 4, 2, true, RGB(255, 0, 255));
	AddImage(eImageTag::Jiwoo_moveRL, "Image/character_run_RL.bmp", 112, 128, 2, 2, true, RGB(255, 0, 255));
	AddImage(eImageTag::DoctorO, "Image/pokemon_O.bmp", 64, 64, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::SubO, "Image/pokemon_Ominion.bmp", 64, 64, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Mom_move, "Image/mom_move.bmp", 128, 128, 2, 2, true, RGB(255, 0, 255));
	//AddImage(eImageTag::Mom_idle, "Image/mom_move.bmp", 128, 128, 2, 2, true, RGB(255, 0, 255));
	AddImage(eImageTag::Mart, "Image/pokemon_mart.bmp", 64, 64, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Nurse, "Image/pokemon_nurse.bmp", 64, 64, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Master, "Image/pokemon_master.bmp", 64, 64, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Master_sub, "Image/master_sub.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	
	// 포켓몬
	AddImage(eImageTag::Caterpie_R, "Image/pokemon/no_10B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Caterpie_F, "Image/pokemon/no_10F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Dandegi_R, "Image/pokemon/no_11B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Dandegi_F, "Image/pokemon/no_11F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Butter_R, "Image/pokemon/no_12B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Butter_F, "Image/pokemon/no_12F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Bbul_R, "Image/pokemon/no_13B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Bbul_F, "Image/pokemon/no_13F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Ddak_R, "Image/pokemon/no_14B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Ddak_F, "Image/pokemon/no_14F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::DokChung_R, "Image/pokemon/no_15B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::DokChung_F, "Image/pokemon/no_15F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Gugu_R, "Image/pokemon/no_16B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Gugu_F, "Image/pokemon/no_16F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Pigeon_R, "Image/pokemon/no_17B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Pigeon_F, "Image/pokemon/no_17F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::PigeonTwo_R, "Image/pokemon/no_18B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::PigeonTwo_F, "Image/pokemon/no_18F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Ggorat_R, "Image/pokemon/no_19B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Ggorat_F, "Image/pokemon/no_19F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Rat_R, "Image/pokemon/no_20B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Rat_F, "Image/pokemon/no_20F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Ggaebi_R, "Image/pokemon/no_21B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Ggaebi_F, "Image/pokemon/no_21F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Ggaebidrill_R, "Image/pokemon/no_22B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Ggaebidrill_F, "Image/pokemon/no_22F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Pika_R, "Image/pokemon/no_25B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Pika_F, "Image/pokemon/no_25F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Richu_R, "Image/pokemon/no_26B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Richu_F, "Image/pokemon/no_26F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Chicorita_R, "Image/pokemon/no_152B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Chicorita_F, "Image/pokemon/no_152F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Bayleaf_R, "Image/pokemon/no_153B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Bayleaf_F, "Image/pokemon/no_153F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Meganium_R, "Image/pokemon/no_154B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Meganium_F, "Image/pokemon/no_154F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Bcane_R, "Image/pokemon/no_155B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Bcane_F, "Image/pokemon/no_155F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Riaco_R, "Image/pokemon/no_158B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Riaco_F, "Image/pokemon/no_158F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Alligay_R, "Image/pokemon/no_159B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Alligay_F, "Image/pokemon/no_159F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Jangcro_R, "Image/pokemon/no_160B.bmp", 192, 192, 1, 1, true, RGB(255, 0, 255));
	AddImage(eImageTag::Jangcro_F, "Image/pokemon/no_160F.bmp", 180, 180, 1, 1, true, RGB(255, 0, 255));


	// 배경
	AddImage(eImageTag::StartRoom, "Image/pokemon_start_home1.bmp", 640, 512);
	AddImage(eImageTag::Background, "Image/mapImage.bmp", 1024, 768);

	// 타일
	AddImage(eImageTag::SampleTile, "Image/pokemon_tile.bmp", 600, 600, 15, 15, true, RGB(255, 0, 255));
	AddImage(eImageTag::DrawTile, "Image/pokemon_tile.bmp", 960, 960, 15, 15, true, RGB(255, 0, 255));
	
}

void ImageManager::Release()
{
	map<eImageTag, Image*>::iterator it;
	for (it = mapImages.begin(); it != mapImages.end();)
	{
		SAFE_RELEASE(it->second);
		it = mapImages.erase(it);	// 다음 원소의 주소(iterator)가 갱신된다.
	}
	mapImages.clear();
}

Image* ImageManager::AddImage(eImageTag tag, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// 이미 등록한 이미지는 nullptr을 반환
	if (mapImages.find(tag) != mapImages.end()) { return nullptr; }

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(tag, img));

	return img;
}

Image* ImageManager::AddImage(eImageTag tag, const char* fileName, int width, int height,
	int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	// 이미 등록한 이미지는 nullptr을 반환
	if (mapImages.find(tag) != mapImages.end()) { return nullptr; }

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, maxFrameX,
		maxFrameY, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(tag, img));

	return img;
}

Image* ImageManager::FindImage(eImageTag tag)
{
	map<eImageTag, Image*>::iterator it = mapImages.find(tag);
	if (it == mapImages.end())
	{
		return nullptr;
	}

	return it->second;
}

void ImageManager::DeleteImage(eImageTag tag)
{
	map<eImageTag, Image*>::iterator it = mapImages.find(tag);
	if (it == mapImages.end())
	{
		return;
	}

	SAFE_RELEASE(it->second);	// Image*	// Image 동적할당 해제
	mapImages.erase(it);		// 맵에서 노드 삭제
}
