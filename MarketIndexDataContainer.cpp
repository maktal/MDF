#include "MarketIndexDataContainer.h"

CMarketIndexDataContainer::CMarketIndexDataContainer(void)
{
}

CMarketIndexDataContainer::~CMarketIndexDataContainer(void)
{
}

void CMarketIndexDataContainer::TrimSecs (std::string& stTime)
{
	stTime = stTime.substr(0, 12);
}

bool CMarketIndexDataContainer::DayKeyPresent (int nDayHour, std::string& stDay)
{
	try
	{
		char psz[10];

		itoa(nDayHour, psz, 10);
		
		std::string stDayHour = std::string(psz);

		if(stDayHour.length() < 4)
			stDayHour = "0" + stDayHour;

		if(stDayHour[0] == stDay[0])
			if(stDayHour[1] == stDay[1])
				return true;
	}
	catch(std::exception* ex)
	{
		std::cout<<std::endl<<ex->what()<<std::endl; 	
	}
	return false;
}

void CMarketIndexDataContainer::ExtractDayHourMin (std::string& stTime, int& nDayHour, int& nMin)
{
	//stTime example is 200512211444 //YYYYMMDDHHMMSSSS

	char pszDayHour[5];
	char pszMin[3];

	TrimSecs(stTime);//YYYYMMDDHHMM

	stTime.copy(pszDayHour, 4, 6);
	stTime.copy(pszMin, 2, 10);

	nDayHour = atoi(pszDayHour);
	nMin = atoi(pszMin);
}

void CMarketIndexDataContainer::AddIndex (std::string & stMarket, std::string & stTradeTime, std::string& stMktSector, std::string& stSectorIndex)
{
	try
	{
		int nDayHour = 0;
		int nMin = 0;
		ExtractDayHourMin(stTradeTime, nDayHour, nMin);

		double dSectorIndex = 0.0;
		char* stopstring = '\0';

		dSectorIndex = strtod(stSectorIndex.c_str(), &stopstring);
		
		Map_Minute_Index mp_MinInd;//Set Minute-MarketIndex Pair
		mp_MinInd[nMin] = dSectorIndex;
			
		Map_Hour_Min_Index mp_HrMinInd;
		mp_HrMinInd[nDayHour] = mp_MinInd;//Associate Hour with Minute-MarketIndex Pair

		Map_SectorName_Hour_Min_Index mp_SectorHrMinInd;
		mp_SectorHrMinInd[stMktSector] = mp_HrMinInd;//Associate MktSector with DayHour-Minute-MarketIndex Pair
		

		It_MktIndexData iterFirstLevel = mp_MktIndexContainer.find(stMarket);

		if(iterFirstLevel != mp_MktIndexContainer.end() )//If this Market Exists
		{
			
			Map_SectorName_Hour_Min_Index* mpSecondLevel = &(iterFirstLevel->second);
			It_SectorName_Hour_Min_Index iterSecondLevel = mpSecondLevel->find(stMktSector);

			if(iterSecondLevel != mpSecondLevel->end())//If this Market Sector Exists
			{
				Map_Hour_Min_Index* mpThirdLevel = &(iterSecondLevel->second);
				It_Hour_Min_Index iterThirdLevel = mpThirdLevel->find(nDayHour);

				if(iterThirdLevel != mpThirdLevel->end())//If this DayHour Exists
				{
					Map_Minute_Index* mpMinuteIndex = &(iterThirdLevel->second);
					
					(*mpMinuteIndex)[nMin] = dSectorIndex;//Add the index
				}
				else//Add this DayHour in this MarketSector
				{
					(*mpThirdLevel)[nDayHour] = mp_MinInd;
					
				}
			}
			else//Add this MarketSector in this Market
			{
				(*mpSecondLevel)[stMktSector] = mp_HrMinInd;

			}

		}
		else//Add the Market along with its index data
		{
			
			//Now associate Market with MktSector-DayHour-Minute-MarketIndex Pair
			mp_MktIndexContainer[stMarket] = mp_SectorHrMinInd;
		}

	}
	catch(std::exception* ex)
	{
		std::cout<<std::endl<<ex->what()<<std::endl; 	
	}
}

