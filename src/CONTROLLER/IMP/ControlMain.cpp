#include "..\HEADER\ControlMain.h"
#include "../../MODEL/HEADER/ModelDAOInterface.h"
#include "../../VIEW/HEADER/ViewGuiBuilderInterface.h"
#include "../../InnerConfig.h"

using namespace FtpClient;

ControlMain::ControlMain(ViewGuiBuilderInterface* viewGuiBuilderObject, ModelDAOInterface* modelDAOObject, InnerConfig* innerConfigObject):viewGuiBuilderObject(viewGuiBuilderObject), modelDAOObject(modelDAOObject), innerConfigObject(innerConfigObject){

}

void ControlMain::startFtpClient(void) {
	this->viewGuiBuilderObject->initializeMainWindow();
	this->viewGuiBuilderObject->bindMainWindowEvents(this);
	this->viewGuiBuilderObject->spawnConnectWindow();
}

void ControlMain::connectWindowButtonConnectClicked(std::string host, std::string port, std::string login, std::string password) {
	//TODO
}

ControlMain::~ControlMain(void){
}
