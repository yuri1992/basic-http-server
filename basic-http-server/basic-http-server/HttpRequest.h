#ifndef _HTTP_REQUEST_
#define _HTTP_REQUEST_

extern const char *ROOT_FOLDER;
extern const char *FILE_CREATED;
extern const char *FILE_NOT_CREATED;
extern const char *FILE_DELETED;
extern const char *FILE_NOT_DELETED;
extern const char *FILE_NOT_FOUND;

enum methods { GET = 0, HEAD = 1, OPTIONS = 2, PUT = 3, MDELETE = 4, TRACE = 5, POST = 6, ILLEGAL = 7, enumSize = 8 };

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

	void parseHeaders(char ** buf, int size);
	void parseMethod(char ** buf, int size);
	void parsePath(char ** buf, int size);
	void parseHttpVersion(char ** buf, int size);
	char* getFullPath();
	HttpRequest(char* buf, int size);
	~HttpRequest();

};
#endif