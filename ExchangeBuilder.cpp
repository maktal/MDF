// ExchangeBuilder2.cpp: implementation of the ExchangeBuilder2 class.
//
//////////////////////////////////////////////////////////////////////
#include "ExchangeBuilder.h"
#include "ExchangeHandler.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CExchangeBuilder* CExchangeBuilder::m_ExchangeBuilder = new CExchangeBuilder();

CExchangeBuilder::~CExchangeBuilder()
{

}

bool CExchangeBuilder::Init()
{
	STExchangeConnectionInfo  oExConInfo;
	bool _ret = true;
	
	STExchangeConnectionInfoList _ExConList = CConfigurationManager::instance()->m_ExchangeInfoList;
	STExchangeConnectionInfoList::iterator itExConInfo = _ExConList.begin();
	
	//--- Iterate all Exchange Connection Info -------------------------
	for ( ; itExConInfo != _ExConList.end() ; itExConInfo++)
	{
		oExConInfo = (STExchangeConnectionInfo) *itExConInfo;	
		CExchangeHandler *oExComm = new CExchangeHandler(oExConInfo);
		if (oExConInfo.Enabled)
		{			
			_ret = oExComm->Create();
		}
		m_ExchangeHandlerList.push_back( oExComm );
	}
	//-------------------------------------------------------------------

	return _ret;

}

bool CExchangeBuilder::CleanUp( void )
{
	bool _ret = true;

	STExchangeConnectionInfoList _ExConList = CConfigurationManager::instance()->m_ExchangeInfoList;
	ACE_Vector<CExchangeHandler*>::iterator itExchangeHandler = m_ExchangeHandlerList.begin();

	//--- Iterate all Exchange Connection Info -------------------------
	for ( ; itExchangeHandler != m_ExchangeHandlerList.end() ; itExchangeHandler++)
	{
		_ret &= ((CExchangeHandler*)*itExchangeHandler)->Destroy();
		m_ExchangeHandlerList.pop_back();
	}
	//-------------------------------------------------------------------

	m_ExchangeHandlerList.clear();
	return _ret;
}