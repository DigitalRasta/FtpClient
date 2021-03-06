#pragma once
#include "ViewGuiBuilderInterface.h"
#include "ContainerException.h"
#include "InnerConfig.h"
#include "ControlMainEventsInterface.h"

namespace FtpClient {
    class ControlExceptionManager;
}
/*
* <summary>Class for exception managing. Spawns information window </summary>
*/
class FtpClient::ControlExceptionManager
{
private:

	ViewGuiBuilderInterface* viewGuiBuilderObject;
	InnerConfig* innerConfigObject;

public:

	ControlExceptionManager(ViewGuiBuilderInterface* viewGuiBuilderObject, InnerConfig* innerConfigObject);

	void manageException(ContainerException &e);

	virtual ~ControlExceptionManager(void);
};

