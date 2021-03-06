#ifndef __IE_MACROS_H__
#define __IE_MACROS_H__

#include <cstdio>
#include <cstdint>
#include "IESystemDefinitions.h"

// Debug Ops
#ifdef IE_DEBUG
	#define DEBUG(string, ...) printf(string"\n", ## __VA_ARGS__ )
#else
	#define DEBUG(...)
#endif

#include <cassert>

// Delete Ops
#define SAFE_DELETE(ptr) if(ptr) delete ptr; ptr = nullptr
#define SAFE_DELETE_ARRAY(ptr) if(ptr) delete [] ptr; ptr = nullptr

// Force Extern Template for Basic Types (single template param)
#define IE_FORCE_EXTERN_BASIC_TYPES(CLASSNAME) \
	extern template class CLASSNAME##<bool>; \
	extern template class CLASSNAME##<int>; \
	extern template class CLASSNAME##<unsigned int>; \
	extern template class CLASSNAME##<float>;  \
	extern template class CLASSNAME##<double>;  \
	extern template class CLASSNAME##<int8_t>;  \
	extern template class CLASSNAME##<uint8_t>;  \
	extern template class CLASSNAME##<int16_t>;  \
	extern template class CLASSNAME##<uint16_t>;  \
	extern template class CLASSNAME##<int32_t>;  \
	extern template class CLASSNAME##<uint32_t>;  \
	extern template class CLASSNAME##<int64_t>;  \
	extern template class CLASSNAME##<uint64_t>;  \
	extern template class CLASSNAME##<size_t>;

#define IE_FORCE_COMPILE_BASIC_TYPES(CLASSNAME) \
	template class CLASSNAME##<bool>; \
	template class CLASSNAME##<int>; \
	template class CLASSNAME##<unsigned int>; \
	template class CLASSNAME##<float>;  \
	template class CLASSNAME##<double>;  \
	template class CLASSNAME##<int8_t>;  \
	template class CLASSNAME##<uint8_t>;  \
	template class CLASSNAME##<int16_t>;  \
	template class CLASSNAME##<uint16_t>;  \
	template class CLASSNAME##<int32_t>;  \
	template class CLASSNAME##<uint32_t>;  \
	template class CLASSNAME##<int64_t>;  \
	template class CLASSNAME##<uint64_t>;  \
	template class CLASSNAME##<size_t>;

// Errors
#define IE_ERROR(string, ...) fprintf( stderr, string"\n", ## __VA_ARGS__ )

// Log
#define IE_LOG(string, ...) fprintf( stdout, string"\n", ## __VA_ARGS__ )

// Check Stuff return false if not avail
#define IE_CHECK(boolExpression, trueString, falseString) \
	if(boolExpression) \
		IE_LOG(trueString); \
	else \
		IE_LOG(falseString)

// Exporting
#if defined IE_WINDOWS_PLATFORM
	#define IE_DLL_EXPORT __declspec(dllexport) 
	#define IE_DLL_IMPORT __declspec(dllimport) 
#elif defined IE_MACOS_PLATFORM 
	#define IE_DLL_EXPORT
	#define IE_DLL_IMPORT
#elif defined IE_LINUX_PLATFORM
	#define IE_DLL_EXPORT __attribute__ ((visibility ("default")))
	#define IE_DLL_IMPORT __attribute__ ((visibility ("default")))
#else
	#error Fatal Error! Unspecified Platform.
#endif

// Call Conventions
#if defined IE_WINDOWS_PLATFORM
	#define IE_STDCALL __stdcall
#elif defined IE_MACOS_PLATFORM 
	#define IE_STDCALL
#elif defined IE_LINUX_PLATFORM
	#define IE_STDCALL
#else
	#error Fatal Error! Unspecified Platform.
#endif

// Unused Macro For Preventing Unused Variable Warning
#if defined IE_WINDOWS_PLATFORM
	#define UNUSED(x) x
#elif defined IE_MACOS_PLATFORM
	#define UNUSED(x) x
#elif defined IE_LINUX_PLATFORM
	#define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#else
	#error Fatal Error! Unspecified Platform.
#endif

#endif //__IE_MACROS_H__