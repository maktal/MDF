#pragma once
#include <string>

#include "ace/Thread.h"

#include "ParsedMessage.h"
#include "Queue.h"

template < typename T > class IQueue;

class IMessageParser
{
protected:

	CQueue<std::string>*									m_RawMessageQueue;
	CQueue<CParsedMessage>*									m_ParsedMessageQueue;
	ACE_thread_t											m_processorThreadID;
	ACE_hthread_t											m_processorThreadHandle;

public:
	IMessageParser(){}
	virtual CParsedMessage ParseMessage(std::string _Message)  = 0;
};