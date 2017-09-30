#include "SoundManager.h"
#include "P2DE_Music.h"
#include "P2DE_Sound.h"

using namespace P2DE::SFX;

void P2DE::SFX::SoundManager::DestroyAllSounds()
{
	for (std::map<std::wstring, P2DE_Sound*>::iterator it = m_Sounds.begin(); it != m_Sounds.end(); ++it)
	{
		it->second->UnloadSound();
		delete it->second;
	}

	m_Sounds.clear();
}

SoundManager::~SoundManager()
{
	DestroyAllSounds();
}

P2DE_Sound* P2DE::SFX::SoundManager::CreateSound(std::wstring name)
{
	if (m_Sounds.find(name) != m_Sounds.end())
	{
		return NULL;
	}

	P2DE_Sound* snd = new P2DE_Sound();
	if (snd->HasError())
	{
		delete snd;
		return NULL;
	}

	m_Sounds.insert(std::pair<std::wstring, P2DE_Sound*>(name, snd));

	return snd;
}

P2DE_Sound* P2DE::SFX::SoundManager::CreateSound(std::wstring name, std::wstring filePath)
{
	if (m_Sounds.find(name) != m_Sounds.end())
	{
		return NULL;
	}

	P2DE_Sound* snd = new P2DE_Sound(filePath);
	if (snd->HasError())
	{
		delete snd;
		return NULL;
	}

	m_Sounds.insert(std::pair<std::wstring, P2DE_Sound*>(name, snd));

	return snd;
}

void P2DE::SFX::SoundManager::DestroySound(std::wstring name)
{
	if (m_Sounds.find(name) != m_Sounds.end())
	{
		delete m_Sounds.at(name);
		m_Sounds.erase(name);
	}
}

P2DE_Sound* P2DE::SFX::SoundManager::GetSound(std::wstring name)
{
	if (m_Sounds.find(name) != m_Sounds.end())
	{
		return m_Sounds.at(name);
	}
	else
	{
		return NULL;
	}
}
