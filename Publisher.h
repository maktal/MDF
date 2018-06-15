#pragma once

#include "ace/Ace.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/INET_Addr.h"
#include "ace/OS.h"
#include "ace/Vector_T.h" 
#include "Queue.h"
#include "Dumper.h"
#include "ParsedMessage.h"
#include "ClientSocket.h"
#include "Constant.h"
#include <xstring>

class CExchangeHandler;
 
class CPublisher : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
	private:	CQueue<CParsedMessage>					m_Queue;
	private:	ACE_thread_t							m_processorThreadID;
	private:	ACE_hthread_t							m_processorThreadHandle;
	private:	ACE_SOCK_Acceptor						m_Acceptor;
	//private:	std::set<ACE_SOCK_Stream*>				m_SocketList;
	private:	std::set<CClientSocket*>				m_SocketList;
	private:	STExchangeConnectionInfo				m_ConnectionInfo;
	private:	bool									m_threadContinue;
	private:	Mutex									m_Mutex;
	private:	CDumper*								m_Dumper;
	private:	IMessageParser*							m_MessageParser;

	private:	bool Start();
	private:	void Start_Callback();
	private:	void RemoveDeadSockets(std::vector<std::set<CClientSocket*>::iterator>&);

	public:		CPublisher();
	public:		CPublisher(STExchangeConnectionInfo&, CDumper*);
	public:    ~CPublisher(void);

	public:		bool PublishMessage(CParsedMessage&);
	public:		long GetNumberOfSubscribers(void);
	public:		std::set<CClientSocket*> GetListOfSubscribers(void);
	private:	bool Publish_Actual(CClientSocket*, std::string&);
	private:	std::string GetFormatedMessage(CParsedMessage&); 

	public:		bool Create  ( void );
	public:		bool Destroy ( void );

	//--- Thread ---
	public:		static void Start_(void*);

	//--- Service Handler Function ---
	public:		int			handle_input(ACE_HANDLE); 
	public:		int			open(const ACE_INET_Addr &listen_addr);
	public:		ACE_HANDLE	get_handle(void) const;
};
