#include "ClientSocket.h"

CClientSocket::CClientSocket(ACE_SOCK_Stream* _socket,CDumper* _dumper)
{
	m_ClientSocket = _socket;	
	m_Dumper = _dumper;
	m_IsDead = false;
	m_bThreadContinue = true;
	ACE_INET_Addr _add;// = (ACE_INET_Addr) _socket->PEER_ADDR;
	int a			 =  _socket->get_remote_addr(_add);
	m_IP = _add.get_host_addr();
	m_Port = _add.get_port_number();
	char _buffer[CLIENT_SEQ_NO_LEN] = "\0";
	long _bytes = _socket->recv(_buffer, 1);

	if( _bytes > 0)
	{
		//--- Recovery Initiation Request
		if(0 == strcmp(_buffer,"R"))
		{			
			 _bytes = _socket->recv(_buffer, CLIENT_SEQ_NO_LEN);
			long _seqNo = atoi(_buffer);
			StartRecovery(_seqNo);
			Start();
			m_inValidCommand = false;
		}
		else if(0 == strcmp(_buffer,"N"))
		{
			m_inValidCommand = false;
			Start();
		}
		else 
			m_inValidCommand = true;
	}
	else
		m_inValidCommand = true;
}

CClientSocket::~CClientSocket(void)
{
	delete m_ClientSocket;
}

bool CClientSocket::Start( void )
{
	if( ACE_Thread::spawn((ACE_THR_FUNC)CClientSocket::Start_,this, 
		THR_JOINABLE | THR_NEW_LWP,		 
		&m_processorThreadID,
		&m_processorThreadHandle ) == -1 )
	{
		// TODO: Log
		m_bThreadContinue = false;
		return false;
	}

	m_bThreadContinue = true;
	return true;
}

void CClientSocket::Start_( void* _param )
{
	((CClientSocket*)_param)->Start_Callback();
}

void CClientSocket::Start_Callback()
{
	std::string _message;
	int bytes;

	while(m_bThreadContinue)
	{
		if( false == m_Queue.pop(_message) )
			m_Queue.wait();

		bytes = m_ClientSocket->send(_message.c_str(), _message.size());

		if(bytes < 0)
		{
			m_Mutex.lock();
			m_IsDead = true;
			m_Mutex.unlock();
			m_bThreadContinue = false;
		}

	}
}

void CClientSocket::PublishMessage(std::string& _message)
{
	m_Queue.push(_message);

	//--- Start data relaying thread if its not started already ---
	if(false == m_bThreadContinue)
	{
		Start();
	}
	//-------------------------------------------------------------
}

void CClientSocket::StartRecovery(long _seqNo)
{
	ACE_Vector<std::string,10> _messagList = m_Dumper->GetMessage(_seqNo);

	for(int i = 0; i < _messagList.size(); ++i)
	{
		m_Queue.push(_messagList[i]);
	}
}

bool CClientSocket::IsAlive( void )
{
	bool _ret;

	m_Mutex.lock();
	_ret = !m_IsDead;
	m_Mutex.unlock();

	return _ret;
}