#pragma once

#include "../MW_Common.h"

class TransformComponent {
public:
	TransformComponent();

	MW_Vec3 position;
	MW_Vec3 rotation;
	MW_Vec3 scale;
};

