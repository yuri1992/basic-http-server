#include "HttpServer.h"
#include "HttpRequest.h"
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

	if ((stat(req->getFullPath, &sb) == 0) && (sb.st_mode & S_IFDIR)) { 
		resp.responseCode = 404;
		return resp;
	}

	// Consider maybe to throw exception instead of changing server response

	int removeFile = remove(req->getFullPath);
	if (removeFile == 0)
		resp.responseCode = 404;
	else
		resp.responseCode = 202;

	return resp;
}


HttpResponse HttpServer::doGet(HttpRequest* req)
{
	HttpResponse resp = HttpResponse(req);
	FILE *f = fopen(req->getFullPath(), "rb");

	//Todo: Allow throwing http errors
	//if (f == nullptr)
	//	throw HTTPError();

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	resp.responesText = (char *)malloc(fsize + 1);
	fread(resp.responesText, fsize, 1, f);
	fclose(f);

	resp.responesText[fsize] = '\0';
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
	// Create all sub directories needed
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


HttpResponse HttpServer::dispatch(HttpRequest* req)
{
	if (req->method == GET) {
		return this->doGet(req);
	}
	else if (req->method == HEAD) {
		return this->doHead(req);
	}
	else if (req->method == OPTIONS) {
		return this->doOption(req);
	}
	else if (req->method == PUT) {
		return this->doPut(req);
	}
	else if (req->method == TRACE) {
		return this->doTrace(req);
	}
	else if (req->method == DELETE) {
		return this->doDelete(req);
	}
	
	return nullptr;
}
 