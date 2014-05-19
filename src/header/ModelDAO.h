#pragma once
#include "ModelDAOInterface.h"
#include "ContainerFileInfo.h"
#include "InnerConfig.h"
#include "ModelConnection.h"
#include <string>
#include <vector>
#include <stdint.h>
#include <Windows.h>
#include <list>

namespace FtpClient {
    class ModelDAO;
	typedef void (*fcallback)(double);
}
class FtpClient::ModelDAO :
	public FtpClient::ModelDAOInterface
{
public:
	ModelDAO(InnerConfig* innerConfigObject);
	virtual ~ModelDAO(void);


	/*
	* INTERFACE
	* Return list of logical drives on user PC. Each vector is letter of drive like A, B, C...
	* return: list of logical drives in linked list of ContainerFileInfo with values:
	*		  fileName = get 
	*		  filePath = get
	*		  fileSize = -1
	*		  day = -1
	*		  month = -1
	*		  year = -1
	*		  hour = -1
	*		  minute = -1
	*		  isDir = true
	*		  attributes = -1
	*		  
	*/
	std::list<ContainerFileInfo>* getLogicalDrives(void);

	/*
	* Convert bit representation of logical drives to letters.
	* params:
	*	*volumesList - 32 bit integer represents list of volumes on user PC. First bit means A, second B, third C....
	*/
	std::vector<std::string> convertLogicalDrives(DWORD volumesList);


	/*
	* INTERFACE
	* Get info from local disk
	* return: Return list of files/folders in path directory
	* throws: ContainerException if cannot read path directory
	*/
	std::list<ContainerFileInfo>* getDirectoryContent(std::string path);

	
	/*
	* INTERFACE
	* Order files list, first sorted by name directories, then sorted by name files
	* return: Return ordered list of files/folder in path directory
	*/
	std::list<ContainerFileInfo>* orderFilesListDirecrotiesFiles(std::list<ContainerFileInfo>* listToOrder);

	/*
	* INTERFACE
	* Check if path is logical partition
	* return:
	*		true - path is like: X:/
	*		false - path is like X:/dir/dir/...
	*/
	bool isPathLogicalPartition(std::string path);

	/*
	* INTERFACE
	* Delete last '/' in path, then find last occurence of '/' and cut directory name
	* return: new path
	*/
	std::string goUpInDirPath(std::string path);

	/*
	* INTERFACE
	* Create new connection and try to connect
	* return: ID of created connection - you need it for connection using
	* throws: ContainerException if cannot connect
	*/
	int createNewConnection(std::string host, std::string port, std::string login, std::string password);

	/*
	* INTERFACE
	* Get content of directory on sever (with connectionID) with path
	* return: Return list of files/folders in path directory
	* throws: ContainerException if cannot list directory
	*/
	std::list<ContainerFileInfo>* serverGetDirectoryContent(std::string path, int connectionID);

	/*
	* INTERFACE
	* Check if path is server root
	* return:
	*		true - path is like: /
	*		false - path is like /dir/dir/...
	*/
	bool isPathServerRoot(std::string path);

	/*
	* INTERFACE
	* Delete file or directory
	* return:
	*		true - delete file or directory succesfull
	*		false - error occured
	*/
	virtual bool deleteLocalFile(ContainerFileInfo *file);

	/*
	* INTERFACE
	* Delete file or directory on server
	* return:
	*		true - delete file or directory succesfull
	*		false - error occured
	*/
	virtual bool deleteServerFile(ContainerFileInfo *file, int connectionID);

	virtual bool newFolderLocal(std::string pathWithName);

	virtual bool newFolderServer(std::string pathWithName, int connectionID);

	virtual bool downloadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, fcallback progressBarCallback, int connectionID);

private:
	InnerConfig* innerConfigObject;
	std::list<ModelConnection*> connectionObjectList;
	int connectionObjectListId;

	ModelConnection* getConnectionById(int id);
};

