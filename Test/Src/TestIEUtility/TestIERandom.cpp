#include "gtest/gtest.h"
#include "../IETest.h"

#include "IEUtility/IERandom.h"

#define CHECK_AMOUNT 20000
#define MIN_RNG 13
#define MAX_RNG 1024

TEST(IERandom, Int)
{
	IERandom rng;

	// Random Max Min
	for(int i = 0; i < CHECK_AMOUNT; i++)
	{
		uint64_t result = rng.IntMM(MIN_RNG, MAX_RNG);
		ASSERT_GE(result, MIN_RNG);
		ASSERT_LE(result, MAX_RNG);
	}
	EXPECT_DEATH(rng.IntMM(10, 0), IE_TEST_ASSERT_FAIL_STRING);
	
	// Random Mean Variance
	for(int i = 0; i < CHECK_AMOUNT; i++)
	{
		uint64_t result = rng.IntMV(MAX_RNG, MIN_RNG);
		ASSERT_GE(result, MAX_RNG - MIN_RNG);
		ASSERT_LE(result, MAX_RNG + MIN_RNG);
	}

	// Random Max
	for(int i = 0; i < CHECK_AMOUNT; i++)
	{
		uint64_t result = rng.Int(MAX_RNG);
		ASSERT_GE(result, std::numeric_limits<uint64_t>::min());
		ASSERT_LE(result, MAX_RNG);
	}

	// Random Engine Limit
	for(int i = 0; i < CHECK_AMOUNT; i++)
	{
		uint64_t result = rng.Int();
		ASSERT_GE(result, std::numeric_limits<uint64_t>::min());
		ASSERT_LE(result, std::numeric_limits<uint64_t>::max());
	}
}

TEST(IERandom, Double)
{
	IERandom rng;

	// Random 0-1
	for(int i = 0; i < CHECK_AMOUNT; i++)
	{
		double result = rng.Double01();
		ASSERT_GE(result, 0.0);
		ASSERT_LE(result, 1.0);
	}

	// Random Mean Variance
	for(int i = 0; i < CHECK_AMOUNT; i++)
	{
		double result = rng.Double(MAX_RNG, MIN_RNG);
		ASSERT_GE(result, MAX_RNG - MIN_RNG);
		ASSERT_LE(result, MAX_RNG + MIN_RNG);
	}
}