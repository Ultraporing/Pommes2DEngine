#pragma once
#include <string>
#include <wrl\client.h>
#include <array>
#include "../Common.h"
using namespace Microsoft::WRL;

namespace P2DE
{
	namespace SFX
	{
		enum SourceType
		{
			Undetermined, // Type is undetermined
			Static,
			Streaming
		};
		
		enum State
		{
			Initial, // Sound is in Initial state
			Playing, // Sound is playing
			Paused,  // Sound is paused
			Stopped	 // Sound is not playing
		};

		class P2DE_DECLSPEC P2DE_SoundSource
		{
			friend class SoundManager;

			private:
			int m_SoundSourceID;
			int m_SoundBufferID;
			std::wstring m_FilePath;		
			bool m_Loaded;
			bool m_HasError;
			int m_Channel;	
			void InitSound();

			public:
			P2DE_SoundSource();
			P2DE_SoundSource(std::wstring path);

			// Load WAV, AIFF, RIFF, OGG or VOC sound file
			bool LoadSoundfile(std::wstring path);
			void UnloadSound();

			// Plays the Sound/Music, loops: -1 = infinite, 0 = plays 1 times, 1 = loops additional 1 times ...
			void Play(int loop = 0);
			void Pause();
			void Stop();

			bool IsLoaded();
			bool HasError();
			int GetChannel();

			// See Documentation here for reference: https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
			#pragma region Source Property Methods
			// Set Source pitch. pitch multiplier, always positive.
			void SetSourcePitch(float pitch);

			// Get Source pitch. pitch multiplier, always positive.
			float GetSourcePitch();

			// Set Source gain. source gain, value should be positive.
			void SetSourceGain(float gain);

			// Get Source gain. source gain, value should be positive.
			float GetSourceGain();

			// Set Source max distance. used with the Inverse Clamped Distance Model to set the distance where there will no longer be any attenuation of the source.
			void SetSourceMaxDistance(float maxDistance);
			// Set Source max distance. used with the Inverse Clamped Distance Model to set the distance where there will no longer be any attenuation of the source.
			void SetSourceMaxDistance(int maxDistance) { SetSourceMaxDistance(maxDistance); }

			// Get Source max distance. used with the Inverse Clamped Distance Model to set the distance where there will no longer be any attenuation of the source.
			float GetSourceMaxDistance();

			// Set Source rolloff factor. the rolloff rate for the source default is 1.0.
			void SetSourceRolloffFactor(float rolloffFactor);
			// Set Source rolloff factor. the rolloff rate for the source default is 1.0.
			void SetSourceRolloffFactor(int rolloffFactor) { SetSourceRolloffFactor(rolloffFactor); }

			// Get Source rolloff factor. the rolloff rate for the source default is 1.0.
			float GetSourceRolloffFactor();

			// Set Source reference distance. the distance under which the volume for the source would normally drop by half(before being influenced by rolloff factor or AL_MAX_DISTANCE).
			void SetSourceReferenceDistance(float referenceDistance);
			// Set Source reference distance. the distance under which the volume for the source would normally drop by half(before being influenced by rolloff factor or AL_MAX_DISTANCE).
			void SetSourceReferenceDistance(int referenceDistance) { SetSourceReferenceDistance(referenceDistance); }

			// Get Source reference distance. the distance under which the volume for the source would normally drop by half(before being influenced by rolloff factor or AL_MAX_DISTANCE).
			float GetReferenceDistance();

			// Set Source min gain. the minimum gain for this source.
			void SetSourceMinGain(float minGain);

			// Get Source min gain. the minimum gain for this source.
			float GetSourceMinGain();

			// Set Source max gain. the maximum gain for this source.
			void SetSourceMaxGain(float maxGain);

			// Get Source max gain. the maximum gain for this source.
			float GetSourceMaxGain();

			// Set Source cone outer gain. the gain when outside the oriented cone.
			void SetSourceConeOuterGain(float coneOuterGain);

			// Get Source cone outer gain. the gain when outside the oriented cone.
			float GetSourceConeOuterGain();

