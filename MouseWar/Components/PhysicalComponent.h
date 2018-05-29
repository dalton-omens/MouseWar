#pragma once

#include "../MW_Common.h"

class PhysicalComponent
{
public:
	PhysicalComponent();

	MW_Vec3f velocity;
	MW_Vec3f acceleration;
};