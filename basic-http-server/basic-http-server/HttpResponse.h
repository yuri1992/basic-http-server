#pragma once
#include "HttpRequest.h"

class HttpResponse
{
	HttpRequest *request;
	int responseCode;
	int numberOfHeaders;
	char *responesText;
	char **headers;
	char *responseData;
public:
	HttpResponse();
	~HttpResponse();
};

