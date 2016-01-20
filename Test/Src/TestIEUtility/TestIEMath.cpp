#include "gtest/gtest.h"
#include "../IETest.h"
#include "IEUtility/IEMath.h"
#include <numeric>

// Get Set Operations
TEST(IEMath12, UpperPowTwo)
{
	const size_t size = 12;
	const uint32_t numbers[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,

		// Exceptional Cases
		std::numeric_limits<uint32_t>::max()
	};
	const uint32_t results[] =
	{
		2, 2, 2, 4, 4, 8, 8, 8, 8, 16, 16,
	};


	for(unsigned int i = 0; i < size - 1; i++)
	{
		EXPECT_EQ(results[i], IEMath::UpperPowTwo(numbers[i]));
	}
	EXPECT_DEATH(IEMath::UpperPowTwo(numbers[size - 1]), IE_TEST_ASSERT_FAIL_STRING);
}