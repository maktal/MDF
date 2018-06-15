#ifndef TEST_TEST
#define TEST_TEST


//------------------------------------------------ UNIVERSAL DEFINES -------------------------------------------
#define MAX_QUEUE_BUFFER_LEN 1024   
#define CLIENT_SEQ_NO_LEN 20
#define APPLICATION_ID "1132C127-B0A8-4770-B877-CD6C3E239F12"
//***************************************************************************************************************
//***************************************************************************************************************

//------------------------------------------------ UNIVERSAL INCLUDES -------------------------------------------
#include <vector>
#include <string>
#include <Queue>
#include <map>
#include <set>
#include <iostream>
#include <conio.h>

//***************************************************************************************************************
//***************************************************************************************************************
enum ENConnectionType
{
	TCP_CLIENT = 0, UDP_CLIENT = 1, TCP_SERVER = 2
};

enum ENParserType
{
	ADSM = 0, DFM = 1, TADAWUL = 2
};

enum ENBufferStatus
{
	COMPLETE = 0, PARTIAL = 1
};

enum ENCommand
{
	ReadConfigFile  , WriteConfigFile, ReadExchangeStatus 

};

enum ENPublishFormat
{
	BINARY = 0, XML = 1
};

enum ENMessageType
{
	FEED = 0, MBO = 1, MBP = 2,MSG_ERROR = 3
};


struct STExchangeConnectionInfo
{

	/*<Exchange>
		<!-- 0 = TCP, 1 = UDP -->
		<ConnectionType>0</ConnectionType>
		<Enable>1</Enable>
		<ID>ADSM</ID>
		<IP>Skywalker</IP>
		<Port>9000</Port>
		<BufferSize>1024</BufferSize>
		<Delimiter> <![CDATA[]]> </Delimiter>
     <!-- 0 = Server, 1 = Client -->
       <MDFMode>1</MDFMode>
     
		<!-- 0 = ADSM, 1 = DFM, 2 = TADAWUL -->
		<ParserType>0</ParserType>

		<!-- 0 = Binary, 1 = XML -->
		<PublishFormat>0</PublishFormat>

		<!-- 0 = TCP, 1 = UDP -->
		<PublisherConnectionType>0</PublisherConnectionType>
		<PublishPort>10000</PublishPort>

		<MBOEnabled></MBOEnabled>
		<MBPEnabled></MBPEnabled>

		<!-- 0 = TCP, 1 = UDP -->
		<RecoveryConnectionType>0</RecoveryConnectionType>
		<RecoveryFile></RecoveryFile>
		<RecoveryPort></RecoveryPort>
		
	</Exchange>*/

	public:
		ENConnectionType	ConnectionType;
		bool				Enabled;
		std::string			ID;
		std::string			IP;
		int					Port;
		int					BufferSize;
		std::string			Delimiter;
		
		ENParserType		ParserType;  

		ENPublishFormat		PublishFormat;
		
		ENConnectionType	PublisherConnectionType;
		int					PublishPort;

		bool				MBOEnabled;
		bool				MBPEnabled;
		
		ENConnectionType	RecoveryConnectionType;
		std::string			RecoveryFile;
		int					RecoveryPort;
};

struct STMBOData
{
public:
	std::string				_Symbol;
	std::string				_Market;
	std::string				_regBkAskOrder;	
	std::string				_regBkAskTotalVol;	
	std::string				_regBkAskPrice;
	std::string				_AskOrdTotalVol1;	
	std::string				_AskOrdPrice1;	
	std::string				_AskOrdTotalVol2;	
	std::string				_AskOrdPrice2;	
	std::string				_AskOrdTotalVol3;	
	std::string				_AskOrdPrice3;	
	std::string				_AskOrdTotalVol4;	
	std::string				_AskOrdPrice4;	
	std::string				_AskOrdTotalVol5;	
	std::string				_AskOrdPrice5;	
	std::string				_AskOrdTotalVol6;	
	std::string				_AskOrdPrice6;	
	std::string				_AskOrdTotalVol7;	
	std::string				_AskOrdPrice7;	
	std::string				_AskOrdTotalVol8;	
	std::string				_AskOrdPrice8;	
	std::string				_AskOrdTotalVol9;	
	std::string				_AskOrdPrice9;	

	
	std::string				_regBkBidOrder;	
	std::string				_regBkBidTotalVol;	
	std::string				_regBkBidPrice;
	std::string				_BidOrdTotalVol1;	
	std::string				_BidOrdPrice1;	
	std::string				_BidOrdTotalVol2;	
	std::string				_BidOrdPrice2;	
	std::string				_BidOrdTotalVol3;	
	std::string				_BidOrdPrice3;	
	std::string				_BidOrdTotalVol4;	
	std::string				_BidOrdPrice4;	
	std::string				_BidOrdTotalVol5;	
	std::string				_BidOrdPrice5;	
	std::string				_BidOrdTotalVol6;	
	std::string				_BidOrdPrice6;	
	std::string				_BidOrdTotalVol7;	
	std::string				_BidOrdPrice7;	
	std::string				_BidOrdTotalVol8;	
	std::string				_BidOrdPrice8;	
	std::string				_BidOrdTotalVol9;	
	std::string				_BidOrdPrice9;	


};

