#pragma once

#include "ace/Ace.h"
#include "ace/Vector_T.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/INET_Addr.h"
#include "Constant.h"

class CRecoveryManager : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
	//---------------------------- Properties ----------------------
	private: STExchangeConnectionInfo			m_ConnectionInfo;
	private: ACE_SOCK_Acceptor					m_Acceptor;
	private: ACE_Vector<ACE_SOCK_Stream*,10>	m_ACE_SockVector;
	//--------------------------------------------------------------

	//------------------------------ Methods -----------------------
	public: CRecoveryManager(void);
	public: CRecoveryManager(STExchangeConnectionInfo _ExConInfo);
	public:	~CRecoveryManager(void);
	public:	int handle_input(ACE_HANDLE);
	public:	int open(const ACE_INET_Addr &listen_addr);
	public:	ACE_HANDLE get_handle(void) const;
	public:	bool Create(void);
	public:	bool Destroy(void);
	//--------------------------------------------------------------
};