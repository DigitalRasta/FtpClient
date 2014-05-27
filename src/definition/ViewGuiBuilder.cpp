#include "../header/ViewGuiBuilder.h"
#include "../header/InnerConfig.h"
#include "../header/ContainerException.h"
#include "../header/ContainerFileInfo.h"

#include <gtk-3.0/gtk/gtk.h>
#include <string>
#include <list>


using namespace FtpClient;
ViewGuiBuilder::ViewGuiBuilder(InnerConfig* innerConfigObject): innerConfigObject(innerConfigObject){
	this->connectWindow = NULL;
	this->exceptionWindow = NULL;
	this->progressBarDialog = NULL;
	this->fileListManagerObject = new ViewFileListManager(this->innerConfigObject);
	this->doubleClick = false;

	this->buttonDownloadIconActive = gtk_image_new_from_file (this->innerConfigObject->view_buttonDownloadActiveIconSrc.c_str());
	this->buttonDownloadIconInactive = gtk_image_new_from_file (this->innerConfigObject->view_buttonDownloadInactiveIconSrc.c_str());
	this->buttonUploadIconActive = gtk_image_new_from_file (this->innerConfigObject->view_buttonUploadActiveIconSrc.c_str());
	this->buttonUploadIconInactive = gtk_image_new_from_file (this->innerConfigObject->view_buttonUploadInactiveIconSrc.c_str());
	this->buttonDeleteIconActive = gtk_image_new_from_file (this->innerConfigObject->view_buttonDeleteActiveIconSrc.c_str());
	this->buttonDeleteIconInactive = gtk_image_new_from_file (this->innerConfigObject->view_buttonDeleteInactiveIconSrc.c_str());
	this->buttonNewFolderIconActive = gtk_image_new_from_file (this->innerConfigObject->view_buttonNewFolderActiveIconSrc.c_str());
	this->buttonNewFolderIconInactive = gtk_image_new_from_file (this->innerConfigObject->view_buttonNewFolderInactiveIconSrc.c_str());
}

	/*START
	*--->mainWindow<---
	*/
void ViewGuiBuilder::initializeMainWindow(void) {
	this->mainWindowHandler = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
	gtk_window_set_icon_from_file(GTK_WINDOW(this->mainWindowHandler), "img/icon.png", NULL);
	gtk_window_set_title(GTK_WINDOW(this->mainWindowHandler), this->innerConfigObject->lang_mainWindowTitle.c_str());
	gtk_widget_set_size_request(GTK_WIDGET(this->mainWindowHandler), this->innerConfigObject->view_mainWindowWidth, this->innerConfigObject->view_mainWindowHeight);
	gtk_window_set_position(GTK_WINDOW(this->mainWindowHandler), GTK_WIN_POS_CENTER);
	GdkRGBA color;
	gdk_rgba_parse(&color,this->innerConfigObject->view_mainWindowBackground.c_str());
	gtk_widget_override_background_color(this->mainWindowHandler, GTK_STATE_FLAG_NORMAL, &color);
	g_signal_connect(G_OBJECT(this->mainWindowHandler), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	this->layoutManager = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(this->layoutManager), 20);
	gtk_grid_set_column_spacing(GTK_GRID(this->layoutManager), 20);
	gtk_grid_set_column_homogeneous (GTK_GRID(this->layoutManager), FALSE);
	gtk_container_add(GTK_CONTAINER(this->mainWindowHandler), this->layoutManager);

	this->buildInterface();

	gtk_widget_show_all(this->mainWindowHandler);
	
}

