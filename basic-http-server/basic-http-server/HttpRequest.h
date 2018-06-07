#include "SocketManager.h";

#pragma once
class HttpRequest
{
	int method;
	int fileExists;
	int numberOfHeaders;
	int numberOfDataArguments;
	char **headers;
	char **dataArguments;
	char *path;
	char *fullFilePath;
	char *requestData;
	char *rawRequest;
	int HTTPVersion;
public:
	HttpRequest(char * buf, int size);
	void parseMethod(char ** buf, int size);
	void parsePath(char ** buf, int size);
	static HttpRequest* fromBuffer(char* buf, int size);

	~HttpRequest();

};

