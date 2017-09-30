#pragma once
#include <map>
#include <string>
#include "../Common.h"

namespace P2DE
{
	namespace SFX
	{
		class P2DE_Sound;

		class P2DE_DECLSPEC SoundManager
		{
			private:
			SoundManager(SoundManager const&) = delete;
			void operator=(SoundManager const&) = delete;
			SoundManager() 
			{
				m_Sounds = std::map<std::wstring, P2DE_Sound*>();
			};
			std::map<std::wstring, P2DE_Sound*> m_Sounds;
			void DestroyAllSounds();

			public:
			static SoundManager& getInstance()
			{
				static SoundManager    instance; // Guaranteed to be destroyed.
												 // Instantiated on first use.
				return instance;
			}
			~SoundManager();

			P2DE_Sound* CreateSound(std::wstring name);
			P2DE_Sound* CreateSound(std::wstring name, std::wstring filePath);
			void DestroySound(std::wstring name);
			P2DE_Sound* GetSound(std::wstring name);
		};
	}
}
#define P2DE_SFX P2DE::SFX::SoundManager::getInstance()
