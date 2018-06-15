#pragma once

class Event
{
public:
  Event()
  {
	  //m_event = CreateEvent( 0, false, false, 0 );
  }

  ~Event()
  {
	  //CloseHandle( m_event );
  }

  void signal()
  {
	  //SetEvent( m_event );
  }

  void wait( int nMiliSec = 10000000 )
  {
	  //WaitForSingleObject( m_event, nMiliSec );
  }

	//private: HANDLE m_event;
};



