#include "SpritesheetAtlas.h"
#include "Spritesheet.h"
/*
using namespace P2DE::GFX;

#ifdef _WIN32
	SpritesheetAtlasMap SpritesheetAtlas::m_SpritesheetAtlasMap = SpritesheetAtlasMap();

	bool SpritesheetAtlas::AddSpritesheet(Spritesheet& spritesheet)
	{
		SpritesheetAtlasMapReturn ret = m_SpritesheetAtlasMap.insert(std::pair<std::wstring, Spritesheet>(spritesheet.GetSpritesheetInfo().m_IdentifierName, spritesheet));
		if (!ret.second)
		{
			return m_SpritesheetAtlasMap.at(spritesheet.GetSpritesheetInfo().m_IdentifierName).ReloadSpritesheetBitmap();
		}

		return true;
	}

	bool SpritesheetAtlas::AddLoadSpritesheet(const std::wstring& pathToSpritesheetInfoTXT, Graphics* graphics)
	{
		SpritesheetInfo info = Spritesheet::ReadSpritesheetInfo(pathToSpritesheetInfoTXT);
	
		SpritesheetAtlasMapReturn ret = m_SpritesheetAtlasMap.insert(std::pair<std::wstring, Spritesheet>(info.m_IdentifierName, Spritesheet()));

		return m_SpritesheetAtlasMap.at(info.m_IdentifierName).LoadSpritesheet(pathToSpritesheetInfoTXT, graphics);
	}

	void SpritesheetAtlas::RemoveSpritesheet(const std::wstring& spritesheetIdentifierName)
	{
		m_SpritesheetAtlasMap.erase(spritesheetIdentifierName);
	}

	void SpritesheetAtlas::UnloadSpritesheetBitmaps()
	{
		for each (std::pair<std::wstring, Spritesheet> sheetPair in m_SpritesheetAtlasMap)
		{
			sheetPair.second.UnloadSpritesheetBitmap();
		}
	}

	Spritesheet* SpritesheetAtlas::GetSpritesheet(const std::wstring& spritesheetIdentifierName)
	{
		return &m_SpritesheetAtlasMap.at(spritesheetIdentifierName);
	}

	void SpritesheetAtlas::ShutdownAtlas()
	{
		m_SpritesheetAtlasMap.clear();
	}

	void SpritesheetAtlas::DrawFrame(D2D1_POINT_2F position, ImageProperties* imageProperties)
	{
		GetSpritesheet(imageProperties->m_SpritesheetName)->DrawFrame(position, imageProperties);
	}
#elif __APPLE__
	// TODO: Mac Code
#endif*/