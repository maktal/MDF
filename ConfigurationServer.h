#pragma once
#include "ace/Ace.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/INET_Addr.h"
#include "ace/OS.h"
#include "ace/Vector_T.h" 
#include "Constant.h"

class CConfigurationManager;


class CCConfigurationServer  : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{

	ACE_thread_t						m_processorThreadID;
	ACE_hthread_t						m_processorThreadHandle;
	ACE_SOCK_Acceptor					m_Acceptor;
	ACE_Vector<ACE_SOCK_Stream*,10>		m_ACE_SockVector;
	ACE_SOCK_Stream*					m_sock;
	int									m_ConfigurationListenerPort;

	public:		CCConfigurationServer(int);
	public:		CCConfigurationServer(void);
	public:		~CCConfigurationServer(void);
	public:		bool Create(void);
	public:		bool Destroy(void);

	// Service Handler Function
	public:		int handle_input(ACE_HANDLE); 
	public:		int open(const ACE_INET_Addr &listen_addr);
	public:		ACE_HANDLE get_handle(void) const;
	public:		int	handle_close (ACE_HANDLE, ACE_Reactor_Mask);
	
	// Thread
	private:	int Start(ACE_SOCK_Stream *ssock);
	public:		static void Start_(ACE_SOCK_Stream *ssock);
};
