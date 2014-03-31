#pragma once
#include "ControlMainEventsInterface.h"
#include <string>
#include "ContainerException.h"
#include "ContainerFileInfo.h"
#include <list>



namespace FtpClient {
    class ViewGuiBuilderInterface;
}
class FtpClient::ViewGuiBuilderInterface
{
public:
	virtual void initializeMainWindow(void) = 0;
	virtual void bindMainWindowEvents(ControlMainEventsInterface* controlObject) = 0;
	virtual void spawnConnectWindow(void) = 0;
	virtual void destroyConnectWindow(void) = 0;

	virtual void spawnExceptionWindow(std::string message, ExceptionLevel errorLevel) = 0;

	virtual void showListInLocalTree(std::list<ContainerFileInfo> filesList) = 0;
};

