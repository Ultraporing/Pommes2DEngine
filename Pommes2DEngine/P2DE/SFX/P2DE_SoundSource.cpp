#include "P2DE_SoundSource.h"
#include <sstream>
#include <comdef.h>
#include <AL\alut.h>


using namespace P2DE::SFX;

P2DE_Sound::P2DE_Sound()
{
	InitSound();
}

P2DE_Sound::P2DE_Sound(std::wstring path)
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

void P2DE_Sound::InitSound()
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

bool P2DE_Sound::LoadSoundfile(std::wstring path)
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

void P2DE_Sound::UnloadSound()
{
	if (!IsLoaded()) return;

	Mix_FreeChunk(m_SoundData);
	m_SoundData = NULL;

	m_FilePath = std::wstring();

	SetPlaybackStatus(Status::Stopped);
	m_Loaded = false;
}

void P2DE_Sound::Play(int loops)
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

void P2DE_Sound::Pause()
{
	if (!IsLoaded()) return;

	Mix_Pause(m_Channel);
	SetPlaybackStatus(Status::Paused);
}

void P2DE_Sound::Stop()
{
	if (!IsLoaded()) return;

	Mix_HaltChannel(m_Channel);
}

void P2DE::SFX::P2DE_Sound::SetPlaybackStatus(Status status)
{
	m_PlaybackStatus = status;
}

Status P2DE_Sound::GetPlaybackStatus()
{
	return m_PlaybackStatus;
}

bool P2DE_Sound::IsLoaded()
{
	return m_Loaded;
}

bool P2DE::SFX::P2DE_Sound::HasError()
{
	return m_HasError;
}

int P2DE::SFX::P2DE_Sound::GetChannel()
{
	return m_Channel;
}
