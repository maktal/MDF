#pragma once

#include "Constant.h"
#include "libxml.h"
#include "ace/Vector_T.h" 
#include "File.h"
#include "ConfigurationServer.h"
#include "ExchangeBuilder.h"
#include "Utility.h"



class CConfigurationManager
{
private: std::string					m_DumpFileName;
private: CLIBXML_DOM_Document*			m_XMLDocument; 
private: bool							m_IsFileOpened;
private: static  CConfigurationManager* m_ConfigurationManager;
private: CCConfigurationServer*			m_configurationServer;
private: int						    m_ConfigurationListenerPort;
private: bool							m_IsFileValid;
public: std::string					m_XMLFileText;	



private: CConfigurationManager();
public:	~CConfigurationManager(void);
public: STExchangeConnectionInfoList m_ExchangeInfoList;

public: bool ReadFile(std::string _FileName);
public:	bool WriteFile(std::string _FileName,std::string _Data);
public:	bool Init(void);
public:	bool CleanUp(void);
public:	std::string GetStatus(void);
public: bool UpdateFile(std::string _FileName);

public:	static CConfigurationManager* instance()
		{ 
			//if(m_ConfigurationManager == NULL)
			//	m_ConfigurationManager = new CConfigurationManager();
		
			return m_ConfigurationManager;
		}
};
