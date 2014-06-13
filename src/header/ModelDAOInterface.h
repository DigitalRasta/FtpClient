#pragma once
#include <vector>
#include <string>
#include <list>
#include <stdint.h>
#include "../header/ContainerFileInfo.h"
#include <functional>

namespace FtpClient {
    class ModelDAOInterface;
}
/*
* <summary>Public interface for ModelDAO</summary>
*/
class FtpClient::ModelDAOInterface
{
public:

	/*
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
	virtual std::list<ContainerFileInfo>* getLogicalDrives(void) = 0;

	/*
	* <summary>Get info from local disk</summary>
	* <param name="path">Information about cell</param>
	* <returns>Return list of files/folders in path directory</returns>
	* <exception cref="ContainerException">Throw if cannot read path directory</exception>
	*/
	virtual std::list<ContainerFileInfo>* getDirectoryContent(std::string path) = 0;

	
	/*
	* <summary>Order files list, first sorted by name directories, then sorted by name files</summary>
	* <param name="listToOrder>Pointer to list</param>
	* <returns>Return ordered list of files/folder in path directory</returns>
	*/
	virtual std::list<ContainerFileInfo>* orderFilesListDirecrotiesFiles(std::list<ContainerFileInfo>* listToOrder) = 0;

	/*
	* <summary>Check if path is logical partition</summary>
	* <param name="path">Path to check</param>
	* <returns>true - path is like: X:/ false - path is like X:/dir/dir/...</returns>
	*/
	virtual bool isPathLogicalPartition(std::string path) = 0;

	/*
	* <summary>Delete last '/' in path, then find last occurence of '/' and cut directory name</summary>
	* <param name="path">Path to convert</param>
	* <returns>new path</returns>
	*/
	virtual std::string goUpInDirPath(std::string path) = 0;

	/*
	* <summary>Create new connection, sets connections params and create ModelConnection object</summary>
	* <param name="host">Server host - ip or something like host.com</param>
	* <param name="port">Number of port, standard for FTP is: 21</param>
	* <param name="login">Login for authetication</param>
	* <param name="password">Password for authetication</param>
	* <exception cref="ContainerException">Throw if one of params is empty</exception>
	*/
	virtual void createNewConnection(std::string host, std::string port, std::string login, std::string password) = 0;

	/*
	* <summary>Get content of directory on server with path</summary>
	* <returns>Return list of files/folders in path directory</returns>
	* <param name="path">Path to get content</param>
	* <exception cref="ContainerException">Throw if cannot list directory</exception>
	*/
	virtual std::list<ContainerFileInfo>* serverGetDirectoryContent(std::string path) = 0;

	/*
	* <summary>Check if path is server root</summary>
	* <param name="path">Path to check</param>
	* <returns>true: path is like "/"; false: path is like /dir/dir/...</returns>
	*/
	virtual bool isPathServerRoot(std::string path) = 0;

	/*
	* <summary>Delete local file or directory</summary>
	* <param name="file">Pointer to fileContainer with information about which file to delete</param>
	* <returns>true: delete file or directory succesfull; false: error occured</returns>
	*/
	virtual bool deleteLocalFile(ContainerFileInfo *file) = 0;

	/*
	* <summary>Delete file or directory on server</summary>
	* <param name="file">Pointer to fileContainer with information about which file or directory to delete</param>
	* <returns>true: delete file or directory succesfull; false: error occured</returns>
	*/
	virtual bool deleteServerFile(ContainerFileInfo *file) = 0;

	/*
	* <summary>Creates new directory on local disk</summary>
	* <param name="pathWithName">Path with directory name to create</param>
	* <returns>true: directory create succesfull; false: error occured</returns>
	*/
	virtual bool newFolderLocal(std::string pathWithName) = 0;

	/*
	* <summary>Creates new directory on server</summary>
	* <param name="pathWithName">Path with directory name to create</param>
	* <returns>true: directory create succesfull; false: error occured</returns>
	*/
	virtual bool newFolderServer(std::string pathWithName) = 0;

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
	virtual void downloadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, std::function<void(double)> progressBarCallback, std::function<void(int)> endDownloadCallback) = 0;
	
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
	virtual void uploadFile(std::string serverPath, std::string localPath, std::string name, uint64_t size, std::function<void(double)> progressBarCallback, std::function<void(int)> endUploadCallback) = 0;

	/*
	* <summary> Kill transfer thread on transfer end<summary>
	*/
	virtual void killTransferThread() = 0;

};

