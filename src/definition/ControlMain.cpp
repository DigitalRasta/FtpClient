#include "../header/ControlMain.h"
#include "../header/ModelDAOInterface.h"
#include "../header/ViewGuiBuilderInterface.h"
#include "../header/ExceptionContainer.h"
#include "../header/InnerConfig.h"

#include "F:\projekty\CPP\FtpClient\lib\Ultimate TCP-IP\ftp_c.h"

using namespace FtpClient;

ControlMain::ControlMain(ViewGuiBuilderInterface* viewGuiBuilderObject, ModelDAOInterface* modelDAOObject, InnerConfig* innerConfigObject):viewGuiBuilderObject(viewGuiBuilderObject), modelDAOObject(modelDAOObject), innerConfigObject(innerConfigObject){

}

void ControlMain::startFtpClient(void) {
	this->viewGuiBuilderObject->initializeMainWindow();
	this->viewGuiBuilderObject->bindMainWindowEvents(this);
	//this->viewGuiBuilderObject->spawnExceptionWindow("Fkurwe przejebany error", CRITICAL);
	//this->viewGuiBuilderObject->spawnConnectWindow();

	this->modelDAOObject->getLogicalDrives();
}

void ControlMain::connectWindowButtonConnectClicked(std::string host, std::string port, std::string login, std::string password) {
	CUT_FTPClient* client = new CUT_FTPClient();
	int retcode = client->FTPConnect("Dundas.com");
}

ControlMain::~ControlMain(void){
}
