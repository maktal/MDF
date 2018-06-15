// File.h: interface for the CFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILE_H__F8CF0BB9_A4AA_4829_AD26_2962F14064A2__INCLUDED_)
#define AFX_FILE_H__F8CF0BB9_A4AA_4829_AD26_2962F14064A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Constant.h"
#include <io.h>
#include <stdio.h>

class CFile  
{		
		public:
			FILE* m_pFile;
			
		public:
			CFile();
			CFile(const char* stFileName, const char* stMode);
			
			virtual ~CFile();
			
			int Open(const char* stFileName, const char* stMode);
			void Close();
			
			int SetPointer(int,int);
			int SetPointerToStart();
			int SetPointerToEnd();
			

			int GetFileSize();
			int GetCurrentLocation();
			
			int Flush();
			
			int Write(const char* stData, int iLength);
			int WriteLine(const char* stData, int iLength);
			
			int Read(char* stBuffer, int iLength);
			int ReadLine(char* stBuffer, int iLength);
			
			bool IsEOF();
};

#endif // !defined(AFX_FILE_H__F8CF0BB9_A4AA_4829_AD26_2962F14064A2__INCLUDED_)
