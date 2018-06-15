#pragma once
#include "messageparser.h"
#include "ParsedMessage.h"
#include "MessageStorage.h"
#include "Constant.h"

#include "Queue.h"

struct STSectorInfo
{
	std::string stName;
	std::string stData;
};


class CMessageParserADSM : public IMessageParser
{
private:
	bool				bContinue;
	int					VerifyMessage(std::string);
	 int FindTagValueIndex (std::string tag, std::string& msg);
protected:
	//CMessageStorage m_MessageStorage;

public:
	CMessageParserADSM();
	~CMessageParserADSM();
	CParsedMessage ParseMessage(std::string _Message);

	void AddSymMktMsgPair(std::string & stSymbol, std::string & stMarket, MapTagVal& mpTagVal, std::string & stExStatsMsgToForward, std::string & stIndexLastValues);

	void GMTtoLocalTime (std::string& stTime);
	bool TagExists (std::string tag, std::string& msg);	
	bool TagExists_( char * szMsg, const std::string & stTag );

	bool GetNextTagVal (std::string& msg, std::string& stTag, std::string& stVal, int & nMsgCounter, int & nMsgLen);

	bool GetNextTagVal ( char *& szMsg, std::string& stTag, std::string& stVal);

	 bool BestMarketData (std::string& stMessage);
	 bool MarketByOrderData (std::string& stMessage);
	 bool MarketByPriceData (std::string& stMessage);
	 bool StateChangeData (std::string& stMessage);

	 bool BestMarketData( char * szMsg );
	 bool MarketByOrderData( char * szMsg );
	 bool MarketByPriceData( char * szMsg );
	 bool StateChangeData( char * szMsg );

	 bool IsSectorIndexTag (int tag) ;
	 bool IsIndexTag (int tag) ;

	 bool UpdateSectorInfo( STSectorInfo *, int tag, const std::string &, const std::string & );

	 bool IsSector1Tag (int tag);
	 bool IsSector2Tag (int tag);
	 bool IsSector3Tag (int tag);
	 bool IsSector4Tag (int tag);
	 bool IsSector5Tag (int tag);
	 bool IsSector6Tag (int tag);
	 bool IsSector7Tag (int tag);
	 bool IsSector8Tag (int tag);
	 bool IsSector9Tag (int tag);
	 bool IsSector10Tag (int tag);

	 bool IsExStatsToForwardTag(int nTag);
	 bool IsExStatsAdvanceTag(int tag);
	 bool IsExStatsDeclineTag(int tag);
	 bool IsExStatsUnchangedTag(int tag);

	 bool IsMktStatsAdvanceTag(int tag);
	 bool IsMktStatsDeclineTag(int tag);
	 bool IsMktStatsUnchangedTag(int tag);


	bool IsStateChangeMessage(char* stMdfMessage);

	//void publishMBPDataToClient( std::string &stKey, std::string &stData );
	//void publishMBODataToClient( std::string &stKey, std::string &stData );
	//int subscribeClientforMBPMBO( std::string &stClientRequest, std::string &stAddr );

public:
	std::string GetMBOBidTopTotalQtyPx( char * szMessage );
	std::string GetMBOAskTopTotalQtyPx( char * szMessage );
private:
	std::map<std::string, std::string> mpSectorTagIndexTag;

	std::set<int> setValidTags;
	std::set<int> setMBOTags;
	std::set<int> setMBPTags;
	std::set<int> setMktIndexTags;

	std::set<int> setSector1Tags;
	std::set<int> setSector2Tags;
	std::set<int> setSector3Tags;
	std::set<int> setSector4Tags;
	std::set<int> setSector5Tags;
	std::set<int> setSector6Tags;
	std::set<int> setSector7Tags;
	std::set<int> setSector8Tags;
	std::set<int> setSector9Tags;
	std::set<int> setSector10Tags;

	std::vector<int> vtExStatsToForwardTags;

};  