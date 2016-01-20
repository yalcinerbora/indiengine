#include "gtest/gtest.h"
#include "../IETest.h"
#include "IEUtility/IEMath.h"
#include "IEUtility/IEMatrix4x4.h"
#include "IEUtility/IEVector3.h"
#include "IEUtility/IEVector4.h"
#include "IEUtility/IEQuaternion.h"


static IEMatrix4x4 testMatrix(	1.0f, 5.0f, 9.0f, 13.0f,
								2.0f, 6.0f, 10.0f, 14.0f,
								3.0f, 7.0f, 11.0f, 15.0f,
								4.0f, 8.0f, 12.0f, 16.0f);
static IEMatrix4x4 testMatrix2;

static float vector4[] = {99.0f, 88.0f, 77.0f, 66.0f};

// Get Set Operations
TEST(IEMatrix4x4, AccessorsMutators)
{
	// Accessors Also Tests Constructors
	EXPECT_FLOAT_EQ(1.0f, testMatrix(1, 1));
	EXPECT_FLOAT_EQ(2.0f, testMatrix(1, 2));
	EXPECT_FLOAT_EQ(3.0f, testMatrix(1, 3));
	EXPECT_FLOAT_EQ(4.0f, testMatrix(1, 4));
	EXPECT_FLOAT_EQ(5.0f, testMatrix(2, 1));
	EXPECT_FLOAT_EQ(6.0f, testMatrix(2, 2));
	EXPECT_FLOAT_EQ(7.0f, testMatrix(2, 3));
	EXPECT_FLOAT_EQ(8.0f, testMatrix(2, 4));
	EXPECT_FLOAT_EQ(9.0f, testMatrix(3, 1));
	EXPECT_FLOAT_EQ(10.0f, testMatrix(3, 2));
	EXPECT_FLOAT_EQ(11.0f, testMatrix(3, 3));
	EXPECT_FLOAT_EQ(12.0f, testMatrix(3, 4));
	EXPECT_FLOAT_EQ(13.0f, testMatrix(4, 1));
	EXPECT_FLOAT_EQ(14.0f, testMatrix(4, 2));
	EXPECT_FLOAT_EQ(15.0f, testMatrix(4, 3));
	EXPECT_FLOAT_EQ(16.0f, testMatrix(4, 4));
	
	// Testing Default Constructor
	EXPECT_FLOAT_EQ(1.0f, testMatrix2(1, 1));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(1, 2));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(1, 3));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(1, 4));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(2, 1));
	EXPECT_FLOAT_EQ(1.0f, testMatrix2(2, 2));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(2, 3));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(2, 4));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(3, 1));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(3, 2));
	EXPECT_FLOAT_EQ(1.0f, testMatrix2(3, 3));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(3, 4));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(4, 1));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(4, 2));
	EXPECT_FLOAT_EQ(0.0f, testMatrix2(4, 3));
	EXPECT_FLOAT_EQ(1.0f, testMatrix2(4, 4));

	// Testing cp Constructor
	IEMatrix4x4 copyMatrix(testMatrix);
	EXPECT_FLOAT_EQ(1.0f, copyMatrix(1, 1));
	EXPECT_FLOAT_EQ(2.0f, copyMatrix(1, 2));
	EXPECT_FLOAT_EQ(3.0f, copyMatrix(1, 3));
	EXPECT_FLOAT_EQ(4.0f, copyMatrix(1, 4));
	EXPECT_FLOAT_EQ(5.0f, copyMatrix(2, 1));
	EXPECT_FLOAT_EQ(6.0f, copyMatrix(2, 2));
	EXPECT_FLOAT_EQ(7.0f, copyMatrix(2, 3));
	EXPECT_FLOAT_EQ(8.0f, copyMatrix(2, 4));
	EXPECT_FLOAT_EQ(9.0f, copyMatrix(3, 1));
	EXPECT_FLOAT_EQ(10.0f, copyMatrix(3, 2));
	EXPECT_FLOAT_EQ(11.0f, copyMatrix(3, 3));
	EXPECT_FLOAT_EQ(12.0f, copyMatrix(3, 4));
	EXPECT_FLOAT_EQ(13.0f, copyMatrix(4, 1));
	EXPECT_FLOAT_EQ(14.0f, copyMatrix(4, 2));
	EXPECT_FLOAT_EQ(15.0f, copyMatrix(4, 3));
	EXPECT_FLOAT_EQ(16.0f, copyMatrix(4, 4));

	// Testing Other Accessors
	const float* firstColumn = testMatrix.getColumn(1);
	EXPECT_FLOAT_EQ(1.0f, firstColumn[0]);
	EXPECT_FLOAT_EQ(5.0f, firstColumn[1]);
	EXPECT_FLOAT_EQ(9.0f, firstColumn[2]);
	EXPECT_FLOAT_EQ(13.0f, firstColumn[3]);

	const float* testData = testMatrix.getData();
	EXPECT_FLOAT_EQ(1.0f, testData[0]);
	EXPECT_FLOAT_EQ(5.0f, testData[1]);
	EXPECT_FLOAT_EQ(9.0f, testData[2]);
	EXPECT_FLOAT_EQ(13.0f, testData[3]);
	EXPECT_FLOAT_EQ(2.0f, testData[4]);
	EXPECT_FLOAT_EQ(6.0f, testData[5]);
	EXPECT_FLOAT_EQ(10.0f, testData[6]);
	EXPECT_FLOAT_EQ(14.0f, testData[7]);
	EXPECT_FLOAT_EQ(3.0f, testData[8]);
	EXPECT_FLOAT_EQ(7.0f, testData[9]);
	EXPECT_FLOAT_EQ(11.0f, testData[10]);
	EXPECT_FLOAT_EQ(15.0f, testData[11]);
	EXPECT_FLOAT_EQ(4.0f, testData[12]);
	EXPECT_FLOAT_EQ(8.0f, testData[13]);
	EXPECT_FLOAT_EQ(12.0f, testData[14]);
	EXPECT_FLOAT_EQ(16.0f, testData[15]);

	// Mutator Test
	copyMatrix.setElement(1, 1, 11111.0f);
	EXPECT_FLOAT_EQ(11111.0f, copyMatrix(1, 1));

	copyMatrix.setColumn(1, vector4);
	EXPECT_FLOAT_EQ(99.0f, copyMatrix(1, 1));
	EXPECT_FLOAT_EQ(88.0f, copyMatrix(2, 1));
	EXPECT_FLOAT_EQ(77.0f, copyMatrix(3, 1));
	EXPECT_FLOAT_EQ(66.0f, copyMatrix(4, 1));

	copyMatrix.setRow(2, vector4);
	EXPECT_FLOAT_EQ(99.0f, copyMatrix(2, 1));
	EXPECT_FLOAT_EQ(88.0f, copyMatrix(2, 2));
	EXPECT_FLOAT_EQ(77.0f, copyMatrix(2, 3));
	EXPECT_FLOAT_EQ(66.0f, copyMatrix(2, 4));
}

