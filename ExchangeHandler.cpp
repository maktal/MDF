// ExchangeCommunicator.h.cpp: implementation of the ExchangeCommunicator.h class.
//
//////////////////////////////////////////////////////////////////////

#include "ExchangeHandler.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExchangeHandler::CExchangeHandler(STExchangeConnectionInfo _ExConInfo)
{ 
	m_ExeConInfo = _ExConInfo;
} 

//////////////////////////////////////////////////////////////////////////

void CExchangeHandler::Start_Callback()
{	
	// Calling  Publisher
	while ( m_bthreadContinue )
	{	
		try
		{
			std::string _item = m_ExchangeConnectionHandler->GetMessage(std::string(m_ExeConInfo.Delimiter));
			std::string _temp = _item.substr(0,_item.find_last_of('\n'));

			//--- Benchmark ----------------------------------
			char _time[100];
			SYSTEMTIME sysDateTime;
			GetLocalTime( &sysDateTime );
			sprintf(_time, ";RecieveTime=%d:%d:%d:%d", sysDateTime.wHour, sysDateTime.wMinute, sysDateTime.wSecond, sysDateTime.wMilliseconds );

			_temp += _time;
			//------------------------------------------------

			if(_item.empty())
				continue;


			CParsedMessage _message = m_MessageParser->ParseMessage(_item);

			printf("\n%s: Message Received ", m_ExeConInfo.ID.c_str());
			printf(_message._SeqNo.c_str());
			m_ExchangeConnectionHandler->Last_Message_Published = _message._SeqNo.c_str();
			m_Dumper->SaveRawMessage(_temp);
			m_Publisher->PublishMessage(_message);
	
		}
		catch(int a)
		{}
	}
}

//////////////////////////////////////////////////////////////////////////

void* CExchangeHandler::Start_(void * pParam )
{
	((CExchangeHandler*)pParam)->Start_Callback();
	return 0;
}


int CExchangeHandler::isExchangeConnected()
{
	return m_ExchangeConnectionHandler->m_Connected;

}

std::string CExchangeHandler::GetExchLastConnectionTime()
{
	return m_ExchangeConnectionHandler->Last_Connection_Time;
}

std::string CExchangeHandler::GetExchLastPublishMessage()
{
	return m_ExchangeConnectionHandler->Last_Message_Published;
}

CExchangeHandler::~CExchangeHandler()
{
	delete m_Dumper;
	Destroy();
}

bool CExchangeHandler::Start()
{

	if( ACE_Thread::spawn((ACE_THR_FUNC)CExchangeHandler::Start_, 
		this, 
		THR_JOINABLE | THR_NEW_LWP,		 
		&m_processorThreadID,
		&m_processorThreadHandle ) == -1 )
	{
		// TODO: Log
		return false;
	}

	return true;
}

bool CExchangeHandler::Destroy()
{
	bool _ret = true;
	m_bthreadContinue = false;

	delete m_Publisher;
	delete m_Dumper;
	delete m_ExchangeConnectionHandler;
	delete m_MessageParser;

	return _ret;
}

bool CExchangeHandler::Create()
{
	m_bthreadContinue = true;
	bool _ret;

	puts("\n---------------------------------");
	printf("Exchange ID: %s", m_ExeConInfo.ID.c_str());
	puts("\n---------------------------------");

	//-------- Service Handler ------------------------------------------------------
	switch(m_ExeConInfo.ConnectionType)
	{
		case UDP_CLIENT:
			this->m_ExchangeConnectionHandler = new CExchangeConnectionHandlerUDPClient(m_ExeConInfo);
			break;
		case TCP_CLIENT:
			this->m_ExchangeConnectionHandler = new CExchangeConnectionHandler(m_ExeConInfo);
			break;
		case TCP_SERVER:
			this->m_ExchangeConnectionHandler = new CExchangeConnectionHandlerServer(m_ExeConInfo);
			break;
	}

	_ret = this->m_ExchangeConnectionHandler->Create();
	(true == _ret) ? printf("\nConnectionHandler Started\n[Mode: %d] - [Exchange Port: %d] [Exchange IP/Host: %s]\n", m_ExeConInfo.ConnectionType, m_ExeConInfo.Port, m_ExeConInfo.IP.c_str()) 
				   : printf("\n*** ERROR *** starting ConnectionHandler\n");	
	//-------------------------------------------------------------------------------

	//-------- Dumper ---------------------------------------------------------------
	char _date[50];
	time_t rawtime;
    struct tm * timeinfo;    
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );	
	strftime(_date,7,"%d%m%y",timeinfo);
    
	std::string _dumFileName; 
	_dumFileName += m_ExeConInfo.ID + + _date + "-" + m_ExeConInfo.RecoveryFile ;
	m_Dumper = new CDumper(_dumFileName);
	(NULL != m_Dumper) ? printf("\nDump File created: %s\n" , _dumFileName.c_str()) 
					   : printf("\n*** ERROR *** creating Dump File: %s\n" , _dumFileName.c_str());	
	//-------------------------------------------------------------------------------

	//-------- Publisher ------------------------------------------------------------
	this->m_Publisher = new CPublisher(m_ExeConInfo, m_Dumper);
	_ret = m_Publisher->Create();
	(true == _ret) ? printf("\nPublisher started for exchange: %s - Port: %d\n" , m_ExeConInfo.ID.c_str(), m_ExeConInfo.PublishPort) 
		: printf("\n*** ERROR *** starting Publisher for exchange: %s - Port: %d\n" , m_ExeConInfo.ID.c_str(), m_ExeConInfo.PublishPort);	
	//-------------------------------------------------------------------------------

	//-------- Message Parser -------------------------------------------------------
	switch(m_ExeConInfo.ParserType)
	{
	case ADSM:
		this->m_MessageParser = new CMessageParserADSM();
		printf("\nParser Initialized for - ADX\n");
		break;

	case DFM:
		this->m_MessageParser = new CMessageParserDFM();
		printf("\nParser Initialized for - DFM\n");
		break;

	case TADAWUL:
		this->m_MessageParser = new CMessageParserTadawul();
		printf("\nParser Initialized for - Tadawul\n");
		break;

	default:
		printf("\n*** ERROR *** Parser is not available\n");
		_ret &= false;
		break;

	}
	//-------------------------------------------------------------------------------

	_ret = (bool)Start();

	(true == _ret) ? printf("\nExchangeHandler Initiated ...\n") 
				   : printf("\n*** ERROR *** initiating ExchangeHandler\n");	

	return _ret;
}