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
	std::copy(this->headers, this->headers + this->numberOfHeaders, headersTemp);
	this->headers = headersTemp;

	// Concat the key + value and inserting to matrix
	char *header = (char *)malloc(sizeof(char) * (strlen(key) + strlen(value) + 1));
	strcpy(header, key);
	strcat(header, value);
	header[strlen(header)] = '\0';
	this->headers[numberOfHeaders - 1] = header;
}

void HttpResponse::prepareHeaders() {
	this->setHeader("Connection: ", "Closed");
	this->setHeader("Content-Type: ", " text/html");
	this->setHeader("Server: ", "Windows Server 1.0v");
	this->setHeader("Date: ", this->getDateTime());
	this->setHeader("Content-Length: ", this->getContentLength());
}

char * HttpResponse::getContentLength() {
	size_t responseLen = 0;
	size_t temp = 0;
	int responseLenDigits = 0;
	char *buf = NULL;

	responseLen = strlen(this->responseData);
	temp = responseLen;
	while (0 != temp) { responseLenDigits++; temp /= 10; }
	if (0 == responseLenDigits) { responseLenDigits++; }

	buf = (char *)malloc(sizeof(char) * responseLenDigits + 1);
	sprintf(buf, "%d", responseLen);
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

	strftime(s, sizeof(s), "%c", tm);
	char* ret = new char[len + dateLen + 2];
	strcpy(ret, s);
	return ret;
}

void HttpResponse::setResponseCodeText()
{
	switch (responseCode) {
		case 200:
			strcpy(responseCodeText, HTTP_200);
		case 201:
			strcpy(responseCodeText, HTTP_201);
		case 202:
			strcpy(responseCodeText, HTTP_202);
		case 404:
			strcpy(responseCodeText, HTTP_404);
		case 500:
			strcpy(responseCodeText, HTTP_500);
		default:
			strcpy(responseCodeText, HTTP_400);
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
	char *buf = new char[1024 + strlen(this->responseData)];

	strcpy(buf, this->request->HTTPVersion);
	strcat(buf, " ");
	char responseCodeStr[16] = { 0 };
	sprintf(responseCodeStr, "%d", this->responseCode);
	strcat(buf, responseCodeStr);
	strcat(buf, " ");
	strcat(buf, this->responseCodeText);
	strcat(buf, "\n");

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
