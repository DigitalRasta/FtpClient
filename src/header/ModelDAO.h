#pragma once
#include "ModelDAOInterface.h"
#include "../header/ContainerFileInfo.h"
#include "InnerConfig.h"
#include <string>
#include <vector>
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
	std::list<ContainerFileInfo> getLogicalDrives(void);

	/*
	* Convert bit representation of logical drives to letters.
	* params:
	*	*volumesList - 32 bit integer represents list of volumes on user PC. First bit means A, second B, third C....
	*/
	std::vector<std::string> convertLogicalDrives(DWORD volumesList);


	/*
	* INTERFACE
	* Get info from local disk
	* return: Return list of files/folder in path directory
	* throws: ContainerException if cannot read path directory
	*/
	std::list<ContainerFileInfo> getDirectoryContent(std::string path);


private:
	InnerConfig* innerConfigObject;
};

