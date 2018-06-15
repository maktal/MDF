#include "Dumper.h"

CDumper::CDumper(std::string& _fileName)
{
	this->m_DumpFileName = _fileName;
	
	m_dumpFile.open(m_DumpFileName.c_str());


	if(this->m_dumpFile.tableExists("tblDump"))
		m_dumpFile.execDML("drop table tblDump;");;

	if(this->m_dumpFile.tableExists("tblRecovery"))
		m_dumpFile.execDML("drop table tblRecovery;");

	m_dumpFile.execDML("create table tblDump(seqno integer primary key, data char(3000));");
	m_dumpFile.execDML("create table tblRecovery(seqno integer primary key, data char(3000));");
}	


CDumper::~CDumper(void)
{
}

bool CDumper::SaveRawMessage( std::string _rawMessage)
{	
	std::string _str= "insert into tblDump(data) values('";
	_str += _rawMessage;
	_str += "')";

	try
	{
		m_dumpFile.execDML(_str.c_str());
	}
	catch(CppSQLite3Exception* e)
	{
		printf(e->errorMessage());
	}

	return true;
}

long CDumper::GetRowCount()
{	
	CppSQLite3Table x;
	x = m_dumpFile.getTable("select * from tblRecovery");//.numRows();	
	return x.numRows() ;
}

bool CDumper::SavePublishedMessage( std::string _publishedMessage)
{
	std::string _str= "insert into tblRecovery(data) values('";
	_str += _publishedMessage;
	_str += "')";
	m_dumpFile.execDML(_str.c_str());
	return true;
}

ACE_Vector<std::string,10> CDumper::GetMessage( long _seqNo)
{
	char buffer[12];
	int  _column = 0;
	itoa(_seqNo,buffer,10);
	ACE_Vector<std::string,10> _vec;

		
	std::string _str= "select data from tblRecovery where seqno >=";
	_str += buffer;
	_str += ";";
	CppSQLite3Query q = m_dumpFile.execQuery(_str.c_str());

	while (!q.eof())
	{
		_vec.push_back(q.fieldValue(0));
		q.nextRow();
	}

	return	_vec;
}
