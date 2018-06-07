#include "stdafx.h"
#include "HttpRequest.h"


HttpRequest::HttpRequest(char* buf, int size)
{
	this->method = ILLEGAL;
	this->requestData = buf;
	this->parseMethod(&buf, size);
	this->parsePath(&buf, size);
}

void HttpRequest::parseMethod(char** buf, int size) {
	char* method = strtok(*buf, " ");

	if (strncmp("GET", method, 3) == 0) {
		this->method = GET;
		*buf += 3;
	}
	else if (0 == strncmp("POST", method, 4)) {
		this->method = POST;
		*buf += 4;
	}
	else if (0 == strncmp("HEAD", method, 4)) {
		this->method = HEAD;
		*buf += 4;
	}
	else if (0 == strncmp("OPTIONS", method, 7)) {
		this->method = OPTIONS;
		*buf += 7;
	}
	else if (0 == strncmp("PUT", method, 3)) {
		this->method = PUT;
		*buf += 3;
	}
	else if (0 == strncmp("DELETE", method, 6)) {
		this->method = MDELETE;
		*buf += 6;
	}
	else if (0 == strncmp("TRACE", method, 5)) {
		this->method = TRACE;
		*buf += 5;
	}
	else {
		this->method = ILLEGAL;
	}

	*buf += 1;
}

HttpRequest::~HttpRequest()
{
}
