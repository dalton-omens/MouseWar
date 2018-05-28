#pragma once

#include "../MW_Common.h"

class TransformComponent {
public:
	TransformComponent();

	MW_Vec3f position;
	MW_Vec3f rotation;
	MW_Vec3f scale;
};

