#include "ConfigurationServer.h"
#include "ConfigurationManager.h"

CCConfigurationServer::CCConfigurationServer(void)
{
}

CCConfigurationServer::CCConfigurationServer(int _configurationListenerPort)
{
	this->m_ConfigurationListenerPort = _configurationListenerPort;
}

CCConfigurationServer::~CCConfigurationServer(void)
{
	Destroy();
}

int CCConfigurationServer::open(const ACE_INET_Addr &listen_addr)
{
	return this->m_Acceptor.open( listen_addr, 1 );
}

int CCConfigurationServer::handle_input(ACE_HANDLE handle)
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
		Start(ssock_);

		//	m_ACE_SockVector.push_back(ssock_);
	}
	catch(int a)
	{
		return  -10;
	}
	return 0;

}





ACE_HANDLE CCConfigurationServer::get_handle(void) const 
{ 

	return this->m_Acceptor.get_handle(); 
}





int CCConfigurationServer::Start(ACE_SOCK_Stream* ssock)
{

	if( ACE_Thread::spawn((ACE_THR_FUNC)CCConfigurationServer::Start_,ssock, 
		THR_JOINABLE | THR_NEW_LWP,		 
		&m_processorThreadID,
		&m_processorThreadHandle ) == -1 )
	{
		return -1;
	}

	return 1;


}



void CCConfigurationServer::Start_(ACE_SOCK_Stream* _sock )
{

	try
	{
		/// Read Request For client either Read or Write Xml;
		//Sleep(100);
		char _ch[3];
		int r;
		int attempt=0;


		r =	_sock->recv(_ch,1);
		if(r > 0) 
			_ch[r] = '\0';					
		else
			_ch[1] = '\0';					
		// 
		int result =   atoi(_ch);
		if (r!=-1)
		{
			if(ReadConfigFile ==  result)
			{
				_sock->send_n(CConfigurationManager::instance()->m_XMLFileText.c_str(),CConfigurationManager::instance()->m_XMLFileText.length());	
				return;
			}
			else if(WriteConfigFile==atoi(_ch))
			{
				std::string _item, _ret;
				int _position;
				int r;

				while(1)
				{
					
					Sleep(100);
					char ch[2025];
				
					r =	_sock->recv(ch,2024);
										
					if(r > 0) 
						ch[r] = '\0';					
					else
						ch[1] = '\0';		

					_item.append(ch);
			
					//--- Not Receiving any data from client 
					if(r == -1 )
					{
						break; 
					}
				
					printf("\nXml Receiving From Client...\n");
					_position = _item.find(';');
					
					// Message Completed				
					if(_position > 0)
					{
						_ret = _item.substr(0, _position);
						printf("Complete Xml Received........\n");		
						printf("Writing Xml in File..... \n");	
						if( CConfigurationManager::instance()->WriteFile("app.config",_item))
						{
							printf("Xml writing Complete in File.... \n");	
			       			CConfigurationManager::instance()->UpdateFile("app.config");
							printf("Xml Reloaded.... \n");	
						}
						else
							printf("Unable to write File...\n");	
						
						break;
					}
				
				}
				
			}
			else if(ReadExchangeStatus==atoi(_ch))
			{
				std::string _status =  CConfigurationManager::instance()->GetStatus();
				_sock->send_n(_status.c_str(),_status.length());	
				return;
			}

		}
	}
	catch(int a)
	{
		_sock->close();
	}

	_sock->close();
}

bool CCConfigurationServer::Create( void )
{
	bool _ret;

	//--- Open Listener ---
	char szBuffer[12];
	ACE_INET_Addr oSubPort( ACE_OS::itoa(m_ConfigurationListenerPort, szBuffer, 10 ) );
	this->reactor(ACE_Reactor::instance() );
	_ret = (bool) this->open(oSubPort);
	_ret &= (bool) ACE_Reactor::instance()->register_handler( this, ACE_Event_Handler::ACCEPT_MASK ); 

	return _ret;
}

bool CCConfigurationServer::Destroy( void )
{
	bool _ret;
	_ret = (bool) ACE_Reactor::instance()->remove_handler( this, ACE_Event_Handler::ACCEPT_MASK ); 
	return _ret;
}

int CCConfigurationServer::handle_close( ACE_HANDLE, ACE_Reactor_Mask )
{
	return 1;
}