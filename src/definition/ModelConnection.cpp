#include "../header/ModelConnection.h"
#include "../header/ContainerException.h"
#include "../header/InnerConfig.h"
#include "../../lib/Ultimate TCP-IP/ftp_c.h"
#include <sstream>

using namespace FtpClient;

ModelConnection::ModelConnection(std::string host, std::string port, std::string login, std::string password, int connectionId, InnerConfig* configObject){
	this->libFtpObject = CUT_FTPClient();
	this->configObject = configObject;
	int portConverted;
	std::istringstream (port) >> portConverted;
	this->libFtpObject.SetControlPort(portConverted);
	this->libFtpObject.SetDataPort(portConverted);
	int result = this->libFtpObject.FTPConnect(host.c_str(), login.c_str(), password.c_str());
	this->ID = connectionId;
	if(result != UTE_SUCCESS) {
		switch(result) {
		case UTE_BAD_HOSTNAME:
			throw ContainerException(this->configObject->exception_connection_badHostName, ExceptionLevel::EXCEPTIONLEVEL_STANDARD, ExceptionCode::EXCEPTION_CONNECTION_BAD_HOSTNAME);
		break;
		case UTE_CONNECT_FAILED:
			throw ContainerException(this->configObject->exception_connection_connectFailed, ExceptionLevel::EXCEPTIONLEVEL_STANDARD, ExceptionCode::EXCEPTION_CONNECTION_CONNECT_FAILED);
		break;
		case UTE_NO_RESPONSE:
			throw ContainerException(this->configObject->exception_connection_noResponse, ExceptionLevel::EXCEPTIONLEVEL_STANDARD, ExceptionCode::EXCEPTION_CONNECTION_NO_RESPONSE);
		break;
		case UTE_INVALID_RESPONSE:
			throw ContainerException(this->configObject->exception_connection_invalidResponse, ExceptionLevel::EXCEPTIONLEVEL_STANDARD, ExceptionCode::EXCEPTION_CONNECTION_INVALID_RESPONSE);
		break;
		case UTE_USER_NA:
			throw ContainerException(this->configObject->exception_connection_userNa, ExceptionLevel::EXCEPTIONLEVEL_STANDARD, ExceptionCode::EXCEPTION_CONNECTION_USER_NA);
		break;
		case UTE_PASS_NA:
			throw ContainerException(this->configObject->exception_connection_passNa, ExceptionLevel::EXCEPTIONLEVEL_STANDARD, ExceptionCode::EXCEPTION_CONNECTION_PASS_NA);
		break;
		}
		throw ContainerException(std::string(this->configObject->exception_connection_unknown), ExceptionLevel::EXCEPTIONLEVEL_STANDARD, ExceptionCode::EXCEPTION_CONNECTION_CONNECT_FAILED_UNKNOWN);
	}
}

int ModelConnection::getId(void) {
	return this->ID;
}

ModelConnection::~ModelConnection(void)
{
}
