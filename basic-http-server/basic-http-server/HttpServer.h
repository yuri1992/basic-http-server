
enum methods { GET = 0, HEAD = 1, OPTIONS = 2, PUT = 3, MDELETE = 4, TRACE = 5, POST = 6, ILLEGAL = 7, enumSize = 8 };
const char ROOT_FOLDER[256] = "C:\\www";

class HttpServer
{
public:
	HttpServer();
	~HttpServer();
		
	HttpResponse doDelete(HttpRequest* req);
	HttpResponse doGet(HttpRequest* req);
	HttpResponse doPost(HttpRequest* req);
	HttpResponse doTrace(HttpRequest* req);
	HttpResponse doOption(HttpRequest* req);
	HttpResponse doPut(HttpRequest* req);
	HttpResponse doHead(HttpRequest* req);
	HttpResponse dispatch(HttpRequest * req);
};

