#pragma once
#include "ControlMainEventsInterface.h"
#include "ModelDAOInterface.h"
#include "ViewGuiBuilderInterface.h"
#include "InnerConfig.h"
#include "ControlExceptionManager.h"
#include <string>

namespace FtpClient {
    class ControlMain;
}
class FtpClient::ControlMain :
	public FtpClient::ControlMainEventsInterface
{
public:
	ControlMain(ViewGuiBuilderInterface* viewGuiBuilderObject, ModelDAOInterface* modelDAOObject, InnerConfig* innerConfigObject);

	void startFtpClient(void);

	void initLocalBrowser(std::string startPath);

	/*
	*Interface
	*/
	virtual void connectWindowButtonConnectClicked(std::string host, std::string port, std::string login, std::string password);

	virtual void localTreeCellDoubleClick(std::string cellName);

	virtual ~ControlMain(void);
private:
	ViewGuiBuilderInterface* viewGuiBuilderObject;
	ModelDAOInterface* modelDAOObject;
	InnerConfig* innerConfigObject;
	ControlExceptionManager exceptionManagerObject;

	std::list<ContainerFileInfo> localFilesList;
};

