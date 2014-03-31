#include "../header/ControlMain.h"
#include "../header/ModelDAOInterface.h"
#include "../header/ViewGuiBuilderInterface.h"
#include "../header/ContainerException.h"
#include "../header/ContainerFileInfo.h"
#include "../header/InnerConfig.h"

#include "F:\projekty\CPP\FtpClient\lib\Ultimate TCP-IP\ftp_c.h"

#include <string>
#include <vector>
#include <list>
using namespace FtpClient;

ControlMain::ControlMain(ViewGuiBuilderInterface* viewGuiBuilderObject, ModelDAOInterface* modelDAOObject, InnerConfig* innerConfigObject):viewGuiBuilderObject(viewGuiBuilderObject), modelDAOObject(modelDAOObject), innerConfigObject(innerConfigObject){

}

void ControlMain::startFtpClient(void) {
	this->viewGuiBuilderObject->initializeMainWindow();
	this->viewGuiBuilderObject->bindMainWindowEvents(this);
	//this->initLocalBrowser("C:/Windows/addins");
	//this->viewGuiBuilderObject->spawnExceptionWindow("ERROR!", ExceptionLevel::EXCEPTIONLEVEL_CRITICAL);
	this->viewGuiBuilderObject->spawnConnectWindow();

	this->modelDAOObject->getLogicalDrives();
}


void ControlMain::initLocalBrowser(std::string startPath) {
	std::list<ContainerFileInfo> listToDisplay;
	if(startPath.compare("/") == 0 || startPath.compare("\\") == 0 || startPath.compare(" ") == 0 ) {
		listToDisplay = this->modelDAOObject->getLogicalDrives();
	} else {
		listToDisplay = this->modelDAOObject->getDirectoryContent(startPath);
	}
	//this->viewGuiBuilderObject->showListInLocalTree(listToDisplay);
}



void ControlMain::connectWindowButtonConnectClicked(std::string host, std::string port, std::string login, std::string password) {
	CUT_FTPClient* client = new CUT_FTPClient();
	int retcode = client->FTPConnect("Dundas.com");
}

ControlMain::~ControlMain(void){
}