bool CMarketIndexDataContainer::GetDayHourMarketIndGraphData(std::string& stMktKey, std::string& stDayHour, std::string& stMktGraphData)
{
	try
	{
	
		char pszHour[3];
		char pszDay[3];
		
		stDayHour.copy(pszHour, 2, 2);
		stDayHour.copy(pszDay, 2, 0);

		int nHour = atoi(pszHour);
		int nDay = atoi(pszDay);
		int nDayHour = atoi(stDayHour.c_str());
			
		if(mp_MktIndexContainer.find(stMktKey) != mp_MktIndexContainer.end())
		{
			 It_SectorName_Hour_Min_Index it_SectorName_Hour_Min_Index = mp_MktIndexContainer[stMktKey].begin();
			
			 int nSectors = 0;
			 const std::string* stSectorName = NULL;
			 bool bDayHourRecordExist = false;

			 //Extracting Hourly Data From Each "Sector"
			 for(; it_SectorName_Hour_Min_Index != mp_MktIndexContainer[stMktKey].end(); it_SectorName_Hour_Min_Index++)
			 {
				 nSectors++;

				 stSectorName = &(it_SectorName_Hour_Min_Index->first);
				 
				 Map_Hour_Min_Index* mp_Hour_Min_Index = &(it_SectorName_Hour_Min_Index->second);

				 It_Hour_Min_Index it_Hour_Min_Index = mp_Hour_Min_Index->find(nDayHour);

				 if(it_Hour_Min_Index != mp_Hour_Min_Index->end())//If Minutely Data Exists for this hour, in this Day
				 {
					 bDayHourRecordExist = true;
					 bool bFirstRecordOfThisHour = false;

					 Map_Minute_Index* mp_Min_Index = &(it_Hour_Min_Index->second);

					 It_Minute_Index it_Minute_Index = mp_Min_Index->begin();
					 
					 for(; it_Minute_Index != mp_Min_Index->end(); it_Minute_Index++)
					 {
						 int nMin = it_Minute_Index->first;
						 double dIndex = it_Minute_Index->second;
						 char pszMin[3];
						 char pszIndex[20];
						 
						  itoa(nMin, pszMin, 10);
						  _gcvt(dIndex, 10, pszIndex);

						 std::string stMin = std::string(pszMin);
						 std::string stIndex = std::string(pszIndex);
						 
						 if(stIndex[stIndex.length() - 1] == '.')
							 stIndex += "00";
					 		
				 		 if(!bFirstRecordOfThisHour)
						 {
							 if(nSectors > 1)
								stMktGraphData += "|" + *stSectorName + "?";//adding Sector Name
							 else
								stMktGraphData += *stSectorName + "?";//adding Sector Name

							 stMktGraphData +=  stMin + ";" + stIndex;		 
						 }
						 else
							 stMktGraphData += "?" + stMin + ";" + stIndex;		 
							 
						 bFirstRecordOfThisHour = true;
					 }
					
				 }
			 }

			 if(!bDayHourRecordExist)
				 return false;

      		stMktGraphData += "~\r\n";

			return true;
		}
	}
	catch(std::exception* ex)
	{
		std::cout<<std::endl<<ex->what()<<std::endl; 	
	}
	return false;
}

bool CMarketIndexDataContainer::GetDayMarketIndGraphData(std::string& stMktKey, std::string& stDay, std::string& stMktGraphData)
{
	try
	{
		
		if(mp_MktIndexContainer.find(stMktKey) != mp_MktIndexContainer.end())
		{
			 It_SectorName_Hour_Min_Index it_SectorName_Hour_Min_Index = mp_MktIndexContainer[stMktKey].begin();
			
			 int nSectors = 0;
			 const std::string* stSectorName = NULL;
			 bool bDayRecordExist = false;

			 //Extracting Hourly Data From Each "Sector"
			 for(; it_SectorName_Hour_Min_Index != mp_MktIndexContainer[stMktKey].end(); it_SectorName_Hour_Min_Index++)
			 {
				 nSectors++;

				 stSectorName = &(it_SectorName_Hour_Min_Index->first);
				 
				 Map_Hour_Min_Index* mp_Hour_Min_Index = &(it_SectorName_Hour_Min_Index->second);

				 It_Hour_Min_Index it_Hour_Min_Index = mp_Hour_Min_Index->begin();

				 bool bFirstRecordOfThisSector = false;

				 for(; it_Hour_Min_Index != mp_Hour_Min_Index->end(); it_Hour_Min_Index++)
				 {
					 int nDayHour = it_Hour_Min_Index->first;
					 
					if(DayKeyPresent(nDayHour, stDay))
					{
						 bDayRecordExist = true;

						 Map_Minute_Index* mp_Min_Index = &(it_Hour_Min_Index->second);

						 It_Minute_Index it_Minute_Index = mp_Min_Index->begin();

						 double dIndex = 0.0;
						 int count = 0;
						
						 for(; it_Minute_Index != mp_Min_Index->end(); it_Minute_Index++)
						 {
							 dIndex += it_Minute_Index->second;
							 count++;
						 }
						
						 if (count == 0)
							 continue;
						 
						 dIndex = dIndex/count;

						 char pszIndex[20];
						 char pszHour[20];
						 
						 itoa(nDayHour, pszHour, 10);
						_gcvt(dIndex, 10, pszIndex);

						std::string stIndex = std::string(pszIndex);
						std::string stHour = std::string(pszHour);

						if(stHour.length() == 4)
							stHour = stHour.substr(2, 2);
						else if(stHour.length() == 3)
							stHour = stHour.substr(1, 2);

						if(stIndex[stIndex.length() - 1] == '.')
							 stIndex += "00";
						
						 if(!bFirstRecordOfThisSector)
						 {
							 if(nSectors > 1)
								stMktGraphData += "|" + *stSectorName + "?";//adding Sector Name
							 else
								stMktGraphData += *stSectorName + "?";//adding Sector Name

							 stMktGraphData +=  stHour + ";" + stIndex;		 
						 }
						 else
							 stMktGraphData += "?" + stHour + ";" + stIndex;		 

						 bFirstRecordOfThisSector = true;
					}
				 }
			 }

			 if(nSectors == 0)
				return false;

			 if(!bDayRecordExist)
				 return false;

      		stMktGraphData += "~\r\n";

			return true;
		}
	}
	catch(std::exception* ex)
	{
		std::cout<<std::endl<<ex->what()<<std::endl; 	
	}
	return false;
}