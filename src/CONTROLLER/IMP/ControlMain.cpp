#include "..\HEADER\ControlMain.h"
#include "../../MODEL/HEADER/ModelDAOInterface.h"
#include "../../VIEW/HEADER/ViewGuiBuilderInterface.h"
#include "../../ExceptionContainer.h"
#include "../../InnerConfig.h"

#include "../../../lib/Ultimate TCP-IP/ftp_c.h"

using namespace FtpClient;

ControlMain::ControlMain(ViewGuiBuilderInterface* viewGuiBuilderObject, ModelDAOInterface* modelDAOObject, InnerConfig* innerConfigObject):viewGuiBuilderObject(viewGuiBuilderObject), modelDAOObject(modelDAOObject), innerConfigObject(innerConfigObject){

}

void ControlMain::startFtpClient(void) {
	this->viewGuiBuilderObject->initializeMainWindow();
	this->viewGuiBuilderObject->bindMainWindowEvents(this);
	this->viewGuiBuilderObject->spawnExceptionWindow("Fkurwe przejebany error", CRITICAL);
	//this->viewGuiBuilderObject->spawnConnectWindow();
}

void ControlMain::connectWindowButtonConnectClicked(std::string host, std::string port, std::string login, std::string password) {
	CUT_FTPClient* client = new CUT_FTPClient();
	int retcode = client->FTPConnect("Dundas.com");
}

ControlMain::~ControlMain(void){
}
