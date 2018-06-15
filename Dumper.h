#pragma once

#include "ace/Vector_T.h"

#include "File.h"
#include "Constant.h"
#include "LIBXML.h"
#include "ParsedMessage.h"
#include "Utility.h"
#include "CppSQLite3.h"



class CDumper
{
	private: std::string m_DumpFileName;
	private: CppSQLite3DB  m_dumpFile;
	private: bool m_IsFileOpened;
	private: const char* GetSequenceNumber(void);
	private: bool IncreamentSequenceNumber();

	public: CDumper(std::string&);
	public: ~CDumper(void);
	public: 
		bool SaveRawMessage(std::string);
		long GetRowCount();

	public: bool SavePublishedMessage(std::string);
	public: long GetMessageCount(void);
	public: ACE_Vector<std::string,10> GetMessage(long);
};
