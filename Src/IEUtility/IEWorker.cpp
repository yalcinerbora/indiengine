#include "IEWorker.h"

IEWorker::IEWorker() : stopSignal(false)
{}

void IEWorker::THRDEntryPoint()
{
	// Thread Entry Point
	while(ProcessJob());
}

bool IEWorker::ProcessJob()
{
	std::unique_lock<IEMutex> lock(mutex);

	// Wait if Nothing to do
	//while(!stopSignal && assignedJobs.empty())
	conditionVar.wait(lock, [&] { return stopSignal || !assignedJobs.empty(); });

	// Exit if Stop is Signaled and There is no other 
	if(stopSignal && assignedJobs.empty())
		return false;

	assignedJobs.front()();
	assignedJobs.pop();
	return true;
}

void IEWorker::Start()
{
	workerThread = IEThread(&IEWorker::THRDEntryPoint, this);
}

void IEWorker::Stop()
{
	mutex.lock();
	stopSignal = true;
	mutex.unlock();
	conditionVar.notify_all();
	workerThread.join();
}

int IEWorker::QueuedJobs() const
{
	std::unique_lock<IEMutex> lock(mutex);
	return static_cast<int>(assignedJobs.size());
}