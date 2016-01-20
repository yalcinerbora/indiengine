
template <class T> 
inline T IEMath::Cos(T radians)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::cos(radians);
}

template <class T> 
inline T IEMath::Sin(T radians)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::sin(radians);
}

template <class T> 
inline T IEMath::Tan(T radians)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::tan(radians);
}

template <class T> 
inline T IEMath::Acos(T value)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	assert(value <= 1.0 && value >= -1.0);
	return std::acos(value);
}

template <class T> 
inline T IEMath::Asin(T value)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	assert(value <= 1.0 && value >= -1.0);
	return std::asin(value);
}

template <class T> 
inline T IEMath::Atan(T value)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::atan(value);
}

template <class T>
inline T IEMath::Atan2(T x, T y)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::atan2(x, y);
}

template <class T>
inline T IEMath::ToRadians(T degree)
{
	static constexpr T DegToRadCoef = PI / 180.0f;
	return degree * DegToRadCoef;
}

template <class T>
inline T IEMath::ToDegrees(T radian)
{
	static constexpr T RadToDegCoef = 180.0f / PI;
	return radian * RadToDegCoef;
}

template<class T>
inline T IEMath::Log(T number)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::log(number);
}

template<class T>
inline T IEMath::Log10(T number)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::log10(number);
}

template<class T>
inline T IEMath::Log2(T number)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::log2(number);
}

template<class T, class F> 
inline T IEMath::Pow(T number, F power)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	static_assert(std::is_floating_point<F>::value, "Function Requires Arithmetic Type");
	return std::pow(number, power);
}

template<class T> 
inline T IEMath::Exp(T power)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::exp(power);
}

template<class T> 
inline T IEMath::Exp2(T power)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::exp2(power);
}

template<class T> 
inline T IEMath::Exp10(T power)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::pow(static_cast<T>(10.0f), power);
}

template<class T> T IEMath::Sqrt(T number)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::sqrt(number);
}

template<class T> T IEMath::Cbrt(T number)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::cbrt(number);
}

template<class T> T IEMath::InvSqrt(T power)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	assert(std::sqrt(number) != 0.0f);
	return static_cast<T>(1.0f) / std::sqrt(number);
}

template<class T> T IEMath::InvCbrt(T power)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	assert(std::cbrt(number) != 0.0f);
	return static_cast<T>(1.0f) / std::cbrt(number);
}

template<class T> 
inline T IEMath::IsExp2(T number)
{
	static_assert(std::is_integral<T>::value, "Function Requires Integral Type");
	return (number && !(number & (number - 1)));
}

inline uint32_t IEMath::UpperPowTwo(uint32_t number)
{
	assert(number <= 0x80000000);

	if(number <= 1) return 2;
	number--;
	number |= number >> 1;
	number |= number >> 2;
	number |= number >> 4;
	number |= number >> 8;
	number |= number >> 16;
	number++;

	return number;
}

inline uint64_t IEMath::UpperPowTwo(uint64_t number)
{
	assert(number <= 0x8000000000000000);

	if(number <= 1) return 2;
	number--;
	number |= number >> 1;
	number |= number >> 2;
	number |= number >> 4;
	number |= number >> 8;
	number |= number >> 16;
	number |= number >> 32;
	number++;

	return number;
}

template <class T>
inline T IEMath::Abs(T number)
{
	static_assert(std::is_arithmetic<T>::value, "Function Requires Arithmetic Type");
	return std::abs(number);
}

template <class T>
inline T IEMath::Clamp(T x, T max, T min)
{
	static_assert(std::is_arithmetic<T>::value, "Function Requires Arithmetic Type");
	return x < max ? max : (x > min ? min : x);
}

template <class T>
inline T IEMath::Max(T a, T b)
{
	static_assert(std::is_arithmetic<T>::value, "Function Requires Arithmetic Type");
	return std::max(a, b);
}

template <class T>
inline T IEMath::Min(T a, T b)
{
	static_assert(std::is_arithmetic<T>::value, "Function Requires Arithmetic Type");
	return std::min(a, b);
}

template<class T> 
inline T IEMath::Ceil(T number)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::ceil(number);
}

template<class T> 
inline T IEMath::Floor(T number)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::floor(numb);
}

template<class T> 
inline T IEMath::Round(T number)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::round(number);
}

template<class T> 
inline T IEMath::Trunc(T number)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::trunc(number);
}

template<class T> 
inline T IEMath::Mod(T a, T b)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return std::fmod(a, b);
}

template <class T> 
inline void IEMath::FractDecimal(T number, T& fraction, T& decimal)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	fraction = std::modf(number, &decimal);
}

template<class T> 
inline T IEMath::Lerp(T a, T b, T ratio)
{
	static_assert(std::is_floating_point<T>::value, "Function Requires Floating Point Type");
	return ratio * a + (static_cast<T>(1.0f) - ratio) * b;
}