TEST(IEMatrix4x4, Operators)
{
	// Equality Operators
	EXPECT_TRUE(testMatrix == testMatrix);
	EXPECT_FALSE(testMatrix == testMatrix2);
	EXPECT_TRUE(testMatrix != testMatrix2);
	EXPECT_FALSE(testMatrix != testMatrix);
	
	// Std Operators
	EXPECT_EQ(IEMatrix4x4(	2.0f, 5.0f, 9.0f, 13.0f,
							2.0f, 7.0f, 10.0f, 14.0f,
							3.0f, 7.0f, 12.0f, 15.0f,
							4.0f, 8.0f, 12.0f, 17.0f), testMatrix + testMatrix2);

	EXPECT_EQ(IEMatrix4x4(	0.0f, 5.0f, 9.0f, 13.0f,
							2.0f, 5.0f, 10.0f, 14.0f,
							3.0f, 7.0f, 10.0f, 15.0f,
							4.0f, 8.0f, 12.0f, 15.0f), testMatrix - testMatrix2);

	EXPECT_EQ(IEMatrix4x4(	1.0f, 5.0f, 9.0f, 13.0f,
							2.0f, 6.0f, 10.0f, 14.0f,
							3.0f, 7.0f, 11.0f, 15.0f,
							4.0f, 8.0f, 12.0f, 16.0f), testMatrix / 1.0f);

	EXPECT_EQ(IEMatrix4x4(	1.0f, 5.0f, 9.0f, 13.0f,
							2.0f, 6.0f, 10.0f, 14.0f,
							3.0f, 7.0f, 11.0f, 15.0f,
							4.0f, 8.0f, 12.0f, 16.0f), testMatrix * 1.0f);

	EXPECT_EQ(IEMatrix4x4(	1.0f, 5.0f, 9.0f, 13.0f,
							2.0f, 6.0f, 10.0f, 14.0f,
							3.0f, 7.0f, 11.0f, 15.0f,
							4.0f, 8.0f, 12.0f, 16.0f), 1.0f * testMatrix);

	// Matrix Matrix Mult
	IEMatrix4x4 multMatrix(	1.0f, 5.0f, 9.0f, 13.0f,
							2.0f, 6.0f, 10.0f, 14.0f,
							3.0f, 7.0f, 11.0f, 15.0f,
							4.0f, 8.0f, 12.0f, 16.0f);
	EXPECT_EQ(IEMatrix4x4(	90.0f, 202.0f, 314.0f, 426.0f,
							100.0f, 228.0f, 356.0f, 484.0f,
							110.0f, 254.0f, 398.0f, 542.0f,
							120.0f, 280.0f, 440.0f, 600.0f), multMatrix * multMatrix);

	// Matrix Vector Mult
	EXPECT_EQ(IEVector4(18.0f, 46.0f, 74.0f, 102.0f), testMatrix * IEVector3(1.0f, 2.0f, 3.0f));
	EXPECT_EQ(IEVector4(30.0f, 70.0f, 110.0f, 150.0f), testMatrix * IEVector4(1.0f, 2.0f, 3.0f, 4.0f));

	// Operate and Assign Operators
	IEMatrix4x4 leftCopy(testMatrix);
	leftCopy *= testMatrix;
	EXPECT_EQ(IEMatrix4x4(	90.0f, 202.0f, 314.0f, 426.0f,
							100.0f, 228.0f, 356.0f, 484.0f,
							110.0f, 254.0f, 398.0f, 542.0f,
							120.0f, 280.0f, 440.0f, 600.0f), leftCopy);

	leftCopy = testMatrix;
	leftCopy *= leftCopy;	// Self Mult Testing data dependancy
	EXPECT_EQ(IEMatrix4x4(	90.0f, 202.0f, 314.0f, 426.0f,
							100.0f, 228.0f, 356.0f, 484.0f,
							110.0f, 254.0f, 398.0f, 542.0f,
							120.0f, 280.0f, 440.0f, 600.0f), leftCopy);
	
	leftCopy = testMatrix;
	leftCopy *= 2.0f;
	EXPECT_EQ(IEMatrix4x4(	2.0f, 10.0f, 18.0f, 26.0f,
							4.0f, 12.0f, 20.0f, 28.0f,
							6.0f, 14.0f, 22.0f, 30.0f,
							8.0f, 16.0f, 24.0f, 32.0f), leftCopy);
	
	leftCopy = testMatrix;
	leftCopy += leftCopy;
	EXPECT_EQ(IEMatrix4x4(	2.0f, 10.0f, 18.0f, 26.0f,
							4.0f, 12.0f, 20.0f, 28.0f,
							6.0f, 14.0f, 22.0f, 30.0f,
							8.0f, 16.0f, 24.0f, 32.0f), leftCopy);

	leftCopy = testMatrix;
	leftCopy -= leftCopy;
	EXPECT_EQ(IEMatrix4x4(	0.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 0.0f), leftCopy);

	leftCopy = testMatrix;
	leftCopy += leftCopy;
	leftCopy /= 2.0f;
	EXPECT_EQ(IEMatrix4x4(	1.0f, 5.0f, 9.0f, 13.0f,
							2.0f, 6.0f, 10.0f, 14.0f,
							3.0f, 7.0f, 11.0f, 15.0f,
							4.0f, 8.0f, 12.0f, 16.0f), leftCopy);
}

