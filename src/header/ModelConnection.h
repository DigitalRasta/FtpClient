#pragma once
#include "InnerConfig.h"
#include "ContainerFileInfo.h"
#include <list>
#include <string>
#include <curl\curl.h>
#include "ContainerException.h"

namespace FtpClient {
    class ModelConnection;
}
class FtpClient::ModelConnection {
private:
	CURL * libFtpObject;
	InnerConfig* configObject;
	int ID;
	std::string currentPath;
	std::string loginPass;
	std::string hostURL;
	std::list<ContainerFileInfo>* filesList;

	ExceptionCode translateCurlErrorCode(int code);

public:
	ModelConnection(std::string host, std::string port, std::string login, std::string password, int connectionId, InnerConfig* configObject);

	int getId(void);
	std::list<ContainerFileInfo>* getDirectoryContent(std::string path);
	
	bool deleteFile(ContainerFileInfo *file);
	bool newFolder(std::string pathWithName);

	void setFilesList(std::list<ContainerFileInfo>* list);

	void parseLineAndAddToList(std::string line, int id);
	void clearListAndInit(void);
	virtual ~ModelConnection(void);
	static size_t GetFilesList_response(void *ptr, size_t size, size_t nmemb, void * object);
};

