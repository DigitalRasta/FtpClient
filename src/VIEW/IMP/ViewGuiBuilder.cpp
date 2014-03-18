#include "..\HEADER\ViewGuiBuilder.h"
#include "../../InnerConfig.h"
#include "../../ExceptionContainer.h"
#include <gtk-3.0/gtk/gtk.h>
#include <string>


using namespace FtpClient;
ViewGuiBuilder::ViewGuiBuilder(InnerConfig* innerConfigObject): innerConfigObject(innerConfigObject){
	this->connectWindow = NULL;
	this->exceptionWindow = NULL;
	this->fileListManagetObject = new ViewFileListManager(this->innerConfigObject);
}

	/*START
	*--->mainWindow<---
	*/
void ViewGuiBuilder::initializeMainWindow(void) {
	this->mainWindowHandler = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
	gtk_window_set_title(GTK_WINDOW(this->mainWindowHandler), this->innerConfigObject->lang_mainWindowTitle.c_str());
	gtk_widget_set_size_request(GTK_WIDGET(this->mainWindowHandler), this->innerConfigObject->view_mainWindowWidth, this->innerConfigObject->view_mainWindowHeight);
	gtk_window_set_position(GTK_WINDOW(this->mainWindowHandler), GTK_WIN_POS_CENTER);
	gtk_widget_override_background_color(this->mainWindowHandler, GTK_STATE_FLAG_NORMAL, &this->innerConfigObject->view_mainWindowBackground);
	g_signal_connect(G_OBJECT(this->mainWindowHandler), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	this->layoutManager = gtk_grid_new();
	gtk_grid_set_column_homogeneous (GTK_GRID(this->layoutManager), FALSE);
	this->buildInterface();
	gtk_container_add(GTK_CONTAINER(this->mainWindowHandler), this->layoutManager);
	gtk_grid_set_row_spacing(GTK_GRID(this->layoutManager), 20);
	gtk_grid_set_column_spacing(GTK_GRID(this->layoutManager), 20);
	gtk_widget_show_all(this->mainWindowHandler);
	
}

void ViewGuiBuilder::buildInterface(void) {
	this->menuBar = gtk_menu_bar_new();
	GtkWidget* menuItemButtonConnect =  gtk_menu_item_new_with_label(this->innerConfigObject->lang_mainWindowMenuConnectButtonText.c_str());
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menuBar), menuItemButtonConnect);
	gtk_widget_set_hexpand(this->menuBar, TRUE);
	gtk_grid_attach(GTK_GRID(this->layoutManager), this->menuBar,0,0,3,1);
	gtk_grid_attach(GTK_GRID(this->layoutManager), this->fileListManagetObject->createFilesListServer(),0,1,1,1);
	gtk_grid_attach(GTK_GRID(this->layoutManager), this->fileListManagetObject->createFilesListLocal(),2,1,1,1);

	
	g_signal_connect(menuItemButtonConnect, "activate", G_CALLBACK(this->mainWindowMenuBarButtonConnectClicked), this);

}

void ViewGuiBuilder::mainWindowMenuBarButtonConnectClicked(GtkWidget* object, gpointer* data) {
	ViewGuiBuilder* guiObject = (ViewGuiBuilder*)data;

	if(guiObject->connectWindow == NULL) {
		guiObject->spawnConnectWindow();
	} else {
		gtk_widget_destroy(guiObject->connectWindow);
		guiObject->spawnConnectWindow();
	}
}

void ViewGuiBuilder::bindMainWindowEvents(ControlMainEventsInterface* controlObject) {
	this->controlObject = controlObject;
}
	/*END
	*<---mainWindow--->
	*/

	/*START
	*--->connectWindow<---
	*/
void ViewGuiBuilder::spawnConnectWindow(void) {
	this->connectWindow = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(this->connectWindow), this->innerConfigObject->lang_connectWindowTitle.c_str());
	gtk_widget_set_size_request(this->connectWindow, this->innerConfigObject->view_connectWindowWidth, this->innerConfigObject->view_connectWindowHeight);
	gtk_window_set_resizable(GTK_WINDOW(this->connectWindow), FALSE);
	gtk_window_set_position(GTK_WINDOW(this->connectWindow), GTK_WIN_POS_CENTER);
	gtk_widget_override_background_color(this->connectWindow, GTK_STATE_FLAG_NORMAL, &this->innerConfigObject->view_mainWindowBackground);
	GtkWidget* contentArea = gtk_dialog_get_content_area (GTK_DIALOG (this->connectWindow));
	gtk_container_add(GTK_CONTAINER(contentArea), this->buildConnectWindowInterface());
	//Events
	g_signal_connect(this->connectWindow_buttonConnect, "clicked", G_CALLBACK(this->connectWindowButtonConnectClicked), this);
	gtk_widget_show_all (this->connectWindow);
	gtk_dialog_run(GTK_DIALOG(this->connectWindow));
}

