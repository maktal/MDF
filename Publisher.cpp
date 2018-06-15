#include "Publisher.h"
#include "ExchangeHandler.h"

CPublisher::CPublisher()
{
}

CPublisher::CPublisher( STExchangeConnectionInfo& _ConnectionInfo, CDumper* _dumper)
{
	m_ConnectionInfo = _ConnectionInfo;
	m_Dumper = _dumper;
}

CPublisher::~CPublisher(void)
{
	Destroy();
}

bool CPublisher::Start()
{
	try
	{
		this->m_threadContinue = true;

		if( ACE_Thread::spawn((ACE_THR_FUNC)CPublisher::Start_,this, 
			THR_JOINABLE | THR_NEW_LWP,		 
			&m_processorThreadID,
			&m_processorThreadHandle ) == -1 )
		{
			// TODO: Log
			return false;
		}
	}
	catch(int a)
	{
		return  false;
	}

	return true;
}

void CPublisher::Start_( void* _param )
{
	((CPublisher*)_param)->Start_Callback();
}


// For Publishing Data

void CPublisher::Start_Callback()
{
	CParsedMessage _message;
	std::string	   _strMessage;
	std::vector<std::set<CClientSocket*>::iterator> _deadSockets;
	

	while(m_threadContinue)
	{
		try
		{
			if( m_Queue.pop(_message) )
			{
				_strMessage.clear();
				
				char m_buf[10];

				itoa( m_Dumper->GetRowCount() + 1, m_buf, 10);
				
				_message._SeqNo = m_buf;

				_strMessage = GetFormatedMessage(_message); // XML or BINARY

				if (!_strMessage.empty())
				{

					//--- Benchmark ----------------------------------
					char _time[100];
					SYSTEMTIME sysDateTime;
					GetLocalTime( &sysDateTime );
					sprintf(_time, ";RecieveTime=%d:%d:%d:%d", sysDateTime.wHour, sysDateTime.wMinute, sysDateTime.wSecond, sysDateTime.wMilliseconds );
			
				//	_strMessage += _time;
					//------------------------------------------------

					m_Dumper->SavePublishedMessage(_strMessage);

					std::set<CClientSocket*>::iterator _itr;
					for( _itr = m_SocketList.begin(); _itr != m_SocketList.end(); _itr++)
					{
						if( Publish_Actual((CClientSocket*)(*_itr), _strMessage) == false)
							_deadSockets.push_back(_itr);
					}
					
					RemoveDeadSockets(_deadSockets);
				}			

				m_Mutex.unlock();
			}
			else
				m_Queue.wait(3000);
		}
		catch(int a)
		{	
		}
	}
}

 int CPublisher::handle_input(ACE_HANDLE handle)
{
	static int i = 0;
	ACE_SOCK_Stream* ssock_;
	ACE_INET_Addr _clientAddr;

	try
	{
		ACE_NEW_RETURN (ssock_, ACE_SOCK_Stream, -1);
		
		if (this->m_Acceptor.accept (*ssock_) == -1)
			return -1;
		else
		{
			//ssock_->get_remote_addr(_clientAddr);
			//std::string _hostname = _clientAddr.get_host_addr();
			//_clientAddr.get_port_number();
			
			CClientSocket* _clientSocket = new CClientSocket(ssock_, m_Dumper);

			//m_Mutex.lock();
			if (!_clientSocket->m_inValidCommand)
					m_SocketList.insert(_clientSocket);
			else
				delete _clientSocket;
			//m_Mutex.unlock();
		}
	}
	catch(int a)
	{
		return  -10;
	}
	return 0;

}


int CPublisher::open(const ACE_INET_Addr &listen_addr)
{
  return this->m_Acceptor.open( listen_addr, 1 );
}

ACE_HANDLE CPublisher::get_handle(void) const 
{ 
	return this->m_Acceptor.get_handle(); 
}

bool CPublisher::PublishMessage( CParsedMessage& _parsedMessage )
{
	m_Queue.push(_parsedMessage);
	return true;
}

bool CPublisher::Publish_Actual( CClientSocket* _socket, std::string& _strMessage )
{
	if(false ==_socket->IsAlive())
		return false;

	_socket->PublishMessage(_strMessage);
	
	return true;
}

bool CPublisher::Create( void )
{
	bool _ret = true;

	char szBuffer[12];

	ACE_INET_Addr oSubPort( ACE_OS::itoa(m_ConnectionInfo.PublishPort, szBuffer, 10 ) );
	this->reactor( ACE_Reactor::instance() );

	this->open(oSubPort);
	_ret = !(bool)ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::ACCEPT_MASK ); 
	
	_ret &= Start();
	return _ret;
}

bool CPublisher::Destroy( void )
{
	m_threadContinue = false;

	return (bool) ACE_Reactor::instance()->remove_handler(this, ACE_Event_Handler::ACCEPT_MASK ); 
}

void CPublisher::RemoveDeadSockets( std::vector<std::set<CClientSocket*>::iterator>& _deadSockets )
{
		for(unsigned int i=0; i < _deadSockets.size(); i++)
		{
			delete *(_deadSockets[i]);
			m_SocketList.erase(_deadSockets[i]);
		}

		_deadSockets.clear();
}

long CPublisher::GetNumberOfSubscribers( void )
{
	//m_Mutex.lock();
	long _ret = m_SocketList.size();
	//m_Mutex.unlock();
		
	return _ret;
}

std::set<CClientSocket*> CPublisher::GetListOfSubscribers(void)
{
	return m_SocketList;
}

std::string CPublisher::GetFormatedMessage(CParsedMessage& _message)
{
	std::string _buffer;

	//-------- What Format to Send: Binary or XML --------
	switch(m_ConnectionInfo.PublishFormat)
	{
	case BINARY:
		_buffer = _message.GetBinary();
		break;

	case XML:
		_buffer = _message.GetXML();
		break;
	}
	//----------------------------------------------------


	switch(_message._messageType)
	{
	case MBO:
		if(m_ConnectionInfo.MBOEnabled == true)  return _buffer;
		break;

	case MBP:
		if(m_ConnectionInfo.MBPEnabled == true)  return _buffer;
		break;

	case FEED:
		return _buffer;
		break;

	default:
		return std::string();
	}

	return std::string();

}