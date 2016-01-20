/**
Event System Implementation

Author(s):
Bora Yalciner
*/

#ifndef __IE_EVENTSYSTEM_H__
#define __IE_EVENTSYSTEM_H__

#include "IEClassList.h"

template<class T> class IEListener;

template <class Event>
class IEDispatcher
{
	private:
		IEClassList<IEListener<Event>*>	registeredListeners;

	protected:

	public:
		// Constructors & Destructor
										IEDispatcher() = default;
										~IEDispatcher() = default;
		
		void							DispatchEvent(const Event* e);

		// Listener Management
		void							AddListener(IEListener<Event>*);
		void							RemoveListener(IEListener<Event>*);
};

template <class Event>
class IEListener
{
	private:
		friend class					IEDispatcher<Event>;
		void							DispathcerCallOnEvent(const Event* e);

	protected:
		mutable IEMutex					mutex;

	public:
		// Constructor & Destructor
										IEListener() = default;
										~IEListener() = default;

		// Mutex And Function
		virtual void					OnEvent(const Event* e) = 0;
};

template <class Event>
void IEDispatcher<Event>::DispatchEvent(const Event* e)
{
	registeredListeners.CallFunctionAll(&IEListener<Event>::DispathcerCallOnEvent, e);
}

template <class Event>
void IEDispatcher<Event>::AddListener(IEListener<Event>* l)
{
	registeredListeners.Append(l);
}

template <class Event>
void IEDispatcher<Event>::RemoveListener(IEListener<Event>* l)
{
	registeredListeners.DeleteFirst(l);
}

template <class Event>
void IEListener<Event>::DispathcerCallOnEvent(const Event* e)
{
	std::lock_guard<IEMutex> lock(mutex);
	OnEvent(e);
}
#endif //__IE_EVENTSYSTEM_H__