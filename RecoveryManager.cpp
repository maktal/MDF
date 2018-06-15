#include "RecoveryManager.h"

CRecoveryManager::CRecoveryManager()
{
}

CRecoveryManager::~CRecoveryManager(void)
{
}

CRecoveryManager::CRecoveryManager(STExchangeConnectionInfo _ConnectionInfo )
{
	m_ConnectionInfo = _ConnectionInfo;
	char szBuffer[12];
	ACE_INET_Addr oSubPort( ACE_OS::itoa(_ConnectionInfo.RecoveryPort, szBuffer, 10 ) );
	this->reactor( ACE_Reactor::instance() );
}

int CRecoveryManager::handle_input(ACE_HANDLE handle)
{
	static int i = 0;
	ACE_SOCK_Stream* ssock_;
	try
	{
		ACE_NEW_RETURN (ssock_, ACE_SOCK_Stream, -1);
		if (this->m_Acceptor.accept (*ssock_) == -1)
		{
			return -1;
		}
		m_ACE_SockVector.push_back(ssock_);
	}
	catch(int a)
	{
		return  -10;
	}
	return 0;

}


int CRecoveryManager::open(const ACE_INET_Addr &listen_addr)
{
	return this->m_Acceptor.open( listen_addr, 1 );
}

ACE_HANDLE CRecoveryManager::get_handle(void) const 
{ 
	return this->m_Acceptor.get_handle(); 
}

bool CRecoveryManager::Create( void )
{
	bool _ret;
	char szBuffer[12];

	ACE_INET_Addr oSubPort( ACE_OS::itoa(m_ConnectionInfo.PublishPort, szBuffer, 10 ) );
	this->reactor( ACE_Reactor::instance() );
	this->open(oSubPort);

	_ret =  (bool) this->open(oSubPort);
	_ret &= (bool)ACE_Reactor::instance()->register_handler( this, ACE_Event_Handler::ACCEPT_MASK ); 

	return _ret;
}

bool CRecoveryManager::Destroy( void )
{
	return (bool)ACE_Reactor::instance()->remove_handler(this, ACE_Event_Handler::ACCEPT_MASK ); 
}