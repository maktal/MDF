#pragma once

#include "Constant.h"
#include "ConfigurationManager.h"
#include "ExchangeBuilder.h"
#include "ace/Process_Mutex.h"

class CApplication
{	
	private: ACE_Process_Mutex m_procMutex;
	private: static CApplication* m_Instance;
	private: CApplication(void);
	public:	~CApplication(void);
	public: bool Run(void);
	public: static CApplication* instance(void) { return m_Instance; }
};