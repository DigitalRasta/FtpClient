#include <gtk-3.0/gtk/gtk.h>

#include "../header/ControlMain.h"
#include "../header/ViewGuiBuilder.h"
#include "../header/ModelDAO.h"
#include "../header/InnerConfig.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;
using namespace FtpClient;
int main(int argc, char* argv[])
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    gtk_init(&argc, &argv);
	/*
	* Layers initialization
	*/
	InnerConfig* innerConfigObject = new InnerConfig();
	ViewGuiBuilder* viewGuiBuilderObject = new ViewGuiBuilder(innerConfigObject);
	ModelDAO* modelDAOObject = new ModelDAO(innerConfigObject);
	/*
	* Dependency injection
	*/
	ControlMain* controlMainObject = new ControlMain(viewGuiBuilderObject, modelDAOObject, innerConfigObject);
	/*
	* Start program - all control receive controller
	*/
	controlMainObject->startFtpClient(); 
	while(true) {
		controlMainObject->checkTransferEnd();
		if(controlMainObject->checkProgramEnd()) {
			break;
		}
		gtk_main_iteration_do(TRUE);
	}
	delete(innerConfigObject);
	delete(viewGuiBuilderObject);
	delete(modelDAOObject);
	delete(controlMainObject);
    return 0;
}