			// Set Source cone inner angle. inner angle of the sound cone, in degrees default is 360.
			void SetSourceConeInnerAngle(float coneInnerAngle);
			// Set Source cone inner angle. inner angle of the sound cone, in degrees default is 360.
			void SetSourceConeInnerAngle(int coneInnerAngle) { SetSourceConeInnerAngle(coneInnerAngle); }

			// Get Source cone inner angle. inner angle of the sound cone, in degrees default is 360.
			float GetConeInnerAngle();

			// Set Source cone outer angle. outer angle of the sound cone, in degrees default is 360.
			void SetSourceConeOuterAngle(float coneOuterAngle);
			// Set Source cone outer angle. outer angle of the sound cone, in degrees default is 360.
			void SetSourceConeOuterAngle(int coneOuterAngle) { SetSourceConeOuterAngle(coneOuterAngle); }

			// Get Source cone outer angle. outer angle of the sound cone, in degrees default is 360.
			float GetConeOuterAngle();

			// Set Source position vector. X, Y, Z position.
			void SetSourcePos(float x, float y, float z);
			// Set Source position vector. X, Y, Z position.
			void SetSourcePos(std::array<float, 3> pos) { SetSourcePos(pos[0], pos[1], pos[2]); }

			// Get Source position vector. X, Y, Z position.
			std::array<float, 3> GetSourcePos();

			// Set Source velocity vector. velocity vector.
			void SetSourceVel(float x, float y, float z);
			// Set Source velocity vector. velocity vector.
			void SetSourceVel(std::array<float, 3> pos) { SetSourceVel(pos[0], pos[1], pos[2]); }

			// Get Source velocity vector. velocity vector.
			std::array<float, 3> GetSourceVel();

			// Set Source direction vector. direction vector.
			void SetSourceDir(float x, float y, float z);
			// Set Source direction vector. direction vector.
			void SetSourceDir(std::array<float, 3> pos) { SetSourceDir(pos[0], pos[1], pos[2]); }

			// Get Source direction vector. direction vector.
			std::array<float, 3> GetSourceDir();

			// Set Source relative. determines if the positions are relative to the listener default is AL_FALSE.
			void SetSourceRelative(bool relative);

			// Get Source relative. determines if the positions are relative to the listener default is AL_FALSE.
			bool GetSourceRelative();

			// Set Source type. the soruce type – AL_UNDETERMINED, AL_STATIC, or AL_STREAMING.
			void SetSourceType(SourceType type);

			// Get Source type. the soruce type – AL_UNDETERMINED, AL_STATIC, or AL_STREAMING.
			SourceType GetSourceType();

			// Set Source looping. turns looping on (AL_TRUE) or off (AL_FALSE).
			void SetSourceLooping(bool looping);

			// Get Source looping. turns looping on (AL_TRUE) or off (AL_FALSE).
			bool GetSourceLooping();

			// Set Source buffer. the ID of the attached buffer.
			void SetSourceBuffer(int bufferID);

			// Get Source buffer. the ID of the attached buffer.
			int GetSourceBuffer();
			
			// Set Source state. the state of the source (AL_STOPPED, AL_PLAYING, …).
			void SetSourceState(State state);

			// Get Source state. the state of the source (AL_STOPPED, AL_PLAYING, …).
			State GetSourceState();

			// Get Source buffers queued. the number of buffers queued on this source.
			int GetSourceBuffersQueued();

			// Set Source buffer processed. the number of buffers in the queue that have been processed.
			void SetSourceBuffersProcessed(int buffersProcessed);

			// Get Source buffer processed. the number of buffers in the queue that have been processed.
			int GetSourceBuffersProcessed();

			// Set Source sec offset. the playback position, expressed in seconds.
			void SetSourceSecOffset(int sec);

			// Get Source sec offset. the playback position, expressed in seconds.
			int GetSourceSecOffset();

			// Set Source sample offset. the playback position, expressed in samples.
			void SetSourceSampleOffset(int samples);

			// Get Source sample offset. the playback position, expressed in samples.
			int GetSourceSampleOffset();

			// Set Source byte offset. the playback position, expressed in bytes.
			void SetSourceByteOffset(int bytes);

			// Get Source byte offset. the playback position, expressed in bytes.
			int GetSourceByteOffset();
			#pragma endregion
		};
	}
}

