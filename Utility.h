#pragma once

#include <xstring>
#include "Constant.h"

class CUtility
{
	public: static inline bool is_base64(unsigned char c) 
	{
			return (isalnum(c) || (c == '+') || (c == '/'));
	}

	public: static std::string Encode64(std::string _message) 
	{ 
		const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-";
		char* dst;
		int len = _message.size();

		int x, y = 0, i, flag=0, m=0; 
		int n = 3; 
		char triple[3], quad[4], c; 
		dst = new char[len*2];
		char* encode = new char[len*2];

		for(x = 0; x < len; x = x + 3) 
		{ 
			if((len - x) / 3 == 0) n = (len - x) % 3; 

			for(i=0; i < 3; i++) triple[i] = '0'; 
			for(i=0; i < n; i++) triple[i] = _message[x + i]; 
			quad[0] = base64_chars[(triple[0] & 0xFC) >> 2]; // FC = 11111100 
			quad[1] = base64_chars[((triple[0] & 0x03) << 4) | ((triple[1] & 0xF0) >> 4)]; // 03 = 11 
			quad[2] = base64_chars[((triple[1] & 0x0F) << 2) | ((triple[2] & 0xC0) >> 6)]; // 0F = 1111, C0=11110 
			quad[3] = base64_chars[triple[2] & 0x3F]; // 3F = 111111 
			if(n < 3) quad[3] = '='; 
			if(n < 2) quad[2] = '='; 
			for(i=0; i < 4; i++) dst[y + i] = quad[i]; 
			y = y + 4; 
			m = m + 4; 
		} 

		dst[y] = '\0'; 
		
		sprintf(encode,dst); 
		return std::string(encode); 
	}


	public: static std::string Decode64(std::string const& encoded_string)
	{
		const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-";
		int in_len = encoded_string.size();
		int i = 0;
		int j = 0;
		int in_ = 0;
		unsigned char char_array_4[4], char_array_3[3];
		std::string ret;

		while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
			char_array_4[i++] = encoded_string[in_]; in_++;
			if (i ==4) {
				for (i = 0; i <4; i++)
					char_array_4[i] = base64_chars.find(char_array_4[i]);

				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

				for (i = 0; (i < 3); i++)
					ret += char_array_3[i];
				i = 0;
			}
		}

		if (i) {
			for (j = i; j <4; j++)
				char_array_4[j] = 0;

			for (j = 0; j <4; j++)
				char_array_4[j] = base64_chars.find(char_array_4[j]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
		}

		return ret;
	}


	public: static std::string GetFormatedMessage(CParsedMessage& _message, STExchangeConnectionInfo _connInfo)
	{
		std::string _buffer;

		//-------- What Format to Send: Binary or XML --------
		switch(_connInfo.PublishFormat)
		{
		case BINARY:
			_buffer = _message.GetBinary().c_str();
			break;

		case XML:
			_buffer = _message.GetXML().c_str();
			break;
		}
		//----------------------------------------------------


		switch(_message._messageType)
		{
		case MBO:
			if(MBO == _connInfo.MBOEnabled)  return _buffer;
			break;

		case MBP:
			if(MBP == _connInfo.MBPEnabled)  return _buffer;
			break;

		case FEED:
			return _buffer;
			break;
		}

		return std::string();

	}

};

