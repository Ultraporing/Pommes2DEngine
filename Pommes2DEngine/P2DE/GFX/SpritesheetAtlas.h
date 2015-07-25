#ifndef SPRITESHEET_ATLAS_H
#define SPRITESHEET_ATLAS_H
	#include "ImagePropertiesAndEnums\ImageProperties.h"
	#ifdef _WIN32
		#include <map>
		#include <string>
	#elif __APPLE__
		// TODO: Mac Header
	#endif

	namespace P2DE
	{
		namespace GFX
		{
			class Spritesheet;
			class Graphics;
			#ifdef _WIN32
				typedef std::map<std::wstring, Spritesheet> SpritesheetAtlasMap;
				typedef std::pair<SpritesheetAtlasMap::iterator, bool> SpritesheetAtlasMapReturn;
			#elif __APPLE__
				// TODO: Mac Code
			#endif

			class SpritesheetAtlas
			{
				#ifdef _WIN32
					private:
					static SpritesheetAtlasMap m_SpritesheetAtlasMap;

					public:
					static bool AddSpritesheet(Spritesheet& spritesheet);
					static bool AddLoadSpritesheet(const std::wstring& pathToSpritesheetInfoTXT, Graphics* graphics);
					static void RemoveSpritesheet(const std::wstring& spritesheetIdentifierName);
			
					static void UnloadSpritesheetBitmaps();

					static Spritesheet* GetSpritesheet(const std::wstring& spritesheetIdentifierName);
					static void ShutdownAtlas();

					static void DrawFrame(D2D1_POINT_2F position, ImageProperties* imageProperties);
				#elif __APPLE__
					// TODO: Mac Code
				#endif
			};	
		}
	}
#endif
