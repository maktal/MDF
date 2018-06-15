// ExchangeDataHandler.cpp: implementation of the CExchangeConnectionHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "ExchangeConnectionHandler.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CExchangeConnectionHandler::CExchangeConnectionHandler(STExchangeConnectionInfo _ExConInfo)
{
	this->m_ExchnageConnectionInfo = _ExConInfo;
	m_Connected = 0;
}


CExchangeConnectionHandler::~CExchangeConnectionHandler()
{
	Destroy();
}


int CExchangeConnectionHandler::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
	m_Connected = 0;
	
	this->peer().close();
	
	m_Event.signal();
	
	return 0;
}



int CExchangeConnectionHandler::handle_input(ACE_HANDLE handle)
{
	try
	{
		long _bufferSize = m_ExchnageConnectionInfo.BufferSize;

		//--- If Buffer Size is Encoded, Decode It ----------
		if(_bufferSize < 0)
			_bufferSize = GetDynamicBufferSize(_bufferSize);
		//---------------------------------------------------

		szMsg = new char[_bufferSize+1];

		memset(szMsg, 0, _bufferSize+1);
		int nBytesRead = this->peer().recv(szMsg, _bufferSize);
		

		if ( nBytesRead == 0  )
		{
			ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
			ACE_DEBUG( ( LM_DEBUG, "(%t) Data Received is not complete...\n\n" ) );
		}

		if ( nBytesRead > 0 )
		{
			std::string _item = szMsg;
			delete szMsg;
			this->m_Queue.push(_item);
		}
		else
		{
			delete szMsg;
			ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
			ACE_DEBUG( ( LM_DEBUG, "(%t) Incomming Connection From FeedServer is disconnected...\n\n" ) );
			m_Connected = 0;
			return -1;
		}
	}
	catch(int a){}

	return 0;
}


bool CExchangeConnectionHandler::Start()
{
	if( ACE_Thread::spawn((ACE_THR_FUNC)CExchangeConnectionHandler::Start_, 
		this, 
		THR_JOINABLE | THR_NEW_LWP,		 
		&m_processorThreadID,
		&m_processorThreadHandle ) == -1 )
	{
		// TODO: Log
		return false;
	}

	return true;
} 

//////////////////////////////////////////////////////////////////////////


void CExchangeConnectionHandler::Start_Callback()
{
	while ( m_bthreadContinue )
	{	
		CExchangeConnectionHandler* _svcHandler = this;

		ACE_INET_Addr _endPoint(m_ExchnageConnectionInfo.Port, m_ExchnageConnectionInfo.IP.c_str());
		
		try
		{
			if ( (0 == m_Connected || 2 == m_Connected) && (this->m_Connector.connect(_svcHandler, _endPoint) == -1)) 
			{
				m_Connected = 0;
				Sleep(5000);
				m_Connected = 2;
				Sleep(5000);
				continue;
			}	
			else
			{
				m_Connected = 1;
				char _date[50];
				time_t rawtime;
				struct tm * timeinfo;    
				time ( &rawtime );
				timeinfo = localtime ( &rawtime );	
				strftime(_date,25,"%d %b %Y %H:%M:%S", timeinfo);
				Last_Connection_Time = _date;		
				m_Event.wait(INFINITE);
			}
		}
		catch(int exp)
		{

		}
		
	}
}

//////////////////////////////////////////////////////////////////////////

void CExchangeConnectionHandler::Start_(void * pParam )
{
	((CExchangeConnectionHandler*)pParam)->Start_Callback();
}


std::string CExchangeConnectionHandler::GetMessage( std::string& _delimeter )
{

	std::string _item, _ret;
	int _position;

	

	while( true) 
	{
		_item.erase();
		if(false == m_Queue.pop(_item))
		{
			m_Queue.wait();
			continue;
		}


		//--- Consider every item in the Queue as a complete message if BufferSize is Dynamic ( i.e < 0 )
		if(m_ExchnageConnectionInfo.BufferSize < 0)
		{
			m_Queue.pop(_item);
			return _item;
		}
		//-----------------------------------------------------------------------------------------------

		m_temp += _item;
		_position = m_temp.find(_delimeter);
		if(_position > 0)
		{
			_ret = m_temp.substr(0, _position);
			m_temp = m_temp.substr(_position+1,m_temp.length()+1);

			return _ret;
		}
	}

}

bool CExchangeConnectionHandler::Create( void )
{
	bool _ret = false;
	m_bthreadContinue = true;

	_ret = (bool)Start();

	//szMsg = new char[m_ExchnageConnectionInfo.BufferSize];

	return _ret;
}

bool CExchangeConnectionHandler::Destroy( void )
{
	bool _ret;
	
	m_bthreadContinue = false;

	if(szMsg) delete[] szMsg;

	return true;
}

long CExchangeConnectionHandler::GetDynamicBufferSize(long _bufferSize)
{
	u_long _actuaSize = 0;
	char _termpBuffer[20] = "\0";

	switch(_bufferSize)
	{
		case -2:
			if(peer().recv(_termpBuffer,2) > 0)
			{
				memcpy(&_actuaSize, _termpBuffer, 2);
				_actuaSize = ntohs(_actuaSize);
			}

			break;

		case -4:
			if( peer().recv(_termpBuffer,4) > 0)
			{
				memcpy(&_actuaSize, _termpBuffer, 4);
				_actuaSize = ntohl(_actuaSize);
			}
			break;		
	}

	return _actuaSize;
}