#ifndef _HTTP_RESPONSE_
#define _HTTP_RESPONSE_

#include <string>
#include "HttpRequest.h"

const char HTTP_200[256] = "OK";
const char HTTP_201[256] = "CREATED";
const char HTTP_202[256] = "ACCEPTED";
const char HTTP_204[256] = "NO CONTENT";
const char HTTP_400[256] = "BAD REQUEST";
const char HTTP_404[256] = "NOT FOUND";
const char HTTP_500[256] = "INTERNAL ERROR";


class HttpResponse
{
	
public:
	HttpRequest* request;
	int responseCode;
	char responseCodeText[256] = {0};
	int numberOfHeaders = 0;
	bool isClosed = false;
	char **headers;
	char *responseData = nullptr;

	HttpResponse(HttpRequest* request);
	~HttpResponse();
	char* getBuffer();
	void prepareHeaders();
	void setHeader(const char* key, const char* value);
	char* getContentLength();
	char* getDateTime();
	int getResponseDataLength();
	void setResponseCodeText();
	void complete();
};

#endif