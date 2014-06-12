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
/*
* <summary>Class provides methods for communication with FTP server</summary>
*/
class FtpClient::ModelConnection {
private:
	CURL * libFtpObject;
	InnerConfig* configObject;
	std::string currentPath;
	std::string loginPass;
	std::string hostURL;
	std::list<ContainerFileInfo>* filesList;

	int transferCode;

	ExceptionCode translateCurlErrorCode(int code);

	static DWORD WINAPI startTransfer(void* Param);

	std::function<void(int)> endDownloadCallback;
	std::function<void(int)> endUploadCallback;

	bool downloadOrUpload;

public:
	/*
	*<summary>Constructor, sets params for connection</summary>
	* <param name="host">Server host - ip or something like host.com</param>
	* <param name="port">Number of port, standard for FTP is: 21</param>
	* <param name="login">Login for authetication</param>
	* <param name="password">Password for authetication</param>
	* <param name="configObject">pointer to inner config</param>
	*/
	ModelConnection(std::string host, std::string port, std::string login, std::string password, InnerConfig* configObject);

	/*
	* <summary>Get content of directory on server with path</summary>
	* <returns>Return list of files/folders in path directory not ordered</returns>
	* <param name="path">Path to get content</param>
	* <exception cref="ContainerException">Throw if cannot list directory</exception>
	*/
	std::list<ContainerFileInfo>* getDirectoryContent(std::string path);
	
	/*
	* <summary>Delete file or directory on server</summary>
	* <param name="file">Pointer to fileContainer with information about which file or directory to delete</param>
	* <returns>true: delete file or directory succesfull; false: error occured</returns>
	*/
	bool deleteFile(ContainerFileInfo *file);

	/*
	* <summary>Creates new directory on server</summary>
	* <param name="pathWithName">Path with directory name to create</param>
	* <returns>true: directory create succesfull; false: error occured</returns>
	*/
	bool newFolder(std::string pathWithName);

	/*
	* <summary>Download file from server</summary>
	* <param name="serverPath">Full path to file</param>
	* <param name="localPath">Full path to place to download</param>
	* <param name="name">Name of file to download</param>
	* <param name="size">Size of file to download</param>
	* <param name="progressBarCallback">Function callback for update progress of download</param>
	* <param name="endDownloadCallback">Callback which will be executed on download end</param>
	* <exception cref="ContainerException">Throw if problem with file I/O</exception>
	*/
	void downloadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, std::function<void(double)> progressBarCallback, std::function<void(int)> endDownloadCallback);
	
	/*
	* <summary>Upload file to server</summary>
	* <param name="serverPath">Full path to place to upload</param>
	* <param name="localPath">Full path to local file</param>
	* <param name="name">Name of file to upload</param>
	* <param name="size">Size of file to upload</param>
	* <param name="progressBarCallback">Function callback for update progress of download</param>
	* <param name="endUploadCallback">Callback which will be executed on upload end</param>
	* <exception cref="ContainerException">Throw if problem with file I/O</exception>
	*/
	void uploadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, std::function<void(double)> progressBarCallback, std::function<void(int)> endUploadCallback);

	/*
	* <summary> Standard setter for filesList</summary>
	* <param name="list">list to set</param>
	*/
	void setFilesList(std::list<ContainerFileInfo>* list);

	/*
	* <summary> parse line from ftpparse and add it to current files list</summary>
	* <param name="line">one line from ftpparse</param>
	* <param name="id">id of file, unique number</param>
	*/
	void parseLineAndAddToList(std::string line, int id);

	void clearListAndInit(void);
	virtual ~ModelConnection(void);
	static size_t GetFilesList_response(void *ptr, size_t size, size_t nmemb, void * object);
	static size_t downloadFileWriteFunction(void *buffer, size_t size, size_t nmemb, void *stream);
	static size_t uploadFileWriteFunction(void *buffer, size_t size, size_t nmemb, void *stream);

	HANDLE transferThread;
	HANDLE transferObserverThread;
	struct FtpClient::FtpFile transferFileHandler;
};

