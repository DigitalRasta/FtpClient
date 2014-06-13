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
	* <param name="listToOrder>Pointer to list</param>
	* <returns>Return ordered list of files/folder in path directory</returns>
	*/
	std::list<ContainerFileInfo>* orderFilesListDirecrotiesFiles(std::list<ContainerFileInfo>* listToOrder);

	/*
	* OVERRIDE
	* <summary>Check if path is logical partition</summary>
	* <param name="path">Path to check</param>
	* <returns>true - path is like: X:/ false - path is like X:/dir/dir/...</returns>
	*/
	bool isPathLogicalPartition(std::string path);

	/*
	* OVERRIDE
	* <summary>Delete last '/' in path, then find last occurence of '/' and cut directory name</summary>
	* <param name="path">Path to convert</param>
	* <returns>new path</returns>
	*/
	std::string goUpInDirPath(std::string path);

	/*
	* OVERRIDE
	* <summary>Create new connection, sets connections params and create ModelConnection object</summary>
	* <param name="host">Server host - ip or something like host.com</param>
	* <param name="port">Number of port, standard for FTP is: 21</param>
	* <param name="login">Login for authetication</param>
	* <param name="password">Password for authetication</param>
	* <exception cref="ContainerException">Throw if one of params is empty</exception>
	*/
	void createNewConnection(std::string host, std::string port, std::string login, std::string password);

	/*
	* OVERRIDE
	* <summary>Get content of directory on server with path</summary>
	* <returns>Return list of files/folders in path directory</returns>
	* <param name="path">Path to get content</param>
	* <exception cref="ContainerException">Throw if cannot list directory</exception>
	*/
	std::list<ContainerFileInfo>* serverGetDirectoryContent(std::string path);

	/*
	* OVERRIDE
	* <summary>Check if path is server root</summary>
	* <param name="path">Path to check</param>
	* <returns>true: path is like "/"; false: path is like /dir/dir/...</returns>
	*/
	bool isPathServerRoot(std::string path);

	/*
	* OVERRIDE
	* <summary>Delete local file or directory</summary>
	* <param name="file">Pointer to fileContainer with information about which file to delete</param>
	* <returns>true: delete file or directory succesfull; false: error occured</returns>
	*/
	bool deleteLocalFile(ContainerFileInfo *file);

	/*
	* OVERRIDE
	* <summary>Delete file or directory on server</summary>
	* <param name="file">Pointer to fileContainer with information about which file or directory to delete</param>
	* <returns>true: delete file or directory succesfull; false: error occured</returns>
	*/
	bool deleteServerFile(ContainerFileInfo *file);

	/*
	* OVERRIDE
	* <summary>Creates new directory on local disk</summary>
	* <param name="pathWithName">Path with directory name to create</param>
	* <returns>true: directory create succesfull; false: error occured</returns>
	*/
	bool newFolderLocal(std::string pathWithName);

	/*
	* OVERRIDE
	* <summary>Creates new directory on server</summary>
	* <param name="pathWithName">Path with directory name to create</param>
	* <returns>true: directory create succesfull; false: error occured</returns>
	*/
	bool newFolderServer(std::string pathWithName);

	/*
	* OVERRIDE
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
	* OVERRIDE
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
	* OVERRIDE
	* <summary> Kill transfer thread on transfer end<summary>
	*/
	void killTransferThread();

	/*
	* <summary>Convert bit representation of logical drives to letters.</summary>
	* <param name="volumesList">volumesList - 32 bit integer represents list of volumes on user PC. First bit means A, second B, third C...</param>
	* <returns>vector of strings with letters</returns>
	*/
	std::vector<std::string> convertLogicalDrives(DWORD volumesList);
private:
	InnerConfig* innerConfigObject;
	ModelConnection* connectionObject;

};

