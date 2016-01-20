/**

*/

#ifndef __IE_MATH_H__
#define __IE_MATH_H__

#include <cmath>
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <algorithm>

namespace IEMath
{
	// PI Stuff
	static constexpr float PI = 3.14159265f;
	static constexpr float PISqr = PI * PI;
	static constexpr float InvPI = 1.0f / PI;
	static constexpr float InvPISqr = 1.0f / (PI * PI);

	// E Stuff
	static constexpr float E = 3.14159265f;
	static constexpr float InvE = 1.0f / E;

	// Trigonometry
	template<class T> T Cos(T radians);
	template<class T> T Sin(T radians);
	template<class T> T Tan(T radians);
	template<class T> T Acos(T);
	template<class T> T Asin(T);
	template<class T> T Atan(T);
	template<class T> T Atan2(T, T);

	// Degree-Radian Conversion
	template<class T> T ToRadians(T degree);
	template<class T> T ToDegrees(T radian);

	// Logarithm
	template<class T> T Log(T);
	template<class T> T Log2(T);
	template<class T> T Log10(T);

	// Power
	template<class T, class F> T Pow(T number, F power);
	template<class T> T Exp(T power);
	template<class T> T Exp2(T power);
	template<class T> T Exp10(T power);

	template<class T> T Sqrt(T);
	template<class T> T Cbrt(T);
	template<class T> T InvSqrt(T);
	template<class T> T InvCbrt(T);

	template<class T> T IsExp2(T integer);

	// Integer Power
	uint32_t UpperPowTwo(uint32_t);
	uint64_t UpperPowTwo(uint64_t);

	// Numerical Functions
	template<class T> T Abs(T);
	template<class T> T Clamp(T x, T max, T min);
	template<class T> T Max(T, T);
	template<class T> T Min(T, T);

	template<class T> T Ceil(T);
	template<class T> T Floor(T);
	template<class T> T Round(T);
	template<class T> T Trunc(T);
	template<class T> T Mod(T, T);

	template <class T> void FractDecimal(T number, T& fraction, T& decimal);

	// Interpolation
	template<class T> T Lerp(T, T, T ratio);
}
#include "IEMath.hpp"
#endif //__IE_MATH_H__