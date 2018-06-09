#include "stdafx.h"
#include "HttpServer.h"
#include <fstream>
#include <windows.h>
#include <string>
#include <sys/stat.h>

#include <direct.h>  
#include <stdlib.h>  
#include <stdio.h>  

#include <iostream>


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
		int removeFile = remove(req->getFullPath());
		resp.responseCode = 202;
		resp.responseData = new char[strlen(FILE_DELETED)];
		strcpy(resp.responseData, FILE_DELETED);
	}
	else {
		resp.responseCode = 404;
		resp.responseData = new char[strlen(FILE_NOT_DELETED)];
		strcpy(resp.responseData, FILE_NOT_DELETED);
	}

	return resp;
}


HttpResponse HttpServer::doGet(HttpRequest* req)
{
	HttpResponse resp = HttpResponse(req);
	FILE *f = fopen(req->getFullPath(), "rb");

	if (f == nullptr) {
		resp.responseCode = 404;
		resp.responseData = new char[strlen(FILE_NOT_FOUND) + 1];
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
	HttpResponse resp = HttpResponse(req);
	resp.responseCode = 200;
	return resp;
}


HttpResponse HttpServer::doOption(HttpRequest* req)
{
	HttpResponse resp = HttpResponse(req);
	resp.responseCode = 200;
	resp.setHeader("Allow: ", "OPTIONS, DELETE, GET, HEAD, TRACE");
	resp.setHeader("Content-Length: ", "0");
	return resp;
}

bool HttpServer::createFolders(char * path) {

	size_t len = 0;
	size_t pathLen = 0;
	size_t rootFolderLen = 0;
	char *folder = NULL;
	char *folderBeginning = NULL;
	char *token = NULL;
	char *addFolderPath = NULL;
	struct stat sb;

	pathLen = strlen(path);
	rootFolderLen = strlen(ROOT_FOLDER);

	len = pathLen - rootFolderLen;
	folder = new char[len + 1];
	folderBeginning = folder;
	strcpy(folder, path + rootFolderLen + 1);

	addFolderPath = new char[pathLen + 1];
	strcpy(addFolderPath, ROOT_FOLDER);
	addFolderPath[rootFolderLen] = '\0';

	while (strchr(folder, '/'))
	{
		token = strtok(folder, "/");
		strcat(addFolderPath, "/");
		strcat(addFolderPath, token);
		if (!((stat(addFolderPath, &sb) == 0) && (sb.st_mode & S_IFDIR)))
		{
			if (!(0 == _mkdir(addFolderPath))) { return false; }
			folder += strlen(token) + 1;
		}
	}

	free(folderBeginning);
	free(addFolderPath);

	return true;
}

HttpResponse HttpServer::doPut(HttpRequest* req)
{
	HttpResponse resp = HttpResponse(req);
	FILE *f = NULL;

	struct stat buffer;
	if (stat(req->getFullPath(), &buffer) == 0) {
		// Todo: Create all sub directories needed
		f = fopen(req->getFullPath(), "w");
		fprintf(f, "%s", req->requestData);
		resp.responseCode = 204;
		fclose(f);
	}
	else {
		// Todo: Create all sub directories needed
		HttpServer::createFolders(req->getFullPath());

		f = fopen(req->getFullPath(), "w");
		fprintf(f, "%s", req->requestData);
		resp.responseCode = 201;
		fclose(f);
	}

	// Todo: set response code depending on the status create/update/error/
	return resp;
}


HttpResponse HttpServer::doHead(HttpRequest* req)
{
	HttpResponse resp = HttpResponse(req);
	resp.responseCode = 200;
	return resp;
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
