#pragma once

namespace P2DE
{
	namespace GFX
	{
		/// <summary>	Values that represent sprite flip modes. </summary>
		///
		/// <remarks>	Tobias, 26.05.2015. </remarks>
		enum SPRITE_FLIP_MODE
		{
			NONE = 0,
			HORIZONTAL = 1 << 0,
			VERTICAL = 1 << 1
		};
	}
}