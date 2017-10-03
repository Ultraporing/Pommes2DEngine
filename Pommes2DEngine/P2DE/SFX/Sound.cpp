#include "Sound.h"
#include <iostream>
#include <al.h>
#include <alc.h>
#include <AL\alut.h>
#include <Windows.h>
#include "../Utilities/StringConversion.h"

using namespace P2DE::SFX;

Sound::Sound()
{
	m_IsInitDevice = false;
}

Sound::~Sound()
{
	m_Context = alcGetCurrentContext();
	m_Device = alcGetContextsDevice(m_Context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(m_Context);
	alcCloseDevice(m_Device);
}

bool Sound::InitSound(const std::wstring deviceName)
{
	if (deviceName.empty())
	{
		m_Device = alcOpenDevice(NULL);
		if (!m_Device)
		{
			MessageBox(NULL, StringToWString(alutGetErrorString(alGetError())).c_str(), L"Error", MB_ICONERROR);
			return false;
		}
	}
	else
	{
		m_Device = alcOpenDevice(WStringToString(deviceName).c_str());
		if (!m_Device)
		{
			MessageBox(NULL, StringToWString(alutGetErrorString(alGetError())).c_str(), L"Error", MB_ICONERROR);
			return false;
		}
	}

	
	m_IsInitDevice = true;
	return true;
}

bool Sound::InitContext(const int * contextAttributes)
{
	if (alcGetCurrentContext())
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(m_Context);
	}

	m_Context = alcCreateContext(m_Device, contextAttributes);
	if (!alcMakeContextCurrent(m_Context))
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(alGetError())).c_str(), L"Error", MB_ICONERROR);
		return false;
	}

	return true;
}

bool Sound::IsInit()
{
	return m_IsInitDevice && alcGetCurrentContext();
}

void Sound::SetListenerPos(float x, float y, float z)
{
	alListener3f(AL_POSITION, x, y, z);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

std::array<float, 3> Sound::GetListenerPos()
{
	std::array<float, 3> oA = std::array<float, 3>();
	alGetListenerfv(AL_POSITION, oA.data());
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void Sound::SetListenerVel(float x, float y, float z)
{
	alListener3f(AL_VELOCITY, x, y, z);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

std::array<float, 3> Sound::GetListenerVel()
{
	std::array<float, 3> oA = std::array<float, 3>();
	alGetListenerfv(AL_VELOCITY, oA.data());
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void Sound::SetListenerOri(float x, float y, float z, float xUp, float yUp, float zUp)
{
	float ori[6] = { x, y, z, xUp, yUp, zUp };
	alListenerfv(AL_ORIENTATION, ori);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

std::array<float, 6> Sound::GetListenerOri()
{
	std::array<float, 6> oA = std::array<float, 6>();
	alGetListenerfv(AL_ORIENTATION, oA.data());
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

void P2DE::SFX::Sound::SetListenerGain(float gain)
{
	alListenerf(AL_GAIN, gain);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}
}

float P2DE::SFX::Sound::GetListenerGain()
{
	float oA = 0;
	alGetListenerf(AL_GAIN, &oA);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
	{
		MessageBox(NULL, StringToWString(alutGetErrorString(error)).c_str(), L"Error", MB_ICONERROR);
	}

	return oA;
}

std::vector<std::wstring> Sound::GetAudioDeviceNames()
{
	ALboolean enumeration;

	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (enumeration == AL_FALSE)
	{
		return std::vector<std::wstring>();
	}

	std::vector<std::wstring> outDevices = std::vector<std::wstring>();
	const ALCchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	while (device && *device != '\0' && next && *next != '\0') {
		outDevices.push_back(StringToWString(device));
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	
	return outDevices;
}