#include "stdafx.h"
#include "HttpRequest.h"


HttpRequest::HttpRequest(char* buf, int size)
{
	this->method = ILLEGAL;
	this->requestData = buf;
	this->parseMethod(&buf, size);
	this->parsePath(&buf, size);
}


void HttpRequest::parsePath(char** buf, int size) {
	char *token = strtok(*buf, " ");
	int len = strlen(token) + 1;
	this->path = (char *)malloc(sizeof(token) * 1 + 1);
	strcpy(this->path, token);
	*buf += strlen(this->path) + 1;
}

void HttpRequest::parseHttpVersion(char** buf, int size) {
	char *token = strtok(*buf, " \n");
	this->HTTPVersion = (char *)malloc(sizeof(token) * 1 + 1);
	strcpy(this->HTTPVersion, token);
	*buf += strlen(this->HTTPVersion) + 1;
}

char * HttpRequest::getFullPath()
{
	char *path = (char *)malloc(strnlen(this->path) + strlen(ROOT_FOLDER) + 1);
	strcpy(path, ROOT_FOLDER);
	strcat(path, this->path);
	return path;
}

void HttpRequest::parseHeaders(char** buf, int size) {

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
	if (this->fullFilePath)
		free(this->fullFilePath);

	if (this->path)
		free(this->path);

	if (this->HTTPVersion)
		free(this->HTTPVersion)
}
