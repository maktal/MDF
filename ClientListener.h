#pragma once

#include "Constant.h"
class CClientListener :public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
public:
	ACE_SOCK_Acceptor							m_Acceptor;
	ACE_Vector<ACE_SOCK_Stream*,10>				m_ClientVector;
	CClientListener(void);

public:
	~CClientListener(void);
	int open(const ACE_INET_Addr &listen_addr);
	int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE) 
	virtual ACE_HANDLE get_handle(void) const 

	 

};
