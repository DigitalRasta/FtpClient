#pragma once
#include "ViewGuiBuilderInterface.h"
#include "ContainerException.h"
#include "InnerConfig.h"

namespace FtpClient {
    class ControlExceptionManager;
}
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

