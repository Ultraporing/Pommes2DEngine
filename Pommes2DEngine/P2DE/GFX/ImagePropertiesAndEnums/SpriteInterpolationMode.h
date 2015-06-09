#pragma once

namespace P2DE
{
	namespace GFX
	{
		enum SPRITE_INTERPOLATION_MODE
		{
			NEAREST_NEIGHBOR = 0,
			LINEAR = 1,
			CUBIC = 2,
			MULTI_SAMPLE_LINEAR = 3,
			ANISOTROPIC = 4,
			HIGH_QUALITY_CUBIC = 5,
			FORCE_DWORD = 0xffffffff
		};
	}
}