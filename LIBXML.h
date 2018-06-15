#pragma once
#pragma warning( disable : 4503 4355 4786 4290 198 200 92 )
//#pragma warning( disable : 4503 4355 4786 4290 )
//#pragma comment( lib, "libxml2" )

#include <map>
#include <string>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

class CLIBXML_DOM_Attribute
{
public:

	CLIBXML_DOM_Attribute( xmlNodePtr pNode );
	virtual ~CLIBXML_DOM_Attribute() ;

	typedef std::map<std::string, std::string> map;
	bool get( const std::string&, std::string& );

	CLIBXML_DOM_Attribute::map ToMap( void );

private:	
    xmlNodePtr m_pNode;
};

typedef std::auto_ptr<CLIBXML_DOM_Attribute> DOMAttrPtr;

/////////////////////////////////////////////////////

class CLIBXML_DOM_Node
{
public:
	CLIBXML_DOM_Node( xmlNodePtr pNode );
	~CLIBXML_DOM_Node();

	std::auto_ptr<CLIBXML_DOM_Node> getFirstChildNode();
	std::auto_ptr<CLIBXML_DOM_Node> getNextSiblingNode();

	DOMAttrPtr getAttributes()
	{
		return DOMAttrPtr( new CLIBXML_DOM_Attribute( m_pNode ) );
	}

	std::string getName( void )
	{
		return ( char* ) m_pNode->name;
	}

	std::string getText( void )
	{
		return ( char* ) m_pNode->content;
	}

	const char *getFirstText( void )
	{
		return ( const char * ) m_pNode->children->content;
	}

	void setText( const std::string stText )
	{
		xmlNodeSetContent( m_pNode, (const xmlChar *) stText.c_str() );
	}

	void addText( const std::string stText )
	{
		xmlNodeAddContent( m_pNode, (const xmlChar *) stText.c_str() );
	}

	xmlNodePtr get();

private:
    xmlNodePtr m_pNode;
};

typedef std::auto_ptr<CLIBXML_DOM_Node> DOMNodePtr;

/////////////////////////////////////////////////////

class CLIBXML_DOM_Document
{
public:	
    CLIBXML_DOM_Document();
	
    ~CLIBXML_DOM_Document();
	
    //bool load( istream& );	
    bool load( const std::string& );
	int  save( const std::string& );
	void addNode(xmlNodePtr _parent, xmlNodePtr _child);
    
	DOMNodePtr getNode( const std::string& );

	const char *getTextFromPath( const std::string &pchXPath )
	{
		DOMNodePtr pFixNode = this->getNode( pchXPath.c_str() );
		if( !pFixNode.get() )
			return 0;

		return ( const char * ) pFixNode->getFirstText();
	}

	int setTextOnPath( const std::string& stXPathQuery, const std::string& value )
	{
		DOMNodePtr pNode;

		pNode = this->getNode( stXPathQuery.c_str() );

		if( !pNode.get() )
			return -1;

		pNode->setText( value.c_str() );

		return 0;
	}

	int addTextOnPath( const std::string& stXPathQuery, const std::string& value )
	{
		DOMNodePtr pNode;

		pNode = this->getNode( stXPathQuery.c_str() );

		if( !pNode.get() )
			return -1;

		pNode->addText( value.c_str() );

		return 0;
	}
		
	xmlDocPtr get();

private:	
    xmlDocPtr m_pDoc;
};

typedef std::auto_ptr<CLIBXML_DOM_Document> DOMDocumentPtr;