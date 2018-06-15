#pragma once

#include "Queue.h"
#include "MessageParser.h"
#include "Constant.h"
#include "ExchangeDataHandler.h"
#include "MessageParserADSM.h"
#include "Publisher.h"
#include "ace/Connector.h"
#include "ace/Reactor.h"


class CExchangeCommunicator  
{ 
public:
	STExchangeConnectionInfo								m_ExeConInfo;
	CQueue<std::string>*									m_QueueRawMsg;				// Raw	Message (From Exchange) Queue
	CQueue<CParsedMessage>*									m_QueueParsedMessage;		// Parsed Message (From Message Parser) Queue
	IMessageParser*											m_MessageParser;
	CExchangeDataHandler*									m_ExDataHandler;		// Ace Service Handler Receiving Data
	CPublisher*												m_Publisher;
private:
	ACE_Connector<CExchangeDataHandler, ACE_SOCK_CONNECTOR> m_Connector;			// ACE_Connector
	ACE_thread_t											m_processorThreadID;
	ACE_hthread_t											m_processorThreadHandle;

public:
	CExchangeCommunicator();
	CExchangeCommunicator(STExchangeConnectionInfo _ExConInfo);
	virtual ~CExchangeCommunicator();
	int ConnectToExchange();
	static void* Start_( void * pParam ); 
	void Start_Callback();
	
};

typedef std::vector<CExchangeCommunicator*> CExchangeCommunicatorList;