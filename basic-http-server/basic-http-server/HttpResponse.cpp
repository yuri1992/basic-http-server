#include "stdafx.h"
#include <ctime>
#include "HttpResponse.h"


HttpResponse::HttpResponse(HttpRequest* request)
{
	this->request = request;
}

HttpResponse::~HttpResponse()
{
}


void HttpResponse::setHeader(const char* key, const char* value) {
	// Alocating extra place for next header
	this->numberOfHeaders++;
	char** headersTemp = new char*[this->numberOfHeaders];
	if (this->headers) {
		std::copy(this->headers, this->headers + (this->numberOfHeaders - 1), headersTemp);
	}

	this->headers = headersTemp;

	// Concat the key + value and inserting to matrix
	char *header = new char[(strlen(key) + strlen(value) + 1)];
	strcpy(header, key);
	strcat(header, value);
	header[strlen(header)] = '\0';
	this->headers[numberOfHeaders - 1] = header;
}

void HttpResponse::prepareHeaders() {
	this->setHeader("Connection: ", "close");
	this->setHeader("Content-Type: ", "text/html");
	this->setHeader("Server: ", "Windows Server 1.0v");
	this->setHeader("Date: ", this->getDateTime());
	if (this->responseData) {
		this->setHeader("Content-Length: ", this->getContentLength());
	}
}

char * HttpResponse::getContentLength() {
	size_t temp = 0;
	int responseLenDigits = 1;
	char *buf = NULL;

	temp = this->getResponseDataLength();
	while (0 != temp) { responseLenDigits++; temp /= 10; }
	if (0 == responseLenDigits) { responseLenDigits++; }

	buf = new char[responseLenDigits + 1];
	sprintf(buf, "%d", this->getResponseDataLength());
	buf[responseLenDigits] = '\0';
	return buf;
}

char * HttpResponse::getDateTime()
{
	size_t len = 0;
	size_t dateLen = 0;
	time_t t = time(NULL);

	struct tm *tm = localtime(&t);
	char s[64];
	
	//Sat, 09 Jun 2018 13:45:09 GMT
	strftime(s, sizeof(s), "%a, %d %b %Y %T", tm);
	char* ret = new char[strlen(s) + 1];
	strcpy(ret, s);
	ret[strlen(s)] = '\0';
	return ret;
}

int HttpResponse::getResponseDataLength()
{
	if (this->responseData == nullptr)
		return 0;
	return strlen(this->responseData);
}

void HttpResponse::setResponseCodeText()
{
	switch (responseCode) {
		case 200:
			strcpy(responseCodeText, HTTP_200);
			break;
		case 201:
			strcpy(responseCodeText, HTTP_201);
			break;
		case 202:
			strcpy(responseCodeText, HTTP_202);
			break;
		case 204:
			strcpy(responseCodeText, HTTP_204);
			break;
		case 404:
			strcpy(responseCodeText, HTTP_404);
			break;
		case 500:
			strcpy(responseCodeText, HTTP_500);
			break;
		default:
			strcpy(responseCodeText, HTTP_400);
			break;
	}
}


void HttpResponse::complete() {
	if (!this->isClosed) {
		this->setResponseCodeText();
		this->prepareHeaders();
		this->isClosed = true;
	}
}

char* HttpResponse::getBuffer()
{
	this->complete();

	int currentLength = 0;
	char *buf = new char[1024 + this->getResponseDataLength()];

	strcpy(buf, this->request->HTTPVersion);
	strcat(buf, " ");
	char responseCodeStr[16] = { 0 };
	sprintf(responseCodeStr, "%d", this->responseCode);
	strcat(buf, responseCodeStr);
	strcat(buf, " ");
	strcat(buf, this->responseCodeText);
	strcat(buf, " \n");

	for (int i = 0; i < this->numberOfHeaders; i++) {
		strcat(buf, this->headers[i]);
		strcat(buf, "\n");
	}
	
	strcat(buf, "\n");

	if (this->responseData) {
		strcat(buf, this->responseData);
		strcat(buf, "\n");
	}

	return buf;
}
