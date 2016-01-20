
//template <class T> 
//inline T IEBitManipulation::Reverse(T)
//{
//	static_assert(std::is_integral<T>::value, "Function Requires Integral Type");
//}

template <class T> 
inline T IEBitManipulation::FetchBit(T number, uint32_t offset, uint32_t count)
{
	static_assert(std::is_integral<T>::value, "Function Requires Integral Type");
	return (number >> offset) & static_cast<T>(std::exp2(count) - 1.0);
}

template <class T> 
inline T IEBitManipulation::ApplyBit(T number, T bits, uint32_t offset, uint32_t count)
{
	static_assert(std::is_integral<T>::value, "Function Requires Integral Type");
	assert(offset < sizeof(T) * 8);
	assert(count <= sizeof(T) * 8);
	return number & ((bits & static_cast<T>((std::exp2(count) - 1.0))) << offset);
}

//template <class T> 
//inline uint32_t IEBitManipulation::BitCount(T)
//{
//	static_assert(std::is_arithmetic<T>::value, "Function Requires Arithmetic Type");
//}

template <class T, class F> 
inline T IEBitManipulation::FloatToBits(F)
{
	static_assert(std::is_floating_point<F>::value, "Function Requires Floating Point Type");
	static_assert(std::is_integral<T>::value, "Function Requires Integral Type");
	static_assert(std::is_unsigned<T>::value, "Function Requires Unsigned Type");
	return *reinterpret_cast<T>(&number);
}

template <class F, class T> 
inline F IEBitManipulation::BitsToFloat(T bits)
{
	static_assert(std::is_floating_point<F>::value, "Function Requires Floating Point Type");
	static_assert(std::is_integral<T>::value, "Function Requires Integral Type");
	static_assert(std::is_unsigned<T>::value, "Function Requires Unsigned Type");
	return *reinterpret_cast<F>(&bits);
}

template <class T> 
inline uint32_t IEBitManipulation::SignBit(T number)
{
	static_assert(std::is_arithmetic<T>::value, "Function Requires Arithmetic Type");
	return std::signbit(number) ? 1u : 0u;
}