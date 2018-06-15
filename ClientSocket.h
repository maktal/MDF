#pragma once


#include <xstring>
#include "Queue.h"
#include "ParsedMessage.h"
#include "Dumper.h"
#include "MessageParser.h"

#include "ace/Ace.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Vector_T.h"


class CClientSocket
{
private:	bool									m_IsDead;
private:	Mutex									m_Mutex;
private:	CQueue<std::string>						m_Queue;
public:	ACE_SOCK_Stream*						m_ClientSocket;
private:	ACE_thread_t							m_processorThreadID;
private:	ACE_hthread_t							m_processorThreadHandle;
private:	CDumper*								m_Dumper;
public:	STExchangeConnectionInfo				m_ConnectionInfo;
public:		bool									m_inValidCommand;
public:		bool									m_bThreadContinue;
public: std::string									m_IP;
public: int											m_Port;
private:	bool Start(void);
private:	void Start_Callback();

public:		static void Start_(void*);
public:		void PublishMessage(std::string&);
public:		void StartRecovery(long _seqNo);
public:		CClientSocket(ACE_SOCK_Stream*,CDumper*);
public:		~CClientSocket(void);
public:		bool IsAlive(void);

};
