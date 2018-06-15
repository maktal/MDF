#pragma once

#include "Constant.h"
#include "Queue.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Stream.h" 
#include "ace/INET_Addr.h" 
#include "ace/Vector_T.h" 

#include <xstring>


class CExchangeConnectionHandlerServer : public IExchangeConnectionHandler
{	
	private:	CQueue<std::string>					m_Queue;
	private:	std::string							m_temp;
	private:	STExchangeConnectionInfo			m_ExchnageConnectionInfo;
	private:	bool								m_bthreadContinue;
	private:	char*								szMsg;
	private:	Event								m_Event;
	public:		ACE_SOCK_Stream*					ssock_;
	private:	ACE_thread_t						m_processorThreadID;
	private:	ACE_hthread_t						m_processorThreadHandle;
	private:	ACE_SOCK_Acceptor					m_Acceptor;
	private:	ACE_Vector<ACE_SOCK_Stream*,10>		m_ACE_SockVector;
	private:	ACE_SOCK_Stream*					m_sock;
	private:	int									m_MDFListenerPort;
	private:	int									m_BufferSize;
	public:		CExchangeConnectionHandlerServer(void);
	public:		CExchangeConnectionHandlerServer(STExchangeConnectionInfo&);
	public:		~CExchangeConnectionHandlerServer(void);


	public:		std::string		GetMessage(std::string&);
	public:		bool			Create(void);
	public:		bool			Destroy(void);
	private: long				GetDynamicBufferSize(long,CExchangeConnectionHandlerServer*);

	// Service Handler Function
	public:		int handle_input(ACE_HANDLE); 
	public:		int open(const ACE_INET_Addr &listen_addr);
	public:		ACE_HANDLE get_handle(void) const;
	public:		int	handle_close (ACE_HANDLE, ACE_Reactor_Mask);

	// Thread
	private:	int Start(CExchangeConnectionHandlerServer*);
    private:      void StartCallBack(CExchangeConnectionHandlerServer*);
	public:		static void Start_(CExchangeConnectionHandlerServer*);
};
