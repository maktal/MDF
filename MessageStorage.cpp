#include "MessageStorage.h"
#include "ace/Global_Macros.h"

CMessageStorage::CMessageStorage(void)
{
}

CMessageStorage::~CMessageStorage(void)
{
}

//*************************************** Cache Recovery Functions ***************************************

/*bool CMessageStorage::AdsmCacheRecovery (int& len, char*& pszMsg)
{

	return m_pAdsmMsgLogger->CacheRecovery(len, pszMsg);
}

bool CMessageStorage::DfmCacheRecovery (int& len, char*& pszMsg)
{

	return m_pDfmMsgLogger->CacheRecovery(len, pszMsg);
}*/

//*************************************** Utility Functions **********************************************

void CMessageStorage::TrimSecs (std::string& stTime)
{
	stTime = stTime.substr(0, 12);
}

void CMessageStorage::ExtractHourMin (std::string& stTime, char*& stHour, char*& stMin)
{
	stTime.copy(stHour, 2, 8);
	stTime.copy(stMin, 2, 10);
}

void CMessageStorage::ExtractMinVal (std::string& stTimeVal, std::string& stMinute, std::string& stValue)
{
	char* stMin = new char[3];
	char* stVal = new char[stTimeVal.length() - 12];

	stMin[2] = '\0';
	stVal[stTimeVal.length() - 12 - 1] = '\0';
	
	stTimeVal.copy(stMin, 2, 10);
	stTimeVal.copy(stVal, stTimeVal.length() - 12, 13);
	
	stMinute = stMin;
	stValue = stVal;

	delete []stMin;
	delete []stVal;
}

void CMessageStorage::ExtractHourVal (std::string& stTimeVal, std::string& stHour, std::string& stValue)
{
	char* stHr = new char[3];
	char* stVal = new char[stTimeVal.length() - 12];

	stHr[2] = '\0';
	stVal[stTimeVal.length() - 12 - 1] = '\0';
	
	stTimeVal.copy(stHr, 2, 8);
	stTimeVal.copy(stVal, stTimeVal.length() - 12, 13);
	
	stHour = stHr;
	stValue = stVal;

	delete []stHr;
	delete []stVal;
}

bool CMessageStorage::DayHourKeyPresent (std::string& stTime, std::string& stKey)
{
	return (stTime.compare(6, 4, stKey, 0, 4) == 0) ? true:false;
}

bool CMessageStorage::DayKeyPresent (std::string& stTime, std::string& stKey)
{
	return (stTime.compare(6, 2, stKey, 0, 2) == 0) ? true:false;
}

bool CMessageStorage::ContainsOnlyZero (std::string & str)
{
	for(int i = 0; i < str.length(); i++)
		if(str[i] != '0')
		{
			if(str[i] != '.')
				return false;
		}

	return true;
}

//######################################### END: Utility Functions #####################################

//****************************************** Refresh Data **********************************************

void CMessageStorage::AddRefreshData(std::string & stSymbol, std::string & stMarket, MapTagVal& mpTagVal, std::string& stExStats, std::string& stIndexLastValues)
{
	try
	{
		
	
		std::string stSymMkt = stSymbol + "/" + stMarket;
		
		IteratorTagVal iterTagVal = mpTagVal.begin();
			
		if( m_mpTagMsg.find(stSymMkt) != m_mpTagMsg.end())//If the stSymMkt and its associated record exists
		{
			MapTagVal* mp = &m_mpTagMsg[stSymMkt];

			while(iterTagVal != mpTagVal.end())
			{

				std::string stTag = iterTagVal->first;
				std::string stVal = iterTagVal->second;

				IteratorTagVal iterMsg = mp->find(stTag);//Finding the record associated with the Tag

				if(iterMsg != mp->end())
				{
					if( !ContainsOnlyZero(stVal) )
						iterMsg->second = stVal;
				}
				else
					mp->insert(MapTagVal::value_type(stTag, stVal));
					
					iterTagVal++;	
			}
		}
		else
			m_mpTagMsg.insert(MapTagMsg::value_type(stSymMkt, mpTagVal));

		std::string stExchange = "";

		int i = stMarket.find('/');

		stExchange = stMarket.substr(0, i);

		if(stExStats != "")
			m_mpExStatsMsg[stExchange] = stExStats;

		if(stIndexLastValues != "")
			m_mpIndexLastValues[stExchange] = stIndexLastValues;

	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
	}
}


