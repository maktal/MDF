#pragma once
#include "messageparser.h"
#include "ParsedMessage.h"
#include "MessageStorage.h"
#include "Constant.h"
class CMessageParserTadawul : public IMessageParser
{
public:
	CMessageParserTadawul(void);
	CParsedMessage ParseMessage(std::string _Message);

	bool TagExists (std::string tag, std::string& msg);	
	bool TagExists_( char * szMsg, const std::string & stTag );

	bool GetNextTagVal (std::string& msg, std::string& stTag, std::string& stVal, int & nMsgCounter, int & nMsgLen);

	bool GetNextTagVal ( char *& szMsg, std::string& stTag, std::string& stVal);

	 bool BestMarketData (std::string& stMessage);
	 bool MarketByOrderData (std::string& stMessage);
	 bool MarketByPriceData (std::string& stMessage);	 

	 bool BestMarketData( char * szMsg );
	 bool MarketByOrderData( char * szMsg );
	 bool MarketByPriceData( char * szMsg );	

public:
	~CMessageParserTadawul(void);
private:
	private:
	int FindTagValueIndex (std::string tag, std::string& msg);
	std::set<int> setValidTags;
	std::set<int> setMBOTags;
	std::set<int> setMBPTags;
};
