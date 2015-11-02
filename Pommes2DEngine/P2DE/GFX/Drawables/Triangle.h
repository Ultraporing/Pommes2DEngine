#pragma once
#include "BaseDrawable.h"

class Triangle : public BaseDrawable
{
	public:
		virtual void Load() override;
		virtual void Unload() override;
		virtual void Draw() override;
};

