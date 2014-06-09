#pragma once
#include "ViewGuiBuilderInterface.h"
#include "ContainerException.h"
#include "InnerConfig.h"
#include "ControlMainEventsInterface.h"

namespace FtpClient {
    class ControlExceptionManager;
}
class FtpClient::ControlExceptionManager
{
private:

	ViewGuiBuilderInterface* viewGuiBuilderObject;
	InnerConfig* innerConfigObject;
	ControlMainEventsInterface* mainControlObject;

public:

	ControlExceptionManager(ViewGuiBuilderInterface* viewGuiBuilderObject, InnerConfig* innerConfigObject, ControlMainEventsInterface* ctrl);

	void manageException(ContainerException &e);

	virtual ~ControlExceptionManager(void);
};

