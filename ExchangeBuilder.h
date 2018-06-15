#pragma once	

#include "ace/Vector_T.h"
#include "ExchangeHandler.h"
#include "ConfigurationManager.h"
#include "constant.h"
#include "string"

class CExchangeBuilder  
{

private:	CExchangeBuilder() {};
private:	~CExchangeBuilder();

public:		ACE_Vector<CExchangeHandler*,10> m_ExchangeHandlerList;
private:	static CExchangeBuilder * m_ExchangeBuilder;
private:	CConfigurationManager*  m_ConfigurationManager;

public:	 bool Init();
public:	 bool CleanUp(void);
public:	 static CExchangeBuilder* instance() { return m_ExchangeBuilder; }
};


