#pragma once
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
};

