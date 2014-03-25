#pragma once
#include <vector>
#include <string>

namespace FtpClient {
    class ModelDAOInterface;
}
class FtpClient::ModelDAOInterface
{
public:

	virtual std::vector<std::string> getLogicalDrives(void) = 0;

};

