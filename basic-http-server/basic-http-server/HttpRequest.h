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
	HttpRequest();
	~HttpRequest();
};

