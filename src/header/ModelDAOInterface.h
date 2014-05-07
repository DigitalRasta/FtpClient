#pragma once
#include <vector>
#include <string>
#include <list>
#include "../header/ContainerFileInfo.h"

namespace FtpClient {
    class ModelDAOInterface;
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

	virtual int createNewConnection(std::string host, std::string port, std::string login, std::string password) = 0;

	virtual std::list<ContainerFileInfo>* serverGetDirectoryContent(std::string path, int connectionID) = 0;

	virtual bool deleteLocalFile(ContainerFileInfo *file) = 0;

	virtual bool deleteServerFile(ContainerFileInfo *file, int connectionID) = 0;
	
	virtual bool newFolderLocal(std::string pathWithName) = 0;

	virtual bool newFolderServer(std::string pathWithName, int connectionID) = 0;
};

