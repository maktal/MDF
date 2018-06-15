#pragma once
#include "Constant.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Dgram.h"
#include "ace/INET_Addr.h" 
#include "ace/SOCK_Connector.h" 
#include "ace/Connector.h" 
#include "Queue.h"
#include "ExchangeConnectionHandler.h"
#include "ParsedMessage.h"

 

class CExchangeConnectionHandlerUDPClient  : public IExchangeConnectionHandler
{
public:
	CExchangeConnectionHandlerUDPClient(STExchangeConnectionInfo _ExConInfo);
	private: CQueue<std::string>		m_Queue;
	private: std::string				m_temp;
	private: STExchangeConnectionInfo	m_ExchnageConnectionInfo;
    private: ACE_thread_t				m_processorThreadID;
    private: ACE_hthread_t				m_processorThreadHandle;
	private: int						m_BufferSize;

	private: bool						m_bthreadContinue;
	private: char*						szMsg;
	private: Event						m_Event;
	private: ACE_SOCK_Dgram             m_sockDgram;
    private: ACE_INET_Addr              m_Inet_Addr; 
	private:	bool Start();
	private:	void Start_Callback();

	//--- Thread ---
	public:		static void Start_(void*);

	public:		int handle_input(ACE_HANDLE){return 0;} 		
	public:		int	handle_close (ACE_HANDLE, ACE_Reactor_Mask){return 0;}
	public:		int open();	


	public:	~CExchangeConnectionHandlerUDPClient(void);
	public:  bool				Create(void);
	public:  bool				Destroy(void);		
	public:	 std::string		GetMessage(std::string&);

};
