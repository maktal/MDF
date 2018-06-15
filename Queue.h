#pragma once

class Event;
class Mutex;

#include "ace/unbounded_queue.h"


class Mutex
{
public:
	Mutex()
	{
#ifdef _MSC_VER
		InitializeCriticalSection( &m_mutex );
#endif
	}

	~Mutex()
	{
#ifdef _MSC_VER
		DeleteCriticalSection( &m_mutex );
#endif
	}

	void lock()
	{
#ifdef _MSC_VER
		EnterCriticalSection( &m_mutex );
#endif
	}

	void unlock()
	{
#ifdef _MSC_VER
		LeaveCriticalSection( &m_mutex );
#endif
	}

private:

#ifdef _MSC_VER
	CRITICAL_SECTION m_mutex;
#endif
};

class Locker
{
public:
	Locker( Mutex& mutex ) : m_mutex( mutex )
	{
		m_mutex.lock();
	}

	~Locker()
	{ 
		m_mutex.unlock(); 
	}
private:
	Mutex& m_mutex;
};


class Event
{
public:
	Event()
	{
#ifdef _MSC_VER
		m_event = CreateEvent( 0, false, false, 0 );
#endif
	}

	~Event()
	{
#ifdef _MSC_VER
		CloseHandle( m_event );
#endif
	}

	void signal()
	{
#ifdef _MSC_VER
		SetEvent( m_event );
#endif
	}

	void wait()
	{
#ifdef _MSC_VER
		WaitForSingleObject(m_event, INFINITE );
#endif
	}

	void wait(unsigned long ulWaitTime)
	{
#ifdef _MSC_VER
		WaitForSingleObject( m_event, ulWaitTime );
#endif
	}

private:
#ifdef _MSC_VER
	HANDLE m_event;
#endif
};







template < typename T > class CQueue
{
public:
	void push( const T& value )
	{
		Locker locker( m_mutex );
		m_queue.enqueue_tail( value );
		if( m_queue.size() == 1 )
			signal();
	}

	void push_front(const T& value)
	{
		Locker locker( m_mutex );
		m_queue.enqueue_head( value );

		if (m_queue.size() == 1)
			signal();
	}

	bool pop( T& value )
	{
		Locker locker( m_mutex );
		if ( !m_queue.size() ) return false;
		m_queue.dequeue_head( value );
		return true;
	}

	int size()
	{
		Locker locker( m_mutex );
		return m_queue.size();
	}

	void wait()
	{
		m_event.wait();
	}

	void wait(unsigned long ulWaitTime)
	{
		m_event.wait(ulWaitTime);
	}

	void signal()
	{
		m_event.signal();
	}

private:
	Event m_event;
	Mutex m_mutex;
	ACE_Unbounded_Queue<T> m_queue;
};