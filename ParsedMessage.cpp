#include "ParsedMessage.h"

CParsedMessage::CParsedMessage(void)
{
		
			_SeqNo = "";
			_Exchange  = "";
			_Symbol = "";
			_Market = "";

			_LastVolume = "";
			_LastPrice = "";
			_PrevClose = "";
			_AvgPrice = "";
			_OpenPrice = "";
			_HighPrice = "";
			_LowPrice = "";
			_TotalVolume = "";	
			_TotalTrades = "";	
			_TradeTime = "";
			_52WeekHigh = "";
			_52WeekLow = "";

			m_MBOData._Symbol = "";
			m_MBOData._Market = "";
			m_MBOData._regBkAskOrder = "";
			m_MBOData._regBkAskTotalVol = "";
			m_MBOData._regBkAskPrice = "";	
			m_MBOData._AskOrdTotalVol1 = "";	
			 /*"<AskOrdPrice1>" + m_MBOData._AskOrdPrice1 + "</AskOrdPrice1>";		
			 "<AskOrdVol2>" + m_MBOData._AskOrdTotalVol2 + "</AskOrdVol2>";		
			 "<AskOrdPrice2>" + m_MBOData._AskOrdPrice2 + "</AskOrdPrice2>";		
			 "<AskOrdVol3>" + m_MBOData._AskOrdTotalVol3 + "</AskOrdVol3>";		
			 "<AskOrdPrice3>" + m_MBOData._AskOrdPrice3 + "</AskOrdPrice3>";		
			 "<AskOrdVol4>" + m_MBOData._AskOrdTotalVol4 + "</AskOrdVol4>";		
			 "<AskOrdPrice4>" + m_MBOData._AskOrdPrice4 + "</AskOrdPrice4>";		
			 "<AskOrdVol5>" + m_MBOData._AskOrdTotalVol5 + "</AskOrdVol5>";		
			 "<AskOrdPrice5>" + m_MBOData._AskOrdPrice5 + "</AskOrdPrice5>";		
			 "<AskOrdVol6>" + m_MBOData._AskOrdTotalVol6 + "</AskOrdVol6>";		
			 "<AskOrdPrice6>" + m_MBOData._AskOrdPrice6 + "</AskOrdPrice6>";		
			 "<AskOrdVol7>" + m_MBOData._AskOrdTotalVol7 + "</AskOrdVol7>";		
			 "<AskOrdPrice7>" + m_MBOData._AskOrdPrice7 + "</AskOrdPrice7>";		
			 "<AskOrdVol8>" + m_MBOData._AskOrdTotalVol8 + "</AskOrdVol8>";		
			 "<AskOrdPrice8>" + m_MBOData._AskOrdPrice8 + "</AskOrdPrice8>";		
			 "<AskOrdVol9>" + m_MBOData._AskOrdTotalVol9 + "</AskOrdVol9>";		
			 "<AskOrdPrice9>" + m_MBOData._AskOrdPrice9 + "</AskOrdPrice9>";		
				
			 "<BidOrder>" + m_MBOData._regBkBidOrder + "</BidOrder>";		
			 "<BidTotalVol>" + m_MBOData._regBkBidTotalVol + "</BidTotalVol>";		
			 "<BidPrice>" + m_MBOData._regBkBidPrice + "</BidPrice>";
			 "<BidOrdVol1 >" + m_MBOData._BidOrdTotalVol1 + "</BidOrdVol1 >";
			 "<BidOrdPrice1>" + m_MBOData._BidOrdPrice1 + "</BidOrdPrice1>";		
			 "<BidOrdVol2>" + m_MBOData._BidOrdTotalVol2 + "</BidOrdVol2>";
			 "<BidOrdPrice2>" + m_MBOData._BidOrdPrice2 + "</BidOrdPrice2>";
			 "<BidOrdVol3>" + m_MBOData._BidOrdTotalVol3 + "</BidOrdVol3>";
			 "<BidOrdPrice3>" + m_MBOData._BidOrdPrice3 + "</BidOrdPrice3>";
			 "<BidOrdVol4>" + m_MBOData._BidOrdTotalVol4 + "</BidOrdVol4>";
			 "<BidOrdPrice4>" + m_MBOData._BidOrdPrice4 + "</BidOrdPrice4>";
			 "<BidOrdVol5>" + m_MBOData._BidOrdTotalVol5 + "</BidOrdVol5>";
			 "<BidOrdPrice5>" + m_MBOData._BidOrdPrice5 + "</BidOrdPrice5>";
			 "<BidOrdVol6>" + m_MBOData._BidOrdTotalVol6 + "</BidOrdVol6>";
			 "<BidOrdPrice6>" + m_MBOData._BidOrdPrice6 + "</BidOrdPrice6>";
			 "<BidOrdVol7>" + m_MBOData._BidOrdTotalVol7 + "</BidOrdVol7>";
			 "<BidOrdPrice7>" + m_MBOData._BidOrdPrice7 + "</BidOrdPrice7>";
			 "<BidOrdVol8>" + m_MBOData._BidOrdTotalVol8 + "</BidOrdVol8>";
			 "<BidOrdPrice8>" + m_MBOData._BidOrdPrice8 + "</BidOrdPrice8>";
			 "<BidOrdVol9>" + m_MBOData._BidOrdTotalVol9 + "</BidOrdVol9>";
			 "<BidOrdPrice9>" + m_MBOData._BidOrdPrice9 + "</BidOrdPrice9>";		*/

		m_MBPData._Symbol = "";
		m_MBPData._Market = "";		
			 /*"<BidPriceCnt>" + m_MBPData._BidPriceCount+ "</BidPriceCnt>";		
			 "<BidPriceL1>" + m_MBPData._BidPriceLevel1 + "</BidPriceL1>";		
			 "<BidOrderL1>" + m_MBPData._BidOrderLevel1 + "</BidOrderL1>";		
			 "<BidVolL1>" + m_MBPData._BidVolLevel1 + "</BidVolL1>";		
			 "<BidPriceL2>" + m_MBPData._BidPriceLevel2 + "</BidPriceL2>";
			 "<BidOrderL2>" + m_MBPData._BidOrderLevel2 + "</BidOrderL2>";
			 "<BidVolL2>" + m_MBPData._BidVolLevel2 + "</BidVolL2>";
			 "<BidPriceL3>" + m_MBPData._BidPriceLevel3 + "</BidPriceL3>";
			 "<BidOrderL3>" + m_MBPData._BidOrderLevel3 + "</BidOrderL3>";
			 "<BidVolL3>" + m_MBPData._BidVolLevel3 + "</BidVolL3>";
			 "<BidPriceL4>" + m_MBPData._BidPriceLevel4 + "</BidPriceL4>";
			 "<BidOrderL4>" + m_MBPData._BidOrderLevel4 + "</BidOrderL4>";
			 "<BidVolL4>" + m_MBPData._BidVolLevel4 + "</BidVolL4>";
			 "<BidPriceL5>" + m_MBPData._BidPriceLevel5 + "</BidPriceL5>";
			 "<BidOrderL5>" + m_MBPData._BidOrderLevel5 + "</BidOrderL5>";
			 "<BidVolL5>" + m_MBPData._BidVolLevel5 + "</BidVolL5>";		
			 "<AskPriceCnt>" + m_MBPData._AskPriceCount+ "</AskPriceCnt>";		
			 "<AskPriceL1>" + m_MBPData._AskPriceLevel1 + "</AskPriceL1>";		
			 "<AskOrderL1>" + m_MBPData._AskOrderLevel1 + "</AskOrderL1>";		
			 "<AskVolL1>" + m_MBPData._AskVolLevel1 + "</AskVolL1>";		
			 "<AskPriceL2>" + m_MBPData._AskPriceLevel2 + "</AskPriceL2>";		
			 "<AskOrderL2>" + m_MBPData._AskOrderLevel2 + "</AskOrderL2>";		
			 "<AskVolL2>" + m_MBPData._AskVolLevel2 + "</AskVolL2>";		
			 "<AskPriceL3>" + m_MBPData._AskPriceLevel3 + "</AskPriceL3>";		
			 "<AskOrderL3>" + m_MBPData._AskOrderLevel3 + "</AskOrderL3>";		
			 "<AskVolL3>" + m_MBPData._AskVolLevel3 + "</AskVolL3>";		
			 "<AskPriceL4>" + m_MBPData._AskPriceLevel4 + "</AskPriceL4>";		
			 "<AskOrderL4>" + m_MBPData._AskOrderLevel4 + "</AskOrderL4>";		
			 "<AskVolL4>" + m_MBPData._AskVolLevel4 + "</AskVolL4>";		
			 "<AskPriceL5>" + m_MBPData._AskPriceLevel5 + "</AskPriceL5>";		
			 "<AskOrderL5>" + m_MBPData._AskOrderLevel5 + "</AskOrderL5>";		
			 "<AskVolL5>" + m_MBPData._AskVolLevel5 + "</AskVolL5>";		*/
}

