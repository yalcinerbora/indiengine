/**

*/

#ifndef __IE_BITMANIPULATION_H__
#define __IE_BITMANIPULATION_H__

#include <cstdint>
#include <type_traits>
#include <cmath>

namespace IEBitManipulation
{
//	template <class T> T		Reverse(T);
	template <class T> T		FetchBit(T, uint32_t offset, uint32_t count);
	template <class T> T		ApplyBit(T number, T bits, uint32_t offset, uint32_t count);
//	template <class T> uint32_t BitCount(T);
	
	// Float bits
	template <class T, class F> T FloatToBits(F);
	template <class F, class T> F BitsToFloat(T);
	
	template <class T> uint32_t   SignBit(T);

	// TODO: Add Pack unpack functions

};
#include "IEBitManipulation.hpp"
#endif //__IE_BITMANIPULATION_H__