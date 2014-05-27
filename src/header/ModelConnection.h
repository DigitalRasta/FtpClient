#pragma once
#include "InnerConfig.h"
#include "ContainerFileInfo.h"
#include <list>
#include <string>
#include <curl\curl.h>
#include <stdint.h>
#include <Windows.h>
#include <functional>
#include "ContainerException.h"

namespace FtpClient {
    class ModelConnection;
	typedef void (*fcallback)(double);
	struct FtpFile {
		uint64_t size;
		uint64_t progress;
		std::function<void(double)> progressBarCallback;
		FILE *stream;
	};
}
class FtpClient::ModelConnection {
private:
	CURL * libFtpObject;
	InnerConfig* configObject;
	std::string currentPath;
	std::string loginPass;
	std::string hostURL;
	std::list<ContainerFileInfo>* filesList;

	HANDLE mainThread;
	int downloadCode;

	ExceptionCode translateCurlErrorCode(int code);

	static DWORD WINAPI startDownload(void* Param);

	std::function<void(int)> endDownloadCallback;

public:
	ModelConnection(std::string host, std::string port, std::string login, std::string password, InnerConfig* configObject);

	std::list<ContainerFileInfo>* getDirectoryContent(std::string path);
	
	bool deleteFile(ContainerFileInfo *file);
	bool newFolder(std::string pathWithName);
	bool downloadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, std::function<void(double)> progressBarCallback, std::function<void(int)> endDownloadCallback);

	void setFilesList(std::list<ContainerFileInfo>* list);

	static DWORD WINAPI checkDownloadRunning(void* Param);

	void parseLineAndAddToList(std::string line, int id);
	void clearListAndInit(void);
	virtual ~ModelConnection(void);
	static size_t GetFilesList_response(void *ptr, size_t size, size_t nmemb, void * object);
	static size_t downloadFileWriteFunction(void *buffer, size_t size, size_t nmemb, void *stream);

	HANDLE downloadThread;
	HANDLE downloadObserverThread;
	struct FtpClient::FtpFile downloadFileHandler;
};

