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

	virtual std::list<ContainerFileInfo> getLogicalDrives(void) = 0;

	virtual std::list<ContainerFileInfo> getDirectoryContent(std::string path) = 0;

};

