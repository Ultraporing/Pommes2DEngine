#pragma once
#include <string>

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

			class P2DE_Shader
			{
				public:
				P2DE_Shader();
				~P2DE_Shader();

				public:
				virtual void LoadShader() {};
				virtual void UnloadShader() {};
			};

			class MyClass : public P2DE::GFX::SHADER::P2DE_Shader
			{
				public:
				void LoadShader() override {}
				void UnloadShader() override {}
			};
		}
	}
}
