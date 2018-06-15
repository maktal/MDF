#include "ConfigurationManager.h"


CConfigurationManager* CConfigurationManager::m_ConfigurationManager = new CConfigurationManager();

 
CConfigurationManager::CConfigurationManager()
{
	m_XMLDocument = new CLIBXML_DOM_Document();
}	

CConfigurationManager::~CConfigurationManager(void)
{	
}


bool CConfigurationManager::ReadFile(std::string _FileName)
{
	Sleep(100);
	int nCount=0;
	char szBuffer[10];
	DOMNodePtr _nodes;
	std::string _xPath;
	std::string _value;
	STExchangeConnectionInfo _exchangeInfo;


	//--- Error Loading File ---------------------
	if( false == m_XMLDocument->load(_FileName) )
	{
		this->m_IsFileOpened = false;
		return false;
	}
	//--------------------------------------------


	 _xPath = "/MDFConfig/Exchanges";
	_nodes = m_XMLDocument->getNode(_xPath.c_str());
	
	if( !_nodes.get() )
	{
		ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
		return false;
	}

	//--- Exchanges -------------------------------------------------------------------------------------------
	while(true)
	{
			_xPath = "/MDFConfig/Exchanges/Exchange[" + std::string( itoa( ++nCount, szBuffer, 10 ) ) + "]";
			_nodes = m_XMLDocument->getNode(_xPath.c_str());
		
			if( !_nodes.get() )
			{
				if(nCount == 1) // If Its First Node
					m_IsFileValid = false;

				m_IsFileValid = true;

				break;
			}

			/*
			<Exchange>
				<!-- 0 = TCP, 1 = UDP -->
				<ConnectionType>0</ConnectionType>
				<Enable>1</Enable>
				<ID>ADSM</ID>
				<IP>Skywalker</IP>
				<Port>9000</Port>
				<BufferSize>1024</BufferSize>
				<Delimiter> <![CDATA[]]> </Delimiter>

				<!-- 0 = ADSM, 1 = DFM, 2 = TADAWUL -->
				<ParserType>0</ParserType>

				
				<!-- 0 = Binary, 1 = XML -->
				<PublishFormat>0</PublishFormat>
				<!-- 0 = TCP, 1 = UDP -->
				<PublisherConnectionType>0</PublisherConnectionType>
				<PublishPort>10000</PublishPort>

				<MBOEnabled></MBOEnabled>
				<MBPEnabled></MBPEnabled>

				<!-- 0 = TCP, 1 = UDP -->
				<RecoveryConnectionType>0</RecoveryConnectionType>
				<RecoveryFile></RecoveryFile>
				<RecoveryPort></RecoveryPort>

				<ConfigurationListenerPort></ConfigurationListenerPort>

			</Exchange>

			<Configuration>
				<Port>99</Port>
			</Configuration>
			*/

			// Exchange (7)
			_value = m_XMLDocument->getTextFromPath( _xPath + "/Enabled" );
			//if (_value == "0")
			//		continue;

			_value = m_XMLDocument->getTextFromPath( _xPath + "/ConnectionType" );
			_exchangeInfo.ConnectionType = (ENConnectionType)atoi(_value.c_str());
			_value = m_XMLDocument->getTextFromPath( _xPath + "/Enabled" );
			_exchangeInfo.Enabled = atoi(_value.c_str());
			_value = m_XMLDocument->getTextFromPath( _xPath + "/ID" );
			_exchangeInfo.ID= _value;

			

			_value = m_XMLDocument->getTextFromPath( _xPath + "/IP" );
			_exchangeInfo.IP= _value;
			_value = m_XMLDocument->getTextFromPath( _xPath + "/Port" );
			_exchangeInfo.Port=atoi(_value.c_str());
			_value = m_XMLDocument->getTextFromPath( _xPath + "/BufferSize" );
			_exchangeInfo.BufferSize = atoi(_value.c_str());
			_value = m_XMLDocument->getTextFromPath( _xPath + "/Delimiter" );
			_exchangeInfo.Delimiter = CUtility::Decode64(_value);

			//std::string a = CUtility::Encode64(";\n1=");


			// Parser (1)
			_value = m_XMLDocument->getTextFromPath( _xPath + "/ParserType" );
			_exchangeInfo.ParserType = (ENParserType)atoi(_value.c_str());


			// Publisher (3)
			_value = m_XMLDocument->getTextFromPath( _xPath + "/PublishFormat" );
			_exchangeInfo.PublishFormat = (ENPublishFormat)atoi(_value.c_str());
			_value = m_XMLDocument->getTextFromPath( _xPath + "/PublisherConnectionType" );
			_exchangeInfo.PublisherConnectionType= (ENConnectionType)atoi(_value.c_str());
			_value = m_XMLDocument->getTextFromPath( _xPath + "/PublishPort" );
			_exchangeInfo.PublishPort= atoi(_value.c_str());


			// MBO + MBP (2)
			_value = m_XMLDocument->getTextFromPath( _xPath + "/MBOEnabled" );
			_exchangeInfo.MBOEnabled = atoi(_value.c_str());
			_value = m_XMLDocument->getTextFromPath( _xPath + "/MBPEnabled" );
			_exchangeInfo.MBPEnabled = atoi(_value.c_str());


			// Recovery (3)
			_value = m_XMLDocument->getTextFromPath( _xPath + "/RecoveryConnectionType" );
			_exchangeInfo.RecoveryConnectionType = (ENConnectionType) atoi(_value.c_str());
			_value = m_XMLDocument->getTextFromPath( _xPath + "/RecoveryFile" );
			_exchangeInfo.RecoveryFile = _value.c_str();
			
			/*_value = m_XMLDocument->getTextFromPath( _xPath + "/RecoveryPort" );
			_exchangeInfo.RecoveryPort = atoi(_value.c_str());*/
			
			m_ExchangeInfoList.push_back(_exchangeInfo);
	}

	//------------------------------------------------------------------------------------------
	

	//--- Configuration Server ----------------------------------------------------------------

	//m_ConfigurationListenerPort = ; //atoi(_value.c_str());

	_xPath = "/MDFConfig/ConfigurationService";
	_nodes = m_XMLDocument->getNode(_xPath.c_str());
	
	if( _nodes.get() )
	{
		_value = m_XMLDocument->getTextFromPath( _xPath + "/Port" );
		m_ConfigurationListenerPort = atoi(_value.c_str());
	}
	else
		m_IsFileValid = false;

	


	//------------------------------------------------------------------------------------------

	UpdateFile(_FileName);

	


	//////// Read Text of Xml File/////////////////////////


	return true;

}


