#pragma once

#include "Constant.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Stream.h" 
#include "ace/INET_Addr.h" 
#include "ace/SOCK_Connector.h" 
#include "ace/Connector.h" 
#include "Queue.h"
#include "ExchangeConnectionHandler.h"
#include "ParsedMessage.h"

 
class CExchangeConnectionHandler : public IExchangeConnectionHandler
{
private: ACE_Connector<CExchangeConnectionHandler, ACE_SOCK_CONNECTOR>  m_Connector;
private: CQueue<std::string>		m_Queue;
private: std::string				m_temp;
private: STExchangeConnectionInfo	m_ExchnageConnectionInfo;
private: bool						m_bthreadContinue;
private: char*						szMsg;
private: Event						m_Event;

private:  ACE_thread_t				m_processorThreadID;
private:  ACE_hthread_t				m_processorThreadHandle;
private:  void  Start_Callback();
private:  bool  Start();

public:						CExchangeConnectionHandler(){}
public:						CExchangeConnectionHandler(STExchangeConnectionInfo _ExConInfo);
public:						~CExchangeConnectionHandler();
public:  int				handle_close (ACE_HANDLE, ACE_Reactor_Mask);
public:	 ACE_INT32			handle_input(ACE_HANDLE);

public:	 std::string		GetMessage(std::string&);
public:	 static void		Start_( void * pParam ); 
public:  bool				Create(void);
public:  bool				Destroy(void);
private: long				GetDynamicBufferSize(long);
};