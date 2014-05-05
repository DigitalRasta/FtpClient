#pragma once
#include "ViewGuiBuilderInterface.h"
#include "InnerConfig.h"
#include "ControlMainEventsInterface.h"
#include "ViewFileListManager.h"
#include "ContainerFileInfo.h"
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

	/*
	* INTERFACE
	* Destroy exceptionWindow and sets all linked variables to null
	*/
	virtual void destroyExceptionWindow(void);

	/*
	* INTERFACE
	* Show files list in local tree
	*/
	virtual void showListInLocalTree(std::list<ContainerFileInfo>* filesList);


	virtual void showListInServerTree(std::list<ContainerFileInfo>* filesList);


	virtual void activateDownloadButton();
	virtual void deactivateDownloadButton();
	virtual void activateUploadButton();
	virtual void deactivateUploadButton();
	virtual void activateDeleteButton();
	virtual void deactivateDeleteButton();
	virtual void activateNewFolderButton();
	virtual void deactivateNewFolderButton();

	bool spawnAreYouSureWindow();
	

private:
	InnerConfig* innerConfigObject;
	ControlMainEventsInterface* controlObject;
	ViewFileListManager* fileListManagerObject;

	ContainerFileInfo* serverCurrentFileSelected;
	ContainerFileInfo* localCurrentFileSelected;
	bool lastSelectedLocal;

	bool doubleClick;

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

	GtkWidget* buttonDownload;
	GtkWidget* buttonUpload;
	GtkWidget* buttonDelete;
	GtkWidget* buttonNewFolder;

	GtkWidget* buttonDownloadIconActive;
	GtkWidget* buttonUploadIconActive;
	GtkWidget* buttonDeleteIconActive;
	GtkWidget* buttonNewFolderIconActive;

	GtkWidget* buttonDownloadIconInactive;
	GtkWidget* buttonUploadIconInactive;
	GtkWidget* buttonDeleteIconInactive;
	GtkWidget* buttonNewFolderIconInactive;

	/*
	* Build interface for main window. Create menu bar, create layout manager, spawn connect window on start, create files lists
	*/
	virtual void buildInterface(void);

	virtual GtkWidget* createStandardButtons(void);



	virtual void bindMainWindowEvents(ControlMainEventsInterface* controlObject);


	/*
	* Build interface (labels, inputs, buttons) for connectWindow.
	* Return: Container containing interfaces elements.
	*/
	virtual GtkWidget* buildConnectWindowInterface(void);


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

	/*
	*Events
	* Callback for OK button in exceptionWindow. Destroys it.
	* Params:
	*	object - do nothing, lib require
	*	data - pointer casting to ViewGuiBuilder object
	*/
	static void exceptionWindowOkButton(GtkDialog* dialog, gint id, gpointer* data);

	/*
	*Events
	* Callback local list double click on row
	* Params:
	*	object - do nothing, lib require
	*	data - pointer casting to ViewGuiBuilder object
	*/
	static void localTreeRowDoubleClick(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer* data);
	
	/*
	*Events
	* Callback server list double click on row
	* Params:
	*	object - do nothing, lib require
	*	data - pointer casting to ViewGuiBuilder object
	*/
	static void serverTreeRowDoubleClick(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer* data);


	static gboolean localTreeRowSelected (GtkTreeSelection *selection,GtkTreeModel *model,GtkTreePath *path,gboolean path_currently_selected,
											gpointer userdata);

	static gboolean serverTreeRowSelected (GtkTreeSelection *selection,GtkTreeModel *model,GtkTreePath *path,gboolean path_currently_selected,
											gpointer userdata);


	static void deleteButtonClicked(GtkWidget *widget, gpointer data);

};

