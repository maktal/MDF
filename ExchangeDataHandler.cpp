// ExchangeDataHandler.cpp: implementation of the CExchangeDataHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "ExchangeDataHandler.h"
#include "ExchangeCommunicator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CExchangeDataHandler::CExchangeDataHandler()
{

}


CExchangeDataHandler::~CExchangeDataHandler()
{

}


int CExchangeDataHandler::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
	
	return 0;
}



int CExchangeDataHandler::handle_input(ACE_HANDLE handle)
{
	
		char* szMsg = new char[m_BufferSize];

		//memset(szMsg,'\0',m_BufferSize);
		int nBytesRead = this->peer().recv(szMsg, m_BufferSize);
		szMsg[nBytesRead]= '\0';
		if ( nBytesRead == 0  )
		{
			ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
			ACE_DEBUG( ( LM_DEBUG, "(%t) Data Received is not complete...\n\n" ) );

		}

		if ( nBytesRead > 0 )
		{
		
			this->m_ExChangeCommunicator->m_QueueRawMsg->push( szMsg );
		//	printf("Data Received %s",  szMsg);
		}
		else
		{

			ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
			ACE_DEBUG( ( LM_DEBUG, "(%t) Incomming Connection From MDFServer is disconnected...\n\n" ) );

			return -1;
		}
	
	return 0;
}

CExchangeDataHandler::CExchangeDataHandler( CExchangeCommunicator* _ExchangeCommunicator )
{
	m_ExChangeCommunicator = _ExchangeCommunicator;
	m_BufferSize = m_ExChangeCommunicator->m_ExeConInfo.BufferSize;
}