void CMessageStorage::Refresh (std::vector<std::string>& vtMsgs)
{
	try
	{
		std::string stHeader = "MDF;";

		for (int nIndex ; nIndex < m_vtIPEndPoints.size() ; nIndex++)
		{
			STIPEndPoint oIPEndPoint = m_vtIPEndPoints[nIndex];

			if ( m_mpExStatsMsg.find( oIPEndPoint.stExchange.c_str() ) != m_mpExStatsMsg.end() )
			{
				vtMsgs.push_back( stHeader + "102=" + oIPEndPoint.stExchange.c_str() + ";" + m_mpExStatsMsg[ oIPEndPoint.stExchange.c_str() ] );
			}

			if ( m_mpIndexLastValues.find( oIPEndPoint.stExchange.c_str()  ) != m_mpIndexLastValues.end() )
			{
				vtMsgs.push_back( stHeader + "102=" + oIPEndPoint.stExchange.c_str()  + ";" + m_mpIndexLastValues[ oIPEndPoint.stExchange.c_str() ] );
			}
		}

		std::string stMdfMsg = "";
		IteratorTagVal itTagValue;

		IteratorTagMsg itTagMap = m_mpTagMsg.begin();
		for ( ; itTagMap != m_mpTagMsg.end(); itTagMap++)
		{
			stMdfMsg = "MDF;";
			
			itTagValue = itTagMap->second.begin();			
			for( ; itTagValue != itTagMap->second.end(); itTagValue++)
				stMdfMsg += itTagValue->first + "=" + itTagValue->second + ";";

			vtMsgs.push_back( stMdfMsg );
		}		
		
/*
		if( m_mpExStatsMsg.find("ADSM") != m_mpExStatsMsg.end() )
		{
			stRow += "102=ADSM;" + m_mpExStatsMsg["ADSM"];
			vtMsgs.push_back(stRow);
		}

		if( m_mpExStatsMsg.find("DFM") != m_mpExStatsMsg.end() )
		{
			stRow = "MDF;";
			stRow += "102=DFM;" + m_mpExStatsMsg["DFM"];
			vtMsgs.push_back(stRow);
		}

		if(m_mpIndexLastValues.find("ADSM") != m_mpIndexLastValues.end())
		{
			stRow = "MDF;";
			stRow += "102=ADSM;" + m_mpIndexLastValues["ADSM"];
			vtMsgs.push_back(stRow);
		}

		if(m_mpIndexLastValues.find("DFM") != m_mpIndexLastValues.end())
		{
			stRow = "MDF;";
			stRow += "102=DFM;" + m_mpIndexLastValues["DFM"];
			vtMsgs.push_back(stRow);
		}

		

		for(IteratorTagMsg iter = m_mpTagMsg.begin(); iter != m_mpTagMsg.end(); iter++)
		{
			std::string stRow = "MDF;";
			std::string stMktID = "";
			std::string stMktStats = "";

			std::string stTimeStamp;

			IteratorTagVal iterMap = iter->second.begin();
			
			for( ;iterMap != iter->second.end(); iterMap++)
			{
				if(iterMap->first == "102")
					stMktID = iterMap->second;
*/						
/*				if(iterMap->first == "117")		//TradeTimeTag is Present
				{
				
					stTimeStamp = iterMap->first + "=" + iterMap->second+";";
					continue;
				}

				stRow += iterMap->first + "=" + iterMap->second + ";";

			}
			*/

/*			if(stMktID != "")
			{
				std::string stExchange = "";

				int i = stMktID.find('/');

				stExchange = stMktID.substr(0, i);
	
				if(GetLastMktVol(stExchange, stMktStats))
				{
					std::string stTimeVal = "";//TagID = "117"
					std::string stMktVol = ""; //TagID = "250"
					char ch = ' ';
					bool bl = false;

					for(int i = 0; i < stMktStats.length(); i++)
					{
						ch = stMktStats[i];

						if(!bl)
						{
							if(ch == ';')
							{
								bl = true;
								continue;
							}
							else
								stTimeVal += ch;
						}
						else
							stMktVol += ch;
												
					}

					stRow += "117=" + stTimeVal + "000000" + ";250=" + stMktVol + ";";
				}
				else
					stRow += stTimeStamp;

			}

			vtMsgs.push_back(stRow);
		}		
		*/		
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
	}
}

