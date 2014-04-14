#include "../header/ModelConnection.h"
#include "../header/ContainerException.h"
#include "../header/InnerConfig.h"
#include "../header/ContainerFileInfo.h"
#include "../../lib/CurlEasy.h"
#include <sstream>
#include <list>

using namespace FtpClient;

ModelConnection::ModelConnection(std::string host, std::string port, std::string login, std::string password, int connectionId, InnerConfig* configObject){
}

int ModelConnection::getId(void) {
	return this->ID;
}

std::list<ContainerFileInfo> ModelConnection::getDirectoryContent(void) {
	std::list<ContainerFileInfo> listToReturn;
	return listToReturn;
}

ModelConnection::~ModelConnection(void)
{
}
