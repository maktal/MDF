#include "ExchangeConnectionHandlerServer.h"

CExchangeConnectionHandlerServer::CExchangeConnectionHandlerServer(void)
{
}

CExchangeConnectionHandlerServer::CExchangeConnectionHandlerServer( STExchangeConnectionInfo& _ExchangeInfo )
{	
	this->m_ExchnageConnectionInfo = _ExchangeInfo;
	this->m_MDFListenerPort = _ExchangeInfo.Port;
	this->m_BufferSize =_ExchangeInfo.BufferSize;
	m_Connected = 0;
}

CExchangeConnectionHandlerServer::~CExchangeConnectionHandlerServer(void)
{
	delete szMsg;
	Destroy();
}

int CExchangeConnectionHandlerServer::open(const ACE_INET_Addr &listen_addr)
{
	return this->m_Acceptor.open( listen_addr, 1 );
}

int CExchangeConnectionHandlerServer::handle_input(ACE_HANDLE handle)
{
	static int i = 0;
	
	try
	{
		ACE_NEW_RETURN (ssock_, ACE_SOCK_Stream, -1);
		if (this->m_Acceptor.accept (*ssock_) == -1)
		{
			return -1;
			m_Connected = 0;	
		}

		char _date[50];
		time_t rawtime;
		struct tm * timeinfo;    
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );			
		strftime(_date,25,"%d %b %Y %H:%M:%S", timeinfo);
		Last_Connection_Time = _date;

		

		Start(this); //Thread

		//	m_ACE_SockVector.push_back(ssock_);
	}
	catch(int a)
	{
		return  -10;
		m_Connected = 0;
	}
	return 0;

}



ACE_HANDLE CExchangeConnectionHandlerServer::get_handle(void) const 
{ 

	return this->m_Acceptor.get_handle(); 
}


int CExchangeConnectionHandlerServer::Start(CExchangeConnectionHandlerServer* ssock)
{

	if( ACE_Thread::spawn((ACE_THR_FUNC)CExchangeConnectionHandlerServer::Start_,ssock, 
		THR_JOINABLE | THR_NEW_LWP,		 
		&m_processorThreadID,
		&m_processorThreadHandle ) == -1 )
	{
		return -1;
	}

	return 1;
}


void CExchangeConnectionHandlerServer::Start_(CExchangeConnectionHandlerServer* _sock )
{
((CExchangeConnectionHandlerServer*)_sock)->StartCallBack(_sock);
}


void CExchangeConnectionHandlerServer::StartCallBack(CExchangeConnectionHandlerServer* mThis )
{		
		while(1)
		{
			try
			{
				//--- If Buffer Size is Encoded, Decode It ----------
				long _bufferSize = m_ExchnageConnectionInfo.BufferSize;
				if(_bufferSize < 0)
					_bufferSize = GetDynamicBufferSize(_bufferSize,mThis);
				//---------------------------------------------------

				szMsg = new char[_bufferSize];
				
				memset(szMsg,'\0',_bufferSize);
				int nBytesRead = mThis->ssock_->recv(szMsg, _bufferSize);
				

				if ( nBytesRead == 0  )
				{
					ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
					ACE_DEBUG( ( LM_DEBUG, "(%t) Data Received is not complete...\n\n" ) );
				}

				if ( nBytesRead > 0 )
				{
					std::string _item = szMsg;
					m_Connected = 1;								
					this->m_Queue.push(_item);						
				}
				else
				{
					ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
					ACE_DEBUG( ( LM_DEBUG, "(%t) Incomming Connection From FeedServer is disconnected...\n\n" ) );
					m_Connected = 0;
					return;
				}
				
				delete[] szMsg;			
				Sleep(500);
			}
			catch(int a)
			{

			}
		}
		return;
}
long CExchangeConnectionHandlerServer::GetDynamicBufferSize(long _bufferSize, CExchangeConnectionHandlerServer* _sock)
{
	u_long _actuaSize = 0;
	char _termpBuffer[4];
	int m_bytesRead;
	switch(_bufferSize)
	{
		case -2:
			if( _sock->ssock_->recv(_termpBuffer,2) > 0)
			{
				memcpy(&_actuaSize, _termpBuffer, 2);
				_actuaSize = ntohs(_actuaSize);
			}
			break;

		case -4:
			if( _sock->ssock_->recv(_termpBuffer,4) > 0)
			{
				memcpy(&_actuaSize, _termpBuffer, 4);
				_actuaSize = ntohl(_actuaSize);
			}
			break;		
	}

	//--- Buffer Size can never be greater than 32768 ---
	if(_actuaSize < 32768)
		return _actuaSize;
	else
		return(32768);
	//---------------------------------------------------

}
std::string CExchangeConnectionHandlerServer::GetMessage( std::string& _delimeter )
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

bool CExchangeConnectionHandlerServer::Create( void )
{
	bool _ret;

	//--- Open Listener ---
	char szBuffer[12];	
	ACE_INET_Addr oSubPort( ACE_OS::itoa(m_MDFListenerPort, szBuffer, 10 ) );
	this->reactor(ACE_Reactor::instance() );
	_ret = (bool) this->open(oSubPort);
	_ret &= (bool) ACE_Reactor::instance()->register_handler( this, ACE_Event_Handler::ACCEPT_MASK ); 

	return !_ret;
}

bool CExchangeConnectionHandlerServer::Destroy( void )
{
	bool _ret;
	_ret = (bool) ACE_Reactor::instance()->remove_handler( this, ACE_Event_Handler::ACCEPT_MASK ); 
	return _ret;
}

int CExchangeConnectionHandlerServer::handle_close( ACE_HANDLE, ACE_Reactor_Mask )
{
	return 1;
	m_Connected = 0;	
}
