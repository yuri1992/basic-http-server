#include "stdafx.h"
#include "HttpServer.h"
#include <fstream>


HttpServer::HttpServer()
{
}


HttpServer::~HttpServer()
{
}



HttpResponse HttpServer::doDelete(HttpRequest* req)
{
	HttpResponse resp = HttpResponse(req);
	struct stat sb;

	if (stat(req->getFullPath(), &sb) == 0) {
		resp.responseCode = 404;
		resp.responseData = new char[strlen(FILE_NOT_DELETED)];
		strcpy(resp.responseData, FILE_NOT_DELETED);
		return resp;
	}

	int removeFile = remove(req->getFullPath());
	if (removeFile == 0) {
		resp.responseCode = 404;
		resp.responseData = new char[strlen(FILE_NOT_DELETED)];
		strcpy(resp.responseData, FILE_NOT_DELETED);
	}
	else {
		resp.responseCode = 202;
		resp.responseData = new char[strlen(FILE_DELETED)];
		strcpy(resp.responseData, FILE_DELETED);
	}


	return resp;
}


HttpResponse HttpServer::doGet(HttpRequest* req)
{
	HttpResponse resp = HttpResponse(req);
	FILE *f = fopen(req->getFullPath(), "rb");

	if (f == nullptr) {
		resp.responseCode = 404;
		strcpy(resp.responseData, FILE_NOT_FOUND);
		return resp;
	}

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	resp.responseData = new char[fsize + 1];
	fread(resp.responseData, fsize, 1, f);
	fclose(f);

	resp.responseData[fsize] = '\0';
	resp.responseCode = 200;
	return resp;
}


HttpResponse HttpServer::doPost(HttpRequest* req)
{
	// TODO: Add your implementation code here.
	return nullptr;
}


HttpResponse HttpServer::doTrace(HttpRequest* req)
{
	// TODO: Add your implementation code here.
	return nullptr;
}


HttpResponse HttpServer::doOption(HttpRequest* req)
{
	/*
	We should not do anything special- just return the headers
	*/
	return nullptr;
}


HttpResponse HttpServer::doPut(HttpRequest* req)
{
	HttpResponse resp = HttpResponse(req);
	FILE *f = NULL;
	// Todo: Create all sub directories needed
	f = fopen(req->getFullPath(), "w");
	fprintf(f, "%s", req->requestData);
	resp.responseCode = 201;

	// Todo: set response code depending on the status create/update/error/
	return resp;
}


HttpResponse HttpServer::doHead(HttpRequest* req)
{
	/*
		Head method not invoke any special logic, just return a pure data.
	*/
	return nullptr;
}

HttpResponse HttpServer::doException(HttpRequest* req) {
	HttpResponse resp = HttpResponse(req);
	resp.responseCode = 500;
	return resp;
}

HttpResponse HttpServer::dispatch(HttpRequest* req)
{
	HttpResponse resp = nullptr;

	if (req->method == GET) {
		resp = HttpServer::doGet(req);
	}
	else if (req->method == HEAD) {
		resp = HttpServer::doHead(req);
	}
	else if (req->method == OPTIONS) {
		resp = HttpServer::doOption(req);
	}
	else if (req->method == PUT) {
		resp = HttpServer::doPut(req);
	}
	else if (req->method == TRACE) {
		resp = HttpServer::doTrace(req);
	}
	else if (req->method == MDELETE) {
		resp = HttpServer::doDelete(req);
	}
	else {
		resp = HttpServer::doException(req);

	}

	return resp;
}