TEST(IEMatrix4x4, LinearAlgebra)
{
	// Transpose
	EXPECT_EQ(IEMatrix4x4(	1.0f, 2.0f, 3.0f, 4.0f,
							5.0f, 6.0f, 7.0f, 8.0f,
							9.0f, 10.0f, 11.0f, 12.0f,
							13.0f, 14.0f, 15.0f, 16.0f), testMatrix.Transpose());

	IEMatrix4x4 copyMatrix(testMatrix);
	EXPECT_EQ(IEMatrix4x4(	1.0f, 2.0f, 3.0f, 4.0f,
							5.0f, 6.0f, 7.0f, 8.0f,
							9.0f, 10.0f, 11.0f, 12.0f,
							13.0f, 14.0f, 15.0f, 16.0f), copyMatrix.TransposeSelf());

	// Determinant
	EXPECT_NEAR(0.0f, copyMatrix.Determinant(), 0.0001f);

	IEMatrix4x4 otherMatrix(1.0f, 5.0f, 9.0f, 133.0f,
							2.0f, 6.0f, 10.0f, 14.0f,
							31.0f, 7.0f, 11.0f, 15.0f,
							40.0f, 8.0f, 12.0f, 16.0f);

	EXPECT_NEAR(-9600.0f, otherMatrix.Determinant(), 0.0001f);

	// Inverse
	IEMatrix4x4 inverseMat = otherMatrix.Inverse();
	EXPECT_NEAR(0.00000f, inverseMat(1,1), 0.0001f);
	EXPECT_NEAR(-0.05000f, inverseMat(2,1), 0.0001f);
	EXPECT_NEAR(0.10000f, inverseMat(3,1), 0.0001f);
	EXPECT_NEAR(-0.05000f, inverseMat(4,1), 0.0001f);
	EXPECT_NEAR(0.00833f, inverseMat(1,2), 0.0001f);
	EXPECT_NEAR(0.84500f, inverseMat(2,2), 0.0001f);
	EXPECT_NEAR(-4.71500f, inverseMat(3,2), 0.0001f);
	EXPECT_NEAR(3.61167f, inverseMat(4,2), 0.0001f);
	EXPECT_NEAR(-0.01667f, inverseMat(1,3), 0.0001f);
	EXPECT_NEAR(-0.39000f, inverseMat(2,3), 0.0001f);
	EXPECT_NEAR(2.83000f, inverseMat(3,3), 0.0001f);
	EXPECT_NEAR(-2.17333f, inverseMat(4,3), 0.0001f);
	EXPECT_NEAR(0.00833f, inverseMat(1,4), 0.0001f);
	EXPECT_NEAR(-0.00500f, inverseMat(2,4), 0.0001f);
	EXPECT_NEAR(-0.01500f, inverseMat(3,4), 0.0001f);
	EXPECT_NEAR(0.01167f, inverseMat(4,4), 0.0001f);

	// Inverse of Non Invertible
	EXPECT_EQ(testMatrix2, testMatrix.Inverse());

	// Inverse Self
	IEMatrix4x4 otherMatCpy(otherMatrix);
	otherMatCpy.InverseSelf();
	EXPECT_NEAR(0.00000f, otherMatCpy(1,1), 0.0001f);
	EXPECT_NEAR(-0.05000f, otherMatCpy(2,1), 0.0001f);
	EXPECT_NEAR(0.10000f, otherMatCpy(3,1), 0.0001f);
	EXPECT_NEAR(-0.05000f, otherMatCpy(4,1), 0.0001f);
	EXPECT_NEAR(0.00833f, otherMatCpy(1,2), 0.0001f);
	EXPECT_NEAR(0.84500f, otherMatCpy(2,2), 0.0001f);
	EXPECT_NEAR(-4.71500f, otherMatCpy(3,2), 0.0001f);
	EXPECT_NEAR(3.61167f, otherMatCpy(4,2), 0.0001f);
	EXPECT_NEAR(-0.01667f, otherMatCpy(1,3), 0.0001f);
	EXPECT_NEAR(-0.39000f, otherMatCpy(2,3), 0.0001f);
	EXPECT_NEAR(2.83000f, otherMatCpy(3,3), 0.0001f);
	EXPECT_NEAR(-2.17333f, otherMatCpy(4,3), 0.0001f);
	EXPECT_NEAR(0.00833f, otherMatCpy(1,4), 0.0001f);
	EXPECT_NEAR(-0.00500f, otherMatCpy(2,4), 0.0001f);
	EXPECT_NEAR(-0.01500f, otherMatCpy(3,4), 0.0001f);
	EXPECT_NEAR(0.01167f, otherMatCpy(4,4), 0.0001f);
}

