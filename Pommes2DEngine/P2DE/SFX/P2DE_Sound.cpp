#include "P2DE_Sound.h"
#include <SFML\Audio.hpp>

using namespace P2DE::SFX;

P2DE_Sound::P2DE_Sound()
{
	m_Sound = new sf::Sound();
	m_SoundBuffer = new sf::SoundBuffer();
	m_Loaded = false;
}

P2DE_Sound::P2DE_Sound(std::string path)
{
	if (!m_SoundBuffer->loadFromFile(path))
	{
		printf("Error: Sound file (%s) not found!", path.c_str());
		m_Loaded = false;

		return;
	}	

	m_Sound->setBuffer(*m_SoundBuffer);

	m_Loaded = true;
}

P2DE_Sound::~P2DE_Sound()
{
	if (m_Sound)
	{
		delete m_Sound;
		m_Sound = NULL;
	}
		
	if (m_SoundBuffer)
	{
		delete m_SoundBuffer;
		m_SoundBuffer = NULL;
	}		
}

bool P2DE_Sound::LoadSoundfile(std::string path)
{
	if (!m_SoundBuffer->loadFromFile(path))
	{
		printf("Error: Sound file (%s) not found!", path.c_str());
		m_Loaded = false;

		return false;
	}

	m_Sound->setBuffer(*m_SoundBuffer);

	m_Loaded = true;

	return true;
}

void P2DE_Sound::UnloadSound()
{
	m_Sound->resetBuffer();
	if (m_SoundBuffer)
	{
		delete m_SoundBuffer;
		m_SoundBuffer = NULL;
	}

	m_Loaded = false;
}

void P2DE_Sound::Play()
{
	if (IsLoaded())
		m_Sound->play();
}

void P2DE_Sound::Pause()
{
	if (IsLoaded())
		m_Sound->pause();
}

void P2DE_Sound::Stop()
{
	if (IsLoaded())
		m_Sound->stop();
}

Status P2DE_Sound::GetPlaybackStatus()
{
	switch (m_Sound->getStatus())
	{
		case 0:
			return Status::Stopped;
		case 1:
			return Status::Paused;
		case 2:
			return Status::Playing;
	}

	return Status::Stopped;
}

bool P2DE_Sound::IsLoaded()
{
	return m_Loaded;
}