bool CConfigurationManager::UpdateFile(std::string _FileName)
{
	CFile* configFile = new CFile( _FileName.c_str() , "r" );
	int fileSize = configFile->GetFileSize();
	char* buffer = new char[fileSize+2];
	fileSize  = configFile->Read( buffer, fileSize);
	configFile->Close();

	buffer[fileSize] = ';';
	buffer[fileSize+1] = '\0';
	

	this->m_XMLFileText = buffer;

	if (buffer)
		delete[] buffer;
	/////////////////////////////////////////////////////

	return true;

}


bool CConfigurationManager::WriteFile(std::string _FileName,std::string _Data)
{
	CFile* configFile = new CFile( _FileName.c_str() , "wt" );
	
	if(configFile == NULL)
		return false;
	
	if(configFile->Write(_Data.c_str(),_Data.length()-1) < 0 )
	{
		configFile->Close();
		return false;
	}

	configFile->Close();

	return true;
}

bool CConfigurationManager::CleanUp( void )
{
	bool _ret;

	return _ret;

}

bool CConfigurationManager::Init( void )
{
	bool _ret;

	if(true == m_IsFileValid)
	{
		m_configurationServer = new CCConfigurationServer(m_ConfigurationListenerPort);
		m_configurationServer->Create();

		_ret = true;
	}

	else
		_ret = false;

	return _ret;
}


