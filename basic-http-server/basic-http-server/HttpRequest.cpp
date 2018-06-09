#include "stdafx.h"
#include <string>
#include "HttpRequest.h"

const char *ROOT_FOLDER = "C:\\www";
const char *FILE_CREATED = "<html>\n<body>\n<h1>The file was created.</h1>\n</body>\n</html>";
const char *FILE_NOT_CREATED = "<html>\n<body>\n<h1>The file was not created.</h1>\n</body>\n</html>";
const char *FILE_DELETED = "<html>\n<body>\n<h1>The file was deleted.</h1>\n</body>\n</html>";
const char *FILE_NOT_DELETED = "<html>\n<body>\n<h1>The file was not deleted.</h1>\n</body>\n</html>";
const char *FILE_NOT_FOUND = "<html>\n<body>\n<h1>The file was not found.</h1>\n</body>\n</html>";


HttpRequest::HttpRequest(char* buf, int size)
{
	this->method = ILLEGAL;
	this->requestData = buf;
	this->parseMethod(&buf, size);
	this->parsePath(&buf, size);
	this->parseHttpVersion(&buf, size);
	this->parseHeaders(&buf, size);
	this->parseRequestData(&buf, size);
}


void HttpRequest::parsePath(char** buf, int size) {
	char *token = strtok(*buf, " ");
	int len = strlen(token) + 1;
	this->path = new char[strlen(token) + 1];
	strcpy(this->path, token);
	*buf += strlen(this->path) + 1;
}

void HttpRequest::parseHttpVersion(char** buf, int size) {
	char *token = strtok(*buf, " \r\n");
	this->HTTPVersion = new char[strlen(token) + 1];
	strcpy(this->HTTPVersion, token);
	*buf += strlen(this->HTTPVersion) + 1;
}

char * HttpRequest::getFullPath()
{
	char *path = new char[strlen(this->path) + strlen(ROOT_FOLDER) + 1];
	strcpy(path, ROOT_FOLDER);
	strcat(path, this->path);
	return path;
}

void HttpRequest::parseHeaders(char** buf, int size) {
	int headerNum = 0;
	char** headersTemp = NULL;
	char* tmp = new char[strlen(*buf)];
	strcpy(tmp, *buf);
	char* header = strtok(tmp, "\n");
	while (header && strlen(header) > 1) {
		headerNum++;
		headersTemp = new char*[headerNum];
		if (this->headers) {
			std::copy(this->headers, this->headers + (headerNum - 1), headersTemp);
		}
		this->headers = headersTemp;
		this->headers[headerNum - 1] = new char[strlen(header) + 1];
		strcpy(this->headers[headerNum - 1], header);
		this->headers[headerNum - 1][strlen(header)] = '\0';
		*buf += strlen(header) + 1;
		header = strtok(NULL, "\n");
	}
	this->numberOfHeaders = headerNum;
	*buf += 1;

}

void HttpRequest::parseRequestData(char** buf, int size) {
	if (buf) {
		this->requestData = new char[strlen(*buf)];
		strcpy(this->requestData, *buf);
	}
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

	*buf+= 1 ;
}

HttpRequest::~HttpRequest()
{
	if (this->fullFilePath)
		free(this->fullFilePath);

	if (this->path)
		free(this->path);

	if (this->HTTPVersion)
		free(this->HTTPVersion);
}
