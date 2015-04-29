#pragma once

namespace P2DE
{
	namespace GAME
	{
		class BaseGame
		{
			public:
			// Use this Method to Load Resources wich use the Graphics Class
			virtual bool LoadResources() = 0;
			// Use this Method to Unload Resources wich use the Graphics Class, or Windowresizing will fail
			virtual bool UnloadResources() = 0;
		};
	}
}