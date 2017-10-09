#pragma once
#include <vector>
#include <string>
#include <array>
#include "SoundDefines.h"
#include "../Common.h"

typedef struct ALCdevice_struct ALCdevice;
typedef struct ALCcontext_struct ALCcontext;

namespace P2DE
{
	namespace SFX
	{
		class P2DE_DECLSPEC Sound
		{
			Sound(Sound const&) = delete;
			void operator=(Sound const&) = delete;
			Sound();
			~Sound();

		public:
			/// <summary>	Default constructor. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			static Sound& getInstance()
			{
				static Sound    instance; // Guaranteed to be destroyed.
											 // Instantiated on first use.
				return instance;
			}

		private:
			ALCdevice* m_Device;
			ALCcontext* m_Context;
			bool m_IsInitDevice;

		public:
			std::vector<std::wstring> GetAudioDeviceNames();
			bool InitSound(const std::wstring deviceName);
			bool InitContext(const int* contextAttributes = NULL);
			ALCcontext* GetContext() { return m_Context; }
			bool IsInit();
			
			// See Documentation here for reference: https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
			#pragma region Listener Property Methods
			// Set Listener position. X, Y, Z position.
			void SetListenerPos(float x, float y, float z);
			// Set Listener position. X, Y, Z position.
			void SetListenerPos(std::array<float, 3> pos) { SetListenerPos(pos[0], pos[1], pos[2]); }

			// Get Listener position. X, Y, Z position.
			std::array<float, 3> GetListenerPos();

			// Set Listener velocity vector.
			void SetListenerVel(float x, float y, float z);
			// Set Listener velocity vector.
			void SetListenerVel(std::array<float, 3> pos) { SetListenerVel(pos[0], pos[1], pos[2]); }

			// Get Listener velocity vector.
			std::array<float, 3> GetListenerVel();

			// Set Listener orientation. orientation expressed as “at” and “up” vectors.
			void SetListenerOri(float x, float y, float z, float xUp, float yUp, float zUp);
			// Set Listener orientation. orientation expressed as “at” and “up” vectors.
			void SetListenerOri(std::array<float, 6> ori) { SetListenerOri(ori[0], ori[1], ori[2], ori[3], ori[4], ori[5]); }

			// Get Listener orientation. orientation expressed as “at” and “up” vectors.
			std::array<float, 6> GetListenerOri();

			// Set Listener gain. “master gain” value should be positive.
			void SetListenerGain(float gain);

			// Get Listener gain. “master gain” value should be positive.
			float GetListenerGain();
			#pragma endregion
		};
	}
}

#define P2DE_SFX P2DE::SFX::Sound::getInstance()