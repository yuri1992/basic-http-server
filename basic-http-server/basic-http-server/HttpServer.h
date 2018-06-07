#define ROOT_FOLDER "C:\\www";
enum methods { GET = 0, HEAD = 1, OPTIONS = 2, PUT = 3, MDELETE = 4, TRACE = 5, POST = 6, ILLEGAL = 7, enumSize = 8 };

class HttpServer
{
public:
	HttpServer();
	~HttpServer();
	int doDelete();
	int doGet();
	int doPost();
	int doTrace();
	int doOption();
	int doPut();
	int doHead();
	int dispatch();
};

