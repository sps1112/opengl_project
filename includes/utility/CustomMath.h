#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

// glm libraries for math
#include <external/glm/glm/glm.hpp>
#include <external/glm/glm/gtc/matrix_transform.hpp>
#include <external/glm/glm/gtc/type_ptr.hpp>
#include <external/glm/glm/gtc/quaternion.hpp>
#include <external/glm/glm/gtx/quaternion.hpp>

// Constant values
#define PI_VAL 3.14159265 // Custom Value of PI

// Custom Vector Math Definitions
using Vec2 = glm::vec2; // Vector2 data type as (x,y)
using Vec3 = glm::vec3; // Vector3 data type as (x,y,z)
using Vec4 = glm::vec4; // Vector4 data type as (x,y,z,w)
using Mat3 = glm::mat3; // A 3x3 Matrix
using Mat4 = glm::mat4; // A 4x4 Matrix

// Custom Functions

// Clamps the value of a variable between some maximum and minimum value
float clamp(float a, float min, float max);
// Returns the max number b/w a and b
float max(float a, float b);
// Returns the min number b/w a and b
float min(float a, float b);
// Clamps the value of a b/w 0 and 1
float saturate(float a);
// Overflows the value of a from -period/2 to period/2
float overflow(float a, float period);
// Makes a greater than said value
float floor(float a, float val, float diff = 0.001);
// Makes a less than said value
float ciel(float a, float val, float diff = 0.001);
// Converts an Angle given in radians to degrees
float radian_to_degree(float rad);
// Converts an Angle given in degrees to radians
float degree_to_radian(float degree);

#endif // !CUSTOM_MATH_H
