#pragma once
#include <string>
#include "ContainerFileInfo.h"

namespace FtpClient {
    class ControlMainEventsInterface;
}
class FtpClient::ControlMainEventsInterface
{
public:
	virtual void connectWindowButtonConnectClicked(std::string host, std::string port, std::string login, std::string password) = 0;

	virtual void localTreeCellDoubleClick(std::string cellName) = 0;

	virtual void serverTreeCellDoubleClick(std::string cellName) = 0;

	virtual void serverDeleteButton(ContainerFileInfo* file) = 0;

	virtual void localDeleteButton(ContainerFileInfo* file) = 0;

	virtual void localNewFolderButton() = 0;

	virtual void serverNewFolderButton() = 0;
};

