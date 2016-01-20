#include "gtest/gtest.h"
#include "../IETest.h"
#include "IEUtility/IEJobExecutor.h"

#include <random>
#include <chrono>
#include <vector>
#include "IEUtility/IEMacros.h"

TEST(IEJobExecutor, DistributionQuality)
{
	std::random_device rd;
	std::default_random_engine Engine(rd());
	std::uniform_int_distribution<uint32_t> distribution(5000, 150000);

	// Create tasks with varying lengths
	auto taskSum = [](int taskLength)
	{
		int result = 0;
		for(int i = 0; i < taskLength; i++)
		{
			if(i % 2)
				result += i;
			else
				result -= i;
		}
	};

	//
	IEJobExecutor<> jobManager;
	jobManager.Start();
	double timings[10];
	std::vector<std::future<void>> results;

	// Time Each Iteration
	for(int a = 0; a < 10; a++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < 500; i++)
		{
			int taskLength = distribution(Engine);
			results.push_back(jobManager.AssignJob(taskSum, taskLength));
		}
		// Wait All Results
		for(auto iterator = results.begin(); iterator != results.end(); ++iterator) 
			iterator->wait();

		auto end = std::chrono::high_resolution_clock::now();
		auto diff = end - start;
		timings[a] = std::chrono::duration <double, std::milli>(diff).count();
		results.clear();
	}

	double avg = 0.0;
	for(int i = 0; i < 10; i++)
		avg += timings[i];
	avg /= 10.0;
	for(int i = 0; i < 10; i++)
		EXPECT_NEAR(timings[i], avg, 100.0);
	jobManager.Stop();
}