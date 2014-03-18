#pragma once
#include "ViewGuiBuilderInterface.h"
#include "../../InnerConfig.h"
#include "../../CONTROLLER/HEADER/ControlMainEventsInterface.h"
#include "ViewFileListManager.h"
#include <gtk-3.0/gtk/gtk.h>

namespace FtpClient {
    class ViewGuiBuilder;
}
class FtpClient::ViewGuiBuilder :
	public FtpClient::ViewGuiBuilderInterface
{
public:
	ViewGuiBuilder(InnerConfig* innerConfigObject);
	virtual ~ViewGuiBuilder(void);

	virtual void initializeMainWindow(void);

	/*
	* INTERFACE
	* Spawn connect window and gives all control to it
	*/
	virtual void spawnConnectWindow(void);

	/*
	* INTERFACE
	* Destroy connectWindow and sets all linked variables to null
	*/
	virtual void destroyConnectWindow(void);

	/*
	* INTERFACE
	* Spawn window for exception message.
	* params:
	*	*message: message for user
	*	*errorLevel: needed for display proper window
	*/
	virtual void spawnExceptionWindow(std::string message, ExceptionLevel errorLevel);
private:
	InnerConfig* innerConfigObject;
	ControlMainEventsInterface* controlObject;
	ViewFileListManager* fileListManagetObject;

	GtkWidget* mainWindowHandler;
	GtkWidget* layoutManager;

	GtkWidget* menuBar;

	GtkWidget* connectWindow; //dialog for connect params
	GtkWidget* connectWindow_inputHost; //entry handlers
	GtkWidget* connectWindow_inputPort;
	GtkWidget* connectWindow_inputLogin;
	GtkWidget* connectWindow_inputPassword;
	GtkWidget* connectWindow_buttonConnect;

	GtkWidget* exceptionWindow;
	GtkWidget* exceptionWindow_buttonOk;

	/*
	* Build interface for main window. Create menu bar, create layout manager, spawn connect window on start, create files lists
	*/
	virtual void buildInterface(void);



	virtual void bindMainWindowEvents(ControlMainEventsInterface* controlObject);


	/*
	* Build interface (labels, inputs, buttons) for connectWindow.
	* Return: Container containing interfaces elements.
	*/
	virtual GtkWidget* buildConnectWindowInterface(void);


	/*
	* Build content for exceptionWindow
	* Return: Container containing elements to show
	*/
	virtual GtkWidget* buildExceptionWindowInterface(std::string message, ExceptionLevel errorLevel);

	/*
	*Events
	* Callback for connect button in connectWindow. Send to control object data received from connectWindow form.
	* Params:
	*	button - do nothing, lib require
	*	data - pointer casting to ViewGuiBuilder object
	*/
	static void connectWindowButtonConnectClicked(GtkWidget* button, gpointer* data);

	/*
	*Events
	* Callback for connect button in menu bar in mainWinow. Spawn connectWindow if not spawned yet.
	* Params:
	*	object - do nothing, lib require
	*	data - pointer casting to ViewGuiBuilder object
	*/
	static void mainWindowMenuBarButtonConnectClicked(GtkWidget* object, gpointer* data);

};

