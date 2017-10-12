#pragma once
#include <string>
#include "..\..\Common.h"

namespace P2DE
{
	namespace GFX
	{
		namespace SHADER
		{
			enum EShaderID
			{
				BASE,
				COLOR,
				TEXTURE,
				_LAST
			};

			class P2DE_DECLSPEC Shader
			{
				public:
				Shader();
				~Shader();

				public:
				virtual void LoadShader() {};
				virtual void UnloadShader() {};
			};

			class P2DE_DECLSPEC MyClass : public P2DE::GFX::SHADER::Shader
			{
				public:
				void LoadShader() override {}
				void UnloadShader() override {}
			};
		}
	}
}
