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
		
		class P2DE_DECLSPEC P2DE_SoundSource
		{
			friend class SoundManager;

			private:
			unsigned int m_SoundSourceID;
			unsigned int m_SoundBufferID;
			std::wstring m_FilePath;
			Status m_PlaybackStatus;		
			bool m_Loaded;
			bool m_HasError;
			int m_Channel;	
			void InitSound();

			public:
			P2DE_Sound();
			P2DE_Sound(std::wstring path);

			// Load WAV, AIFF, RIFF, OGG or VOC sound file
			bool LoadSoundfile(std::wstring path);
			void UnloadSound();

			// Plays the Sound/Music, loops: -1 = infinite, 0 = plays 1 times, 1 = loops additional 1 times ...
			void Play(int loop = 0);
			void Pause();
			void Stop();

			void SetPlaybackStatus(Status status);
			Status GetPlaybackStatus();
			bool IsLoaded();
			bool HasError();
			int GetChannel();
		};
	}
}

