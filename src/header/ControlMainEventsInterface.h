#pragma once
#include <string>

namespace FtpClient {
    class ControlMainEventsInterface;
}
class FtpClient::ControlMainEventsInterface
{
public:
	virtual void connectWindowButtonConnectClicked(std::string host, std::string port, std::string login, std::string password) = 0;

	virtual void localTreeCellDoubleClick(std::string cellName) = 0;
};

