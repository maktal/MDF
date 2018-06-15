#pragma once
#ifndef MARKETINDEXDATACONTAINER_H_
#define MARKETINDEXDATACONTAINER_H_

#include "Constant.h"
typedef std::map< int, double > Map_Minute_Index;
typedef std::map< int, double >::iterator It_Minute_Index;

typedef std::map< int, std::map< int, double > > Map_Hour_Min_Index;
typedef std::map< int, std::map< int, double > >::iterator It_Hour_Min_Index;

typedef std::map< std::string, std::map< int, std::map< int, double > > > Map_SectorName_Hour_Min_Index;
typedef std::map< std::string, std::map< int, std::map< int, double > > >::iterator It_SectorName_Hour_Min_Index;

			         //MarketID        //Index Name    	     //Hour       //Minute //Index Value
typedef std::map< std::string, std::map< std::string, std::map< int, std::map< int, double > > > > MapMktIndexData;
typedef std::map< std::string, std::map< std::string, std::map< int, std::map< int, double > > > >::iterator It_MktIndexData;

class CMarketIndexDataContainer
{
	MapMktIndexData mp_MktIndexContainer;

public:
	
	CMarketIndexDataContainer();
	~CMarketIndexDataContainer();

	void AddIndex (std::string & stMarket, std::string & stTradeTime, std::string& stMktSector, std::string& stSectorIndex);
	
	bool DayKeyPresent ( int nDayHour, std::string& stDay);
	void ExtractDayHourMin (std::string& stTime, int& nDayHour, int& nMin);

	bool GetDayHourMarketIndGraphData(std::string& stMktKey,  std::string& stDayHour, std::string& stMktGraphData);
	bool GetDayMarketIndGraphData(std::string& stMktKey, std::string& stDay, std::string& stMktGraphData);
	void TrimSecs (std::string& stTime);
};
#endif
