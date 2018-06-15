
#include "LIBXML.h"
#include <libxml/xpath.h>
#include <libxml/tree.h>

/////////////////  CLIBXML_DOM_Attribute /////////////////

CLIBXML_DOM_Attribute::CLIBXML_DOM_Attribute( xmlNodePtr pNode ) : m_pNode( pNode ) 
{

}


CLIBXML_DOM_Attribute::~CLIBXML_DOM_Attribute() 
{

}


bool CLIBXML_DOM_Attribute::get( const std::string &stName, std::string &stValue )
{
	xmlChar* xchResult = xmlGetProp( m_pNode, (const xmlChar*) stName.c_str() );
    
	if( xchResult == NULL ) 
		return false;

    stValue = ( char* ) xchResult;

    return true;
}


CLIBXML_DOM_Attribute::map CLIBXML_DOM_Attribute::ToMap( void )
{
	xmlAttr* Attr = m_pNode->properties;

    CLIBXML_DOM_Attribute::map map;

    while( Attr != 0 )
    {
      std::string stValue;
      std::string stName = ( char* )Attr->name;

      get( stName, stValue );
      map[ stName ] = stValue;

      Attr = Attr->next;
    }   
    return map;
}

/////////////////  CLIBXML_DOM_Attribute /////////////////

/////////////////  CLIBXML_DOM_Node  /////////////////

CLIBXML_DOM_Node::CLIBXML_DOM_Node( xmlNodePtr pNode ) : m_pNode( pNode )
{

}
	
CLIBXML_DOM_Node::~CLIBXML_DOM_Node() 
{

}
	
DOMNodePtr CLIBXML_DOM_Node::getFirstChildNode()
{
	if( !m_pNode->children ) 
		return DOMNodePtr();

	xmlNodePtr pNode = m_pNode->children->next;

    if( pNode == NULL ) 
		return DOMNodePtr();

    return DOMNodePtr( new CLIBXML_DOM_Node( pNode ) );
}


DOMNodePtr CLIBXML_DOM_Node::getNextSiblingNode()
{
	if( !m_pNode->next ) 
		return DOMNodePtr();

    xmlNodePtr pNode = m_pNode->next->next;

    if( pNode == NULL ) 
		return DOMNodePtr();

    return DOMNodePtr( new CLIBXML_DOM_Node( pNode ) );
}

xmlNodePtr CLIBXML_DOM_Node::get()
{
	return m_pNode;
}


/////////////////  CLIBXML_DOM_Node  /////////////////

/////////////////  CLIBXML_DOM_Document /////////////////

CLIBXML_DOM_Document::CLIBXML_DOM_Document() : m_pDoc( NULL )
{

}

	
CLIBXML_DOM_Document::~CLIBXML_DOM_Document()
{

}

void CLIBXML_DOM_Document::addNode( xmlNodePtr _parent, xmlNodePtr _child )
{
	xmlAddChild(_parent, _child);
}

bool CLIBXML_DOM_Document::load( const std::string &stFile )
{
	m_pDoc = xmlParseFile( stFile.c_str() );
	return m_pDoc != NULL;
}

int CLIBXML_DOM_Document::save( const std::string &stFile )
{
	return xmlSaveFile( stFile.c_str(), m_pDoc );
}

DOMNodePtr CLIBXML_DOM_Document::getNode( const std::string &stXPath )
{
	xmlXPathContextPtr context = xmlXPathNewContext( m_pDoc );
    xmlXPathObjectPtr xpathObject = xmlXPathEval( (xmlChar*)stXPath.c_str(), context );

    if( xpathObject == NULL || xpathObject->nodesetval == NULL || xpathObject->nodesetval->nodeNr != 1 )
    {
      xmlXPathFreeContext( context );
      return DOMNodePtr();
    }

    DOMNodePtr result( new CLIBXML_DOM_Node( xpathObject->nodesetval->nodeTab[0] ) );
    xmlXPathFreeContext( context );
    xmlXPathFreeObject( xpathObject );

    return result;
}


xmlDocPtr CLIBXML_DOM_Document::get()
{
	return m_pDoc;
}


/////////////////  CLIBXML_DOM_Document /////////////////
