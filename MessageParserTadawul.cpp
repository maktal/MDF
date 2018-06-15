#include "MessageParserTadawul.h"

CMessageParserTadawul::CMessageParserTadawul(void)
{
	setValidTags.insert(101);//SymbolTag
	setValidTags.insert(102);//MarketTag
	setValidTags.insert(107);//BidVolumeTag
	setValidTags.insert(108);//AskVolumeTag
	setValidTags.insert(109);//BidPriceTag 
	setValidTags.insert(110);//AskPriceTag
	setValidTags.insert(117);//TradeTimeTag
	setValidTags.insert(263);//52WeekHighTag
	setValidTags.insert(264);//52WeekLowTag
	setValidTags.insert(267);//TradeTime For SymbolMarket
	setValidTags.insert(275);//TotalVolumeTag 
	setValidTags.insert(281);//LastPriceTag
	setValidTags.insert(282);//LastVolumeTag
	setValidTags.insert(285);//MktOpeningTag
	setValidTags.insert(437);//MinPriceTag
	setValidTags.insert(438);//MaxPriceTag

	setValidTags.insert(133);//priceChgFromAvg
	setValidTags.insert(134);//prcntChgFromAvg
	setValidTags.insert(135);//tickDirInd


	setValidTags.insert(261);//YestCloseTag
	setValidTags.insert(279);//HighPriceTag
	setValidTags.insert(280);//LowPriceTag
	setValidTags.insert(274);//TotalTradesTag
	setValidTags.insert(276);//TotalValueTag
	setValidTags.insert(271);//AvgPriceTag

	//Market By Order
	setMBOTags.insert(101);
	setMBOTags.insert(102);
	setMBOTags.insert(1100);
	setMBOTags.insert(1101);
	setMBOTags.insert(1102);

	setMBOTags.insert(1104);
	setMBOTags.insert(1105);

	setMBOTags.insert(1107);
	setMBOTags.insert(1108);

	setMBOTags.insert(1110);
	setMBOTags.insert(1111);

	setMBOTags.insert(1113);
	setMBOTags.insert(1114);

	setMBOTags.insert(1116);
	setMBOTags.insert(1117);

	setMBOTags.insert(1119);
	setMBOTags.insert(1120);

	setMBOTags.insert(1122);
	setMBOTags.insert(1123);

	setMBOTags.insert(1125);
	setMBOTags.insert(1126);

	setMBOTags.insert(1128);
	setMBOTags.insert(1129);
	

	setMBOTags.insert(1131);
	setMBOTags.insert(1132);
	setMBOTags.insert(1133);

	setMBOTags.insert(1135);
	setMBOTags.insert(1136);

	setMBOTags.insert(1138);
	setMBOTags.insert(1139);

	setMBOTags.insert(1141);
	setMBOTags.insert(1142);

	setMBOTags.insert(1144);
	setMBOTags.insert(1145);

	setMBOTags.insert(1147);
	setMBOTags.insert(1148);

	setMBOTags.insert(1150);
	setMBOTags.insert(1151);

	setMBOTags.insert(1153);
	setMBOTags.insert(1154);

	setMBOTags.insert(1156);
	setMBOTags.insert(1157);

	setMBOTags.insert(1159);
	setMBOTags.insert(1160);

	//Market By Price
	setMBPTags.insert(101);
	setMBPTags.insert(102);
	setMBPTags.insert(1250);

	setMBPTags.insert(1251);
	setMBPTags.insert(1252);
	setMBPTags.insert(1253);

	setMBPTags.insert(1254);
	setMBPTags.insert(1255);
	setMBPTags.insert(1256);
	
	setMBPTags.insert(1257);
	setMBPTags.insert(1258);
	setMBPTags.insert(1259);

	setMBPTags.insert(1260);
	setMBPTags.insert(1261);
	setMBPTags.insert(1262);

	setMBPTags.insert(1263);
	setMBPTags.insert(1264);
	setMBPTags.insert(1265);


	setMBPTags.insert(1266);

	setMBPTags.insert(1267);
	setMBPTags.insert(1268);
	setMBPTags.insert(1269);

	setMBPTags.insert(1270);
	setMBPTags.insert(1271);
	setMBPTags.insert(1272);
	
	setMBPTags.insert(1273);
	setMBPTags.insert(1274);
	setMBPTags.insert(1275);

	setMBPTags.insert(1276);
	setMBPTags.insert(1277);
	setMBPTags.insert(1278);

	setMBPTags.insert(1279);
	setMBPTags.insert(1280);
	setMBPTags.insert(1281);
}

