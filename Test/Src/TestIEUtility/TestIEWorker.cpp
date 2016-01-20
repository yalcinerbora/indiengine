#include "gtest/gtest.h"
#include "../IETest.h"
#include "IEUtility/IEWorker.h"

class TestClass
{
	public:
		int a;

		TestClass(int kek) { a = kek; }

		void VoidMember(int i) { a = i; }
		void VoidConstMember(bool b) const { EXPECT_TRUE(b); }
		int IntMember(int i) { a += i;  return a; }
		int IntConstMember(int i) const { return i; }
};

int functionAdd(int a, int b)
{
	return a + b;
}

void funcVoid(bool b)
{
	EXPECT_TRUE(b);
}

TEST(IEWorker, BasicTest)
{
	// Init
	IEWorker worker;
	worker.Start();

	// Test Standard Function
	auto result = worker.AddJob(&functionAdd, 22, 14);
	EXPECT_EQ(36, result.get());
	worker.AddJob(funcVoid, true);

	// Test Lambda
	auto voidLambda = [](bool b) { EXPECT_TRUE(b); };
	auto returnLambda = [](int answer) { return answer; };

	result = worker.AddJob(returnLambda, 22);
	EXPECT_EQ(22, result.get());
	worker.AddJob(voidLambda, true);

	// Test Member Function
	TestClass myClass(123);
	auto result2 = worker.AddJob(&TestClass::IntMember, &myClass, 22);
	EXPECT_EQ(145, result2.get());
	EXPECT_EQ(145, myClass.a);
	
	auto result3 = worker.AddJob(&TestClass::IntConstMember, &myClass, 22);
	EXPECT_EQ(22, result3.get());

	auto result4 = worker.AddJob(&TestClass::VoidMember, &myClass, 999);
	result4.wait();
	EXPECT_EQ(999, myClass.a);

	worker.AddJob(&TestClass::VoidConstMember, &myClass, true);
	
	worker.Stop();
}

TEST(IEWorker, StressTest)
{
	static const int LOOP_VALUE = 10000;

	std::function<int(int)> sumRec = [](int value)
	{
		int sum = value;
		for(int i = 0; i < LOOP_VALUE; i++)
		{
			sum += value;
		}
		return sum;
	};

	// Init
	IEWorker worker;
	worker.Start();

	for(int i = 0; i < 100000; i++)
	{
		worker.AddJob(sumRec, 900);
	}
	worker.Stop();
}