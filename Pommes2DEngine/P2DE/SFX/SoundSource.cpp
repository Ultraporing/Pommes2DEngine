#include "SoundSource.h"
#include <sstream>
#include <comdef.h>
#include <al.h>
#include <alc.h>
#include "../Utilities/StringConversion.h"

using namespace P2DE::SFX;

SoundSource::SoundSource()
{
	InitSound();
}

SoundSource::SoundSource(std::wstring path)
{
	InitSound();
	if (!HasError())
	{
		LoadSoundfile(path);
	}
}

void SoundSource::InitSound()
{
	m_Loaded = false;
	m_HasError = true;
	m_Channel = -1;



	m_Loaded = false;
	m_HasError = false;
}

bool SoundSource::LoadSoundfile(std::wstring path)
{
	
	m_FilePath = path;
	_bstr_t cPath(m_FilePath.c_str());
	char* p = (char*)cPath;



	m_Loaded = true;

	return true;
}

void SoundSource::UnloadSound()
{
	if (!IsLoaded()) return;

	m_FilePath = std::wstring();
	m_Loaded = false;
}

void SoundSource::Play(int loops)
{
	if (!IsLoaded()) return;

}

void SoundSource::Pause()
{
	if (!IsLoaded()) return;

	
}

void SoundSource::Stop()
{
	if (!IsLoaded()) return;


}

bool SoundSource::IsLoaded()
{
	return m_Loaded;
}

bool SoundSource::HasError()
{
	return m_HasError;
}

int SoundSource::GetChannel()
{
	return m_Channel;
}

void SoundSource::SetSourcePitch(float pitch)
{
	alSourcef(m_SoundSourceID, AL_PITCH, pitch);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

float SoundSource::GetSourcePitch()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_PITCH, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceGain(float gain)
{
	alSourcef(m_SoundSourceID, AL_GAIN, gain);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

float SoundSource::GetSourceGain()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_GAIN, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceMaxDistance(float maxDistance)
{
	alSourcef(m_SoundSourceID, AL_MAX_DISTANCE, maxDistance);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

float SoundSource::GetSourceMaxDistance()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_MAX_DISTANCE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceRolloffFactor(float rolloffFactor)
{
	alSourcef(m_SoundSourceID, AL_ROLLOFF_FACTOR, rolloffFactor);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

float SoundSource::GetSourceRolloffFactor()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_ROLLOFF_FACTOR, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceReferenceDistance(float referenceDistance)
{
	alSourcef(m_SoundSourceID, AL_REFERENCE_DISTANCE, referenceDistance);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

float SoundSource::GetReferenceDistance()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_REFERENCE_DISTANCE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceMinGain(float minGain)
{
	alSourcef(m_SoundSourceID, AL_MIN_GAIN, minGain);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

float SoundSource::GetSourceMinGain()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_MIN_GAIN, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceMaxGain(float maxGain)
{
	alSourcef(m_SoundSourceID, AL_MAX_GAIN, maxGain);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

float SoundSource::GetSourceMaxGain()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_MAX_GAIN, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceConeOuterGain(float coneOuterGain)
{
	alSourcef(m_SoundSourceID, AL_CONE_OUTER_GAIN, coneOuterGain);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

float SoundSource::GetSourceConeOuterGain()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_CONE_OUTER_GAIN, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceConeInnerAngle(float coneInnerAngle)
{
	alSourcef(m_SoundSourceID, AL_CONE_INNER_ANGLE, coneInnerAngle);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

float SoundSource::GetConeInnerAngle()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_CONE_INNER_ANGLE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceConeOuterAngle(float coneOuterAngle)
{
	alSourcef(m_SoundSourceID, AL_CONE_OUTER_ANGLE, coneOuterAngle);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

float SoundSource::GetConeOuterAngle()
{
	float oA = 0;
	alGetSourcef(m_SoundSourceID, AL_CONE_OUTER_ANGLE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourcePos(float x, float y, float z)
{
	alSource3f(m_SoundSourceID, AL_POSITION, x, y, z);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

std::array<float, 3> SoundSource::GetSourcePos()
{
	std::array<float, 3> oA = std::array<float, 3>();
	alGetSourcefv(m_SoundSourceID, AL_POSITION, oA.data());
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceVel(float x, float y, float z)
{
	alSource3f(m_SoundSourceID, AL_VELOCITY, x, y, z);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

std::array<float, 3> SoundSource::GetSourceVel()
{
	std::array<float, 3> oA = std::array<float, 3>();
	alGetSourcefv(m_SoundSourceID, AL_VELOCITY, oA.data());
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceDir(float x, float y, float z)
{
	alSource3f(m_SoundSourceID, AL_DIRECTION, x, y, z);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

std::array<float, 3> SoundSource::GetSourceDir()
{
	std::array<float, 3> oA = std::array<float, 3>();
	alGetSourcefv(m_SoundSourceID, AL_DIRECTION, oA.data());
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceRelative(bool relative)
{
	alSourcei(m_SoundSourceID, AL_SOURCE_RELATIVE, (int)relative);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

bool SoundSource::GetSourceRelative()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_SOURCE_RELATIVE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceType(SourceType type)
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
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

SourceType SoundSource::GetSourceType()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_SOURCE_TYPE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
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

void SoundSource::SetSourceLooping(bool looping)
{
	alSourcei(m_SoundSourceID, AL_LOOPING, (int)looping);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

bool SoundSource::GetSourceLooping()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_LOOPING, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceBuffer(int bufferID)
{
	alSourcei(m_SoundSourceID, AL_BUFFER, bufferID);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

int SoundSource::GetSourceBuffer()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_BUFFER, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceState(State state)
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
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

State SoundSource::GetSourceState()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_SOURCE_STATE, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
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

int SoundSource::GetSourceBuffersQueued()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_BUFFERS_QUEUED, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceBuffersProcessed(int buffersProcessed)
{
	alSourcei(m_SoundSourceID, AL_BUFFERS_PROCESSED, buffersProcessed);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

int SoundSource::GetSourceBuffersProcessed()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_BUFFERS_PROCESSED, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceSecOffset(int sec)
{
	alSourcei(m_SoundSourceID, AL_SEC_OFFSET, sec);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

int SoundSource::GetSourceSecOffset()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_SEC_OFFSET, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceSampleOffset(int samples)
{
	alSourcei(m_SoundSourceID, AL_SAMPLE_OFFSET, samples);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

int SoundSource::GetSourceSampleOffset()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_SAMPLE_OFFSET, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}

void SoundSource::SetSourceByteOffset(int bytes)
{
	alSourcei(m_SoundSourceID, AL_BYTE_OFFSET, bytes);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}
}

int SoundSource::GetSourceByteOffset()
{
	int oA = 0;
	alGetSourcei(m_SoundSourceID, AL_BYTE_OFFSET, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, (LPCWSTR)error, L"Error", MB_ICONERROR);
	}

	return oA;
}
