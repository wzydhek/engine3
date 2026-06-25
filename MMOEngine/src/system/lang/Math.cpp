/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "system/platform.h"

#ifdef PLATFORM_WIN
#define _USE_MATH_DEFINES
#include <cmath>
#endif

#include "Math.h"

const constexpr double Math::PI;
const constexpr double Math::DEG2RAD;
const constexpr double Math::RAD2DEG;
const constexpr double Math::E;

double Math::sqrt(double number) {
	return ::sqrt(number);
}

double Math::cbrt(double number) {
	return ::cbrt(number);
}

float Math::getPrecision(float num, int digits) {
	float power = pow((float)10, digits);
	return float(floor(num * power + .05f) / power);
}

double Math::acos(double arg) {
	return ::acos(arg);
}

double Math::sin(double arg) {
	return ::sin(arg);
}

double Math::cos(double arg) {
	return ::cos(arg);
}

double Math::ln(float value) {
	return (log10(value) / log10(E));
}

/*double Math::sqrt(double number) { // from Q3 fix for 64 bit
	long i;
	float x, y;
	const float f = 1.5F;

	x = number * 0.5F;
	y  = number;

	i  = * (long*) &y;
	i  = 0x5f3759df - ( i >> 1 );

	y  = * (float*) &i;
	y  = y * (f - (x * y * y));
	y  = y * (f - (x * y * y));
	return number * y;
}

float Math::rsqrt(float number) {
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * (long*) &y;
	i  = 0x5f3759df - ( i >> 1 );
	y  = * (float*) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );
	y  = y * ( threehalfs - ( x2 * y * y ) );

	return y;
}

float Math::fabs(float f) {
	int tmp = *(int*)&f;
	tmp &= 0x7FFFFFFF;
	return *(float*) &tmp;
}*/
