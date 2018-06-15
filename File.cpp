// File.cpp: implementation of the CFile class.
//
//////////////////////////////////////////////////////////////////////

#include "File.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFile::CFile()	: m_pFile( NULL )
{
}

//////////////////////////////////////////////////////////////////////////

CFile::CFile(const char* pszFileName, const char* pszMode)
{
	m_pFile = fopen( pszFileName, pszMode );
}

//////////////////////////////////////////////////////////////////////////

CFile::~CFile()
{
	if( m_pFile != NULL )
	{
		fclose( m_pFile );
	}
}

//////////////////////////////////////////////////////////////////////////

void CFile::Close()
{
	if( m_pFile != NULL )
	{
		fclose( m_pFile );
	}
}

//////////////////////////////////////////////////////////////////////////

int CFile::Flush()
{
	if( !m_pFile )
	{
		return -1;
	}

	if(  fflush( m_pFile ) != 0 )
	{
		return -1;
	}

	return 0; // SUCCESS
}

//////////////////////////////////////////////////////////////////////////

int CFile::GetCurrentLocation()
{
	if( !m_pFile )
	{
		return -1;
	}

	return ftell( m_pFile );
}

//////////////////////////////////////////////////////////////////////////


int CFile::GetFileSize()
{
	if( !m_pFile )
	{
		return -1;
	}

	// Get the file's size
	return filelength( fileno( m_pFile ) );
}

//////////////////////////////////////////////////////////////////////////

bool CFile::IsEOF()
{
	return ( feof( m_pFile ) == 0 ) ? false : true;
}

//////////////////////////////////////////////////////////////////////////

int CFile::Open(const char* pszFileName, const char* pszMode)
{
	if( m_pFile != NULL )
	{
		fclose( m_pFile );
	}

	m_pFile = fopen( pszFileName, pszMode );

	if( m_pFile == NULL )
	{
		return -1;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CFile::Read(char* pszBuffer, int nLength)
{
	if ( !m_pFile )
	{
		return -1;
	}

	return fread( pszBuffer, sizeof( char ), nLength, m_pFile );
}

//////////////////////////////////////////////////////////////////////////

int CFile::ReadLine(char* pszBuffer, int nLength)
{
	if( !m_pFile )
	{
		return -1;
	}

	char* _pszBuffer = pszBuffer;

	while( !this->IsEOF() )
	{
		if ( Read( _pszBuffer, 1 ) != 1 )
			return -1;

		if ( *_pszBuffer == '\n' )
		{
			*_pszBuffer = 0;
			break;
		}

		_pszBuffer++;

		if ( _pszBuffer - pszBuffer >= nLength )
		{
			return -1;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CFile::SetPointer(int nOffset, int mode)
{
	if( !m_pFile )
	{
		return -1;
	}

	return fseek( m_pFile, nOffset, mode );
}

//////////////////////////////////////////////////////////////////////////

int CFile::SetPointerToEnd()
{
	if( !m_pFile )
	{
		return -1;
	}

	return fseek( m_pFile, 0L, SEEK_END );
}

//////////////////////////////////////////////////////////////////////////

int CFile::SetPointerToStart()
{
	if( !m_pFile )
	{
		return -1;
	}

	return fseek( m_pFile, 0L, SEEK_SET );
}

//////////////////////////////////////////////////////////////////////////

int CFile::Write(const char* pszData, int nLength)
{
	if( !m_pFile )
	{
		return -1;
	}

	fwrite( pszData, nLength, 1/*count*/, m_pFile );
	return 0; // SUCCESS
}

//////////////////////////////////////////////////////////////////////////

int CFile::WriteLine(const char* pszData, int nLength)
{
	if( !m_pFile )
		return -1;

	Write( pszData, nLength );
	Write( "\r\n", 2 ); // Each Message must be written on new Line 

	return 0; // SUCCESS
}

//////////////////////////////////////////////////////////////////////////