CParsedMessage::~CParsedMessage(void)
{
}

std::string CParsedMessage::GetXML( void )
{
	std::string m_XMLString;
	char m_DQoute = char(34);
	switch (_messageType)
	{
	case FEED: 	
		m_XMLString = "<Exchange ID = \"" + _Exchange  + "\" MsgType = \"Feed\" SeqNo = \"" + _SeqNo + "\" >";
		m_XMLString += "<Symbol>" + _Symbol + "</Symbol>";
		m_XMLString += "<Market>" + _Market + "</Market>";
		if (_LastVolume != "0" && _LastVolume != "")		
			m_XMLString += "<LastVol>" + _LastVolume + "</LastVol>";
		if (_LastPrice != "0" && _LastPrice != "")		
			m_XMLString += "<LastPrice>" + _LastPrice + "</LastPrice>";
		if (_PrevClose != "0" && _PrevClose != "")		
			m_XMLString += "<PrevClose>" + _PrevClose + "</PrevClose>";
		if (_AvgPrice != "0" && _AvgPrice != "")		
			m_XMLString += "<AvgPrice>" + _AvgPrice + "</AvgPrice>";
		if (_OpenPrice != "0" && _OpenPrice != "")		
			m_XMLString += "<OpenPrice>" + _OpenPrice + "</OpenPrice>";
		if (_HighPrice != "0" && _HighPrice != "")		
			m_XMLString += "<HighPrice>" + _HighPrice + "</HighPrice>";
		if (_LowPrice != "0" && _LowPrice != "")		
			m_XMLString += "<LowPrice>" + _LowPrice + "</LowPrice>";
		if (_TotalVolume != "0" && _TotalVolume != "")		
			m_XMLString += "<TotalVolume>" + _TotalVolume + "</TotalVolume>";
		if (_TotalTrades != "0" && _TotalTrades != "")		
			m_XMLString += "<TotalTrades>" + _TotalTrades + "</TotalTrades>";
		if (_TradeTime != "0" && _TradeTime != "")		
			m_XMLString += "<TradeTime>" + _TradeTime + "</TradeTime>";
		if (_52WeekHigh != "0" && _52WeekHigh != "")		
			m_XMLString += "<WeekHigh52>" + _52WeekHigh + "</WeekHigh52>";
		if (_52WeekLow != "0" && _52WeekLow != "")		
			m_XMLString += "<WeekLow52>" + _52WeekLow + "</WeekLow52>";
		m_XMLString += "</Exchange>";
		break;

	case MBO:		
		m_XMLString = "<Exchange ID = \"" + _Exchange  + "\" MsgType = \"MBO\" SeqNo = \"" + _SeqNo + "\" >";
		m_XMLString += "<Symbol>" + m_MBOData._Symbol + "</Symbol>";
		m_XMLString += "<Market>" + m_MBOData._Market + "</Market>";
		if (m_MBOData._regBkAskOrder != "0" && m_MBOData._regBkAskOrder != "")
			m_XMLString += "<AskOrder>" + m_MBOData._regBkAskOrder+ "</AskOrder>";
		if (m_MBOData._regBkAskTotalVol != "0" && m_MBOData._regBkAskTotalVol != "")
			m_XMLString += "<AskTotalVol>" + m_MBOData._regBkAskTotalVol + "</AskTotalVol>";
		if (m_MBOData._regBkAskPrice != "0" && m_MBOData._regBkAskPrice != "")
			m_XMLString += "<AskPrice>" + m_MBOData._regBkAskPrice + "</AskPrice>";
		if (m_MBOData._AskOrdTotalVol1 != "0" && m_MBOData._AskOrdTotalVol1 != "")
			m_XMLString += "<AskOrdVol1>" + m_MBOData._AskOrdTotalVol1 + "</AskOrdVol1>";
		if (m_MBOData._AskOrdPrice1 != "0" && m_MBOData._AskOrdPrice1 != "")
			m_XMLString += "<AskOrdPrice1>" + m_MBOData._AskOrdPrice1 + "</AskOrdPrice1>";
		if (m_MBOData._AskOrdTotalVol2 != "0" && m_MBOData._AskOrdTotalVol2 != "")
			m_XMLString += "<AskOrdVol2>" + m_MBOData._AskOrdTotalVol2 + "</AskOrdVol2>";
		if (m_MBOData._AskOrdPrice2 != "0" && m_MBOData._AskOrdPrice2 != "")
			m_XMLString += "<AskOrdPrice2>" + m_MBOData._AskOrdPrice2 + "</AskOrdPrice2>";
		if (m_MBOData._AskOrdTotalVol3 != "0" && m_MBOData._AskOrdTotalVol3 != "")
			m_XMLString += "<AskOrdVol3>" + m_MBOData._AskOrdTotalVol3 + "</AskOrdVol3>";
		if (m_MBOData._AskOrdPrice3 != "0" && m_MBOData._AskOrdPrice3 != "")
			m_XMLString += "<AskOrdPrice3>" + m_MBOData._AskOrdPrice3 + "</AskOrdPrice3>";
		if (m_MBOData._AskOrdTotalVol4 != "0" && m_MBOData._AskOrdTotalVol4 != "")
			m_XMLString += "<AskOrdVol4>" + m_MBOData._AskOrdTotalVol4 + "</AskOrdVol4>";
		if (m_MBOData._AskOrdPrice4 != "0" && m_MBOData._AskOrdPrice4 != "")
			m_XMLString += "<AskOrdPrice4>" + m_MBOData._AskOrdPrice4 + "</AskOrdPrice4>";
		if (m_MBOData._AskOrdTotalVol5 != "0" && m_MBOData._AskOrdTotalVol5 != "")
			m_XMLString += "<AskOrdVol5>" + m_MBOData._AskOrdTotalVol5 + "</AskOrdVol5>";
		if (m_MBOData._AskOrdPrice5 != "0" && m_MBOData._AskOrdPrice5 != "")
			m_XMLString += "<AskOrdPrice5>" + m_MBOData._AskOrdPrice5 + "</AskOrdPrice5>";
		if (m_MBOData._AskOrdTotalVol6 != "0" && m_MBOData._AskOrdTotalVol6 != "")
			m_XMLString += "<AskOrdVol6>" + m_MBOData._AskOrdTotalVol6 + "</AskOrdVol6>";
		if (m_MBOData._AskOrdPrice6 != "0" && m_MBOData._AskOrdPrice6 != "")
			m_XMLString += "<AskOrdPrice6>" + m_MBOData._AskOrdPrice6 + "</AskOrdPrice6>";
		if (m_MBOData._AskOrdTotalVol7 != "0" && m_MBOData._AskOrdTotalVol7 != "")
			m_XMLString += "<AskOrdVol7>" + m_MBOData._AskOrdTotalVol7 + "</AskOrdVol7>";
		if (m_MBOData._AskOrdPrice7 != "0" && m_MBOData._AskOrdPrice7 != "")
			m_XMLString += "<AskOrdPrice7>" + m_MBOData._AskOrdPrice7 + "</AskOrdPrice7>";
		if (m_MBOData._AskOrdTotalVol8 != "0" && m_MBOData._AskOrdTotalVol8 != "")
			m_XMLString += "<AskOrdVol8>" + m_MBOData._AskOrdTotalVol8 + "</AskOrdVol8>";
		if (m_MBOData._AskOrdPrice8 != "0" && m_MBOData._AskOrdPrice8 != "")
			m_XMLString += "<AskOrdPrice8>" + m_MBOData._AskOrdPrice8 + "</AskOrdPrice8>";
		if (m_MBOData._AskOrdTotalVol9 != "0" && m_MBOData._AskOrdTotalVol9 != "")
			m_XMLString += "<AskOrdVol9>" + m_MBOData._AskOrdTotalVol9 + "</AskOrdVol9>";
		if (m_MBOData._AskOrdPrice9 != "0" && m_MBOData._AskOrdPrice9 != "")
			m_XMLString += "<AskOrdPrice9>" + m_MBOData._AskOrdPrice9 + "</AskOrdPrice9>";		
		
		if (m_MBOData._regBkBidOrder != "0" && m_MBOData._regBkBidOrder != "") 
			m_XMLString += "<BidOrder>" + m_MBOData._regBkBidOrder + "</BidOrder>";
		if (m_MBOData._regBkBidTotalVol != "0" && m_MBOData._regBkBidTotalVol != "") 
			m_XMLString += "<BidTotalVol>" + m_MBOData._regBkBidTotalVol + "</BidTotalVol>";
		if (m_MBOData._regBkBidPrice != "0" && m_MBOData._regBkBidPrice != "")
			m_XMLString += "<BidPrice>" + m_MBOData._regBkBidPrice + "</BidPrice>";
		if (m_MBOData._BidOrdTotalVol1 != "0" && m_MBOData._BidOrdTotalVol1 != "")
			m_XMLString += "<BidOrdVol1 >" + m_MBOData._BidOrdTotalVol1 + "</BidOrdVol1 >";
		if (m_MBOData._BidOrdPrice1 != "0" && m_MBOData._BidOrdPrice1 != "")
			m_XMLString += "<BidOrdPrice1>" + m_MBOData._BidOrdPrice1 + "</BidOrdPrice1>";
		if (m_MBOData._BidOrdTotalVol2 != "0" && m_MBOData._BidOrdTotalVol2 != "")
			m_XMLString += "<BidOrdVol2>" + m_MBOData._BidOrdTotalVol2 + "</BidOrdVol2>";
		if (m_MBOData._BidOrdPrice2 != "0" && m_MBOData._BidOrdPrice2 != "")
			m_XMLString += "<BidOrdPrice2>" + m_MBOData._BidOrdPrice2 + "</BidOrdPrice2>";
		if (m_MBOData._BidOrdTotalVol3 != "0" && m_MBOData._BidOrdTotalVol3 != "")
			m_XMLString += "<BidOrdVol3>" + m_MBOData._BidOrdTotalVol3 + "</BidOrdVol3>";
		if (m_MBOData._BidOrdPrice3 != "0" && m_MBOData._BidOrdPrice3 != "")
			m_XMLString += "<BidOrdPrice3>" + m_MBOData._BidOrdPrice3 + "</BidOrdPrice3>";
		if (m_MBOData._BidOrdTotalVol4 != "0" && m_MBOData._BidOrdTotalVol4 != "")
			m_XMLString += "<BidOrdVol4>" + m_MBOData._BidOrdTotalVol4 + "</BidOrdVol4>";
		if (m_MBOData._BidOrdPrice4 != "0" && m_MBOData._BidOrdPrice4 != "")
			m_XMLString += "<BidOrdPrice4>" + m_MBOData._BidOrdPrice4 + "</BidOrdPrice4>";
		if (m_MBOData._BidOrdTotalVol5 != "0" && m_MBOData._BidOrdTotalVol5 != "")
			m_XMLString += "<BidOrdVol5>" + m_MBOData._BidOrdTotalVol5 + "</BidOrdVol5>";
		if (m_MBOData._BidOrdPrice5 != "0" && m_MBOData._BidOrdPrice5 != "")
			m_XMLString += "<BidOrdPrice5>" + m_MBOData._BidOrdPrice5 + "</BidOrdPrice5>";
		if (m_MBOData._BidOrdTotalVol6 != "0" && m_MBOData._BidOrdTotalVol6 != "")
			m_XMLString += "<BidOrdVol6>" + m_MBOData._BidOrdTotalVol6 + "</BidOrdVol6>";
		if (m_MBOData._BidOrdPrice6 != "0" && m_MBOData._BidOrdPrice6 != "")
			m_XMLString += "<BidOrdPrice6>" + m_MBOData._BidOrdPrice6 + "</BidOrdPrice6>";
		if (m_MBOData._BidOrdTotalVol7 != "0" && m_MBOData._BidOrdTotalVol7 != "")
			m_XMLString += "<BidOrdVol7>" + m_MBOData._BidOrdTotalVol7 + "</BidOrdVol7>";
		if (m_MBOData._BidOrdPrice7 != "0" && m_MBOData._BidOrdPrice7 != "")
			m_XMLString += "<BidOrdPrice7>" + m_MBOData._BidOrdPrice7 + "</BidOrdPrice7>";
		if (m_MBOData._BidOrdTotalVol8 != "0" && m_MBOData._BidOrdTotalVol8 != "")
			m_XMLString += "<BidOrdVol8>" + m_MBOData._BidOrdTotalVol8 + "</BidOrdVol8>";
		if (m_MBOData._BidOrdPrice8 != "0" && m_MBOData._BidOrdPrice8 != "")
			m_XMLString += "<BidOrdPrice8>" + m_MBOData._BidOrdPrice8 + "</BidOrdPrice8>";
		if (m_MBOData._BidOrdTotalVol9 != "0" && m_MBOData._BidOrdTotalVol9 != "")
			m_XMLString += "<BidOrdVol9>" + m_MBOData._BidOrdTotalVol9 + "</BidOrdVol9>";
		if (m_MBOData._BidOrdPrice9 != "0" && m_MBOData._BidOrdPrice9 != "")
			m_XMLString += "<BidOrdPrice9>" + m_MBOData._BidOrdPrice9 + "</BidOrdPrice9>";		
		m_XMLString += "</Exchange>";
		break;

	case MBP:		
		m_XMLString = "<Exchange ID = \"" + _Exchange  + "\" MsgType = \"MBP\" SeqNo = \"" + _SeqNo + "\" >";
		m_XMLString += "<Symbol>" + m_MBPData._Symbol + "</Symbol>";
		m_XMLString += "<Market>" + m_MBPData._Market + "</Market>";
		if (m_MBPData._BidPriceCount != "0")
			m_XMLString += "<BidPriceCnt>" + m_MBPData._BidPriceCount+ "</BidPriceCnt>";
		if (m_MBPData._BidPriceLevel1 != "0")
			m_XMLString += "<BidPriceL1>" + m_MBPData._BidPriceLevel1 + "</BidPriceL1>";
		if (m_MBPData._BidOrderLevel1 != "0")
			m_XMLString += "<BidOrderL1>" + m_MBPData._BidOrderLevel1 + "</BidOrderL1>";
		if (m_MBPData._BidVolLevel1 != "0")
			m_XMLString += "<BidVolL1>" + m_MBPData._BidVolLevel1 + "</BidVolL1>";
		if (m_MBPData._BidPriceLevel2 != "0")
			m_XMLString += "<BidPriceL2>" + m_MBPData._BidPriceLevel2 + "</BidPriceL2>";
		if (m_MBPData._BidOrderLevel2 != "0")
			m_XMLString += "<BidOrderL2>" + m_MBPData._BidOrderLevel2 + "</BidOrderL2>";
		if (m_MBPData._BidVolLevel2 != "0")
			m_XMLString += "<BidVolL2>" + m_MBPData._BidVolLevel2 + "</BidVolL2>";
		if (m_MBPData._BidPriceLevel3 != "0")
			m_XMLString += "<BidPriceL3>" + m_MBPData._BidPriceLevel3 + "</BidPriceL3>";
		if (m_MBPData._BidOrderLevel3 != "0")
			m_XMLString += "<BidOrderL3>" + m_MBPData._BidOrderLevel3 + "</BidOrderL3>";
		if (m_MBPData._BidVolLevel3 != "0")
			m_XMLString += "<BidVolL3>" + m_MBPData._BidVolLevel3 + "</BidVolL3>";
		if (m_MBPData._BidPriceLevel4 != "0")
			m_XMLString += "<BidPriceL4>" + m_MBPData._BidPriceLevel4 + "</BidPriceL4>";
		if (m_MBPData._BidOrderLevel4 != "0")
			m_XMLString += "<BidOrderL4>" + m_MBPData._BidOrderLevel4 + "</BidOrderL4>";
		if (m_MBPData._BidVolLevel4 != "0")
			m_XMLString += "<BidVolL4>" + m_MBPData._BidVolLevel4 + "</BidVolL4>";
		if (m_MBPData._BidPriceLevel5 != "0")
			m_XMLString += "<BidPriceL5>" + m_MBPData._BidPriceLevel5 + "</BidPriceL5>";
		if (m_MBPData._BidOrderLevel5 != "0")
			m_XMLString += "<BidOrderL5>" + m_MBPData._BidOrderLevel5 + "</BidOrderL5>";
		if (m_MBPData._BidVolLevel5 != "0")
			m_XMLString += "<BidVolL5>" + m_MBPData._BidVolLevel5 + "</BidVolL5>";

		if (m_MBPData._AskPriceCount != "0")
			m_XMLString += "<AskPriceCnt>" + m_MBPData._AskPriceCount+ "</AskPriceCnt>";
		if (m_MBPData._AskPriceLevel1 != "0")
			m_XMLString += "<AskPriceL1>" + m_MBPData._AskPriceLevel1 + "</AskPriceL1>";
		if (m_MBPData._AskOrderLevel1 != "0")
			m_XMLString += "<AskOrderL1>" + m_MBPData._AskOrderLevel1 + "</AskOrderL1>";
		if (m_MBPData._AskVolLevel1 != "0")
			m_XMLString += "<AskVolL1>" + m_MBPData._AskVolLevel1 + "</AskVolL1>";
		if (m_MBPData._AskPriceLevel2 != "0")
			m_XMLString += "<AskPriceL2>" + m_MBPData._AskPriceLevel2 + "</AskPriceL2>";
		if (m_MBPData._AskOrderLevel2 != "0")
			m_XMLString += "<AskOrderL2>" + m_MBPData._AskOrderLevel2 + "</AskOrderL2>";
		if (m_MBPData._AskVolLevel2 != "0")
			m_XMLString += "<AskVolL2>" + m_MBPData._AskVolLevel2 + "</AskVolL2>";
		if (m_MBPData._AskPriceLevel3 != "0")
			m_XMLString += "<AskPriceL3>" + m_MBPData._AskPriceLevel3 + "</AskPriceL3>";
		if (m_MBPData._AskOrderLevel3 != "0")
			m_XMLString += "<AskOrderL3>" + m_MBPData._AskOrderLevel3 + "</AskOrderL3>";
		if (m_MBPData._AskVolLevel3 != "0")
			m_XMLString += "<AskVolL3>" + m_MBPData._AskVolLevel3 + "</AskVolL3>";
		if (m_MBPData._AskPriceLevel4 != "0")
			m_XMLString += "<AskPriceL4>" + m_MBPData._AskPriceLevel4 + "</AskPriceL4>";
		if (m_MBPData._AskOrderLevel4 != "0")
			m_XMLString += "<AskOrderL4>" + m_MBPData._AskOrderLevel4 + "</AskOrderL4>";
		if (m_MBPData._AskVolLevel4 != "0")
			m_XMLString += "<AskVolL4>" + m_MBPData._AskVolLevel4 + "</AskVolL4>";
		if (m_MBPData._AskPriceLevel5 != "0")
			m_XMLString += "<AskPriceL5>" + m_MBPData._AskPriceLevel5 + "</AskPriceL5>";
		if (m_MBPData._AskOrderLevel5 != "0")
			m_XMLString += "<AskOrderL5>" + m_MBPData._AskOrderLevel5 + "</AskOrderL5>";
		if (m_MBPData._AskVolLevel5 != "0")
			m_XMLString += "<AskVolL5>" + m_MBPData._AskVolLevel5 + "</AskVolL5>";		
		m_XMLString += "</Exchange>";
		break;

	default:
		m_XMLString = "<Exchange></Exchange>";
		break;
	}

	if (_SeqNo.empty())
		m_XMLString = "";
	return m_XMLString;

} 

