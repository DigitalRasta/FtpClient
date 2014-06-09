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
	* OVERRIDE
	* <summary>Return list of logical drives on user PC. Each vector is letter of drive like A, B, C...</summary>
	* <returns>list of logical drives in linked list of ContainerFileInfo with values:
			  fileName = get 
			  filePath = get
			  fileSize = -1
			  day = -1
			  month = -1
			  year = -1
			  hour = -1
			  minute = -1
			  isDir = true
			  attributes = -1
	  </returns>		  
	*/
	std::list<ContainerFileInfo>* getLogicalDrives(void);

	/*
	* OVERRIDE
	* <summary>Get info from local disk</summary>
	* <param name="path">Information about cell</param>
	* <returns>Return list of files/folders in path directory</returns>
	* <exception cref="ContainerException">Throw if cannot read path directory</exception>
	*/
	std::list<ContainerFileInfo>* getDirectoryContent(std::string path);

	
	/*
	* OVERRIDE
	* <summary>Order files list, first sorted by name directories, then sorted by name files</summary>
	* <returns>Return ordered list of files/folder in path directory</returns>
	*/
	std::list<ContainerFileInfo>* orderFilesListDirecrotiesFiles(std::list<ContainerFileInfo>* listToOrder);

	/*
	* OVERRIDE
	* <summary>Check if path is logical partition</summary>
	* <returns>true - path is like: X:/ false - path is like X:/dir/dir/...</returns>
	*/
	bool isPathLogicalPartition(std::string path);

	/*
	* OVERRIDE
	* <summary>Delete last '/' in path, then find last occurence of '/' and cut directory name</summary>
	* <returns>new path</returns>
	*/
	std::string goUpInDirPath(std::string path);

	/*
	* INTERFACE
	* Create new connection
	* throws: ContainerException if cannot connect
	*/
	void createNewConnection(std::string host, std::string port, std::string login, std::string password);

	/*
	* INTERFACE
	* Get content of directory on sever (with connectionID) with path
	* return: Return list of files/folders in path directory
	* throws: ContainerException if cannot list directory
	*/
	std::list<ContainerFileInfo>* serverGetDirectoryContent(std::string path);

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
	virtual bool deleteServerFile(ContainerFileInfo *file);

	virtual bool newFolderLocal(std::string pathWithName);

	virtual bool newFolderServer(std::string pathWithName);

	virtual void downloadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, std::function<void(double)> progressBarCallback, std::function<void(int)> endDownloadCallback);
	
	virtual void uploadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, std::function<void(double)> progressBarCallback, std::function<void(int)> endUploadCallback);

	virtual void killTransferThread();

	
	/*
	* Convert bit representation of logical drives to letters.
	* params:
	*	*volumesList - 32 bit integer represents list of volumes on user PC. First bit means A, second B, third C....
	*/
	std::vector<std::string> convertLogicalDrives(DWORD volumesList);
private:
	InnerConfig* innerConfigObject;
	ModelConnection* connectionObject;

};

