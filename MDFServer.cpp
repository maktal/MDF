#ifndef TEST_TEST2
#define TEST_TEST2

#include "Application.h"
#include <tchar.h>

ACE_INT32 main( int argc, char * argv[] )
{
	if(false == CApplication::instance()->Run())
	{
		
		LPCTSTR _messageText = _T("Cannot run application (may be another instance already running)");
		LPCTSTR _messageCaption = _T("Error ...");
		MessageBox(NULL, _messageText, _messageCaption, MB_OK);
		return -1;
	}

}

#endif;