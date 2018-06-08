#ifndef _HTTP_SERVER_
#define _HTTP_SERVER_


#include <cstdio>
#include <cstring>
#include "HttpRequest.h";
#include "HttpResponse.h";



class HttpServer
{
public:
	HttpServer();
	~HttpServer();

	static HttpResponse doDelete(HttpRequest* req);
	static HttpResponse doGet(HttpRequest* req);
	static HttpResponse doPost(HttpRequest* req);
	static HttpResponse doTrace(HttpRequest* req);
	static HttpResponse doOption(HttpRequest* req);
	static HttpResponse doPut(HttpRequest* req);
	static HttpResponse doHead(HttpRequest* req);
	static HttpResponse doException(HttpRequest * req);
	static HttpResponse dispatch(HttpRequest * req);
};
#endif