CMessageParserTadawul::~CMessageParserTadawul(void)
{
}

CParsedMessage CMessageParserTadawul::ParseMessage( std::string _Message)
{
	/* Tadawul Parser Implementation */
	std::string stExchange = "Tadawul"; 	
	CParsedMessage _message;
	_message._Exchange = "Tadawul"; 
	try
	{

		std::string tag = "";	
		std::string stTagVal = "";				
	
		char* pszMsg = (char*)_Message.c_str();

		if(BestMarketData(pszMsg))			
		{
			_message._messageType = FEED;
			while (GetNextTagVal(pszMsg, tag, stTagVal))
			{
				if(stTagVal != "")
				{
					int nTag = atoi( tag.c_str() );								

					if( nTag == 1 )
						_message._SeqNo = stTagVal;

					if( nTag == 101 )		//Symbol Tag is Present
					{
						_message._Symbol = stTagVal;
					}
					
					if( nTag == 102 )		//Market Tag is Present
					{						
						_message._Market = stTagVal;
					}
					
					if( nTag == 282 )		//Last Volume							
						_message._LastVolume = stTagVal;					
					
					if( nTag == 281 )		//Last Price
						_message._LastPrice = stTagVal;
					
					if( nTag == 261 )		//Yesterday Close					
						_message._PrevClose = stTagVal;
					
					if( nTag == 284 )		//Average Price
						_message._AvgPrice = stTagVal;

					if( nTag == 285 )		//Openning Price
						_message._OpenPrice = stTagVal;
					
					if( nTag == 279 )		//High Price
						_message._HighPrice = stTagVal;

					if( nTag == 280 )		//Low Price
						_message._LowPrice = stTagVal;

					if( nTag == 275 )		//Total Volume 
						_message._TotalVolume = stTagVal;

					if( nTag == 274 )		//Total Trades
						_message._TotalTrades = stTagVal;

					if( nTag == 267 )		//Trade Time
						_message._TradeTime = stTagVal;
					
					if( nTag == 277 )		//52 Week High
						_message._52WeekHigh = stTagVal;

					if( nTag == 278 )		//52 Week Low
						_message._52WeekLow = stTagVal;

				}
			}
		}	

		else if(MarketByOrderData(pszMsg))
		{		
			_message._messageType = MBO;
			while (GetNextTagVal(pszMsg, tag, stTagVal))
			{
				if (stTagVal == "" )
					stTagVal = "0";				
				
				int nTag = atoi( tag.c_str() );

				if( nTag == 1 )
					_message._SeqNo = stTagVal;

				if( nTag == 101 ) //Symbol Tag is Present
						_message.m_MBOData._Symbol = stTagVal;
								
									
				if( setMBOTags.find( nTag ) != setMBOTags.end() && stTagVal != "0")
				{
					if( nTag == 102 )		//Market Tag is Present
					{
						_message.m_MBOData._Market = stTagVal;		
					}
					else
					{					

						if( nTag == 1100 )
							_message.m_MBOData._regBkAskOrder = stTagVal;
						if( nTag == 1101 )
							_message.m_MBOData._regBkAskTotalVol = stTagVal;
						if( nTag == 1102 )
							_message.m_MBOData._regBkAskPrice = stTagVal;
						if( nTag == 1104 )
							_message.m_MBOData._AskOrdTotalVol1= stTagVal;
						if( nTag == 1105 )
							_message.m_MBOData._AskOrdPrice1= stTagVal;
						if( nTag == 1107 )
							_message.m_MBOData._AskOrdTotalVol2= stTagVal;
						if( nTag == 1108 )
							_message.m_MBOData._AskOrdPrice2= stTagVal;
						if( nTag == 1110 )
							_message.m_MBOData._AskOrdTotalVol3= stTagVal;
						if( nTag == 1111 )
							_message.m_MBOData._AskOrdPrice3= stTagVal;
						if( nTag == 1113 )
							_message.m_MBOData._AskOrdTotalVol4= stTagVal;
						if( nTag == 1114 )
							_message.m_MBOData._AskOrdPrice4= stTagVal;
						if( nTag == 1116 )
							_message.m_MBOData._AskOrdTotalVol5= stTagVal;
						if( nTag == 1117 )
							_message.m_MBOData._AskOrdPrice5= stTagVal;
						if( nTag == 1119 )
							_message.m_MBOData._AskOrdTotalVol6= stTagVal;
						if( nTag == 1120 )
							_message.m_MBOData._AskOrdPrice6= stTagVal;
						if( nTag == 1122 )
							_message.m_MBOData._AskOrdTotalVol7= stTagVal;
						if( nTag == 1123 )
							_message.m_MBOData._AskOrdPrice7= stTagVal;
						if( nTag == 1125 )
							_message.m_MBOData._AskOrdTotalVol8= stTagVal;
						if( nTag == 1126 )
							_message.m_MBOData._AskOrdPrice8= stTagVal;
						if( nTag == 1128 )
							_message.m_MBOData._AskOrdTotalVol9= stTagVal;
						if( nTag == 1129 )
							_message.m_MBOData._AskOrdPrice9= stTagVal;

						if( nTag == 1131 )
							_message.m_MBOData._regBkBidOrder= stTagVal;	
						if( nTag == 1132 )
							_message.m_MBOData._regBkBidTotalVol= stTagVal;	
						if( nTag == 1133 )
							_message.m_MBOData._regBkBidPrice= stTagVal;
						if( nTag == 1135 )
							_message.m_MBOData._BidOrdTotalVol1= stTagVal;	
						if( nTag == 1136 )
							_message.m_MBOData._BidOrdPrice1= stTagVal;	
						if( nTag == 1138 )
							_message.m_MBOData._BidOrdTotalVol2= stTagVal;	
						if( nTag == 1139 )
							_message.m_MBOData._BidOrdPrice2= stTagVal;	
						if( nTag == 1141 )
							_message.m_MBOData._BidOrdTotalVol3= stTagVal;	
						if( nTag == 1142 )
							_message.m_MBOData._BidOrdPrice3= stTagVal;	
						if( nTag == 1145 )
							_message.m_MBOData._BidOrdTotalVol4= stTagVal;	
						if( nTag == 1145 )
							_message.m_MBOData._BidOrdPrice4= stTagVal;	
						if( nTag == 1147 )
							_message.m_MBOData._BidOrdTotalVol5= stTagVal;	
						if( nTag == 1148 )
							_message.m_MBOData._BidOrdPrice5= stTagVal;	
						if( nTag == 1150 )
							_message.m_MBOData._BidOrdTotalVol6= stTagVal;	
						if( nTag == 1151 )
							_message.m_MBOData._BidOrdPrice6= stTagVal;	
						if( nTag == 1153 )
							_message.m_MBOData._BidOrdTotalVol7= stTagVal;	
						if( nTag == 1154 )
							_message.m_MBOData._BidOrdPrice7= stTagVal;	
						if( nTag == 1156 )
							_message.m_MBOData._BidOrdTotalVol8= stTagVal;	
						if( nTag == 1157 )
							_message.m_MBOData._BidOrdPrice8= stTagVal;	
						if( nTag == 1159 )
							_message.m_MBOData._BidOrdTotalVol9= stTagVal;	
						if( nTag == 1160 )
							_message.m_MBOData._BidOrdPrice9= stTagVal;	
					}						
				}				
			}			
		}
		else if(MarketByPriceData(pszMsg))
		{			
			_message._messageType = MBP;
			while (GetNextTagVal(pszMsg, tag, stTagVal))
			{
				if (stTagVal == "" )
					stTagVal = "0";				

				int nTag = atoi( tag.c_str() );

				if( nTag == 1 )
					_message._SeqNo = stTagVal;

				if( nTag == 101 )		//Symbol Tag is Present
				{	
					_message.m_MBPData._Symbol = stTagVal;
				}				

				if( setMBPTags.find( nTag ) != setMBPTags.end() )
				{
					if( nTag == 102 )		//Market Tag is Present
						_message.m_MBPData._Market = stTagVal;									

					if( nTag == 1250 )
						_message.m_MBPData._BidPriceCount= stTagVal;
					
					if( nTag == 1251 )
						_message.m_MBPData._BidPriceLevel1 = stTagVal;
					if( nTag == 1252 )
						_message.m_MBPData._BidOrderLevel1 = stTagVal;
					if( nTag == 1253 )
						_message.m_MBPData._BidVolLevel1 = stTagVal;
					
					if( nTag == 1254 )
						_message.m_MBPData._BidPriceLevel2 = stTagVal;
					if( nTag == 1255 )
						_message.m_MBPData._BidOrderLevel2 = stTagVal;
					if( nTag == 1256 )
						_message.m_MBPData._BidVolLevel2 = stTagVal;
					
					if( nTag == 1257 )
						_message.m_MBPData._BidPriceLevel3 = stTagVal;
					if( nTag == 1258 )
						_message.m_MBPData._BidOrderLevel3 = stTagVal;
					if( nTag == 1259 )
						_message.m_MBPData._BidVolLevel3 = stTagVal;
					
					if( nTag == 1260 )
						_message.m_MBPData._BidPriceLevel4 = stTagVal;
					if( nTag == 1261 )
						_message.m_MBPData._BidOrderLevel4 = stTagVal;
					if( nTag == 1262 )
						_message.m_MBPData._BidVolLevel4 = stTagVal;

					if( nTag == 1263 )		
						_message.m_MBPData._BidPriceLevel5 = stTagVal;
					if( nTag == 1264 )
						_message.m_MBPData._BidOrderLevel5 = stTagVal;
					if( nTag == 1265 )
						_message.m_MBPData._BidVolLevel5 = stTagVal;

					if( nTag == 1266 )	
						_message.m_MBPData._AskPriceCount = stTagVal;
						
					if( nTag == 1267 )
						_message.m_MBPData._AskPriceLevel1 = stTagVal;
					if( nTag == 1268 )
						_message.m_MBPData._AskOrderLevel1 = stTagVal;
					if( nTag == 1269 )
						_message.m_MBPData._AskVolLevel1 = stTagVal;
					
					if( nTag == 1270 )
						_message.m_MBPData._AskPriceLevel2 = stTagVal;
					if( nTag == 1271 )
						_message.m_MBPData._AskOrderLevel2 = stTagVal;
					if( nTag == 1272 )
						_message.m_MBPData._AskVolLevel2 = stTagVal;
					
					if( nTag == 1273 )
						_message.m_MBPData._AskPriceLevel3 = stTagVal;
					if( nTag == 1274 )
						_message.m_MBPData._AskOrderLevel3 = stTagVal;
					if( nTag == 1275 )
						_message.m_MBPData._AskVolLevel3 = stTagVal;
					
					if( nTag == 1276 )
						_message.m_MBPData._AskPriceLevel4 = stTagVal;
					if( nTag == 1277 )
						_message.m_MBPData._AskOrderLevel4 = stTagVal;
					if( nTag == 1278 )
						_message.m_MBPData._AskVolLevel4 = stTagVal;
					
					if( nTag == 1279 )		
						_message.m_MBPData._AskPriceLevel5 = stTagVal;
					if( nTag == 1280 )
						_message.m_MBPData._AskOrderLevel5 = stTagVal;
					if( nTag == 1281 )
						_message.m_MBPData._AskVolLevel5 = stTagVal;
				}
			}				
		} 
	}
	catch(std::exception* ex)
	{
		std::cout<<std::endl<<ex->what()<<std::endl;
		_message._messageType = MSG_ERROR;
	}
	/* Tadawul Parser Implementation */ 		 		
	return _message;
}

