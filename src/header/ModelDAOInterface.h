#pragma once
#include <vector>
#include <string>
#include <list>
#include <stdint.h>
#include "../header/ContainerFileInfo.h"
#include <functional>

namespace FtpClient {
    class ModelDAOInterface;
	typedef void (*fcallback)(double);
}
class FtpClient::ModelDAOInterface
{
public:

	virtual std::list<ContainerFileInfo>* getLogicalDrives(void) = 0;

	virtual std::list<ContainerFileInfo>* getDirectoryContent(std::string path) = 0;

	virtual std::list<ContainerFileInfo>* orderFilesListDirecrotiesFiles(std::list<ContainerFileInfo>* listToOrder) = 0;

	virtual bool isPathLogicalPartition(std::string path) = 0;

	virtual bool isPathServerRoot(std::string path) = 0;

	virtual std::string goUpInDirPath(std::string path) = 0;

	virtual void createNewConnection(std::string host, std::string port, std::string login, std::string password) = 0;

	virtual std::list<ContainerFileInfo>* serverGetDirectoryContent(std::string path) = 0;

	virtual bool deleteLocalFile(ContainerFileInfo *file) = 0;

	virtual bool deleteServerFile(ContainerFileInfo *file) = 0;
	
	virtual bool newFolderLocal(std::string pathWithName) = 0;

	virtual bool newFolderServer(std::string pathWithName) = 0;

	virtual bool downloadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, std::function<void(double)> progressBarCallback, std::function<void(int)> endDownloadCallback) = 0;

	virtual void killDownloadThread() = 0;
};

