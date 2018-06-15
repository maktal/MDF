#pragma once

#include "Constant.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Connector.h" 

class CExchangeCommunicator;
 
class CExchangeDataHandler : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
private: 
	
	//CExchangeCommunicator* m_ExChangeCommunicator;

	//ACE_Connector<CExchangeDataHandler, ACE_SOCK_CONNECTOR> m_Connector;			// ACE_Connector
	
	int					   m_BufferSize;

public:
	CExchangeDataHandler(CExchangeCommunicator* m_ExChangeCommunicator);

	CExchangeDataHandler();

	virtual ~CExchangeDataHandler();
		
	int handle_close (ACE_HANDLE, ACE_Reactor_Mask);
	 
	ACE_INT32 handle_input(ACE_HANDLE);

	//static void* Start_( void * pParam ); 
	
//	void Start_Callback();


};