void CMessageStorage::RefreshStateChangeMsgs(std::vector<std::string>& vtMsgs)
{
	m_objStateChangeMutex.acquire_read();
	
	StateChangeIterator mpIterator = m_mpStateChangeMsgs.begin();
	
	for ( ; mpIterator != m_mpStateChangeMsgs.end() ; mpIterator++ )
	{
		StringList vtStateChangeMsgList = mpIterator->second;
		
		for (int iIndex = 0 ; iIndex < vtStateChangeMsgList.size() ; iIndex++)
		{
			vtMsgs.push_back( vtStateChangeMsgList[ iIndex ] );
		}
	}
	
	m_objStateChangeMutex.release();		
}

//###################################### END: Refresh Data ##################################################

//************************************* Symbol Volume Graph Data *********************************************

void CMessageStorage::AddSymVolGraphData(std::string & stSymbol, std::string & stMarket, std::string & stTradeTime, std::string & stLastVol)
{
	try
	{
	
		TrimSecs(stTradeTime);
		std::string stKey = stSymbol + "/" + stMarket;
		std::string stData = stTradeTime + ";" + stLastVol;

		if(m_mpSymVolGraph.find(stKey) != m_mpSymVolGraph.end())
		{
	//		int len = m_mpSymVolGraph[stKey].size();

			std::vector<std::string>* vt = &m_mpSymVolGraph[stKey];
			int i = 0;
			for(int i = 0; i < vt->size(); i++)
			{
				int n = (*vt)[i].find(stTradeTime);

				if( n != -1)
				{
					(*vt)[i] = stData;
					break;
				}
			}

			if(i == vt->size())
				vt->push_back(stData);
		}
		else
		{
			std::vector<std::string> vt;
			vt.push_back(stData);

			m_mpSymVolGraph.insert(MapSymMktGraphData::value_type(stKey, vt));
		}
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
	}
}