void ViewGuiBuilder::buildInterface(void) {
	this->menuBar = gtk_menu_bar_new();
	GtkWidget* menuItemButtonConnect =  gtk_menu_item_new_with_label(this->innerConfigObject->lang_mainWindowMenuConnectButtonText.c_str());
	gtk_menu_shell_append(GTK_MENU_SHELL(this->menuBar), menuItemButtonConnect);
	gtk_widget_set_hexpand(this->menuBar, TRUE);
	gtk_grid_attach(GTK_GRID(this->layoutManager), this->menuBar,0,0,3,1);
	gtk_grid_attach(GTK_GRID(this->layoutManager), this->fileListManagerObject->createFilesListServer(),0,1,1,3);
	gtk_grid_attach(GTK_GRID(this->layoutManager), this->fileListManagerObject->createFilesListLocal(),2,1,1,3);
	gtk_grid_attach(GTK_GRID(this->layoutManager), this->createStandardButtons(),1,2,1,1);
	
	g_signal_connect(menuItemButtonConnect, "activate", G_CALLBACK(this->mainWindowMenuBarButtonConnectClicked), this);
	g_signal_connect(this->fileListManagerObject->getLocalTreeHandler(), "row-activated", G_CALLBACK(this->localTreeRowDoubleClick), this);
	g_signal_connect(this->fileListManagerObject->getServerTreeHandler(), "row-activated", G_CALLBACK(this->serverTreeRowDoubleClick), this);
	GtkTreeSelection* selectionServer = gtk_tree_view_get_selection(GTK_TREE_VIEW(this->fileListManagerObject->getServerTreeHandler()));
	gtk_tree_selection_set_mode(selectionServer, GTK_SELECTION_SINGLE);
	gtk_tree_selection_set_select_function(selectionServer, this->serverTreeRowSelected, this, NULL);
	GtkTreeSelection* selectionLocal = gtk_tree_view_get_selection(GTK_TREE_VIEW(this->fileListManagerObject->getLocalTreeHandler()));
	gtk_tree_selection_set_mode(selectionLocal, GTK_SELECTION_SINGLE);
	gtk_tree_selection_set_select_function(selectionLocal, this->localTreeRowSelected, this, NULL);

	 g_signal_connect(this->buttonDelete, "clicked", G_CALLBACK (this->deleteButtonClicked), this);
	 g_signal_connect(this->buttonNewFolder, "clicked", G_CALLBACK (this->newFolderButtonClicked), this);
	 g_signal_connect(this->buttonDownload, "clicked", G_CALLBACK (this->downloadButtonClicked), this);
	 g_signal_connect(this->buttonUpload, "clicked", G_CALLBACK (this->uploadButtonClicked), this);
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

GtkWidget* ViewGuiBuilder::createStandardButtons() {
	GtkWidget* boxContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
	this->buttonUpload = gtk_button_new();
	this->buttonDownload = gtk_button_new();
	this->buttonDelete = gtk_button_new();
	this->buttonNewFolder = gtk_button_new();
	this->deactivateDownloadButton();
	this->deactivateUploadButton();
	this->deactivateDeleteButton();
	this->deactivateNewFolderButton();
	gtk_box_pack_start (GTK_BOX(boxContainer), this->buttonUpload, false, false, 0);
	gtk_box_pack_start (GTK_BOX(boxContainer), this->buttonDownload, false, false, 0 );
	gtk_box_pack_start (GTK_BOX(boxContainer), this->buttonDelete, false, false, 0 );
	gtk_box_pack_start (GTK_BOX(boxContainer), this->buttonNewFolder, false, false, 0 );
	return boxContainer;
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
	GdkRGBA color;
	gdk_rgba_parse(&color,this->innerConfigObject->view_mainWindowBackground.c_str());
	gtk_widget_override_background_color(this->connectWindow, GTK_STATE_FLAG_NORMAL, &color);
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
	
	GtkWidget * frame = gtk_frame_new(this->innerConfigObject->lang_connectWindowTitle.c_str());
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
	GtkMessageType error;
	switch(errorLevel) {
	case FtpClient::EXCEPTIONLEVEL_STANDARD:
		error = GTK_MESSAGE_INFO;
		break;
	case FtpClient::EXCEPTIONLEVEL_HIGH:
		error = GTK_MESSAGE_WARNING;
		break;
	case FtpClient::EXCEPTIONLEVEL_CRITICAL:
		error = GTK_MESSAGE_ERROR;
		break;
	}
	this->exceptionWindow = gtk_message_dialog_new(GTK_WINDOW(this->mainWindowHandler), GTK_DIALOG_DESTROY_WITH_PARENT, error, GTK_BUTTONS_OK, message.c_str());
	g_signal_connect(this->exceptionWindow, "response",G_CALLBACK(this->exceptionWindowOkButton), this);
	gtk_widget_show_all (this->exceptionWindow);
	gtk_dialog_run(GTK_DIALOG(this->exceptionWindow));
}

void ViewGuiBuilder::exceptionWindowOkButton(GtkDialog* dialog, gint id, gpointer* data) {
	ViewGuiBuilder* object = (ViewGuiBuilder*)data;
	object->destroyExceptionWindow();
}

void ViewGuiBuilder::destroyExceptionWindow(void) {
	if(this->exceptionWindow != NULL) {
		gtk_widget_destroy(this->exceptionWindow);
		this->exceptionWindow = NULL;
	}
}

void ViewGuiBuilder::showListInLocalTree(std::list<ContainerFileInfo>* filesList) {
	this->fileListManagerObject->showListInLocalTree(filesList);
	this->doubleClick = false;
	gtk_widget_show_all(this->mainWindowHandler);
}

void ViewGuiBuilder::showListInServerTree(std::list<ContainerFileInfo>* filesList) {
	this->fileListManagerObject->showListInServerTree(filesList);
	this->doubleClick = false;
	gtk_widget_show_all(this->mainWindowHandler);
}





void ViewGuiBuilder::activateDownloadButton() {
	g_object_ref(this->buttonDownloadIconActive);
	g_object_ref(this->buttonDownloadIconInactive);
	gtk_button_set_image(GTK_BUTTON(this->buttonDownload), this->buttonDownloadIconActive);
	gtk_widget_set_sensitive(this->buttonDownload, true);
}

void ViewGuiBuilder::deactivateDownloadButton() {
	g_object_ref(this->buttonDownloadIconActive);
	g_object_ref(this->buttonDownloadIconInactive);
	gtk_button_set_image(GTK_BUTTON(this->buttonDownload), this->buttonDownloadIconInactive);
	gtk_widget_set_sensitive(this->buttonDownload, false);
}

void ViewGuiBuilder::activateUploadButton() {
	g_object_ref(this->buttonUploadIconActive);
	g_object_ref(this->buttonUploadIconInactive);
	gtk_button_set_image(GTK_BUTTON(this->buttonUpload), this->buttonUploadIconActive);
	gtk_widget_set_sensitive(this->buttonUpload, true);
}

void ViewGuiBuilder::deactivateUploadButton() {
	g_object_ref(this->buttonUploadIconActive);
	g_object_ref(this->buttonUploadIconInactive);
	gtk_button_set_image(GTK_BUTTON(this->buttonUpload), this->buttonUploadIconInactive);
	gtk_widget_set_sensitive(this->buttonUpload, false);
}

void ViewGuiBuilder::activateDeleteButton() {
	g_object_ref(this->buttonDeleteIconActive);
	g_object_ref(this->buttonDeleteIconInactive);
	gtk_button_set_image(GTK_BUTTON(this->buttonDelete), this->buttonDeleteIconActive);
	gtk_widget_set_sensitive(this->buttonDelete, true);
}

void ViewGuiBuilder::deactivateDeleteButton() {
	g_object_ref(this->buttonDeleteIconActive);
	g_object_ref(this->buttonDeleteIconInactive);
	gtk_button_set_image(GTK_BUTTON(this->buttonDelete), this->buttonDeleteIconInactive);
	gtk_widget_set_sensitive(this->buttonDelete, false);
}

void ViewGuiBuilder::activateNewFolderButton() {
	g_object_ref(this->buttonNewFolderIconActive);
	g_object_ref(this->buttonNewFolderIconInactive);
	gtk_button_set_image(GTK_BUTTON(this->buttonNewFolder), this->buttonNewFolderIconActive);
	gtk_widget_set_sensitive(this->buttonNewFolder, true);
}

void ViewGuiBuilder::deactivateNewFolderButton() {
	g_object_ref(this->buttonNewFolderIconActive);
	g_object_ref(this->buttonNewFolderIconInactive);
	gtk_button_set_image(GTK_BUTTON(this->buttonNewFolder), this->buttonNewFolderIconInactive);
	gtk_widget_set_sensitive(this->buttonNewFolder, false);
}




void ViewGuiBuilder::localTreeRowDoubleClick(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer* data) {
	ViewGuiBuilder* object = (ViewGuiBuilder*)data;
	object->deactivateUploadButton();
	object->deactivateDeleteButton();
	object->doubleClick = true;
	std::string cellName = object->fileListManagerObject->getNameFromClickedCell(treeview, path, true);
	object->controlObject->localTreeCellDoubleClick(cellName);
}

void ViewGuiBuilder::serverTreeRowDoubleClick(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer* data) {
	ViewGuiBuilder* object = (ViewGuiBuilder*)data;
	object->deactivateDownloadButton();
	object->deactivateDeleteButton();
	object->doubleClick = true;
	std::string cellName = object->fileListManagerObject->getNameFromClickedCell(treeview, path, false);
	object->controlObject->serverTreeCellDoubleClick(cellName);
	
}

gboolean ViewGuiBuilder::serverTreeRowSelected (GtkTreeSelection *selection, GtkTreeModel *model, GtkTreePath *path,gboolean path_currently_selected,
								gpointer userdata){
	ViewGuiBuilder* object = (ViewGuiBuilder*)userdata;
	object->serverCurrentFileSelected = object->fileListManagerObject->getFileFromSelectedCell(selection, model, path, false);
	if(object->serverCurrentFileSelected != NULL && object->doubleClick != true) {
		object->activateNewFolderButton();
		object->activateDeleteButton();
		if(object->serverCurrentFileSelected->isDir) {
			object->deactivateDownloadButton();
		} else {
			object->activateDownloadButton();
		}
		object->lastSelectedLocal = false;
	}
	return TRUE;
}

gboolean ViewGuiBuilder::localTreeRowSelected (GtkTreeSelection *selection, GtkTreeModel *model, GtkTreePath *path,gboolean path_currently_selected,
								gpointer userdata) {
	ViewGuiBuilder* object = (ViewGuiBuilder*)userdata;
	object->localCurrentFileSelected = object->fileListManagerObject->getFileFromSelectedCell(selection, model, path, true);
	if(object->localCurrentFileSelected != NULL && object->doubleClick != true) {
		object->activateNewFolderButton();
		object->activateDeleteButton();
		if(object->localCurrentFileSelected->isDir) {
			object->deactivateUploadButton();
		} else {
			object->activateUploadButton();
		}
		object->lastSelectedLocal = true;
	}
	return TRUE;
}

void ViewGuiBuilder::deleteButtonClicked(GtkWidget *widget, gpointer data) {
	ViewGuiBuilder* object = (ViewGuiBuilder*)data;
	if(object->lastSelectedLocal) {
		object->controlObject->localDeleteButton(object->localCurrentFileSelected);
	} else {
		object->controlObject->serverDeleteButton(object->serverCurrentFileSelected);
	}
}

void ViewGuiBuilder::newFolderButtonClicked(GtkWidget *widget, gpointer data) {
	ViewGuiBuilder* object = (ViewGuiBuilder*)data;
	if(object->lastSelectedLocal) {
		object->controlObject->localNewFolderButton();
	} else {
		object->controlObject->serverNewFolderButton();
	}
}


bool ViewGuiBuilder::spawnAreYouSureWindow() {
	GtkWidget *dialog;
	dialog = gtk_dialog_new_with_buttons (this->innerConfigObject->lang_areYouSureWindowTitle.c_str(), GTK_WINDOW(this->mainWindowHandler), GTK_DIALOG_DESTROY_WITH_PARENT, ("OK"), GTK_RESPONSE_ACCEPT,("Cancel"),GTK_RESPONSE_REJECT,NULL);
	gint result = gtk_dialog_run (GTK_DIALOG (dialog));
	if(result == GTK_RESPONSE_ACCEPT) {
		gtk_widget_destroy(dialog);
		return true;
	} else {
		gtk_widget_destroy(dialog);
		return false;
	}
}

std::string ViewGuiBuilder::spawnInsertNameWindow() {
	GtkWidget *dialog;
	dialog = gtk_dialog_new_with_buttons (this->innerConfigObject->lang_insertNameWindowTitle.c_str(), GTK_WINDOW(this->mainWindowHandler), GTK_DIALOG_DESTROY_WITH_PARENT, ("OK"), GTK_RESPONSE_ACCEPT,("Cancel"),GTK_RESPONSE_REJECT,NULL);
	gtk_widget_set_size_request(dialog, this->innerConfigObject->view_insertNameWindowWidth, this->innerConfigObject->view_insertNameWindowHeight);
	GtkWidget* contentArea = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	GtkWidget* layoutManager = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(layoutManager), 20);
	GtkWidget* label = gtk_label_new(this->innerConfigObject->lang_insertNameWindowLabel.c_str());
	GtkWidget* nameEntry = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(layoutManager), label,0,0,1,1);
	gtk_grid_attach(GTK_GRID(layoutManager), nameEntry,1,0,1,1);
	gtk_container_add(GTK_CONTAINER(contentArea), layoutManager);
	gtk_widget_show_all (dialog);
	gint result = gtk_dialog_run (GTK_DIALOG (dialog));
	if(result == GTK_RESPONSE_ACCEPT) {
		std::string toReturn  = std::string(gtk_entry_get_text(GTK_ENTRY(nameEntry)));
		gtk_widget_destroy(dialog);
		return toReturn;
	} else {
		gtk_widget_destroy(dialog);
		return std::string("");
	}
}