std::string CParsedMessage::GetBinary( void )
{
	std::string _BinaryValue;
	switch (_messageType)
	{
	case FEED: 	
		_BinaryValue = "FEED:";
		_BinaryValue += "SeqNo=" + _SeqNo + ";";
		_BinaryValue += "Symbol=" + _Symbol + ";";
		_BinaryValue += "Market=" + _Market + ";";
		if (_LastVolume != "0" && _LastVolume != "")		
			_BinaryValue += "LastVol=" + _LastVolume + ";";
		if (_LastPrice != "0" && _LastPrice != "")		
			_BinaryValue += "LastPrice=" + _LastPrice + ";";
		if (_PrevClose != "0" && _PrevClose != "")		
			_BinaryValue += "PrevClose=" + _PrevClose + ";";
		if (_AvgPrice != "0" && _AvgPrice != "")		
			_BinaryValue += "AvgPrice=" + _AvgPrice + ";";
		if (_OpenPrice != "0" && _OpenPrice != "")		
			_BinaryValue += "OpenPrice=" + _OpenPrice + ";";
		if (_HighPrice != "0" && _HighPrice != "")		
			_BinaryValue += "HighPrice=" + _HighPrice + ";";
		if (_LowPrice != "0" && _LowPrice != "")		
			_BinaryValue += "LowPrice=" + _LowPrice + ";";
		if (_TotalVolume != "0" && _TotalVolume != "")		
			_BinaryValue += "TotalVolume=" + _TotalVolume + ";";
		if (_TotalTrades != "0" && _TotalTrades != "")		
			_BinaryValue += "TotalTrades=" + _TotalTrades + ";";
		if (_TradeTime != "0" && _TradeTime != "")		
			_BinaryValue += "TradeTime=" + _TradeTime + ";";
		if (_52WeekHigh != "0" && _52WeekHigh != "")		
			_BinaryValue += "WeekHigh52=" + _52WeekHigh + ";";
		if (_52WeekLow != "0" && _52WeekLow != "")		
			_BinaryValue += "WeekLow52=" + _52WeekLow + ";";		
		break;

	case MBO:
		_BinaryValue = "MBO:";
		_BinaryValue += "SeqNo=" + _SeqNo + ";";
		_BinaryValue += "Symbol=" + m_MBOData._Symbol + ";";
		_BinaryValue += "Market=" + m_MBOData._Market + ";";
		if (m_MBOData._regBkAskOrder != "0" && m_MBOData._regBkAskOrder != "")
			_BinaryValue += "AskOrder=" + m_MBOData._regBkAskOrder+ ";";
		if (m_MBOData._regBkAskTotalVol != "0" && m_MBOData._regBkAskTotalVol != "")
			_BinaryValue += "AskTotalVol=" + m_MBOData._regBkAskTotalVol + ";";
		if (m_MBOData._regBkAskPrice != "0" && m_MBOData._regBkAskPrice != "")
			_BinaryValue += "AskPrice=" + m_MBOData._regBkAskPrice + ";";
		if (m_MBOData._AskOrdTotalVol1 != "0" && m_MBOData._AskOrdTotalVol1 != "")
			_BinaryValue += "AskOrdVol1=" + m_MBOData._AskOrdTotalVol1 + ";";
		if (m_MBOData._AskOrdPrice1 != "0" && m_MBOData._AskOrdPrice1 != "")
			_BinaryValue += "AskOrdPrice1=" + m_MBOData._AskOrdPrice1 + ";";
		if (m_MBOData._AskOrdTotalVol2 != "0" && m_MBOData._AskOrdTotalVol2 != "")
			_BinaryValue += "AskOrdVol2=" + m_MBOData._AskOrdTotalVol2 + ";";
		if (m_MBOData._AskOrdPrice2 != "0" && m_MBOData._AskOrdPrice2 != "")
			_BinaryValue += "AskOrdPrice2=" + m_MBOData._AskOrdPrice2 + ";";
		if (m_MBOData._AskOrdTotalVol3 != "0" && m_MBOData._AskOrdTotalVol3 != "")
			_BinaryValue += "AskOrdVol3=" + m_MBOData._AskOrdTotalVol3 + ";";
		if (m_MBOData._AskOrdPrice3 != "0" && m_MBOData._AskOrdPrice3 != "")
			_BinaryValue += "AskOrdPrice3=" + m_MBOData._AskOrdPrice3 + ";";
		if (m_MBOData._AskOrdTotalVol4 != "0" && m_MBOData._AskOrdTotalVol4 != "")
			_BinaryValue += "AskOrdVol4=" + m_MBOData._AskOrdTotalVol4 + ";";
		if (m_MBOData._AskOrdPrice4 != "0" && m_MBOData._AskOrdPrice4 != "")
			_BinaryValue += "AskOrdPrice4=" + m_MBOData._AskOrdPrice4 + ";";
		if (m_MBOData._AskOrdTotalVol5 != "0" && m_MBOData._AskOrdTotalVol5 != "")
			_BinaryValue += "AskOrdVol5=" + m_MBOData._AskOrdTotalVol5 + ";";
		if (m_MBOData._AskOrdPrice5 != "0" && m_MBOData._AskOrdPrice5 != "")
			_BinaryValue += "AskOrdPrice5=" + m_MBOData._AskOrdPrice5 + ";";
		if (m_MBOData._AskOrdTotalVol6 != "0" && m_MBOData._AskOrdTotalVol6 != "")
			_BinaryValue += "AskOrdVol6=" + m_MBOData._AskOrdTotalVol6 + ";";
		if (m_MBOData._AskOrdPrice6 != "0" && m_MBOData._AskOrdPrice6 != "")
			_BinaryValue += "AskOrdPrice6=" + m_MBOData._AskOrdPrice6 + ";";
		if (m_MBOData._AskOrdTotalVol7 != "0" && m_MBOData._AskOrdTotalVol7 != "")
			_BinaryValue += "AskOrdVol7=" + m_MBOData._AskOrdTotalVol7 + ";";
		if (m_MBOData._AskOrdPrice7 != "0" && m_MBOData._AskOrdPrice7 != "")
			_BinaryValue += "AskOrdPrice7=" + m_MBOData._AskOrdPrice7 + ";";
		if (m_MBOData._AskOrdTotalVol8 != "0" && m_MBOData._AskOrdTotalVol8 != "")
			_BinaryValue += "AskOrdVol8=" + m_MBOData._AskOrdTotalVol8 + ";";
		if (m_MBOData._AskOrdPrice8 != "0" && m_MBOData._AskOrdPrice8 != "")
			_BinaryValue += "AskOrdPrice8=" + m_MBOData._AskOrdPrice8 + ";";
		if (m_MBOData._AskOrdTotalVol9 != "0" && m_MBOData._AskOrdTotalVol9 != "")
			_BinaryValue += "AskOrdVol9=" + m_MBOData._AskOrdTotalVol9 + ";";
		if (m_MBOData._AskOrdPrice9 != "0" && m_MBOData._AskOrdPrice9 != "")
			_BinaryValue += "AskOrdPrice9=" + m_MBOData._AskOrdPrice9 + ";";		
		
		if (m_MBOData._regBkBidOrder != "0" && m_MBOData._regBkBidOrder != "") 
			_BinaryValue += "BidOrder=" + m_MBOData._regBkBidOrder + ";";
		if (m_MBOData._regBkBidTotalVol != "0" && m_MBOData._regBkBidTotalVol != "") 
			_BinaryValue += "BidTotalVol=" + m_MBOData._regBkBidTotalVol + ";";
		if (m_MBOData._regBkBidPrice != "0" && m_MBOData._regBkBidPrice != "")
			_BinaryValue += "BidPrice=" + m_MBOData._regBkBidPrice + ";";
		if (m_MBOData._BidOrdTotalVol1 != "0" && m_MBOData._BidOrdTotalVol1 != "")
			_BinaryValue += "BidOrdVol1 =" + m_MBOData._BidOrdTotalVol1 + ";";
		if (m_MBOData._BidOrdPrice1 != "0" && m_MBOData._BidOrdPrice1 != "")
			_BinaryValue += "BidOrdPrice1=" + m_MBOData._BidOrdPrice1 + ";";
		if (m_MBOData._BidOrdTotalVol2 != "0" && m_MBOData._BidOrdTotalVol2 != "")
			_BinaryValue += "BidOrdVol2=" + m_MBOData._BidOrdTotalVol2 + ";";
		if (m_MBOData._BidOrdPrice2 != "0" && m_MBOData._BidOrdPrice2 != "")
			_BinaryValue += "BidOrdPrice2=" + m_MBOData._BidOrdPrice2 + ";";
		if (m_MBOData._BidOrdTotalVol3 != "0" && m_MBOData._BidOrdTotalVol3 != "")
			_BinaryValue += "BidOrdVol3=" + m_MBOData._BidOrdTotalVol3 + ";";
		if (m_MBOData._BidOrdPrice3 != "0" && m_MBOData._BidOrdPrice3 != "")
			_BinaryValue += "BidOrdPrice3=" + m_MBOData._BidOrdPrice3 + ";";
		if (m_MBOData._BidOrdTotalVol4 != "0" && m_MBOData._BidOrdTotalVol4 != "")
			_BinaryValue += "BidOrdVol4=" + m_MBOData._BidOrdTotalVol4 + ";";
		if (m_MBOData._BidOrdPrice4 != "0" && m_MBOData._BidOrdPrice4 != "")
			_BinaryValue += "BidOrdPrice4=" + m_MBOData._BidOrdPrice4 + ";";
		if (m_MBOData._BidOrdTotalVol5 != "0" && m_MBOData._BidOrdTotalVol5 != "")
			_BinaryValue += "BidOrdVol5=" + m_MBOData._BidOrdTotalVol5 + ";";
		if (m_MBOData._BidOrdPrice5 != "0" && m_MBOData._BidOrdPrice5 != "")
			_BinaryValue += "BidOrdPrice5=" + m_MBOData._BidOrdPrice5 + ";";
		if (m_MBOData._BidOrdTotalVol6 != "0" && m_MBOData._BidOrdTotalVol6 != "")
			_BinaryValue += "BidOrdVol6=" + m_MBOData._BidOrdTotalVol6 + ";";
		if (m_MBOData._BidOrdPrice6 != "0" && m_MBOData._BidOrdPrice6 != "")
			_BinaryValue += "BidOrdPrice6=" + m_MBOData._BidOrdPrice6 + ";";
		if (m_MBOData._BidOrdTotalVol7 != "0" && m_MBOData._BidOrdTotalVol7 != "")
			_BinaryValue += "BidOrdVol7=" + m_MBOData._BidOrdTotalVol7 + ";";
		if (m_MBOData._BidOrdPrice7 != "0" && m_MBOData._BidOrdPrice7 != "")
			_BinaryValue += "BidOrdPrice7=" + m_MBOData._BidOrdPrice7 + ";";
		if (m_MBOData._BidOrdTotalVol8 != "0" && m_MBOData._BidOrdTotalVol8 != "")
			_BinaryValue += "BidOrdVol8=" + m_MBOData._BidOrdTotalVol8 + ";";
		if (m_MBOData._BidOrdPrice8 != "0" && m_MBOData._BidOrdPrice8 != "")
			_BinaryValue += "BidOrdPrice8=" + m_MBOData._BidOrdPrice8 + ";";
		if (m_MBOData._BidOrdTotalVol9 != "0" && m_MBOData._BidOrdTotalVol9 != "")
			_BinaryValue += "BidOrdVol9=" + m_MBOData._BidOrdTotalVol9 + ";";
		if (m_MBOData._BidOrdPrice9 != "0" && m_MBOData._BidOrdPrice9 != "")
			_BinaryValue += "BidOrdPrice9=" + m_MBOData._BidOrdPrice9 + ";";				
		break;

	case MBP:
		_BinaryValue = "MBP:";
		_BinaryValue += "SeqNo=" + _SeqNo + ";";
		_BinaryValue += "Symbol=" + m_MBPData._Symbol + ";";
		_BinaryValue += "Market=" + m_MBPData._Market + ";";
		if (m_MBPData._BidPriceCount != "0")
			_BinaryValue += "BidPriceCnt=" + m_MBPData._BidPriceCount+ ";";
		if (m_MBPData._BidPriceLevel1 != "0")
			_BinaryValue += "BidPriceL1=" + m_MBPData._BidPriceLevel1 + ";";
		if (m_MBPData._BidOrderLevel1 != "0")
			_BinaryValue += "BidOrderL1=" + m_MBPData._BidOrderLevel1 + ";";
		if (m_MBPData._BidVolLevel1 != "0")
			_BinaryValue += "BidVolL1=" + m_MBPData._BidVolLevel1 + ";";
		if (m_MBPData._BidPriceLevel2 != "0")
			_BinaryValue += "BidPriceL2=" + m_MBPData._BidPriceLevel2 + ";";
		if (m_MBPData._BidOrderLevel2 != "0")
			_BinaryValue += "BidOrderL2=" + m_MBPData._BidOrderLevel2 + ";";
		if (m_MBPData._BidVolLevel2 != "0")
			_BinaryValue += "BidVolL2=" + m_MBPData._BidVolLevel2 + ";";
		if (m_MBPData._BidPriceLevel3 != "0")
			_BinaryValue += "BidPriceL3=" + m_MBPData._BidPriceLevel3 + ";";
		if (m_MBPData._BidOrderLevel3 != "0")
			_BinaryValue += "BidOrderL3=" + m_MBPData._BidOrderLevel3 + ";";
		if (m_MBPData._BidVolLevel3 != "0")
			_BinaryValue += "BidVolL3=" + m_MBPData._BidVolLevel3 + ";";
		if (m_MBPData._BidPriceLevel4 != "0")
			_BinaryValue += "BidPriceL4=" + m_MBPData._BidPriceLevel4 + ";";
		if (m_MBPData._BidOrderLevel4 != "0")
			_BinaryValue += "BidOrderL4=" + m_MBPData._BidOrderLevel4 + ";";
		if (m_MBPData._BidVolLevel4 != "0")
			_BinaryValue += "BidVolL4=" + m_MBPData._BidVolLevel4 + ";";
		if (m_MBPData._BidPriceLevel5 != "0")
			_BinaryValue += "BidPriceL5=" + m_MBPData._BidPriceLevel5 + ";";
		if (m_MBPData._BidOrderLevel5 != "0")
			_BinaryValue += "BidOrderL5=" + m_MBPData._BidOrderLevel5 + ";";
		if (m_MBPData._BidVolLevel5 != "0")
			_BinaryValue += "BidVolL5=" + m_MBPData._BidVolLevel5 + ";";

		if (m_MBPData._AskPriceCount != "0")
			_BinaryValue += "AskPriceCnt=" + m_MBPData._AskPriceCount+ ";";
		if (m_MBPData._AskPriceLevel1 != "0")
			_BinaryValue += "AskPriceL1=" + m_MBPData._AskPriceLevel1 + ";";
		if (m_MBPData._AskOrderLevel1 != "0")
			_BinaryValue += "AskOrderL1=" + m_MBPData._AskOrderLevel1 + ";";
		if (m_MBPData._AskVolLevel1 != "0")
			_BinaryValue += "AskVolL1=" + m_MBPData._AskVolLevel1 + ";";
		if (m_MBPData._AskPriceLevel2 != "0")
			_BinaryValue += "AskPriceL2=" + m_MBPData._AskPriceLevel2 + ";";
		if (m_MBPData._AskOrderLevel2 != "0")
			_BinaryValue += "AskOrderL2=" + m_MBPData._AskOrderLevel2 + ";";
		if (m_MBPData._AskVolLevel2 != "0")
			_BinaryValue += "AskVolL2=" + m_MBPData._AskVolLevel2 + ";";
		if (m_MBPData._AskPriceLevel3 != "0")
			_BinaryValue += "AskPriceL3=" + m_MBPData._AskPriceLevel3 + ";";
		if (m_MBPData._AskOrderLevel3 != "0")
			_BinaryValue += "AskOrderL3=" + m_MBPData._AskOrderLevel3 + ";";
		if (m_MBPData._AskVolLevel3 != "0")
			_BinaryValue += "AskVolL3=" + m_MBPData._AskVolLevel3 + ";";
		if (m_MBPData._AskPriceLevel4 != "0")
			_BinaryValue += "AskPriceL4=" + m_MBPData._AskPriceLevel4 + ";";
		if (m_MBPData._AskOrderLevel4 != "0")
			_BinaryValue += "AskOrderL4=" + m_MBPData._AskOrderLevel4 + ";";
		if (m_MBPData._AskVolLevel4 != "0")
			_BinaryValue += "AskVolL4=" + m_MBPData._AskVolLevel4 + ";";
		if (m_MBPData._AskPriceLevel5 != "0")
			_BinaryValue += "AskPriceL5=" + m_MBPData._AskPriceLevel5 + ";";
		if (m_MBPData._AskOrderLevel5 != "0")
			_BinaryValue += "AskOrderL5=" + m_MBPData._AskOrderLevel5 + ";";
		if (m_MBPData._AskVolLevel5 != "0")
			_BinaryValue += "AskVolL5=" + m_MBPData._AskVolLevel5 + ";";
		break;

	default:
		_BinaryValue = "";
		break;
	}

	_BinaryValue += "|";

	if (_SeqNo.empty())
		_BinaryValue = "";

	return _BinaryValue;	
}