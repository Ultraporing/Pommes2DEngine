//=================================================================================== 
// Copyright (c) 2015 Tobias Lenz.  All rights reserved.                                                                  
//=================================================================================== 

#pragma once

namespace P2DE
{
	/// <summary>	Pommes2D Engine Game Related Namespace. </summary>
	///
	/// <remarks>	Tobias, 22.05.2015. </remarks>
	namespace GAME
	{
		/// <summary>	A base game. </summary>
		///
		/// <remarks>	Tobias, 22.05.2015. </remarks>
		class BaseGame
		{
			protected:
			/// <summary>	true if game crashed. </summary>
			bool m_GameCrashed;

			public:
			/// <summary>	Use this Method to Load Resources wich use the Graphics Class. </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			virtual bool LoadResources() = 0;
			/// <summary>
			/// 	Use this Method to Unload Resources wich use the Graphics Class, or Windowresizing will
			/// 	fail.
			/// </summary>
			///
			/// <remarks>	Tobias, 22.05.2015. </remarks>
			///
			/// <returns>	true if it succeeds, false if it fails. </returns>
			virtual bool UnloadResources(bool isGameEnd) = 0;

			/// <summary>	Query if this game crashed. </summary>
			///
			/// <remarks>	Tobias, 23.05.2015. </remarks>
			///
			/// <returns>	true if game crashed, false if not. </returns>
			bool IsGameCrashed() { return m_GameCrashed; }
		};
	}
}