ViewGuiBuilder::~ViewGuiBuilder(void){
}


void ViewGuiBuilder::downloadButtonClicked(GtkWidget *widget, gpointer data) {
	ViewGuiBuilder* object = (ViewGuiBuilder*)data;
	object->controlObject->downloadButton(object->serverCurrentFileSelected);
}

void ViewGuiBuilder::uploadButtonClicked(GtkWidget *widget, gpointer data) {
	ViewGuiBuilder* object = (ViewGuiBuilder*)data;
	object->controlObject->downloadButton(object->localCurrentFileSelected);
}

void ViewGuiBuilder::spawnProgressBar() {
	this->deactivateDeleteButton();
	this->deactivateDownloadButton();
	this->deactivateNewFolderButton();
	this->deactivateUploadButton();
	this->progressBarDialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(this->progressBarDialog, 600, 200);
	GtkWidget* layoutManager = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(layoutManager), 20);
	GtkWidget* label = gtk_label_new("Progress");
	this->progressBarHandler = gtk_progress_bar_new();
	gtk_widget_set_hexpand(this->progressBarHandler, TRUE);
	this->progressBarCancelButton = gtk_button_new_with_label("Cancel");
	gtk_grid_attach(GTK_GRID(layoutManager), label,0,0,3,1);
	gtk_grid_attach(GTK_GRID(layoutManager), this->progressBarHandler,0,1,3,1);
	gtk_grid_attach(GTK_GRID(layoutManager), this->progressBarCancelButton,1,2,1,1);
	gtk_container_add(GTK_CONTAINER(this->progressBarDialog), layoutManager);
	gtk_widget_show_all (this->progressBarDialog);
	g_signal_connect(this->progressBarDialog, "delete-event",G_CALLBACK(this->progressBarWindowCloseButtonClicked), this);
	g_signal_connect(this->progressBarCancelButton, "clicked",G_CALLBACK(this->progressBarCancelButtonClicked), this);
}

