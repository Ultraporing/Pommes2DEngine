#pragma once
#include <map>
#include <string>
#include "ImagePropertiesAndEnums\ImageProperties.h"

namespace P2DE
{
	namespace GFX
	{
		class Spritesheet;
		class Graphics;
		typedef std::map<std::wstring, Spritesheet> SpritesheetAtlasMap;
		typedef std::pair<SpritesheetAtlasMap::iterator, bool> SpritesheetAtlasMapReturn;
		class SpritesheetAtlas
		{
			private:
			static SpritesheetAtlasMap m_SpritesheetAtlasMap;

			public:
			static bool AddSpritesheet(Spritesheet& spritesheet);
			static bool AddLoadSpritesheet(const std::wstring& pathToSpritesheetInfoTXT, Graphics* graphics);
			static void RemoveSpritesheet(const std::wstring& spritesheetIdentifierName);
			
			static void UnloadSpritesheetBitmaps();

			static Spritesheet* GetSpritesheet(const std::wstring& spritesheetIdentifierName);
			static void ShutdownAtlas();

			static void DrawFrame(BaseImageProperties* imageProperties);
		};
	}
}