bool CMessageStorage::GetDaySymbolVolGraphData(std::string& stSymMktKey, std::string& stDay, std::string& stSymVolGraphData)
{
	try
	{
	
		MapStrVtInt mpStrVtInt;

		if(m_mpSymVolGraph.find(stSymMktKey) != m_mpSymVolGraph.end())//Finding the SymbolMarket Pair
		{
			std::vector<std::string>* vt = &m_mpSymVolGraph[stSymMktKey];
		
			for(int i = 0; i < vt->size(); i++)//For Each TimeStamp;Value Pairs
			{
				std::string* str = &(*vt)[i];

				if(DayKeyPresent(*str, stDay) )//If that TimeStamp Contains the Specified Day
				{
					std::string stHour;
					std::string stVal;

					ExtractHourVal(*str, stHour, stVal);//Extracting the Hour From Time Stamp and 
														//Associating it with the Value ( which is converted in double)
					if(mpStrVtInt.find(stHour) != mpStrVtInt.end())//If that hour has occured before
					{
						mpStrVtInt[stHour].push_back(atoi(stVal.c_str()));//save the values in Vector
					}
					else
					{
						std::vector<int> vt;

						vt.push_back(atoi(stVal.c_str()));

						mpStrVtInt.insert(MapStrVtInt::value_type(stHour, vt));
					}
					
				}
			}

			IeratorStrVtInt it = mpStrVtInt.begin();

			bool b = true;

			for( ; it != mpStrVtInt.end(); it++)//For Each Hour
			{
				int nVal = 0;

				std::vector<int>* vt = &(it->second);

				for(int i = 0; i < vt->size(); i++)//Averaging the minute values
					nVal += (*vt)[i];

				nVal = nVal/vt->size();
				
				char buff[12];

				std::string stVal = itoa(nVal, buff, 10);

				if(b)
					stSymVolGraphData += it->first + ";" + stVal;//Creating Hour;Val Tuples
				else
					stSymVolGraphData += "?" + it->first + ";" + stVal;

				b = false;
					
			}

			stSymVolGraphData += "~\r\n";

			if(b)
				return false;

			return true;
		}

		return false;
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}

bool CMessageStorage::GetHourSymbolVolGraphData(std::string& stSymMktKey, std::string& stDayHour, std::string& stSymVolGraphData)
{
	try
	{
	
		if(m_mpSymVolGraph.find(stSymMktKey) != m_mpSymVolGraph.end())
		{
			std::vector<std::string>* vt = &m_mpSymVolGraph[stSymMktKey];

			bool b = true;

			for(int i = 0; i < vt->size(); i++)
			{
				std::string* str = &(*vt)[i];

				if(DayHourKeyPresent(*str, stDayHour) )//If Specified Day and Specified Hour is Present
				{
					std::string stMinute;
					std::string stVal;

					ExtractMinVal(*str, stMinute, stVal);//Extracting that Hour's (Minute, Value) Pair

					if(b)
						stSymVolGraphData += stMinute + ";" + stVal;
					else
						stSymVolGraphData += "?" + stMinute + ";" + stVal;

					b = false;
				}
			}

			stSymVolGraphData += "~\r\n";

			if(b)
				return false;

			return true;
		}

		return false;
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}
//#################################### END: Symbol Volume Graph Data #######################################

//************************************ Symbol Price Graph Data ***********************************************

void CMessageStorage::AddSymPxGraphData(std::string & stSymbol, std::string & stMarket, std::string & stTradeTime, std::string & stLastPx)
{
	try
	{
	
		TrimSecs(stTradeTime);
		
		std::string stKey = stSymbol + "/" + stMarket;
		std::string stData = stTradeTime + ";" + stLastPx;

		if(m_mpSymPxGraph.find(stKey) != m_mpSymPxGraph.end())
		{
	//		int len = m_mpSymPxGraph[stKey].size();

			std::vector<std::string>* vt = &m_mpSymPxGraph[stKey];
			int i = 0;
			for(i = 0; i < vt->size(); i++)
			{
				int n = (*vt)[i].find(stTradeTime);

				if( n != -1)
				{
					(*vt)[i] = stData;
					break;
				}
			}

			if(i == vt->size())
				vt->push_back(stData);
		}
		else
		{
			std::vector<std::string> vt;
			vt.push_back(stData);

			m_mpSymPxGraph.insert(MapSymMktGraphData::value_type(stKey, vt));
		}
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
	}
}

bool CMessageStorage::GetDaySymbolPxGraphData(std::string& stSymMktKey, std::string& stDay, std::string& stSymPxGraphData)
{
	try
	{
	
		MapStrVtDouble mpStrVtDouble;

		if(m_mpSymPxGraph.find(stSymMktKey) != m_mpSymPxGraph.end())//Finding the SymbolMarket Pair
		{
			std::vector<std::string>* vt = &m_mpSymPxGraph[stSymMktKey];
		
			for(int i = 0; i < vt->size(); i++)//For Each TimeStamp;Value Pairs
			{
				std::string* str = &(*vt)[i];

				if(DayKeyPresent(*str, stDay) )//If that TimeStamp Contains the Specified Day
				{
					std::string stHour;
					std::string stVal;

					ExtractHourVal(*str, stHour, stVal);//Extracting the Hour From Time Stamp and 
														//Associating it with the Value ( which is converted in double)
					char* stopstring = '\0';
					if(mpStrVtDouble.find(stHour) != mpStrVtDouble.end())//If that hour has occured before
					{
						mpStrVtDouble[stHour].push_back(strtod(stVal.c_str(), &stopstring ));//save the values in Vector
					}
					else
					{
						std::vector<double> vt;

						vt.push_back(strtod(stVal.c_str(), &stopstring ));

						mpStrVtDouble.insert(MapStrVtDouble::value_type(stHour, vt));
					}
					
				}
			}

			IteratorStrVtDouble it = mpStrVtDouble.begin();

			bool b = true;

			for( ; it != mpStrVtDouble.end(); it++)//For Each Hour
			{
				double dVal = 0.0;

				std::vector<double>* vt = &(it->second);

				for(int i = 0; i < vt->size(); i++)//Averaging the minute values
					dVal += (*vt)[i];

				dVal = dVal/vt->size();
				
				char buff[12];

				std::string stVal = _gcvt(dVal, 12, buff);

				if(b)
					stSymPxGraphData += it->first + ";" + stVal;//Creating Hour;Val Tuples
				else
					stSymPxGraphData += "?" + it->first + ";" + stVal;

				b = false;
					
			}

			stSymPxGraphData += "~\r\n";

			if(b)
				return false;

			return true;
		}

		return false;
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}

bool CMessageStorage::GetHourSymbolPxGraphData(std::string& stSymMktKey, std::string& stDayHour, std::string& stSymPxGraphData)
{

	try
	{
	
		if(m_mpSymPxGraph.find(stSymMktKey) != m_mpSymPxGraph.end())
		{
			std::vector<std::string>* vt = &m_mpSymPxGraph[stSymMktKey];

			bool b = true;

			for(int i = 0; i < vt->size(); i++)
			{
				std::string* str = &(*vt)[i];

				if(DayHourKeyPresent(*str, stDayHour) )
				{
					std::string stMinute;
					std::string stVal;

					ExtractMinVal(*str, stMinute, stVal);

					if(b)
						stSymPxGraphData += stMinute + ";" + stVal;
					else
						stSymPxGraphData += "?" + stMinute + ";" + stVal;

					b = false;
				}
			}

			stSymPxGraphData += "~\r\n";

			if(b)
				return false;

			return true;
		}

		return false;
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}
//#################################### END: Symbol Price Graph Data #########################################

//******************************************** Market Index Graph Data **************************************

void CMessageStorage::AddMarketIndGraphData(std::string & stExchange, std::string & stTradeTime, std::string& stMktSector, std::string& stSectorIndex)
{
	try
	{
	
		m_MktIndexContainer.AddIndex(stExchange, stTradeTime, stMktSector, stSectorIndex);
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
	}
}

bool CMessageStorage::GetDayHourMarketIndGraphData(std::string& stMktKey, std::string& stDayHour, std::string& stMktGraphData)
{
	try
	{
	
		return m_MktIndexContainer.GetDayHourMarketIndGraphData(stMktKey, stDayHour, stMktGraphData);
	}

	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}


bool CMessageStorage::GetDayMarketIndGraphData(std::string& stMktKey, std::string& stDay, std::string& stMktGraphData)
{
	try
	{
	
		return m_MktIndexContainer.GetDayMarketIndGraphData(stMktKey, stDay, stMktGraphData);
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}

//######################################## END: Market Index Graph Data #######################################

//**************************************** Market Volume Graph Data *******************************************

void CMessageStorage::AddMarketVolGraphData (std::string & stMarket, std::string & stTradeTime, std::string & stLastVol)
{

	try
	{
	
		TrimSecs(stTradeTime);
		std::string stStatsData = stTradeTime + ";" + stLastVol;

		if(m_mpMktVolGraph.find(stMarket) != m_mpMktVolGraph.end())
		{
	//		int len = m_mpMktVolGraph[stMarket].size();
			std::vector<std::string>* vt = &m_mpMktVolGraph[stMarket];
			int i = 0;
			for(i = 0; i < vt->size(); i++)
			{
				int n = (*vt)[i].find(stTradeTime);

				if( n != -1)
				{
					(*vt)[i] = stStatsData;
					break;
				}
			}

			if(i == vt->size())
				vt->push_back(stStatsData);
		}
		else
		{
			std::vector<std::string> vt;
			vt.push_back(stStatsData);

			m_mpMktVolGraph.insert(MapMktStatsData::value_type(stMarket, vt));
		}
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
	}
}

bool CMessageStorage::GetDayMarketVolGraphData(std::string& stMktKey, std::string& stDay, std::string& stMktGraphData)
{

	try
	{
	
		MapStrVtInt mpStrVtInt;

		if(m_mpMktVolGraph.find(stMktKey) != m_mpMktVolGraph.end())//Finding the Market 
		{
			std::vector<std::string>* vt = &m_mpMktVolGraph[stMktKey];
		
			for(int i = 0; i < vt->size(); i++)//For Each TimeStamp;Value Pairs
			{
				std::string* str = &(*vt)[i];

				if(DayKeyPresent(*str, stDay) )//If that TimeStamp Contains the Specified Day
				{
					std::string stHour;
					std::string stVal;

					ExtractHourVal(*str, stHour, stVal);//Extracting the Hour From Time Stamp and 
														//Associating it with the Value ( which is converted in double)
					char* stopstring = '\0';
					if(mpStrVtInt.find(stHour) != mpStrVtInt.end())//If that hour has occured before
					{
						mpStrVtInt[stHour].push_back(atoi(stVal.c_str()));//save the values in Vector
					}
					else
					{
						std::vector<int> vt;

						vt.push_back(atoi(stVal.c_str()));

						mpStrVtInt.insert(MapStrVtInt::value_type(stHour, vt));
					}
					
				}
			}

			IeratorStrVtInt it = mpStrVtInt.begin();

			bool b = true;

			for( ; it != mpStrVtInt.end(); it++)//For Each Hour
			{
				int nVal = 0;

				std::vector<int>* vt = &(it->second);

				for(int i = 0; i < vt->size(); i++)//Averaging the minute values
					nVal += (*vt)[i];

				nVal = nVal/vt->size();
				
				char buff[12];

				std::string stVal = itoa(nVal, buff, 10);

				if(b)
					stMktGraphData += it->first + ";" + stVal;//Creating Hour;Val Tuples
				else
					stMktGraphData += "?" + it->first + ";" + stVal;

				b = false;
					
			}

			stMktGraphData += "~\r\n";

			if(b)
				return false;

			return true;
		}

		return false;
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}

bool CMessageStorage::GetHourMarketVolGraphData(std::string& stMktKey, std::string& stDayHour, std::string& stMktGraphData)
{	
	try
	{
	
		if(m_mpMktVolGraph.find(stMktKey) != m_mpMktVolGraph.end())
		{
			std::vector<std::string>* vt = &m_mpMktVolGraph[stMktKey];

			bool b = true;

			for(int i = 0; i < vt->size(); i++)
			{
				std::string* str = &(*vt)[i];

				if(DayHourKeyPresent(*str, stDayHour) )
				{
					std::string stMinute;
					std::string stVal;

					ExtractMinVal(*str, stMinute, stVal);

					if(b)
						stMktGraphData += stMinute + ";" + stVal;
					else
						stMktGraphData += "?" + stMinute + ";" + stVal;

					b = false;
				}
			}

			stMktGraphData += "~\r\n";

			if(b)
				return false;

			return true;
		}

		return false;
	
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}

bool CMessageStorage::GetLastMktVol(std::string& stExchange, std::string& stStatsData)
{
	//ACE_READ_GUARD_RETURN (ACE_Recursive_Thread_Mutex, GetLastMktVol, m_RwThreadMutex4, -1);

	try
	{	
		if (m_mpMktVolGraph.find(stExchange) != m_mpMktVolGraph.end())
		{
			stStatsData = m_mpMktVolGraph[stExchange][m_mpMktVolGraph[stExchange].size() - 1];			
			return true;
		}
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
	}
	
	return false;
}
//######################################## END: Market Volume Graph Data ######################################


//************************************* Market By Order Data *****************************************

void CMessageStorage::AddMBOData(std::string & stSymbol, std::string & stMarket, std::string& stData)
{	

	try
	{
		std::string stSymMkt = stSymbol + "/" + stMarket;

		if(m_mpMBOMsg.find(stSymMkt) != m_mpMBOMsg.end())
			m_mpMBOMsg[stSymMkt] = stData;
		else
			m_mpMBOMsg.insert(MapTagVal::value_type(stSymMkt, stData));
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
	}
}

bool CMessageStorage::GetMarketByOrderData(std::string& stSymMktKey, std::string& stData)
{

	try
	{
		if(m_mpMBOMsg.find(stSymMktKey) != m_mpMBOMsg.end())
		{
			stData += m_mpMBOMsg[stSymMktKey] + "~\r\n";
			return true;
		}
		
		stData += "~\r\n";
		return true;
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}	
}
//#################################### END: Market By Order Data ########################################

//*********************************** Market By Price Data *****************************************
	
void CMessageStorage::AddMBPData(std::string & stSymbol, std::string & stMarket, std::string& stData)
{
	try
	{
	
		std::string stSymMkt = stSymbol + "/" + stMarket;

		if(m_mpMBPMsg.find(stSymMkt) != m_mpMBPMsg.end())
			m_mpMBPMsg[stSymMkt] = stData;
		else
			m_mpMBPMsg.insert(MapTagVal::value_type(stSymMkt, stData));

#ifdef _MBP_MBO_OP_
		
		CMessageProcessor::Instance()->publishMBPDataToClient( stSymMkt, stData );

#endif // _MBP_MBO_OP_
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
	}

}


bool CMessageStorage::GetMarketByPriceData(std::string& stSymMktKey, std::string& stData)
{	
	try
	{	
		if(m_mpMBPMsg.find(stSymMktKey) != m_mpMBPMsg.end())
		{
			stData += m_mpMBPMsg[stSymMktKey] + "~\r\n";
			return true;
		}
		
		stData += "~\r\n";
		return true;
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}
//####################################### END: Market By Price Data ################################

//************************************* Market Activity Data *****************************************

void CMessageStorage::AddMarketActivityData(std::string & stMarket, std::string& stData)
{

	try
	{
		if(m_mpMarketActivityMsg.find(stMarket) != m_mpMarketActivityMsg.end())
			m_mpMarketActivityMsg[stMarket] = stData;
		else
			m_mpMarketActivityMsg.insert(MapTagVal::value_type(stMarket, stData));
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
	}
}

bool CMessageStorage::GetMarketActivityData(std::string & stMarket, std::string& stData)
{

	try
	{
		if(m_mpMarketActivityMsg.find(stMarket) != m_mpMarketActivityMsg.end())
		{
			std::string stMarketStatus = "";

			GetMarketStatusData(stMarket, stMarketStatus);

			stData += m_mpMarketActivityMsg[stMarket] + stMarketStatus + "~\r\n";
			return true;
		}

		return false;
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}
//#################################### END: Market Activity Data ########################################

//************************************* Sector Activity Data *****************************************

void CMessageStorage::AddSectorActivityData(std::string & stExchange, std::string & stMktSector, std::string& stData)
{

	m_MktActivityContainer.AddSectorData(stExchange, stMktSector, stData);
}

bool CMessageStorage::GetSectorActivityData(std::string & stMarketSector, std::string& stData)
{	
	std::string stMarket = "";

	std::string stMktSector = "";

	int i = stMarketSector.find('/');

	stMktSector = stMarketSector.substr(0, i);
	stMarket   = stMarketSector.erase(0, i+1);

	return m_MktActivityContainer.GetSectorData(stMarket, stMktSector, stData);
}

//#################################### END: Sector Activity Data ########################################

//************************************* Market Status Data *****************************************

void CMessageStorage::AddMarketStatusData(std::string & stMarket, std::string& stData)
{

	try
	{
		if(m_mpMarketStatusMsg.find(stMarket) != m_mpMarketStatusMsg.end())
			m_mpMarketStatusMsg[stMarket] = stData;
		else
			m_mpMarketStatusMsg.insert(MapTagVal::value_type(stMarket, stData));
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
	}
}

// Called By GetMarketActivityData
bool CMessageStorage::GetMarketStatusData(std::string & stMarket, std::string& stData)
{

	try
	{
		if(m_mpMarketStatusMsg.find(stMarket) != m_mpMarketStatusMsg.end())
		{
			stData = m_mpMarketStatusMsg[stMarket];
			return true;
		}

		return false;
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}
//#################################### END: Market Status Data ########################################

//************************************* Exchange Activity Data *****************************************

void CMessageStorage::AddExActivityData(std::string & stExchange, std::string& stData)
{

	m_mpExActivityMsg[stExchange] = stData;
}

bool CMessageStorage::GetExActivityData(std::string & stExchange, std::string& stData)
{

	if(m_mpExActivityMsg.find(stExchange) != m_mpExActivityMsg.end())
	{
		stData += m_mpExActivityMsg[stExchange] + "~\r\n";
		return true;
	}

	return false;
}


//#################################### END: Exchange Activity Data ########################################

// ************************************* Obsolete Functions ***************************************

bool CMessageStorage::GetSymbolVolGraphData(std::string& stSymMktKey, std::string& stSymVolGraphData)
{
	try
	{
		if(m_mpSymVolGraph.find(stSymMktKey) != m_mpSymVolGraph.end())
		{
			std::vector<std::string> vt = m_mpSymVolGraph[stSymMktKey];

			for(int i = 0; i < vt.size(); i++)
			{
				stSymVolGraphData += vt[i];
				
				if(i < (vt.size() - 1))
					stSymVolGraphData += "?";
				
			}

			stSymVolGraphData += "~\r\n";
			return true;
		}

		return false;
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
	
}



bool CMessageStorage::GetSymbolPxGraphData(std::string& stSymMktKey, std::string& stSymPxGraphData)
{
	try
	{
		if(m_mpSymPxGraph.find(stSymMktKey) != m_mpSymPxGraph.end())
		{
			std::vector<std::string> vt = m_mpSymPxGraph[stSymMktKey];

			for(int i = 0; i < vt.size(); i++)
			{
				stSymPxGraphData += vt[i];
				
				if(i < (vt.size() - 1))
					stSymPxGraphData += "?";
				
			}

			stSymPxGraphData += "~\r\n";
			return true;
		}

		return false;

	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
	
}



bool CMessageStorage::GetMarketVolGraphData(std::string& stMktKey, std::string& stMktGraphData)
{
	try
	{
		if(m_mpMktVolGraph.find(stMktKey) != m_mpMktVolGraph.end())
		{
			std::vector<std::string> vt = m_mpMktVolGraph[stMktKey];

			for(int i = 0; i < vt.size(); i++)
			{
				stMktGraphData += vt[i];

				if(i < (vt.size() - 1))
					stMktGraphData += "?";
			}

			stMktGraphData += "~\r\n";
			return true;
		}

		return false;
	}
	catch(std::exception *ex)
	{
		std::cout<<ex->what()<<std::endl;
		return false;
	}
}

int CMessageStorage::AddStateChangeMessage(const char* stExchange, const char* stMdfMessage)
{
	StringList vtStateChangeMsgList;

	m_objStateChangeMutex.acquire_write();

	if ( m_mpStateChangeMsgs.find( stExchange ) != m_mpStateChangeMsgs.end() )
	{
		vtStateChangeMsgList = m_mpStateChangeMsgs[ stExchange ];
	}

	vtStateChangeMsgList.push_back( stMdfMessage );
	
	m_mpStateChangeMsgs[ stExchange ] = vtStateChangeMsgList;

	m_objStateChangeMutex.release();

	return 1;
}

/*
bool CMessageStorage::GetMarketIndGraphData(std::string& stMktKey, std::string& stMktGraphData)
{
	CAppLogger::Instance()->AtomicWrite("CMessageStorage::GetMarketIndGraphData [Entered]");
	
	if(m_mpMktIndGraph.find(stMktKey) != m_mpMktIndGraph.end())
	{
		std::vector<std::string> vt = m_mpMktIndGraph[stMktKey];

		for(int i = 0; i < vt.size(); i++)
		{
			stMktGraphData += vt[i];

			if(i < (vt.size() - 1))
				stMktGraphData += "?";
		}

		 stMktGraphData += "~\r\n";

	 	CAppLogger::Instance()->AtomicWrite("CMessageStorage::GetMarketIndGraphData (Exit)");

		return true;
	}

 	CAppLogger::Instance()->AtomicWrite("CMessageStorage::GetMarketIndGraphData (Exit)");

	return false;
}*/







//Use it for adding index data against time
/*void CMessageStorage::AddMarketIndGraphData(std::string & stMarket, std::string & stTradeTime, std::string& stMktSector, std::string& stSectorIndex)
{
	TrimSecs(stTradeTime);
	std::string stIndexData = stTradeTime + ";" + stMktSector + ";" + stSectorIndex;

	if(m_mpMktIndGraph.find(stMarket) != m_mpMktIndGraph.end())
	{
//		int len = m_mpMktIndGraph[stMarket].size();
		m_mpMktIndGraph[stMarket].push_back(stIndexData);
	}
	else
	{
		std::vector<std::string> vt;
		vt.push_back(stIndexData);

		m_mpMktIndGraph.insert(MapMktStatsData::value_type(stMarket, vt));
	}
}*/

//########################################## END: Obsolete Funcitons #########################################

//////////////////////////////////////////////////////////////////////////
// Code added by A.H. on February 1st, 2007
//////////////////////////////////////////////////////////////////////////


int CMessageStorage::Init(std::vector<STIPEndPoint> vtIPEndPoints)
{
	m_vtIPEndPoints = vtIPEndPoints;
	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CMessageStorage::Close()
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CMessageStorage::CacheRecovery()
{
	/*
	int nLength = 0, nCount = 0;
	char* pszMessage = NULL;
	
	CMessageProcessor* pMsgPrcsr = CMessageProcessor::Instance();

	MsgLoggerMap::iterator itIter = m_mpMsgLoggers.begin();
	for ( ; itIter != m_mpMsgLoggers.end() ; itIter++)
	{
		ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
		ACE_DEBUG( ( LM_DEBUG, "(%t) Recovering messages for '%s'\n\n", itIter->first.c_str() ) );
		
		nCount = 0;
		while ( itIter->second->pLogHandler->CacheRecovery( nLength, pszMessage ) )
		{
			pMsgPrcsr->InterpretMessage( pszMessage, nLength, itIter->first, false );
			nCount++;
		}

		ACE_DEBUG( ( LM_DEBUG, "(%t) On %D\n" ) );
		ACE_DEBUG( ( LM_DEBUG, "(%t) Total messages recovered for '%s' = %d\n\n", itIter->first.c_str(), nCount ) );
	}
	*/
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
