#pragma once

#include <xstring>
#include "Constant.h"

class CParsedMessage
{
public: 
	std::string			 _SeqNo;	
	ENMessageType		 _messageType;
	std::string			 _Exchange;
	std::string			 _Symbol;
	std::string			 _Market;
	std::string			 _LastVolume;
	std::string			 _LastPrice;
	std::string			 _PrevClose;
	std::string			 _AvgPrice;
	std::string			 _OpenPrice;
	std::string			 _HighPrice;
	std::string			 _LowPrice;
	std::string			 _TotalVolume;
	std::string			 _TotalTrades;
	std::string			 _TradeTime;
	std::string			 _52WeekHigh;
	std::string			 _52WeekLow;

	STMBOData 	m_MBOData;
	STMBPData	m_MBPData;

public: CParsedMessage(void);
public: ~CParsedMessage(void);
public: std::string GetXML(void);
public: std::string GetBinary(void);

};
