#include <Windows.h>
#include <mciapi.h>
#include <sstream>
#include "P2DE_Sound.h"
#include "..\GFX\Graphics.h"

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

void P2DE_Sound::InitSound()
{
	UUID uniqueSoundID = { 0 };
	if (UuidCreate(&uniqueSoundID) != RPC_S_OK)
	{
		printf("Error: Failed to create UUID for Sound!");
		m_Loaded = false;
		m_HasError = true;
		return;
	}

	RPC_WSTR szUuid = NULL;
	if (UuidToString(&uniqueSoundID, &szUuid) != RPC_S_OK)
	{
		printf("Error: Failed to convert UUID to string for Sound!");
		m_Loaded = false;
		m_HasError = true;
		return;
	}

	m_SoundID = (wchar_t*)szUuid;
	RpcStringFree(&szUuid);

	m_Loaded = false;
	m_HasError = false;
	m_PlaybackStatus = Status::Stopped;
}

void showError(DWORD dwError)
{
	wchar_t szErrorBuf[MAXERRORLENGTH];
	MessageBeep(MB_ICONEXCLAMATION);
	if (mciGetErrorString(dwError, (LPWSTR)szErrorBuf, MAXERRORLENGTH))
	{
		MessageBox(NULL, szErrorBuf, L"MCI Error",
			MB_ICONEXCLAMATION);
	}
	else
	{
		MessageBox(NULL, L"Unknown Error", L"MCI Error",
			MB_ICONEXCLAMATION);
	}
}

bool P2DE_Sound::LoadSoundfile(std::wstring path)
{
	m_FilePath = path;

	std::wstringstream wss;
	TCHAR pwd[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pwd);
	wss << L"open \"" << pwd << "\\" << path.c_str() << "\" type waveaudio alias " << m_SoundID.c_str();
	MCIERROR merr = mciSendString(wss.str().c_str(), NULL, 0, NULL);
	
	if (merr != NULL)
	{
		showError(merr);
		printf("Error: Sound file (%ws) not found!", path.c_str());
		m_Loaded = false;

		return false;
	}

	m_Loaded = true;

	return true;
}

void P2DE_Sound::UnloadSound()
{
	std::wstringstream wss;
	wss << L"close " << m_SoundID.c_str();

	mciSendString(wss.str().c_str(), NULL, 0, NULL);
	m_FilePath = std::wstring();

	m_PlaybackStatus = Status::Stopped;
	m_Loaded = false;
}

void P2DE_Sound::Play(bool loop)
{
	if (IsLoaded())
	{
		if (m_PlaybackStatus == Status::Paused)
		{
			std::wstringstream wss;
			wss << L"resume " << m_SoundID.c_str() << L" notify";
			mciSendString(wss.str().c_str(), NULL, 0, NULL);
		}
		else
		{
			if (loop)
			{
				std::wstringstream wss;
				wss << L"play " << m_SoundID.c_str() << L" repeat notify";
				mciSendString(wss.str().c_str(), NULL, 0, NULL);
			}
			else
			{
				std::wstringstream wss;
				wss << L"play " << m_SoundID.c_str() << " from 0 notify";
				MCIERROR merr = mciSendString(wss.str().c_str(), NULL, 0, P2DE_GFX.GetGameWindowHandle());

				if (merr != NULL)
				{
					showError(merr);
					m_Loaded = false;

					return;
				}
			}
		}

		m_PlaybackStatus = Status::Playing;

		return;
	}	
}

void P2DE_Sound::Pause()
{
	if (IsLoaded())
	{
		std::wstringstream wss;
		wss << L"pause " << m_SoundID.c_str();
		mciSendString(wss.str().c_str(), NULL, 0, NULL);

		m_PlaybackStatus = Status::Paused;
	}
}

void P2DE_Sound::Stop()
{
	if (IsLoaded())
	{
		std::wstringstream wss;
		wss << L"stop " << m_SoundID.c_str();
		mciSendString(wss.str().c_str(), NULL, 0, NULL);

		m_PlaybackStatus = Status::Stopped;
	}
		
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
