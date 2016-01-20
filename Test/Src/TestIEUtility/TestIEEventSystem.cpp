#include "gtest/gtest.h"
#include "../IETest.h"
#include "IEUtility/IEEventSystem.h"

struct TestEvent
{
	int int1;
	int int2;
};

class TestListener : public IEListener<TestEvent>
{
	private:
		int storedInt1;
		int storedInt2;

	public:
		virtual void OnEvent(const TestEvent* e)
		{
			storedInt1 = e->int1;
			storedInt2 = e->int2;
		}

		virtual void GetInts(int& i, int& j) const
		{
			// This Is Mandatory if listener and dispatcher on different threads
			// On event function has this wrapper outside of the function
			// Since Class Cannot know how and where the data of the Listener
			// will use the event it its implementors responsibility to add this line
			// where appropirate
			std::lock_guard<IEMutex>	lock(mutex);

			i = storedInt1;
			j = storedInt2;
		}
};

class TestDispatcher : public IEDispatcher<TestEvent>
{
	public:
		void CreateAndSendEvent(int a, int b)
		{
			TestEvent e;
			e.int1 = a;
			e.int2 = b;
			DispatchEvent(&e);
		}
};

TEST(IEEventSystem, All)
{
	// Single Threaded Test
	TestListener list1;
	TestListener list2;
	TestDispatcher dispatcher;

	dispatcher.AddListener(&list1);
	dispatcher.AddListener(&list2);

	// Setup Done
	// Now Testing
	dispatcher.CreateAndSendEvent(10, 15);

	// Check The Events
	int a, b;
	list1.GetInts(a, b);
	EXPECT_EQ(10, a);
	EXPECT_EQ(15, b);

	list2.GetInts(a, b);
	EXPECT_EQ(10, a);
	EXPECT_EQ(15, b);

	dispatcher.RemoveListener(&list1);
	dispatcher.CreateAndSendEvent(30, 455);

	// Check The Events
	list1.GetInts(a, b);
	EXPECT_EQ(10, a);
	EXPECT_EQ(15, b);

	list2.GetInts(a, b);
	EXPECT_EQ(30, a);
	EXPECT_EQ(455, b);
}