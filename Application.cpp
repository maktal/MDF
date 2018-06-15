#include "Application.h"

CApplication* CApplication::m_Instance = new CApplication();


CApplication::CApplication(void)
{
//	m_procMutex = ACE_Process_Mutex(APPLICATION_ID);
}

CApplication::~CApplication(void)
{
	m_procMutex.release();

	CExchangeBuilder::instance()->CleanUp();
}

bool CApplication::Run( void )
{
	ACE_Process_Mutex _procMutex(APPLICATION_ID);

	if( -1 == _procMutex.tryacquire())
		return false;
	else
	{
		if (!CConfigurationManager::instance()->ReadFile("app.config"))
		{
			ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
			ACE_DEBUG( ( LM_DEBUG, "(%t) Unable to read app.configFile...\n\n" ) );
			return  -1;

		}

		CExchangeBuilder::instance()->Init();
		CConfigurationManager::instance()->Init();

		//--- Message Loop ---------------------------
		while(true)
		{
			if( kbhit() )
				break;

			ACE_Reactor::instance()->handle_events();
		}
		//--------------------------------------------

		return true;
	}
}