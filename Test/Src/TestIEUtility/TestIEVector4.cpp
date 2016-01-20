#include "gtest/gtest.h"
#include "../IETest.h"
#include "IEUtility/IEVector4.h"

// Test Stuff (dunno if these should be global)
static IEVector4 testVec1(1.0f, 2.0f, 3.0f, 4.0f);
static IEVector4 testVec2(5.0f, 6.0f, 7.0f, 8.0f);

// Get Set Operations
TEST(IEVector4, AccessorsMutators)
{
	// Accessors
	EXPECT_EQ(1.0f, testVec1.getX());
	EXPECT_EQ(2.0f, testVec1.getY());
	EXPECT_EQ(3.0f, testVec1.getZ());
	EXPECT_EQ(4.0f, testVec1.getW());

	EXPECT_EQ(1.0f, testVec1.getData()[0]);
	EXPECT_EQ(2.0f, testVec1.getData()[1]);
	EXPECT_EQ(3.0f, testVec1.getData()[2]);
	EXPECT_EQ(4.0f, testVec1.getData()[3]);

	// Mutators
	IEVector4 mutateVec;
	mutateVec.setX(testVec1.getX());
	mutateVec.setY(testVec1.getY());
	mutateVec.setZ(testVec1.getZ());
	mutateVec.setW(testVec1.getW());

	EXPECT_EQ(1.0f, mutateVec.getX());
	EXPECT_EQ(2.0f, mutateVec.getY());
	EXPECT_EQ(3.0f, mutateVec.getZ());
	EXPECT_EQ(4.0f, testVec1.getW());

	float data[4] = {0.0f, 1.0f, 11.0f, 22.0f};
	mutateVec.setData(data);

	EXPECT_EQ(0.0f, mutateVec.getX());
	EXPECT_EQ(1.0f, mutateVec.getY());
	EXPECT_EQ(11.0f, mutateVec.getZ());
	EXPECT_EQ(22.0f, mutateVec.getW());

	// Assign operator
	mutateVec = testVec1;

	EXPECT_EQ(1.0f, mutateVec.getX());
	EXPECT_EQ(2.0f, mutateVec.getY());
	EXPECT_EQ(3.0f, mutateVec.getZ());
	EXPECT_EQ(4.0f, mutateVec.getW());
}

// Tests Operators
TEST(IEVector4, Operators) 
{
	// Logic Equal and Not Equal Ops
	EXPECT_TRUE(testVec1 == IEVector4(1.0f, 2.0f, 3.0f, 4.0f));
	EXPECT_FALSE(testVec1 == testVec2);
	EXPECT_TRUE(testVec1 != testVec2);
	EXPECT_FALSE(testVec1 != IEVector4(1.0f, 2.0f, 3.0f, 4.0f));

	// Operators
	EXPECT_EQ(IEVector4(6.0f, 8.0f, 10.0f, 12.0f), testVec1 + testVec2);
	EXPECT_EQ(IEVector4(-4.0f, -4.0f, -4.0f, -4.0f), testVec1 - testVec2);
	EXPECT_EQ(IEVector4(-1.0f, -2.0f, -3.0f, -4.0f), -testVec1);
	EXPECT_EQ(IEVector4(5.0f, 12.0f, 21.0f, 32.0f), testVec1 * testVec2);
	EXPECT_EQ(IEVector4(2.0f, 4.0f, 6.0f, 8.0f), testVec1 * 2.0f);
	EXPECT_EQ(IEVector4(2.0f, 4.0f, 6.0f, 8.0f), 2.0f * testVec1);
	EXPECT_EQ(IEVector4(5.0f, 3.0f, 7.0f/3.0f, 2.0f), testVec2 / testVec1);
	EXPECT_EQ(IEVector4(0.5f, 1.0f, 1.5f, 2.0f), testVec1 / 2.0f);

	// Operators with Assigment
	IEVector4 testVecCopy1(testVec1);

	testVecCopy1 += testVec2;
	EXPECT_EQ(IEVector4(6.0f, 8.0f, 10.0f, 12.0f), testVecCopy1);
	
	testVecCopy1 -= testVec2;
	EXPECT_EQ(IEVector4(1.0f, 2.0f, 3.0f, 4.0f), testVecCopy1);
	
	testVecCopy1 *= testVec2;
	EXPECT_EQ(IEVector4(5.0f, 12.0f, 21.0f, 32.0f), testVecCopy1);
	
	testVecCopy1 *= 2.0f;
	EXPECT_EQ(IEVector4(10.0f, 24.0f, 42.0f, 64.0f), testVecCopy1);
	
	testVecCopy1 /= testVec2;
	EXPECT_EQ(IEVector4(2.0f, 4.0f, 6.0f, 8.0f), testVecCopy1);
	
	testVecCopy1 /= 2.0f;
	EXPECT_EQ(IEVector4(1.0f, 2.0f, 3.0f, 4.0f), testVecCopy1);
}

// Tests Utility Portion
TEST(IEVector4, Utility) 
{
	EXPECT_EQ(70.0f, testVec1.DotProduct(testVec2));
	EXPECT_NEAR(5.47723f, testVec1.Length(), 0.00001f);
	EXPECT_EQ(30.0f, testVec1.LengthSqr());

	IEVector4 normalizedVec(testVec1.Normalize());
	EXPECT_NEAR(0.182574f, normalizedVec.getX(), 0.00001f); 
	EXPECT_NEAR(0.365148f, normalizedVec.getY(), 0.00001f);
	EXPECT_NEAR(0.547723f, normalizedVec.getZ(), 0.00001f);
	EXPECT_NEAR(0.730297f, normalizedVec.getW(), 0.00001f);

	IEVector4 normalizedVec2(testVec1);
	normalizedVec2.NormalizeSelf();
	EXPECT_NEAR(0.182574f, normalizedVec2.getX(), 0.00001f); 
	EXPECT_NEAR(0.365148f, normalizedVec2.getY(), 0.00001f);
	EXPECT_NEAR(0.547723f, normalizedVec2.getZ(), 0.00001f);
	EXPECT_NEAR(0.730297f, normalizedVec2.getW(), 0.00001f);
}
