#pragma once
#include <string>
#include <wrl\client.h>
using namespace Microsoft::WRL;

namespace sf
{
	class Sound;
	class SoundBuffer;
}

namespace P2DE
{
	namespace SFX
	{
		enum Status
		{
			Stopped, ///< Sound is not playing
			Paused,  ///< Sound is paused
			Playing  ///< Sound is playing
		};

		class P2DE_Sound
		{
			private:
			sf::Sound* m_Sound;
			sf::SoundBuffer* m_SoundBuffer;
			bool m_Loaded;

			public:
			P2DE_Sound();
			P2DE_Sound(std::string path);
			~P2DE_Sound();

			bool LoadSoundfile(std::string path);
			void UnloadSound();

			void Play();
			void Pause();
			void Stop();

			Status GetPlaybackStatus();
			bool IsLoaded();
		};
	}
}

