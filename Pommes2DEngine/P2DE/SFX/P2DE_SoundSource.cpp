#include "P2DE_SoundSource.h"
#include <sstream>
#include <comdef.h>
#include <AL\alut.h>
#include "../Utilities/StringConversion.h"

using namespace P2DE::SFX;

P2DE_SoundSource::P2DE_SoundSource()
{
	InitSound();
}

P2DE_SoundSource::P2DE_SoundSource(std::wstring path)
{
	InitSound();
	if (!HasError())
	{
		LoadSoundfile(path);
	}
}

void ChannelFinishedPlayingCallback(int channelID)
{
	if (Mix_Playing(channelID))
	{
		P2DE_Sound* snd = P2DE_SFX.GetSound(channelID);
		if (snd != NULL)
		{
			snd->SetPlaybackStatus(Status::Stopped);
		}
	}

	Mix_ExpireChannel(channelID, -1);
}

void P2DE_SoundSource::InitSound()
{
	m_Loaded = false;
	m_HasError = true;
	m_Channel = -1;

	if (!P2DE_SFX.IsSDLInit()) return;

	UUID uniqueSoundID = { 0 };
	if (UuidCreate(&uniqueSoundID) != RPC_S_OK)
	{
		std::wstringstream wss;
		wss << L"Error: Failed to create UUID for Sound!";
		MessageBox(NULL, wss.str().c_str(), L"Error", MB_ICONERROR);

		return;
	}

	RPC_WSTR szUuid = NULL;
	if (UuidToString(&uniqueSoundID, &szUuid) != RPC_S_OK)
	{
		std::wstringstream wss;
		wss << L"Error: Failed to convert UUID to string for Sound!";
		MessageBox(NULL, wss.str().c_str(), L"Error", MB_ICONERROR);

		return;
	}

	m_SoundID = (wchar_t*)szUuid;
	RpcStringFree(&szUuid);

	m_Loaded = false;
	m_HasError = false;
	SetPlaybackStatus(Status::Stopped);
	Mix_ChannelFinished(&ChannelFinishedPlayingCallback);
}

bool P2DE_SoundSource::LoadSoundfile(std::wstring path)
{
	
	m_FilePath = path;
	_bstr_t cPath(m_FilePath.c_str());
	char* p = (char*)cPath;

	m_SoundData = Mix_LoadWAV(p);
	if (!m_SoundData)
	{
		std::wstringstream wss;
		wss << L"Error: Failed to load soundfile: " << path;
		MessageBox(NULL, wss.str().c_str(), L"Error", MB_ICONERROR);

		return false;
	}

	m_Loaded = true;

	return true;
}

void P2DE_SoundSource::UnloadSound()
{
	if (!IsLoaded()) return;

	Mix_FreeChunk(m_SoundData);
	m_SoundData = NULL;

	m_FilePath = std::wstring();

	SetPlaybackStatus(Status::Stopped);
	m_Loaded = false;
}

void P2DE_SoundSource::Play(int loops)
{
	if (!IsLoaded()) return;

	if (GetPlaybackStatus() == Status::Paused)
	{
		Mix_Resume(m_Channel);
	}
	else
	{
		if (GetPlaybackStatus() == Status::Playing)
		{
			Stop();
		}

		m_Channel = Mix_PlayChannel(m_Channel, m_SoundData, loops);
		if (m_Channel == -1)
		{
			std::wstringstream wss;
			wss << L"Unable to play WAV file: " << Mix_GetError();
			MessageBox(NULL, wss.str().c_str(), L"Error", MB_ICONERROR);

			return;
		}
	}

	SetPlaybackStatus(Status::Playing);
}

void P2DE_SoundSource::Pause()
{
	if (!IsLoaded()) return;

	Mix_Pause(m_Channel);
	SetPlaybackStatus(Status::Paused);
}

void P2DE_SoundSource::Stop()
{
	if (!IsLoaded()) return;

	Mix_HaltChannel(m_Channel);
}

bool P2DE_SoundSource::IsLoaded()
{
	return m_Loaded;
}

bool P2DE_SoundSource::HasError()
{
	return m_HasError;
}

int P2DE_SoundSource::GetChannel()
{
	return m_Channel;
}

