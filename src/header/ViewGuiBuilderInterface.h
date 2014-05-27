#pragma once
#include "ControlMainEventsInterface.h"
#include <string>
#include "ContainerException.h"
#include "ContainerFileInfo.h"
#include <list>
#include <functional>



namespace FtpClient {
    class ViewGuiBuilderInterface;
	typedef void (*fcallback)(double);
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

	virtual void spawnProgressBar() = 0;

	virtual std::function<void(double)> getProgressBarCallback() = 0;

	virtual void refreshProgressBar() = 0;

};