struct STMBPData
{
public:
	std::string				_Symbol;
	std::string				_Market;
	std::string				_BidPriceCount;
	
	std::string				_BidPriceLevel1;
	std::string				_BidOrderLevel1;
	std::string				_BidVolLevel1;
	
	std::string				_BidPriceLevel2;
	std::string				_BidOrderLevel2;
	std::string				_BidVolLevel2;

	std::string				_BidPriceLevel3;
	std::string				_BidOrderLevel3;
	std::string				_BidVolLevel3;

	std::string				_BidPriceLevel4;
	std::string				_BidOrderLevel4;
	std::string				_BidVolLevel4;

	std::string				_BidPriceLevel5;
	std::string				_BidOrderLevel5;
	std::string				_BidVolLevel5;

	std::string				_AskPriceCount;
	
	std::string				_AskPriceLevel1;
	std::string				_AskOrderLevel1;
	std::string				_AskVolLevel1;
	
	std::string				_AskPriceLevel2;
	std::string				_AskOrderLevel2;
	std::string				_AskVolLevel2;

	std::string				_AskPriceLevel3;
	std::string				_AskOrderLevel3;
	std::string				_AskVolLevel3;

	std::string				_AskPriceLevel4;
	std::string				_AskOrderLevel4;
	std::string				_AskVolLevel4;

	std::string				_AskPriceLevel5;
	std::string				_AskOrderLevel5;
	std::string				_AskVolLevel5;

};

struct STIPEndPoint
{
	std::string stIPAddress;
	int nPort;
	int nMode;
	std::string stExchange;
	std::string stLogFileName;

	void Clear()
	{
		stIPAddress= "";
		nPort = 0;
		nMode = 0;
		stLogFileName = "";
		stExchange = "";
	}
};

//------------------------------------------------ UNIVERSAL TYPEDEFS -------------------------------------------
typedef std::vector<STExchangeConnectionInfo>  STExchangeConnectionInfoList;
typedef std::map<std::string, std::vector<int> > MapStrVtInt;
typedef std::map<std::string, std::vector<int> >::iterator IeratorStrVtInt;

typedef std::map<std::string, std::vector<double> > MapStrVtDouble;
typedef std::map<std::string, std::vector<double> >::iterator IteratorStrVtDouble;

typedef std::map<std::string, std::string > MapTagVal;
typedef std::map<std::string, std::string >::iterator IteratorTagVal;

typedef std::map<std::string, std::vector<std::string> > MapSymMktGraphData;
typedef std::map<std::string, std::vector<std::string> >::iterator IteratorSymMktGraphData;

typedef std::map<std::string, std::vector<std::string> > MapMktStatsData;
typedef std::map<std::string, std::vector<std::string> >::iterator IteratorMktStatsData;

typedef std::map<std::string, std::map < std::string, std::string> > MapTagMsg;
typedef std::map<std::string, std::map < std::string, std::string> >::iterator IteratorTagMsg;

typedef std::map<std::string, std::map < std::string, std::map <std::string, std::string> > > MapGraphData;
typedef std::map < std::string, std::map <std::string, std::string> >::iterator IteratorHours;
typedef std::map <std::string, std::string>::iterator IteratorMinutes;

typedef std::vector< std::string > 
		StringList;

typedef StringList::iterator 
		StringListIterator;

typedef std::map< std::string, StringList >
		StateChangeTable;

typedef StateChangeTable::iterator
		StateChangeIterator;

//***************************************************************************************************************
//***************************************************************************************************************

#include "ace/Svc_Handler.h"
#include "ace/SOCK_Stream.h" 
#include "ace/Process_Mutex.h"
class IExchangeConnectionHandler : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
	public:  virtual int				handle_close (ACE_HANDLE, ACE_Reactor_Mask) = 0;
	public:	 virtual ACE_INT32			handle_input(ACE_HANDLE) = 0;

	public:	 virtual std::string		GetMessage(std::string&)=0;
	public:  virtual bool				Create(void)=0;
	public:  virtual bool				Destroy(void)=0;		
	public: int 						m_Connected;
	public: std::string					Last_Connection_Time;
	public: std::string					Last_Message_Published;

};

#endif;