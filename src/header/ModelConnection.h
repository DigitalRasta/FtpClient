#pragma once
#include "InnerConfig.h"
#include "ContainerFileInfo.h"
#include <list>
#include <string>
#include <curl\curl.h>
#include <stdint.h>
#include <Windows.h>
#include "ContainerException.h"

namespace FtpClient {
    class ModelConnection;
	typedef void (*fcallback)(double);
	struct FtpFile {
		uint64_t size;
		uint64_t progress;
		fcallback progressBarCallback;
		FILE *stream;
	};
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

	HANDLE downloadThread;
	struct FtpClient::FtpFile downloadFileHandler;

	ExceptionCode translateCurlErrorCode(int code);

	static DWORD WINAPI startDownload(void* Param);

public:
	ModelConnection(std::string host, std::string port, std::string login, std::string password, int connectionId, InnerConfig* configObject);

	int getId(void);
	std::list<ContainerFileInfo>* getDirectoryContent(std::string path);
	
	bool deleteFile(ContainerFileInfo *file);
	bool newFolder(std::string pathWithName);
	bool downloadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, fcallback progressBarCallback);

	void setFilesList(std::list<ContainerFileInfo>* list);

	void parseLineAndAddToList(std::string line, int id);
	void clearListAndInit(void);
	virtual ~ModelConnection(void);
	static size_t GetFilesList_response(void *ptr, size_t size, size_t nmemb, void * object);
	static size_t downloadFileWriteFunction(void *buffer, size_t size, size_t nmemb, void *stream);
};

