// ExchangeCommunicator.cpp: implementation of the ExchangeCommunicator class.
//
//////////////////////////////////////////////////////////////////////

#include "ExchangeCommunicator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExchangeCommunicator::CExchangeCommunicator(STExchangeConnectionInfo _ExConInfo)
{ 
	m_ExeConInfo = _ExConInfo;

	// Service Handler
	this->m_ExDataHandler = new CExchangeDataHandler(this);

	this->m_MessageParser = new CMessageParserADSM(this->m_QueueRawMsg, this->m_QueueParsedMessage);
 
	// Raw Queue
	this->m_QueueRawMsg = new CQueue<std::string>();						

	this->m_Publisher = new CPublisher(this);
	// Parsed Message Queue
	this->m_QueueParsedMessage = new CQueue<CParsedMessage>();

	//Message Parser
	switch(_ExConInfo.ParserType)
	{
		case 0:
				this->m_MessageParser = NULL;
				break;

		case 1:
				this->m_MessageParser = NULL;
				break;

		default:
			break;
	
	}

} 



int CExchangeCommunicator::ConnectToExchange()
{
 //CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CExchangeCommunicator::Start_, this, 0, NULL);
	
	if( ACE_Thread::spawn((ACE_THR_FUNC)CExchangeCommunicator::Start_, 
						  this, 
						  THR_JOINABLE | THR_NEW_LWP,		 
						  &m_processorThreadID,
						  &m_processorThreadHandle ) == -1 )
	{
		// TODO: Log
	}

	return 1;
} 

//////////////////////////////////////////////////////////////////////////

void CExchangeCommunicator::Start_Callback()
{
	std::string p_IP;
	std::string p_Exchange;
	int p_Port = m_ExeConInfo.Port;
	p_IP = m_ExeConInfo.IP;
	
	
	// Calling  Publisher


	ACE_INET_Addr oHostAddress(p_Port, p_IP.c_str()) ;
	
	while ( true )
	{	
			if ( m_Connector.connect( m_ExDataHandler, oHostAddress ) == -1 ) 
			{
				printf("Failed To Connect %s port \n", m_ExeConInfo.Exchange.c_str() ,m_ExeConInfo.Port );	
			}	
			else
			{
				printf("Connected To %s  Port %d\n", m_ExeConInfo.Exchange.c_str() ,m_ExeConInfo.Port );	
				break;
			}
	}
}

//////////////////////////////////////////////////////////////////////////

void* CExchangeCommunicator::Start_(void * pParam )
{
	((CExchangeCommunicator*)pParam)->Start_Callback();
	return 0;
}




CExchangeCommunicator::~CExchangeCommunicator()
{
}