bool CMessageParserTadawul::GetNextTagVal (std::string& msg, std::string& stTag, std::string& stVal, int & nMsgCounter, int & nMsgLen )
{
	stTag = "";
	stVal = "";

	if( nMsgCounter >= nMsgLen || nMsgCounter > nMsgLen )
		return false;

	while(msg[nMsgCounter] != '=')
	{
		stTag += msg[nMsgCounter++];

		if( nMsgCounter >= nMsgLen )
			return false;		
	}
	
	++nMsgCounter;

	if( nMsgCounter >= nMsgLen || nMsgCounter > nMsgLen )
		return false;

	while(msg[nMsgCounter] != ';')
	{
		stVal += msg[nMsgCounter++];

		if( nMsgCounter >= nMsgLen )
			return false;		
	}


	nMsgCounter += 2;

	return true;
}

bool CMessageParserTadawul::GetNextTagVal( char *& szMsg, std::string& stTag, std::string& stVal)
{
	stTag = "";
	stVal = "";

	while( *szMsg != 0 && *szMsg != '=' )
		stTag += *szMsg++;

	if( *szMsg != 0 )
	{
		szMsg++;
		while( *szMsg != 0 && *szMsg != ';' )
			stVal += *szMsg++;
	}

	szMsg += 2;
	return stTag.length() > 0;
}

