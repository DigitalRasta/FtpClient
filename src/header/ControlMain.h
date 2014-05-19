#pragma once
#include "ControlMainEventsInterface.h"
#include "ModelDAOInterface.h"
#include "ViewGuiBuilderInterface.h"
#include "InnerConfig.h"
#include "ControlExceptionManager.h"
#include <string>
#include <thread>
#include <chrono>


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

	virtual void serverTreeCellDoubleClick(std::string cellName);

	virtual void serverDeleteButton(ContainerFileInfo* file);

	virtual void localDeleteButton(ContainerFileInfo* file);

	virtual void localNewFolderButton();

	virtual void serverNewFolderButton();

	virtual void downloadButton(ContainerFileInfo* fileServer);

	virtual void uploadButton(ContainerFileInfo* fileLocal);

	virtual void cancelDownload();

	virtual ~ControlMain(void);
private:
	ViewGuiBuilderInterface* viewGuiBuilderObject;
	ModelDAOInterface* modelDAOObject;
	InnerConfig* innerConfigObject;
	ControlExceptionManager exceptionManagerObject;

	std::list<ContainerFileInfo>* localFilesList;
	std::list<ContainerFileInfo>* serverFilesList;
	int currentConnectionID;



	void refreshLocalTree(std::string path);
	void refreshServerTree(std::string path, int connectionID);

};