void P2DE_SoundSource::SetSourcePitch(float pitch)
{
	alSourcef(m_SoundSourceID, AL_PITCH, pitch);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

float P2DE_SoundSource::GetSourcePitch()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_PITCH, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceGain(float gain)
{
	alSourcef(m_SoundSourceID, AL_GAIN, gain);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

float P2DE_SoundSource::GetSourceGain()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_GAIN, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceMaxDistance(float maxDistance)
{
	alSourcef(m_SoundSourceID, AL_MAX_DISTANCE, maxDistance);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

float P2DE_SoundSource::GetSourceMaxDistance()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_MAX_DISTANCE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceRolloffFactor(float rolloffFactor)
{
	alSourcef(m_SoundSourceID, AL_ROLLOFF_FACTOR, rolloffFactor);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

float P2DE_SoundSource::GetSourceRolloffFactor()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_ROLLOFF_FACTOR, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceReferenceDistance(float referenceDistance)
{
	alSourcef(m_SoundSourceID, AL_REFERENCE_DISTANCE, referenceDistance);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

float P2DE_SoundSource::GetReferenceDistance()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_REFERENCE_DISTANCE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceMinGain(float minGain)
{
	alSourcef(m_SoundSourceID, AL_MIN_GAIN, minGain);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

float P2DE_SoundSource::GetSourceMinGain()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_MIN_GAIN, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceMaxGain(float maxGain)
{
	alSourcef(m_SoundSourceID, AL_MAX_GAIN, maxGain);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

float P2DE_SoundSource::GetSourceMaxGain()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_MAX_GAIN, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceConeOuterGain(float coneOuterGain)
{
	alSourcef(m_SoundSourceID, AL_CONE_OUTER_GAIN, coneOuterGain);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

float P2DE_SoundSource::GetSourceConeOuterGain()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_CONE_OUTER_GAIN, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceConeInnerAngle(float coneInnerAngle)
{
	alSourcef(m_SoundSourceID, AL_CONE_INNER_ANGLE, coneInnerAngle);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

float P2DE_SoundSource::GetConeInnerAngle()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_CONE_INNER_ANGLE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceConeOuterAngle(float coneOuterAngle)
{
	alSourcef(m_SoundSourceID, AL_CONE_OUTER_ANGLE, coneOuterAngle);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

float P2DE_SoundSource::GetConeOuterAngle()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_CONE_OUTER_ANGLE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourcePos(float x, float y, float z)
{
	alSource3f(m_SoundSourceID, AL_POSITION, x, y, z);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

std::array<float, 3> P2DE_SoundSource::GetSourcePos()
{
	std::array<float, 3> oA = std::array<float, 3>();
	alGetSourcefv(m_SoundSourceID, AL_POSITION, oA.data());
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceVel(float x, float y, float z)
{
	alSource3f(m_SoundSourceID, AL_VELOCITY, x, y, z);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

std::array<float, 3> P2DE_SoundSource::GetSourceVel()
{
	std::array<float, 3> oA = std::array<float, 3>();
	alGetSourcefv(m_SoundSourceID, AL_VELOCITY, oA.data());
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceDir(float x, float y, float z)
{
	alSource3f(m_SoundSourceID, AL_DIRECTION, x, y, z);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

std::array<float, 3> P2DE_SoundSource::GetSourceDir()
{
	std::array<float, 3> oA = std::array<float, 3>();
	alGetSourcefv(m_SoundSourceID, AL_DIRECTION, oA.data());
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceRelative(bool relative)
{
	alSourcei(m_SoundSourceID, AL_SOURCE_RELATIVE, (int)relative);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

bool P2DE_SoundSource::GetSourceRelative()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_SOURCE_RELATIVE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceType(SourceType type)
{
	int t = 0;

	switch (type)
	{
	case P2DE::SFX::Undetermined:
		t = AL_UNDETERMINED;
		break;
	case P2DE::SFX::Static:
		t = AL_STATIC;
		break;
	case P2DE::SFX::Streaming:
		t = AL_STREAMING;
		break;
	default:
		t = AL_UNDETERMINED;
		break;
	}

	alSourcei(m_SoundSourceID, AL_SOURCE_TYPE, t);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

SourceType P2DE_SoundSource::GetSourceType()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_SOURCE_TYPE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	switch (oA)
	{
	case AL_UNDETERMINED:
		return SourceType::Undetermined;
	case AL_STATIC:
		return SourceType::Static;
	case AL_STREAMING:
		return SourceType::Streaming;
	default:
		return SourceType::Undetermined;
	}
}

void P2DE_SoundSource::SetSourceLooping(bool looping)
{
	alSourcei(m_SoundSourceID, AL_LOOPING, (int)looping);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

bool P2DE_SoundSource::GetSourceLooping()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_LOOPING, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceBuffer(int bufferID)
{
	alSourcei(m_SoundSourceID, AL_BUFFER, bufferID);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

int P2DE_SoundSource::GetSourceBuffer()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_BUFFER, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceState(State state)
{
	int t = 0;

	switch (state)
	{
	case P2DE::SFX::Initial:
		t = AL_INITIAL;
		break;
	case P2DE::SFX::Playing:
		t = AL_PLAYING;
		break;
	case P2DE::SFX::Paused:
		t = AL_PAUSED;
		break;
	case P2DE::SFX::Stopped:
		t = AL_STOPPED;
		break;
	default:
		t = AL_INITIAL;
		break;
	}

	alSourcei(m_SoundSourceID, AL_SOURCE_STATE, t);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

State P2DE_SoundSource::GetSourceState()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_SOURCE_STATE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	switch (oA)
	{
	case AL_INITIAL:
		return State::Initial;
	case AL_PLAYING:
		return State::Playing;
	case AL_PAUSED:
		return State::Paused;
	case AL_STOPPED:
		return State::Stopped;
	default:
		return State::Initial;
	}
}

int P2DE_SoundSource::GetSourceBuffersQueued()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_BUFFERS_QUEUED, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceBuffersProcessed(int buffersProcessed)
{
	alSourcei(m_SoundSourceID, AL_BUFFERS_PROCESSED, buffersProcessed);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

int P2DE_SoundSource::GetSourceBuffersProcessed()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_BUFFERS_PROCESSED, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceSecOffset(int sec)
{
	alSourcei(m_SoundSourceID, AL_SEC_OFFSET, sec);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

int P2DE_SoundSource::GetSourceSecOffset()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_SEC_OFFSET, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceSampleOffset(int samples)
{
	alSourcei(m_SoundSourceID, AL_SAMPLE_OFFSET, samples);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

int P2DE_SoundSource::GetSourceSampleOffset()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_SAMPLE_OFFSET, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE_SoundSource::SetSourceByteOffset(int bytes)
{
	alSourcei(m_SoundSourceID, AL_BYTE_OFFSET, bytes);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

int P2DE_SoundSource::GetSourceByteOffset()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_BYTE_OFFSET, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}
