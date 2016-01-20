/**

Author(s):
	Bora Yalciner

*/

#ifndef __IE_TEST_H__
#define __IE_TEST_H__

#include "IEUtility/IESystemDefinitions.h"

#if defined IE_WINDOWS_PLATFORM
	static const char IE_TEST_ASSERT_FAIL_STRING[] = "Assertion failed.*";
#elif defined IE_MACOS_PLATFORM
	static const char IE_TEST_ASSERT_FAIL_STRING[] = ".*";
#elif defined IE_LINUX_PLATFORM
	static const char IE_TEST_ASSERT_FAIL_STRING[] = ".*";
#else
	#error Fatal Error! Unspecified Platform.
#endif

#endif //__IE_TEST_H__