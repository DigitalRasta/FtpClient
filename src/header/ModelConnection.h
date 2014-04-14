#pragma once
#include "../../lib/CurlEasy.h"
#include "InnerConfig.h"
#include "ContainerFileInfo.h"
#include <list>
#include <string>

namespace FtpClient {
    class ModelConnection;
}
class FtpClient::ModelConnection {
private:
	curl::CurlEasy libFtpObject;
	InnerConfig* configObject;
	int ID;
	std::string currentPath;

public:
	ModelConnection(std::string host, std::string port, std::string login, std::string password, int connectionId, InnerConfig* configObject);

	int getId(void);
	std::list<ContainerFileInfo> getDirectoryContent(void);
	virtual ~ModelConnection(void);
};

