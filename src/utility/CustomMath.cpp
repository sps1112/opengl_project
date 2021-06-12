#include <utility/CustomMath.h>

float clamp(float a, float min, float max)
{
    return glm::clamp(a, min, max);
}

float max(float a, float b)
{
    return ((a > b) ? a : b);
}

float min(float a, float b)
{
    return ((a > b) ? a : b);
}

float saturate(float a)
{
    return clamp(a, 0.0f, 1.0f);
}

float radian_to_degree(float rad)
{
    return ((rad / PI_VAL) * 180.0f);
}

float degree_to_radian(float degree)
{
    return ((degree / 180.0f) * PI_VAL);
}