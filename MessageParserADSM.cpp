#include "MessageParserADSM.h"


CMessageParserADSM::CMessageParserADSM()
{
		//Normal Messages
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

CMessageParserADSM::~CMessageParserADSM()
{
}

CParsedMessage CMessageParserADSM::ParseMessage( std::string _Message)
{
	/* ADSM Parser Implementation */
	std::string stExchange = "ADX"; 	
	CParsedMessage _message;
	_message._Exchange = "ADX"; 
	try
	{
		bool isMktIndex = false;

		std::string tag = "";	
		std::string stTagVal = "";

		MapTagVal mpTagVal;
		IteratorTagVal iterTagVal;

		std::string stSymbol = "";
		std::string stMarket = "";
		std::string stCurrTradeTime = "";
		std::string stSymMktLastTradeTime = "";
		std::string stLastSymPrice = "";
		std::string stLastSymVolume = "";

		std::string stExVolume = "";
		
		//std::map<std::string, std::string> mpSectorTagSectorName;
		//std::map<std::string, std::string> mpIndexTagIndexName;
		
		//STSectorInfo SectorInfo[10];

		std::string stMktSectorName = "";
		std::string stMktIndex = "";

		std::string stMktActivity = "";
		std::string stExActivity = "";
		std::string stIndexLastValues = "";;

		char* pszMsg = (char*)_Message.c_str();
		
		if( IsStateChangeMessage( pszMsg ) )		
		{
			//std::string* pstMdfMessage = new std::string( "SC;" + stExchange + ";" + _Message );

			//m_MessageStorage.AddStateChangeMessage( stExchange.c_str(), pstMdfMessage->c_str() );						
			_message._messageType = MSG_ERROR;
		}
		else if(BestMarketData(pszMsg))			
		{			
			_message._messageType = FEED;
			bool isMsgToForward = false;
			bool isExStatsToForward = false;
			//std::string * pstMsgToForward = new std::string( "MDF;" );
			std::string stExStatsMsgToForward = "";

			while (GetNextTagVal(pszMsg, tag, stTagVal))
			{
				if(stTagVal != "")
				{
					int nTag = atoi( tag.c_str() );

					if( nTag == 1 )
						_message._SeqNo = stTagVal;

					if( nTag == 101 )		//Symbol Tag is Present
					{
						stSymbol = stTagVal;
						_message._Symbol = stSymbol;
					}
					
					if( nTag == 102 )		//Market Tag is Present
					{
						stMarket = stExchange + std::string("/") + stTagVal;
						_message._Market = stMarket;
					}
					
					if( nTag == 282 )		//Last Volume							
						_message._LastVolume = stTagVal;					
					
					if( nTag == 281 )		//Last Price
						_message._LastPrice = stTagVal;
					
					if( nTag == 261 )		//Yesterday Close					
						_message._PrevClose = stTagVal;
					
					if( nTag == 271 )		//Average Price
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
						_message._TradeTime = stTagVal;//GMTtoLocalTime(stTagVal);
					
					if( nTag == 263 )		//52 Week High
						_message._52WeekHigh = stTagVal;

					if( nTag == 264 )		//52 Week Low
						_message._52WeekLow = stTagVal;
		
				}
			}
					/*if( setValidTags.find( nTag ) != setValidTags.end() )
					{
						bool bIndexTag = false;
						isMsgToForward = true;

						if( nTag == 117 || nTag == 267 )
							GMTtoLocalTime(stTagVal);
					
						if( nTag == 102 )		//Market Tag is Present
						{
							*pstMsgToForward += tag + "=" + stMarket+";";
							stTagVal = stMarket;
						}
						else if(nTag != 267)
							*pstMsgToForward += tag + "=" + stTagVal+";";

						if( nTag == 117 )
							stCurrTradeTime = stTagVal;
						
						if(nTag == 267)		//SymMktLastTradeTimeTag is Present
						{
							stSymMktLastTradeTime = stTagVal;
							
						}

						if(nTag == 282)		//LastVolume Tag is Present
							stLastSymVolume = stTagVal;
						
						if(nTag == 151)
							isMktIndex = true;

							//Checking Index Tag
						if (IsIndexTag(nTag))
							mpIndexTagIndexName[tag] = stTagVal;

						//Checking SectorIndex Tag
						if(IsSectorIndexTag(nTag))
							mpSectorTagSectorName[tag] = stTagVal;

						
						if(setMktIndexTags.find(nTag) != setMktIndexTags.end() )
						{
							stIndexLastValues += tag + "=" + stTagVal+";";	
						}
						else
						{
							iterTagVal = mpTagVal.find(tag);

							if(iterTagVal != mpTagVal.end())
								iterTagVal->second = stTagVal;
							else
								mpTagVal.insert(MapTagVal::value_type(tag, stTagVal));
						}
					}

					UpdateSectorInfo( SectorInfo, nTag, tag, stTagVal );

					//Add Market Statistics Data
					if( std::find(vtExStatsToForwardTags.begin(), vtExStatsToForwardTags.end(), nTag) != vtExStatsToForwardTags.end() )
					//if( IsExStatsToForwardTag( nTag ) )
					{
						if(nTag == 243)
							stExVolume = stTagVal;

						stExStatsMsgToForward += tag + "=" + stTagVal+";";
						isExStatsToForward = true;
				
					}
				
					//Add Market Activity Data 
					if( IsMktStatsAdvanceTag( nTag ) || IsMktStatsDeclineTag( nTag ) || IsMktStatsUnchangedTag( nTag ) )
						stMktActivity += tag + "=" + stTagVal+";";


					//Add Exchange Activity Data 
					if( IsExStatsAdvanceTag( nTag ) || IsExStatsDeclineTag( nTag ) || IsExStatsUnchangedTag( nTag ) )
						stExActivity += tag + "=" + stTagVal+";";
				}
			}

			//Add Refresh Data
			if(isMsgToForward  && (stSymbol != "") && (stMarket != ""))
				AddSymMktMsgPair(stSymbol, stMarket, mpTagVal, stExStatsMsgToForward, stIndexLastValues);

			//Add Graph Data on Symbol (TradeTime-SymbolVolume and TradeTime-SymbolPrice)
			if((stSymbol != "") && (stMarket != "") && (stCurrTradeTime != "") && (stLastSymPrice != "") && (stLastSymVolume != ""))
			{
				m_MessageStorage.AddSymVolGraphData(stSymbol, stMarket, stCurrTradeTime, stLastSymVolume);
				m_MessageStorage.AddSymPxGraphData(stSymbol, stMarket, stCurrTradeTime, stLastSymPrice);
			}

			//Add Graph Data on Market (TradeTime-MarketVolume)
			if(isExStatsToForward && (stMarket != "")  && (stCurrTradeTime != "") )
				m_MessageStorage.AddMarketVolGraphData(stExchange, stCurrTradeTime, stExVolume);

			//Add Graph Data on Market (TradeTime-SectorIndexID-Index)
			if(isMktIndex && (stMarket != "")  && (stCurrTradeTime != "") )
			{

				std::map<std::string, std::string>::iterator it = mpSectorTagSectorName.begin();

				for(; it != mpSectorTagSectorName.end(); it++)
					m_MessageStorage.AddMarketIndGraphData(stExchange, stCurrTradeTime, it->second, mpIndexTagIndexName[mpSectorTagIndexTag[it->first]]);

			}
			
			if( (stMktActivity != "") && (stMarket != "") )
			{
				m_MessageStorage.AddMarketActivityData(stMarket, stMktActivity );
			}

			if(stExActivity != "")
			{
				m_MessageStorage.AddExActivityData(stExchange, stExActivity);
			}

			for( int nSector = 0 ; nSector < 10 ; nSector++ )
			{
				if( SectorInfo[ nSector ].stData.length() > 0 )
					m_MessageStorage.AddSectorActivityData( stExchange, SectorInfo[ nSector ].stName, SectorInfo[ nSector ].stData );
			}

			//if(isMsgToForward)//If Exchange  Statistics Data is available
			//{
			//	if( isExStatsToForward )
			//		*pstMsgToForward += stExStatsMsgToForward;
			//}
			//else
				delete pstMsgToForward;*/
		}	

		else if(MarketByOrderData(pszMsg))
		{			
			_message._messageType = MBO;
			std::string stMBOMsgToAdd = "";
		
			while (GetNextTagVal(pszMsg, tag, stTagVal))
			{
				if (stTagVal == "" )
					stTagVal = "0";
				
				int nTag = atoi( tag.c_str() );

				if( nTag == 1 )
					_message._SeqNo = stTagVal;

				if( nTag == 101 ) //Symbol Tag is Present
				{
					stSymbol = stTagVal;					
					_message.m_MBOData._Symbol = stTagVal;
				}
				else if( nTag == 102 )		//Market Tag is Present
				{
					stMarket = stExchange + std::string("/") + stTagVal;											
					_message.m_MBOData._Market = stTagVal;
				}
									
				if( setMBOTags.find( nTag ) != setMBOTags.end() && stTagVal != "0")
				{
					if( nTag == 102 )		//Market Tag is Present
					{
						stMBOMsgToAdd += tag + "=" + stMarket+";";
					}
					else
					{
						stMBOMsgToAdd += tag + "=" + stTagVal+";";

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
			/*if((stSymbol != "") && (stMarket != "") && (stMBOMsgToAdd != ""))
				m_MessageStorage.AddMBOData(stSymbol, stMarket, stMBOMsgToAdd);					*/
		}

		else if(MarketByPriceData(pszMsg))
		{			
			_message._messageType = MBP;
			std::string stMBPMsgToAdd = "";
			
			while (GetNextTagVal(pszMsg, tag, stTagVal))
			{
				if (stTagVal == "" )
					stTagVal = "0";

				int nTag = atoi( tag.c_str() );

				if( nTag == 1 )
					_message._SeqNo = stTagVal;

				if( nTag == 101 )		//Symbol Tag is Present
				{
					stSymbol = stTagVal;
					_message.m_MBPData._Symbol = stTagVal;
				}

				if( nTag == 102 )		//Market Tag is Present
				{
					stMarket = stExchange + std::string("/") + stTagVal;
					_message.m_MBPData._Market = stTagVal;
				}

				if( setMBPTags.find( nTag ) != setMBPTags.end() )
				{
					if( nTag == 102 )		//Market Tag is Present
						stMBPMsgToAdd += tag + "=" + stMarket+";";						
					else
						stMBPMsgToAdd += tag + "=" + stTagVal+";";

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
				
			/*if((stSymbol != "") && (stMarket != "") && (stMBPMsgToAdd != ""))
				m_MessageStorage.AddMBPData(stSymbol, stMarket, stMBPMsgToAdd);*/
		} 
		else if ( StateChangeData(pszMsg) )
		{
			/*std::string stMarket = "";
			std::string stMktState = "";

			while (GetNextTagVal(pszMsg, tag, stTagVal))
			{
				
				if(tag == "1002")
				{
					if(stTagVal != "")
						stMarket = stExchange + std::string("/") + stTagVal;	
				}
				if(tag == "1003")
				{
					stMktState = stTagVal;					
				}	
			}
			if( (stMarket != "") && (stMktState != "") )
			{
				m_MessageStorage.AddMarketStatusData(stMarket, "1003=" + stMktState + ";");
			}*/
			_message._messageType = MSG_ERROR;
		}	
		
	}
	catch(std::exception* ex)
	{
		//std::cout<<std::endl<<ex->what()<<std::endl;		
		_message._messageType = MSG_ERROR;
	}	
	/* ADX Parser Implementation */ 		 		
	return _message;
}

int CMessageParserADSM::VerifyMessage(std::string _item)
{
	return 1;
}


bool CMessageParserADSM::GetNextTagVal (std::string& msg, std::string& stTag, std::string& stVal, int & nMsgCounter, int & nMsgLen )
{
	stTag = "";
	stVal = "";

	// code added by Sajjad bhai
	if( nMsgCounter >= nMsgLen || nMsgCounter > nMsgLen )
		return false;

	while(msg[nMsgCounter] != '=')
	{
		stTag += msg[nMsgCounter++];

		// code added by Asad Haqqui
		if( nMsgCounter >= nMsgLen )
			return false;		
	}
	
	++nMsgCounter;

	// code added by Asad Haqqui
	if( nMsgCounter >= nMsgLen || nMsgCounter > nMsgLen )
		return false;

	while(msg[nMsgCounter] != ';')
	{
		stVal += msg[nMsgCounter++];

		// code added by Asad Haqqui
		if( nMsgCounter >= nMsgLen )
			return false;		
	}


	nMsgCounter += 2;

	return true;
}

bool CMessageParserADSM::GetNextTagVal( char *& szMsg, std::string& stTag, std::string& stVal)
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

bool CMessageParserADSM::BestMarketData (std::string& stMessage)
{
	return TagExists ("139", stMessage);
}

bool CMessageParserADSM::MarketByOrderData (std::string& stMessage)
{
	return (TagExists ("1100", stMessage) || TagExists ("1131", stMessage));
}
	
bool CMessageParserADSM::MarketByPriceData (std::string& stMessage)
{
	return (TagExists ("1250", stMessage) || TagExists ("1266", stMessage));
}

bool CMessageParserADSM::StateChangeData( std::string& stMessage )
{
	return  TagExists( "1000", stMessage );		
}

bool CMessageParserADSM::BestMarketData( char * szMsg )
{
	return TagExists_( szMsg, "139" );
}

bool CMessageParserADSM::MarketByOrderData( char * szMsg )
{
	return TagExists_( szMsg, "1100" ) || TagExists_( szMsg, "1131" );
}
	
bool CMessageParserADSM::MarketByPriceData( char * szMsg )
{
	return TagExists_( szMsg, "1250" ) || TagExists_( szMsg, "1266" );
}

bool CMessageParserADSM::StateChangeData( char * szMsg )
{
	return TagExists_( szMsg, "1000" );
}
bool CMessageParserADSM::IsSectorIndexTag (int tag) 
{

	return ( (tag == 152) || (tag == 170) || (tag == 188) || (tag == 206) || (tag == 224) || (tag == 500) || 
			(tag == 600) || (tag == 700) || (tag == 800) || (tag == 900) );
}

bool CMessageParserADSM::IsIndexTag (int tag)
{
	return ( (tag == 160) || (tag == 178) || (tag == 196) || (tag == 214) || (tag == 232) || (tag == 509) || 
			 (tag == 609) || (tag == 709) || (tag == 809) || (tag == 909) );
}
bool CMessageParserADSM::UpdateSectorInfo( STSectorInfo * SectorInfo, int nTag, const std::string & tag, const std::string & stTagVal )
{
	if(IsSector1Tag(nTag))
	{
		if( nTag == 152 )
			SectorInfo[0].stName = stTagVal;
		else
			SectorInfo[0].stData += tag + "=" + stTagVal + ";";
	}

	else if(IsSector2Tag(nTag))
	{
		if( nTag == 170 )
			SectorInfo[1].stName = stTagVal;
		else
			SectorInfo[1].stData += tag + "=" + stTagVal + ";";
	}

	else if(IsSector3Tag(nTag))
	{
		if( nTag == 188 )
			SectorInfo[2].stName = stTagVal;
		else
			SectorInfo[2].stData += tag + "=" + stTagVal + ";";
	}

	else if(IsSector4Tag(nTag))
	{
		if( nTag == 206 )
			SectorInfo[3].stName = stTagVal;
		else
			SectorInfo[3].stData += tag + "=" + stTagVal + ";";
	}

	else if(IsSector5Tag(nTag))
	{
		if( nTag == 224 )
			SectorInfo[4].stName = stTagVal;
		else
			SectorInfo[4].stData += tag + "=" + stTagVal + ";";
	}

	else if(IsSector6Tag(nTag))
	{
		if( nTag == 500 )
			SectorInfo[5].stName = stTagVal;
		else
			SectorInfo[5].stData += tag + "=" + stTagVal + ";";
	}

	else if(IsSector7Tag(nTag))
	{
		if( nTag == 600 )
			SectorInfo[6].stName = stTagVal;
		else
			SectorInfo[6].stData += tag + "=" + stTagVal + ";";
	}

	else if(IsSector8Tag(nTag))
	{
		if( nTag == 700 )
			SectorInfo[7].stName = stTagVal;
		else
			SectorInfo[7].stData += tag + "=" + stTagVal + ";";
	}

	else if(IsSector9Tag(nTag))
	{
		if( nTag == 800 )
			SectorInfo[8].stName = stTagVal;
		else
			SectorInfo[8].stData += tag + "=" + stTagVal + ";";
	}

	else if(IsSector10Tag(nTag))
	{
		if( nTag == 900 )
			SectorInfo[9].stName = stTagVal;
		else
			SectorInfo[9].stData += tag + "=" + stTagVal + ";";
	}
	return true;
}
bool CMessageParserADSM::IsSector1Tag (int tag)
{
	return setSector1Tags.find( tag ) != setSector1Tags.end();
}

bool CMessageParserADSM::IsSector2Tag (int tag)
{
	return setSector2Tags.find( tag ) != setSector2Tags.end();
}

bool CMessageParserADSM::IsSector3Tag (int tag)
{
	return setSector3Tags.find( tag ) != setSector3Tags.end();
}

bool CMessageParserADSM::IsSector4Tag (int tag)
{
	return setSector4Tags.find( tag ) != setSector4Tags.end();
}

bool CMessageParserADSM::IsSector5Tag (int tag)
{
	return setSector5Tags.find( tag ) != setSector5Tags.end();
}

bool CMessageParserADSM::IsSector6Tag (int tag)
{
	return setSector6Tags.find( tag ) != setSector6Tags.end();
}

bool CMessageParserADSM::IsSector7Tag (int tag)
{
	return setSector7Tags.find( tag ) != setSector7Tags.end();
}

bool CMessageParserADSM::IsSector8Tag (int tag)
{
	return setSector8Tags.find( tag ) != setSector8Tags.end();
}

bool CMessageParserADSM::IsSector9Tag (int tag)
{
	return setSector9Tags.find( tag ) != setSector9Tags.end();
}

bool CMessageParserADSM::IsSector10Tag (int tag)
{
	return setSector10Tags.find( tag ) != setSector10Tags.end();
}
bool CMessageParserADSM::IsExStatsToForwardTag(int nTag)
{
	return std::find(vtExStatsToForwardTags.begin(), vtExStatsToForwardTags.end(), nTag) != vtExStatsToForwardTags.end();
}

bool CMessageParserADSM::IsExStatsAdvanceTag(int tag)
{
	return tag == 413 ||//No Of Symbols Traded in this Exchange
		   tag == 246 ||//Todays Trades
		   tag == 414 ||//Todays Volume
		   tag == 415;  //Todays Value
}

bool CMessageParserADSM::IsExStatsDeclineTag(int tag)
{
	return tag == 416 ||//No Of Symbols Traded in this Exchange
		   tag == 247 ||//Todays Trades
		   tag == 417 ||//Todays Volume
		   tag == 418;  //Todays Value
}

bool CMessageParserADSM::IsExStatsUnchangedTag(int tag)
{
	return tag == 419 ||//No Of Symbols Traded in this Exchange
		   tag == 248 ||//Todays Trades
		   tag == 420 ||//Todays Volume
		   tag == 421 ||//Todays Value
		   tag == 422;  //Market Capital
}
bool CMessageParserADSM::IsMktStatsAdvanceTag(int tag)
{
	return tag == 423 ||//No Of Symbols Traded in this Market
		   tag == 253 ||//Todays Trades
		   tag == 424 ||//Todays Volume
		   tag == 425  ;//Todays Value
}

bool CMessageParserADSM::IsMktStatsDeclineTag(int tag)
{
	return tag == 426 ||//No Of Symbols Traded in this Market
		   tag == 254 ||//Todays Trades
		   tag == 427 ||//Todays Volume
		   tag == 428;  //Todays Value
}

bool CMessageParserADSM::IsMktStatsUnchangedTag(int tag)
{
	return tag == 429 ||//No Of Symbols Traded in this Market
		   tag == 255 ||//Todays Trades
		   tag == 430 ||//Todays Volume
		   tag == 431;  //Todays Value
}
bool CMessageParserADSM::IsStateChangeMessage(char* stMdfMessage)
{
	return TagExists_( stMdfMessage, "1000" );
}

bool CMessageParserADSM::TagExists (std::string tag, std::string& msg)
{
	
	int pos = FindTagValueIndex(tag, msg);
	
	if(pos == -1)
		return false;

	return true;	
}

bool CMessageParserADSM::TagExists_( char * szMsg, const std::string & stTag )
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

void CMessageParserADSM::GMTtoLocalTime (std::string& stTime)
{
	struct tm *ptm;
	
	time_t ltime;

	time(&ltime);
		
	ptm = gmtime( &ltime );
	
	int nGMTTimeHour = ptm->tm_hour;

	ptm = localtime(&ltime);
	
	int nLocalTimeHour = ptm->tm_hour;

	int nTimeDiffToAdd = nLocalTimeHour - nGMTTimeHour;

	char pszStr[3];

	stTime.copy(pszStr, 2, 8);

	pszStr[2] = '\0';

	int nHour = atoi(pszStr);	

	nHour += nTimeDiffToAdd;

	itoa(nHour, pszStr, 10);

	stTime[8] = pszStr[0];
	stTime[9] = pszStr[1];

}
void CMessageParserADSM::AddSymMktMsgPair(std::string & stSymbol, std::string & stMarket, MapTagVal& mpTagVal,  std::string & stExStatsMsgToForward, std::string & stIndexLastValues)
{

	//m_MessageStorage.AddRefreshData(stSymbol, stMarket, mpTagVal, stExStatsMsgToForward, stIndexLastValues);

}
int CMessageParserADSM::FindTagValueIndex (std::string tag, std::string& msg)
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
