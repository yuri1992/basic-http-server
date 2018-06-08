#include <string>


class HttpResponse
{
public:
	HttpRequest * request;
	int responseCode;
	int numberOfHeaders;
	char *responesText;
	char **headers;
	char *responseData;

	HttpResponse(HttpRequest* request);
	~HttpResponse();
	char* getBuffer();
};