TEST(IEMatrix4x4, Transformations)
{
	IEVector4 vectorT(1.0f, 0.0f, 1.0f, 1.0f);
	IEVector4 vectorR(0.0f, 1.0f, 0.0f, 1.0f);
	IEVector4 vectorS(1.0f, 1.0f, 1.0f, 1.0f);

	// Translation
	IEMatrix4x4 translateMatrix = IEMatrix4x4::Translate(-vectorT);
	EXPECT_EQ(IEVector4(0.0f, 0.0f, 0.0f, 1.0f), translateMatrix * vectorT);

	// Rotation
	IEMatrix4x4 rotateMatrix = IEMatrix4x4::Rotate(IEMath::ToRadians(90.0f), IEVector3(1.0f, 0.0f, 0.0f));
	IEVector4 rotateResult =  rotateMatrix * vectorR;
	EXPECT_NEAR(0.0f, rotateResult.getX(), 0.0001f);
	EXPECT_NEAR(0.0f, rotateResult.getY(), 0.0001f);
	EXPECT_NEAR(1.0f, rotateResult.getZ(), 0.0001f);
	EXPECT_NEAR(1.0f, rotateResult.getW(), 0.0001f);

	rotateMatrix = IEMatrix4x4::Rotate(IEQuaternion(IEMath::ToRadians(90.0f), IEVector3(1.0f, 0.0f, 0.0f)));
	rotateResult =  rotateMatrix * vectorR;
	EXPECT_NEAR(0.0f, rotateResult.getX(), 0.0001f);
	EXPECT_NEAR(0.0f, rotateResult.getY(), 0.0001f);
	EXPECT_NEAR(1.0f, rotateResult.getZ(), 0.0001f);
	EXPECT_NEAR(1.0f, rotateResult.getW(), 0.0001f);

	// Scale
	IEMatrix4x4 scaleMatrix = IEMatrix4x4::Scale(2.0f);
	EXPECT_EQ(IEVector4(2.0f, 2.0f, 2.0f, 1.0f), scaleMatrix * vectorS);
	scaleMatrix = IEMatrix4x4::Scale(2.0f, 3.0f, 11.0f);
	EXPECT_EQ(IEVector4(2.0f, 3.0f, 11.0f, 1.0f), scaleMatrix * vectorS);

	// Projection Matrices / Look At Matrix
	// Will Be Tested seperately
}