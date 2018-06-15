#pragma once

#include "Queue.h"

#include "Constant.h"
#include "ExchangeConnectionHandler.h"
#include "ExchangeConnectionHandlerUDPClient.h"
#include "ExchangeConnectionHandlerServer.h"

#include "MessageParser.h"
#include "MessageParserADSM.h"
#include "MessageParserDFM.h"
#include "MessageParserTadawul.h"

#include "Publisher.h"

#include "Dumper.h"

#include "ace/Connector.h"
#include "ace/Reactor.h"


class CExchangeHandler 
{ 
public:
	STExchangeConnectionInfo								m_ExeConInfo;
	IMessageParser*											m_MessageParser;
	IExchangeConnectionHandler*								m_ExchangeConnectionHandler;		// Ace Service Handler Receiving Data
	CPublisher*												m_Publisher;
	CDumper*												m_Dumper;
	bool													m_bthreadContinue;
	int 													isExchangeConnected();
	std::string												GetExchLastConnectionTime();
	std::string												GetExchLastPublishMessage();
private:
				// ACE_Connector
	ACE_thread_t											m_processorThreadID;
	ACE_hthread_t											m_processorThreadHandle;

private: bool Start(void);
private: void Start_Callback();

public:
	CExchangeHandler();
	CExchangeHandler(STExchangeConnectionInfo _ExConInfo);
	~CExchangeHandler();
	bool Create();
	bool Destroy();
	static void* Start_( void * pParam ); 
	

	
};