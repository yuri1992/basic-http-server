
class HttpResponse
{
	HttpRequest *request;
	int responseCode;
	int numberOfHeaders;
	char *responesText;
	char **headers;
	char *responseData;
public:
	HttpResponse(HttpRequest* request);
	~HttpResponse();
	char* getBuffer();
};

