#pragma once

/* Common typedefs and other things for general MouseWar use. */

#include <cstdint>

typedef struct MW_Vec3f {
	float& operator[](int i) { return vec[i]; }
	float vec[3];
} MW_Vec3f;

/* MW_ComponentField is a bitfield representing the components that any given
 * Entity contains. It is used mainly for instantiation and safety to make sure
 * that an entity has a component before trying to access it.
 */
typedef uint8_t MW_ComponentField;

/* Component field constants, representing the location of different components in
 * the field.
 */
#define TRANSFORM_COMPONENT 0b10000000
#define DRAW_COMPONENT      0b01000000
#define PHYSICAL_COMPONENT  0b00100000

/* Every entity has a unique ID */
typedef uint32_t MW_EntityID;
