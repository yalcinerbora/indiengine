#include <algorithm>
#include <climits>

template <size_t W>
IEJobExecutor<W>::IEJobExecutor()
{}

template <size_t W>
IEJobExecutor<W>::~IEJobExecutor()
{}

template <size_t W>
int IEJobExecutor<W>::ChooseWorker()
{
	// Return the Worker that has lowest amount of jobs
	// TODO: make this more sophisticated (check actual amount of work)
	int value = INT_MAX;
	int index = -1;
	for(int i = 0; i < W; i++)
	{
		int valueNominee = workers[i].QueuedJobs();
		if(valueNominee < value)
		{
			index = i;
			value = valueNominee;
		}
	}
	return index;
}

// Thread Lifetime JobExecuter	
template <size_t W>
void IEJobExecutor<W>::Start()
{
	for(IEWorker &w : workers)
	{
		w.Start();
	}
}

template <size_t W>
void IEJobExecutor<W>::Stop()
{
	for(IEWorker &w : workers)
	{
		w.Stop();
	}
}

template <size_t W>
template <class Function, class... Args>
std::future<typename std::result_of<Function(Args...)>::type>
IEJobExecutor<W>::AssignJob(Function&& f, Args&&... args)
{
	return workers[ChooseWorker()].AddJob(f, args...);
}