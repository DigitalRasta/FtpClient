#pragma once
#include "../../lib/Ultimate TCP-IP/ftp_c.h"
#include "InnerConfig.h"
#include <string>

namespace FtpClient {
    class ModelConnection;
}
class FtpClient::ModelConnection {
private:
	CUT_FTPClient libFtpObject;
	InnerConfig* configObject;
	int ID;
public:
	ModelConnection(std::string host, std::string port, std::string login, std::string password, int connectionId, InnerConfig* configObject);

	int getId(void);


	virtual ~ModelConnection(void);
};

