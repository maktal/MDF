#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "Constant.h"
//#include "LogFileHandler.h"
#include "MarketIndexDataContainer.h"
#include "MarketActivityDataContainer.h"
#include "ace/Recursive_Thread_Mutex.h" 


class CMessageStorage
{
public:
	CMessageStorage(void);
	~CMessageStorage(void);

	void AddRefreshData (std::string & stSymbol, std::string & stMarket, MapTagVal& mpTagVal, std::string& stExStats, std::string& stIndexLastValues);
	
	bool ContainsOnlyZero (std::string & str);

	void AddSymVolGraphData(std::string & stSymbol, std::string & stMarket, std::string & stTradeTime, std::string & stLastVol);
	bool GetSymbolVolGraphData(std::string& stSymMktKey, std::string& stSymVolGraphData);
	bool GetDaySymbolVolGraphData(std::string& stSymMktKey, std::string& stDay, std::string& stSymVolGraphData);
	bool GetHourSymbolVolGraphData(std::string& stSymMktKey, std::string& stDayHour, std::string& stSymVolGraphData);
	
	void AddSymPxGraphData(std::string & stSymbol, std::string & stMarket, std::string & stTradeTime, std::string & stLastPx);
	bool GetSymbolPxGraphData(std::string& stSymMktKey, std::string& stSymPxGraphData);
	bool GetDaySymbolPxGraphData(std::string& stSymMktKey, std::string& stDay, std::string& stSymPxGraphData);
	bool GetHourSymbolPxGraphData(std::string& stSymMktKey, std::string& stDayHour, std::string& stSymPxGraphData);
		
	void AddMarketVolGraphData(std::string & stMarket, std::string & stTradeTime, std::string & stLastVol);
	bool GetMarketVolGraphData(std::string& stMktKey, std::string& stMktGraphData);
	bool GetDayMarketVolGraphData(std::string& stMktKey, std::string& stDay, std::string& stMktGraphData);
	bool GetHourMarketVolGraphData(std::string& stMktKey, std::string& stDayHour, std::string& stMktGraphData);

	void AddMarketIndGraphData(std::string & stExchange, std::string & stTradeTime, std::string& stMktSector, std::string& stSectorIndex);
	bool GetDayHourMarketIndGraphData(std::string& stMktKey, std::string& stDayHour, std::string& stMktGraphData);
	bool GetDayMarketIndGraphData(std::string& stMktKey, std::string& stDay, std::string& stMktGraphData);

	void AddMBOData(std::string & stSymbol, std::string & stMarket, std::string& stData);
	bool GetMarketByOrderData(std::string& stSymMktKey, std::string& stData);

	void AddMBPData(std::string & stSymbol, std::string & stMarket, std::string& stData);
	bool GetMarketByPriceData(std::string& stSymMktKey, std::string& stData);

	void AddMarketStatusData(std::string & stMarket, std::string& stData);
	bool GetMarketStatusData(std::string & stMarket, std::string& stData);

	void AddMarketActivityData(std::string & stMarket, std::string& stData);
	bool GetMarketActivityData(std::string & stMarket, std::string& stData);

	void AddSectorActivityData(std::string & stExchange, std::string & stMktSector, std::string& stData);
	bool GetSectorActivityData(std::string & stMarketSector, std::string& stData);

	void AddExActivityData(std::string & stExchange, std::string& stData);
	bool GetExActivityData(std::string & stExchange, std::string& stData);

	bool GetLastMktVol (std::string& stExchange, std::string& stStatsData);

	void Refresh (std::vector<std::string>& vtMsgs);
	void RefreshStateChangeMsgs(std::vector<std::string>& vtMsgs);
	
	void AdsmDumpData (void* msg, int len);
	void SaveAdsmMsgToLog (std::string& stMessage, int len); 

	void DfmDumpData (void* msg, int len);
	void SaveDfmMsgToLog (std::string& stMessage, int len); 

	void TrimSecs (std::string& stTime);
	void ExtractHourMin (std::string& stTime, char*& stHour, char*& stMin);
	bool DayKeyPresent (std::string& stTime, std::string& stKey);
	bool DayHourKeyPresent (std::string& stTime, std::string& stKey);
	void ExtractMinVal (std::string& stTimeVal, std::string& stMinute, std::string& stValue);
	void ExtractHourVal (std::string& stTimeVal, std::string& stHour, std::string& stValue);
	
	//bool AdsmCacheRecovery (int& len, char*& pszMsg);
	//bool DfmCacheRecovery (int& len, char*& pszMsg);

	int AddStateChangeMessage(const char* stExchange, const char* stMdfMessage);
	
	int Init(std::vector<STIPEndPoint> vtIPEndPoints);
	int Close();

	int CacheRecovery();
private:
	ACE_Recursive_Thread_Mutex m_objStateChangeMutex;
	StateChangeTable m_mpStateChangeMsgs;	
	
	MapTagMsg m_mpTagMsg;//Key=Symbol/Market; Value = Msg
	
	MapSymMktGraphData m_mpSymVolGraph;//Key=Symbol/Market; Value = Vector<(Time, LastVol) tuple
	MapSymMktGraphData m_mpSymPxGraph;//Key=Symbol/Market; Value = Vector<(Time, LastPx) tuple

	MapMktStatsData m_mpMktVolGraph;//Key=Market; Value = Vector<(Time, LastVol) tuple

	CMarketIndexDataContainer m_MktIndexContainer;
	CMarketActivityDataContainer m_MktActivityContainer;

	MapTagVal m_mpMBOMsg;
	MapTagVal m_mpMBPMsg;

	MapTagVal m_mpMarketActivityMsg;
	MapTagVal m_mpExActivityMsg;
	MapTagVal m_mpMarketStatusMsg;

	std::map<std::string, std::string> m_mpExStatsMsg;
	std::map<std::string, std::string> m_mpIndexLastValues;	
	std::vector<STIPEndPoint> m_vtIPEndPoints;

};
#endif