bool CMessageParserTadawul::BestMarketData (std::string& stMessage)
{
	return TagExists ("139", stMessage); 
}

bool CMessageParserTadawul::MarketByOrderData (std::string& stMessage)
{
	return (TagExists ("1100", stMessage) || TagExists ("1121", stMessage));
}
	
bool CMessageParserTadawul::MarketByPriceData (std::string& stMessage)
{
	return (TagExists ("1200", stMessage) || TagExists ("1216", stMessage));
}

bool CMessageParserTadawul::TagExists (std::string tag, std::string& msg)
{
	
	int pos = FindTagValueIndex(tag, msg);
	
	if(pos == -1)
		return false;

	return true;	
}

bool CMessageParserTadawul::TagExists_( char * szMsg, const std::string & stTag )
{
	int nChar  = 0;
	int nStart = 0;
	while( szMsg[ nChar ] != 0  )
	{
		if( szMsg[ nChar ] == '\n' )
			nStart = nChar + 1;

		else if( szMsg[ nChar ] == '=' && (nChar - nStart) == stTag.length() )
		{
			if( strncmp( szMsg + nStart, stTag.c_str(), stTag.length() ) == 0 )
				return true;
		}
		nChar++;
	}
	return false;
}
bool CMessageParserTadawul::BestMarketData( char * szMsg )
{
	return TagExists_( szMsg, "139" );
}

bool CMessageParserTadawul::MarketByOrderData( char * szMsg )
{
	return TagExists_( szMsg, "1100" ) || TagExists_( szMsg, "1131" );
}
	
bool CMessageParserTadawul::MarketByPriceData( char * szMsg )
{
	return TagExists_( szMsg, "1250" ) || TagExists_( szMsg, "1266" );
}
int CMessageParserTadawul::FindTagValueIndex (std::string tag, std::string& msg)
{
	std::string str = "\n"+tag+"=";
	int nsymbolIndex = msg.find(str);

	if(nsymbolIndex == -1)
	{
		std::string str = msg.substr(0,tag.length() + 1) ;

		if(str == (tag+"="))
			nsymbolIndex = tag.length() + 1;
		else
			return -1;
	}
	else
		nsymbolIndex  = nsymbolIndex  + tag.length()+2; // Inorder to skip "\nTag="

	return nsymbolIndex;  
}