GtkWidget* ViewGuiBuilder::buildConnectWindowInterface(void) {
	GtkWidget* connectWindowManager = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(connectWindowManager), 20);
	GtkWidget* label_host = gtk_label_new(this->innerConfigObject->lang_connectWindowLabelHost.c_str());
	GtkWidget* label_port = gtk_label_new(this->innerConfigObject->lang_connectWindowLabelPort.c_str());
	GtkWidget* label_login = gtk_label_new(this->innerConfigObject->lang_connectWindowLabelLogin.c_str());
	GtkWidget* label_password = gtk_label_new(this->innerConfigObject->lang_connectWindowLabelPassword.c_str());
	this->connectWindow_inputHost = gtk_entry_new();
	this->connectWindow_inputPort = gtk_entry_new();
	this->connectWindow_inputLogin = gtk_entry_new();
	this->connectWindow_inputPassword = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(this->connectWindow_inputPassword), FALSE);

	this->connectWindow_buttonConnect = gtk_button_new_with_label(this->innerConfigObject->lang_connectWindowButtonConnect.c_str());
	
	GtkWidget * frame = gtk_frame_new("Connection info");
	gtk_grid_attach(GTK_GRID(connectWindowManager), label_host,0,0,1,1);
	gtk_grid_attach(GTK_GRID(connectWindowManager), this->connectWindow_inputHost,1,0,1,1);
	gtk_grid_attach(GTK_GRID(connectWindowManager), label_port,0,1,1,1);
	gtk_grid_attach(GTK_GRID(connectWindowManager), this->connectWindow_inputPort,1,1,1,1);
	gtk_grid_attach(GTK_GRID(connectWindowManager), label_login,0,2,1,1);
	gtk_grid_attach(GTK_GRID(connectWindowManager), this->connectWindow_inputLogin,1,2,1,1);
	gtk_grid_attach(GTK_GRID(connectWindowManager), label_password,0,3,1,1);
	gtk_grid_attach(GTK_GRID(connectWindowManager), this->connectWindow_inputPassword,1,3,1,1);
	gtk_grid_attach(GTK_GRID(connectWindowManager), this->connectWindow_buttonConnect,0,4,2,1);
	gtk_container_add(GTK_CONTAINER(frame), connectWindowManager);
	return frame;
}

void ViewGuiBuilder::connectWindowButtonConnectClicked(GtkWidget* button, gpointer* data) {
	ViewGuiBuilder* object = (ViewGuiBuilder*)data;
	object->controlObject->connectWindowButtonConnectClicked(
		std::string(gtk_entry_get_text(GTK_ENTRY(object->connectWindow_inputHost))),
		std::string(gtk_entry_get_text(GTK_ENTRY(object->connectWindow_inputPort))),
		std::string(gtk_entry_get_text(GTK_ENTRY(object->connectWindow_inputLogin))),
		std::string(gtk_entry_get_text(GTK_ENTRY(object->connectWindow_inputPassword)))
		);
	object->destroyConnectWindow();
}

void ViewGuiBuilder::destroyConnectWindow(void) {
	if(this->connectWindow != NULL) {
		gtk_widget_destroy(this->connectWindow);
		this->connectWindow = NULL;
	}
}
	/*END
	*<---connectWindow--->
	*/


void ViewGuiBuilder::spawnExceptionWindow(std::string message, ExceptionLevel errorLevel) {
	this->exceptionWindow = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(this->exceptionWindow), this->innerConfigObject->lang_exceptionWindowTitle.c_str());
	gtk_widget_set_size_request(this->exceptionWindow, this->innerConfigObject->view_exceptionWindowWidth, this->innerConfigObject->view_exceptionWindowHeight);
	gtk_window_set_resizable(GTK_WINDOW(this->exceptionWindow), FALSE);
	gtk_window_set_position(GTK_WINDOW(this->exceptionWindow), GTK_WIN_POS_CENTER);
	gtk_widget_override_background_color(this->exceptionWindow, GTK_STATE_FLAG_NORMAL, &this->innerConfigObject->view_mainWindowBackground);
	GtkWidget* contentArea = gtk_dialog_get_content_area (GTK_DIALOG (this->exceptionWindow));
	gtk_container_add(GTK_CONTAINER(contentArea), this->buildExceptionWindowInterface());
	//Events
	gtk_widget_show_all (this->exceptionWindow);
	gtk_dialog_run(GTK_DIALOG(this->exceptionWindow));
}

GtkWidget* ViewGuiBuilder::buildExceptionWindowInterface(std::string message, ExceptionLevel errorLevel) {
	GtkWidget* exceptionWindowManager = gtk_grid_new();
	std::string iconSrc;
	switch(errorLevel) {
		case STANDARD:
			iconSrc = innerConfigObject->view_exceptionWindowIconSrcStandard;
			break;
		case HIGH:
			iconSrc = innerConfigObject->view_exceptionWindowIconSrcHigh;
			break;
		case CRITICAL:
			iconSrc = innerConfigObject->view_exceptionWindowIconSrcCritical;
			break;
	}
	GtkWidget* iconImage = gtk_image_new_from_file(iconSrc.c_str());
	GtkWidget* label_message = gtk_label_new(message.c_str());
	gtk_widget_set_hexpand(label_message, TRUE);

	this->exceptionWindow_buttonOk = gtk_button_new_with_label("OK");
	gtk_grid_attach(GTK_GRID(exceptionWindowManager), iconImage,0,0,1,1);
	gtk_grid_attach(GTK_GRID(exceptionWindowManager), label_message,1,0,1,1);
	return exceptionWindowManager;
}



ViewGuiBuilder::~ViewGuiBuilder(void){
}
