#pragma once
#ifndef MARKETACTIVITYDATACONTAINER_H_
#define MARKETACTIVITYDATACONTAINER_H_

#include "Constant.h"

typedef std::map< std::string, std::string > Map_MktSector_Data;
typedef std::map< std::string, std::string >::iterator It_MktSector_Data;

typedef std::map< std::string, std::map< std::string, std::string> > Map_Market_MktSector_Data;
typedef std::map< std::string, std::map< std::string, std::string> >::iterator It_Market_MktSector_Data;

class CMarketActivityDataContainer
{
	Map_Market_MktSector_Data m_mpMarket_MktSector_Data;

public:

	CMarketActivityDataContainer();
	~CMarketActivityDataContainer();

	void AddSectorData (std::string & stMarket, std::string & stMktSector, std::string & stData);
	bool GetSectorData (std::string & stMarket, std::string & stMktSector, std::string & stData);
};
#endif