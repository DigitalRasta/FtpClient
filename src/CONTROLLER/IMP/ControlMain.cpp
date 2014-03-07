#include "..\HEADER\ControlMain.h"
#include "../../MODEL/HEADER/ModelDAOInterface.h"
#include "../../VIEW/HEADER/ViewGuiBuilderInterface.h"
#include "../../InnerConfig.h"

using namespace FtpClient;

ControlMain::ControlMain(ViewGuiBuilderInterface* viewGuiBuilderObject, ModelDAOInterface* modelDAOObject, InnerConfig* innerConfigObject):viewGuiBuilderObject(viewGuiBuilderObject), modelDAOObject(modelDAOObject), innerConfigObject(innerConfigObject){

}

void ControlMain::startFtpClient(void) {
	this->viewGuiBuilderObject->initializeMainWindow();
}


ControlMain::~ControlMain(void){
}
