#include "gtest/gtest.h"
#include "../IETest.h"
#include "IEUtility/IEVector3.h"

// Test Stuff (dunno if these should be global)
static IEVector3 testVec1(1.0f, 2.0f, 3.0f);
static IEVector3 testVec2(4.0f, 5.0f, 6.0f);

// Get Set Operations
TEST(IEVector3, AccessorsMutators)
{
	// Accessors
	EXPECT_EQ(1.0f, testVec1.getX());
	EXPECT_EQ(2.0f, testVec1.getY());
	EXPECT_EQ(3.0f, testVec1.getZ());

	EXPECT_EQ(1.0f, testVec1.getData()[0]);
	EXPECT_EQ(2.0f, testVec1.getData()[1]);
	EXPECT_EQ(3.0f, testVec1.getData()[2]);

	// Mutators
	IEVector3 mutateVec;
	mutateVec.setX(testVec1.getX());
	mutateVec.setY(testVec1.getY());
	mutateVec.setZ(testVec1.getZ());

	EXPECT_EQ(1.0f, mutateVec.getX());
	EXPECT_EQ(2.0f, mutateVec.getY());
	EXPECT_EQ(3.0f, mutateVec.getZ());
	
	float data[3] = {0.0f, 1.0f, 11.0f};
	mutateVec.setData(data);

	EXPECT_EQ(0.0f, mutateVec.getX());
	EXPECT_EQ(1.0f, mutateVec.getY());
	EXPECT_EQ(11.0f, mutateVec.getZ());

	// Assign operator
	mutateVec = testVec1;

	EXPECT_EQ(1.0f, mutateVec.getX());
	EXPECT_EQ(2.0f, mutateVec.getY());
	EXPECT_EQ(3.0f, mutateVec.getZ());
}

// Tests Operators
TEST(IEVector3, Operators) 
{
	// Logic Equal and Not Equal Ops
	EXPECT_TRUE(testVec1 == IEVector3(1.0f, 2.0f, 3.0f));
	EXPECT_FALSE(testVec1 == testVec2);
	EXPECT_TRUE(testVec1 != testVec2);
	EXPECT_FALSE(testVec1 != IEVector3(1.0f, 2.0f, 3.0f));

	// Operators
	EXPECT_EQ(IEVector3(5.0f, 7.0f, 9.0f), testVec1 + testVec2);
	EXPECT_EQ(IEVector3(-3.0f, -3.0f, -3.0f), testVec1 - testVec2);
	EXPECT_EQ(IEVector3(-1.0f, -2.0f, -3.0f), -testVec1);
	EXPECT_EQ(IEVector3(4.0f, 10.0f, 18.0f), testVec1 * testVec2);
	EXPECT_EQ(IEVector3(2.0f, 4.0f, 6.0f), testVec1 * 2.0f);
	EXPECT_EQ(IEVector3(2.0f, 4.0f, 6.0f), 2.0f * testVec1);
	EXPECT_EQ(IEVector3(0.25f, 0.4f, 0.5f), testVec1 / testVec2);
	EXPECT_EQ(IEVector3(0.5f, 1.0f, 1.5f), testVec1 / 2.0f);

	// Operators with Assigment
	IEVector3 testVecCopy1(testVec1);

	testVecCopy1 += testVec2;
	EXPECT_EQ(IEVector3(5.0f, 7.0f, 9.0f), testVecCopy1);
	
	testVecCopy1 -= testVec2;
	EXPECT_EQ(IEVector3(1.0f, 2.0f, 3.0f), testVecCopy1);
	
	testVecCopy1 *= testVec2;
	EXPECT_EQ(IEVector3(4.0f, 10.0f, 18.0f), testVecCopy1);
	
	testVecCopy1 *= 2.0f;
	EXPECT_EQ(IEVector3(8.0f, 20.0f, 36.0f), testVecCopy1);
	
	testVecCopy1 /= testVec2;
	EXPECT_EQ(IEVector3(2.0f, 4.0f, 6.0f), testVecCopy1);
	
	testVecCopy1 /= 2.0f;
	EXPECT_EQ(IEVector3(1.0f, 2.0f, 3.0f), testVecCopy1);
}

// Tests Utility Portion
TEST(IEVector3, Utility) 
{
	EXPECT_EQ(32.0f, testVec1.DotProduct(testVec2));
	EXPECT_EQ(IEVector3(-3.0f, 6.0f, -3.0f), testVec1.CrossProduct(testVec2));
	EXPECT_NEAR(3.741657f, testVec1.Length(), 0.00001f);
	EXPECT_EQ(14.0f, testVec1.LengthSqr());

	IEVector3 normalizedVec(testVec1.Normalize());
	EXPECT_NEAR(0.267261f, normalizedVec.getX(), 0.00001f); 
	EXPECT_NEAR(0.534522f, normalizedVec.getY(), 0.00001f);
	EXPECT_NEAR(0.801784f, normalizedVec.getZ(), 0.00001f);

	IEVector3 normalizedVec2(testVec1);
	normalizedVec2.NormalizeSelf();
	EXPECT_NEAR(0.267261f, normalizedVec2.getX(), 0.00001f); 
	EXPECT_NEAR(0.534522f, normalizedVec2.getY(), 0.00001f);
	EXPECT_NEAR(0.801784f, normalizedVec2.getZ(), 0.00001f);
}

// Test Constants
TEST(IEVector3, Constants) 
{
	// X axis
	EXPECT_EQ(1.0f, IEVector3::Xaxis.getX());
	EXPECT_EQ(0.0f, IEVector3::Xaxis.getY());
	EXPECT_EQ(0.0f, IEVector3::Xaxis.getZ());

	// X axis
	EXPECT_EQ(0.0f, IEVector3::Yaxis.getX());
	EXPECT_EQ(1.0f, IEVector3::Yaxis.getY());
	EXPECT_EQ(0.0f, IEVector3::Yaxis.getZ());

	// X axis
	EXPECT_EQ(0.0f, IEVector3::Zaxis.getX());
	EXPECT_EQ(0.0f, IEVector3::Zaxis.getY());
	EXPECT_EQ(1.0f, IEVector3::Zaxis.getZ());

	// Zero Vector
	EXPECT_EQ(0.0f, IEVector3::ZeroVector.getX());
	EXPECT_EQ(0.0f, IEVector3::ZeroVector.getY());
	EXPECT_EQ(0.0f, IEVector3::ZeroVector.getZ());
}