#pragma once
#include "ControlMainEventsInterface.h"
#include <string>
#include "ExceptionContainer.h"



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
};

