#include "SocketManager.h";

#pragma once
class HttpRequest
{
public:
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
	char *HTTPVersion;

	HttpRequest(char * buf, int size);
	void parseHeaders(char ** buf, int size);
	void parseMethod(char ** buf, int size);
	void parsePath(char ** buf, int size);
	void parseHttpVersion(char ** buf, int size);
	char* getFullPath();
	static HttpRequest* fromBuffer(char* buf, int size);

	~HttpRequest();

};