std::function<void(double)> ViewGuiBuilder::getProgressBarCallback() {
	return std::bind(&ViewGuiBuilder::progressBarSetProgress, this, std::placeholders::_1);
}

void ViewGuiBuilder::progressBarSetProgress(double set) {
	if(this->progressBarDialog != NULL) {
		if(set > 0.99) {
			gtk_widget_destroy(this->progressBarDialog);
			this->progressBarDialog = NULL;
			this->activateDeleteButton();
			this->activateDownloadButton();
			this->activateNewFolderButton();
			this->activateUploadButton();
		} else {
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(this->progressBarHandler), set);
		}
	}
}

void ViewGuiBuilder::refreshProgressBar() {
	if(this->progressBarDialog != NULL) {
		gtk_widget_queue_draw(this->progressBarHandler);
	}
}

void ViewGuiBuilder::progressBarWindowCloseButtonClicked(GtkWidget* widget, GdkEvent* events, gpointer data) {
	ViewGuiBuilder* This = (ViewGuiBuilder*)data;
	This->controlObject->cancelDownload();
	gtk_widget_destroy(This->progressBarDialog);
}

void ViewGuiBuilder::progressBarCancelButtonClicked(GtkWidget *widget, gpointer data) {
	ViewGuiBuilder* This = (ViewGuiBuilder*)data;
	This->controlObject->cancelDownload();
	gtk_widget_destroy(This->progressBarDialog);
}
