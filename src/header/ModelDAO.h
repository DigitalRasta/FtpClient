#pragma once
#include "ModelDAOInterface.h"
#include "InnerConfig.h"
#include <string>
#include <vector>
#include <Windows.h>

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
	* return: list of logical drives
	*/
	std::vector<std::string> getLogicalDrives(void);

	/*
	* Convert bit representation of logical drives to letters.
	* params:
	*	*volumesList - 32 bit integer represents list of volumes on user PC. First bit means A, second B, third C....
	*/
	std::vector<std::string> convertLogicalDrives(DWORD volumesList);


private:
	InnerConfig* innerConfigObject;
};

