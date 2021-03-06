#include "ExchangeConnectionHandlerUDPClient.h"

CExchangeConnectionHandlerUDPClient::CExchangeConnectionHandlerUDPClient(STExchangeConnectionInfo _ExConInfo)
{
	this->m_ExchnageConnectionInfo = _ExConInfo;
	this->m_BufferSize = _ExConInfo.BufferSize;
	this->m_Connected = 0;
}
int CExchangeConnectionHandlerUDPClient::open ()
{
	ACE_INET_Addr _endPoint(m_ExchnageConnectionInfo.Port, m_ExchnageConnectionInfo.IP.c_str());
	
	//	m_Inet_Addr(m_ExchnageConnectionInfo.Port, m_ExchnageConnectionInfo.IP.c_str());

	m_Inet_Addr = _endPoint;

	if(this->m_sockDgram.open(m_Inet_Addr)==-1	)
	{
		ACE_ERROR_RETURN ((LM_ERROR,"%p\n", "ACE_SOCK_Dgram::open"), -1);
		return -1;
	}
	return 0;
}



bool CExchangeConnectionHandlerUDPClient::Start()
{


	if( ACE_Thread::spawn((ACE_THR_FUNC)CExchangeConnectionHandlerUDPClient::Start_,this, 
		THR_JOINABLE | THR_NEW_LWP,		 
		&m_processorThreadID,
		&m_processorThreadHandle ) == -1 )
	{
		// TODO: Log
		return false;
	}

	return true;
}

void CExchangeConnectionHandlerUDPClient::Start_( void* _param )
{
	((CExchangeConnectionHandlerUDPClient*)_param)->Start_Callback();
}



void CExchangeConnectionHandlerUDPClient::Start_Callback()
{
		
	

	while(m_bthreadContinue) // Connection loop
	{	
		int nResult = open();
		if(nResult !=-1 )
			while(m_bthreadContinue)
			{
				int nBytesRead = m_sockDgram.recv(szMsg,1024,m_Inet_Addr);
			
				if ( nBytesRead == -1  )
				{
					this->m_Connected = 0;
					ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
					ACE_DEBUG( ( LM_DEBUG, "(%t) Not Receiveing data...\n\n" ) );
					Sleep(1000);			
					continue;
				}
				if (nBytesRead > 0)
					szMsg[nBytesRead]= '\0';
				else
					szMsg[1]= '\0';
				if ( nBytesRead > 0 )
				{
					std::string _item = szMsg;
					char _date[50];
					time_t rawtime;
					struct tm * timeinfo;    
					time ( &rawtime );
					timeinfo = localtime ( &rawtime );	
					strftime(_date,25,"%d %b %Y %H:%M:%S", timeinfo);
					Last_Connection_Time = _date;		
					this->m_Connected = 1;
					this->m_Queue.push(_item);

				}
				else
				{
					this->m_Connected = 2;
					ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
					ACE_DEBUG( ( LM_DEBUG, "(%t) Incomming Connection From MDFServer is disconnected...\n\n" ) );


					return;
				}


	}

}
}

bool CExchangeConnectionHandlerUDPClient::Destroy( void )
{
	m_bthreadContinue = false;
	return true;


}

CExchangeConnectionHandlerUDPClient::~CExchangeConnectionHandlerUDPClient(void)
{
}

bool CExchangeConnectionHandlerUDPClient::Create( void )
{
	m_bthreadContinue = true;
	return 	Start();

}

std::string CExchangeConnectionHandlerUDPClient::GetMessage( std::string& )
{

	return std::string();

}