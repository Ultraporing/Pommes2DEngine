#pragma once
#include <SFML\Audio.hpp>

namespace P2DE
{
	namespace SFX
	{
		class SoundManager
		{
			private:
			SoundManager(SoundManager const&) = delete;
			void operator=(SoundManager const&) = delete;
			SoundManager() {};

			public:
			static SoundManager& getInstance()
			{
				static SoundManager    instance; // Guaranteed to be destroyed.
												 // Instantiated on first use.
				return instance;
			}
			~SoundManager();
		};
	}
}
#define P2DE_SFX P2DE::SFX::SoundManager::getInstance()
