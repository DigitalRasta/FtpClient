#include <gtk-3.0/gtk/gtk.h>

#include "CONTROLLER\HEADER\ControlMain.h"
#include "VIEW\HEADER\ViewGuiBuilder.h"
#include "MODEL\HEADER\ModelDAO.h"
#include "InnerConfig.h"

using namespace std;
using namespace FtpClient;
int main(int argc, char* argv[])
{
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
	gtk_main(); 
    return 0;
}