std::string CConfigurationManager::GetStatus(void)
{
	std::string _xml = "<Exchanges>";
	char* _buffer = new char[12];
			
	// iterate all Exchange Handler

	for (int i=0; i < CExchangeBuilder::instance()->m_ExchangeHandlerList.size(); i++)
	{
		_xml = _xml + "<Exchange>";

		///////////////ID/////////////////////////////////////////////////////
		_xml = _xml + "<ID>";
		_xml = _xml + CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_ExeConInfo.ID;
		_xml = _xml + "</ID>";
		///////////////IP/////////////////////////////////////////////////////
		_xml = _xml + "<IP>";
		_xml = _xml + CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_ExeConInfo.IP;
		_xml = _xml + "</IP>";
		///////////////IP/////////////////////////////////////////////////////
		_xml = _xml + "<Port>";
		_xml = _xml + itoa(CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_ExeConInfo.Port,_buffer,10);
		_xml = _xml + "</Port>";

		///////////////Connection Type /////////////////////////////////////////////////////
		_xml = _xml + "<ConnectionType>";
	
		switch(CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_ExeConInfo.ConnectionType)
		{
				
		case TCP_CLIENT:
				  _xml = _xml + "TCP CLIENT";
		break;
			case TCP_SERVER:
		  _xml = _xml + "TCP SERVER";
		break;
			case UDP_CLIENT:
		  _xml = _xml + "UDP CLIENT";
		break;
		}
		
		_xml = _xml + "</ConnectionType>";
		///////////////Number OF Client///////////////////////////////////////
		_xml = _xml + "<NoOfClient>";
		if(CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_ExeConInfo.Enabled)
			_xml = _xml + itoa(CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_Publisher->GetNumberOfSubscribers(), _buffer, 10);
		else
			_xml = _xml + "0";	
		_xml = _xml + "</NoOfClient>";


		_xml = _xml + "<ExchangeStatus>";	
		if(CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_ExeConInfo.Enabled)
		{
			if (CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->isExchangeConnected() == 0)
			{			
				_xml = _xml + "Not Connected";
			}
			else if (CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->isExchangeConnected() == 2)
				_xml = _xml + "Trying to Reconnect";
			else
				_xml = _xml + "Connected";
		}	
		else
				_xml = _xml + "Disabled";

		_xml = _xml + "</ExchangeStatus>";

		
		
		
		if(!CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_ExeConInfo.Enabled ||
			CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->GetExchLastConnectionTime().empty())
			_xml = _xml + "<LastConnectionTime>0</LastConnectionTime>";
		else
			_xml = _xml + "<LastConnectionTime>" + CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->GetExchLastConnectionTime() + "</LastConnectionTime>";

		if (!CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_ExeConInfo.Enabled ||
			CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->GetExchLastPublishMessage().empty())
			_xml = _xml + "<SeqNumber>0</SeqNumber>";
		else
			_xml = _xml + "<SeqNumber>" +  CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->GetExchLastPublishMessage() +  "</SeqNumber>";
	
		if (CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_ExeConInfo.Enabled)
			if(CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_Publisher->GetNumberOfSubscribers() > 0)
			{
				
				char _Port[50];
				CPublisher* _pPublisher = CExchangeBuilder::instance()->m_ExchangeHandlerList[i]->m_Publisher;
				std::set<CClientSocket*> _SetClientSocket = _pPublisher->GetListOfSubscribers();
				std::set<CClientSocket*>::iterator _itr = _SetClientSocket.begin();
				

			   for( ; _itr != _SetClientSocket.end(); _itr++)
				{
								
					_xml = _xml + "<Client><IP>";
				_xml = _xml + ((CClientSocket*)(*_itr))->m_IP;
					_xml = _xml +  "</IP><Port>";
					_xml = _xml + itoa(((CClientSocket*)(*_itr))->m_Port,_Port,10);
					_xml = _xml + "</Port></Client>";
				}
			}

		_xml = _xml + "</Exchange>";

	}

	_xml = _xml + "</Exchanges>;";
	
	delete _buffer;
	return _xml;

}