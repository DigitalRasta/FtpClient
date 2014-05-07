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

	virtual void showListInLocalTree(std::list<ContainerFileInfo>* filesList) = 0;

	virtual void showListInServerTree(std::list<ContainerFileInfo>* filesList) = 0;

	virtual void activateDownloadButton() = 0;
	virtual void deactivateDownloadButton() = 0;
	virtual void activateUploadButton() = 0;
	virtual void deactivateUploadButton() = 0;
	virtual void activateDeleteButton() = 0;
	virtual void deactivateDeleteButton() = 0;
	virtual void activateNewFolderButton() = 0;
	virtual void deactivateNewFolderButton() = 0;

	virtual bool spawnAreYouSureWindow() = 0;

	virtual std::string spawnInsertNameWindow() = 0;
};

