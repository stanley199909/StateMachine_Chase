#include "AnimationFunction.h"

inline float Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
};