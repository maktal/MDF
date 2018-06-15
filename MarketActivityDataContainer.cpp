#include "MarketActivityDataContainer.h"

CMarketActivityDataContainer::CMarketActivityDataContainer(void)
{
}

CMarketActivityDataContainer::~CMarketActivityDataContainer(void)
{
}
void CMarketActivityDataContainer::AddSectorData (std::string & stMarket, std::string & stMktSector, std::string & stData)
{
	It_Market_MktSector_Data itFirstLevel = m_mpMarket_MktSector_Data.find(stMarket);

	if(itFirstLevel != m_mpMarket_MktSector_Data.end())
	{
		Map_MktSector_Data* pMktSector_Data = &(itFirstLevel->second);
		
		(*pMktSector_Data)[stMktSector] = stData;
		
	}
	else
	{
		Map_MktSector_Data mpMktSector_Data;

		mpMktSector_Data[stMktSector] = stData;

		m_mpMarket_MktSector_Data[stMarket] = mpMktSector_Data;
	}
}

bool CMarketActivityDataContainer::GetSectorData (std::string & stMarket, std::string & stMktSector, std::string & stData)
{

	It_Market_MktSector_Data itFirstLevel = m_mpMarket_MktSector_Data.find(stMarket);

	if(itFirstLevel != m_mpMarket_MktSector_Data.end())
	{
		Map_MktSector_Data* pMktSector_Data = &(itFirstLevel->second);

		It_MktSector_Data itSecondLevel = pMktSector_Data->find(stMktSector);

		if(itSecondLevel != pMktSector_Data->end())
		{
			stData += itSecondLevel->second + "~\r\n";

			return true;
		}
	}

	return false;
}