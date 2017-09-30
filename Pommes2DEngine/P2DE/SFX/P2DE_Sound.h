#pragma once
#include <string>
#include <wrl\client.h>
#include "../Common.h"
using namespace Microsoft::WRL;

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

		class P2DE_DECLSPEC P2DE_Sound
		{
			private:
			std::wstring m_SoundID;
			std::wstring m_FilePath;
			Status m_PlaybackStatus;
			bool m_Loaded;
			bool m_HasError;

			void SetPlaybackStatus(Status status);
			void InitSound();

			public:
			P2DE_Sound();
			P2DE_Sound(std::wstring path);

			bool LoadSoundfile(std::wstring path);
			void UnloadSound();

			void Play(bool loop = false);
			void Pause();
			void Stop();

			Status GetPlaybackStatus();
			bool IsLoaded();
			bool HasError();
		};
	}
}

