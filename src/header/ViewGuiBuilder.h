#pragma once
#include "ViewGuiBuilderInterface.h"
#include "InnerConfig.h"
#include "ControlMainEventsInterface.h"
#include "ViewFileListManager.h"
#include "ContainerFileInfo.h"
#include <gtk-3.0/gtk/gtk.h>
#include <functional>
#include <atomic>

namespace FtpClient {
    class ViewGuiBuilder;
}

/*
* <summary>Class used for creating and managing user GUI. Based on GTK+ library.</summary>
*/
class FtpClient::ViewGuiBuilder :
	public FtpClient::ViewGuiBuilderInterface
{
public:
	/*
	* <summary>Standard constructor. Use dependency injection for get data from config. Load buttons images.</summary>
	* <param name="innerConfigObject"> Pointer to config </param>
	*/
	ViewGuiBuilder(InnerConfig* innerConfigObject);

	/*
	* <summary>Nothing special</summary>
	*/
	virtual ~ViewGuiBuilder(void);


	/*
	* OVERRIDE
	* <summary>Creates main window. Sets window size, title, position, background color, layout manager, based on config object.
	           Connect delete and destroy signals.</summary>
	*/
	void initializeMainWindow(void);

	/*
	* OVERRIDE
	* <summary>Create connect dialog with fields: host,port,login,password. Block main window events.</summary>
	*/
	void spawnConnectWindow(void);

	/*
	* OVERRIDE
	* <summary>Destroy connect dialog and set dialog widget field to null</summary>
	*/
	void destroyConnectWindow(void);

	/*
	* OVERRIDE
	* <summary>Spawn exception window for display message to user</summary>
	* <param name="massage"> Message to display </param>
	* <param name="errorLeveL"> Error level - different window desing for different level</param>
	*/
	void spawnExceptionWindow(std::string message, ExceptionLevel errorLevel);

	/*
	* OVERRIDE
	* <summary>Destroy exception window and set window widget field to null</summary>
	*/
	void destroyExceptionWindow(void);

	/*
	* OVERRIDE
	* <summary>Show filesList in local files tree</summary>
	* <param name="filesList"> Pointer to list with files containers</param>
	*/
	void showListInLocalTree(std::list<ContainerFileInfo>* filesList);

	/*
	* OVERRIDE
	* <summary>Show filesList in server files tree</summary>
	* <param name="filesList"> Pointer to list with files containers</param>
	*/
	void showListInServerTree(std::list<ContainerFileInfo>* filesList);

	/*
	* OVERRIDE
	* <summary>Activate button</summary>
	*/
	void activateDownloadButton();

	/*
	* OVERRIDE
	* <summary>Deactivate button</summary>
	*/
	void deactivateDownloadButton();

	/*
	* OVERRIDE
	* <summary>Activate button</summary>
	*/
	void activateUploadButton();

	/*
	* OVERRIDE
	* <summary>Deactivate button</summary>
	*/
	void deactivateUploadButton();

	/*
	* OVERRIDE
	* <summary>Activate button</summary>
	*/
	void activateDeleteButton();

	/*
	* OVERRIDE
	* <summary>Deactivate button</summary>
	*/
	void deactivateDeleteButton();

	/*
	* OVERRIDE
	* <summary>Activate button</summary>
	*/
	void activateNewFolderButton();

	/*
	* OVERRIDE
	* <summary>Deactivate button</summary>
	*/
	void deactivateNewFolderButton();

	/*
	* OVERRIDE
	* <summary>Spawn dialog with 2 buttons: OK and CANCEL. Block main window events.</summary>
	* <returns> True if answer was: OK
	*			False if answer was: CANCEL </returns>
	*/
	bool spawnAreYouSureWindow();

	/*
	* OVERRIDE
	* <summary>Spawn dialog for creating new directory. Text field for insert name of new directory and OK button.</summary>
	* <returns> String inserted in field or empty string if close button was clicked</returns>
	*/
	std::string spawnInsertNameWindow();

	/*
	* OVERRIDE
	* <summary>Spawn window with progress bar and cancel button. Connect cancel button signals</summary>
	* <param name="download"> true - download; false - upload</param>
	*/
	void spawnProgressBar(bool download);

	/*
	* OVERRIDE
	* <summary>Get progress callback for update progress in progress bar</summary>
	* <returns> Function callback: progressBarSetProgress, double param should be [0;1.0]</returns>
	*/
	std::function<void(double)> getProgressBarCallback();
	
	/*
	* OVERRIDE
	* <summary>Refresh progress bar and progress precent label based on progress field.</summary>
	*/
	void refreshProgressBar();

	/*
	* OVERRIDE
	* <summary>Destroy progress window </summary>
	*/
	void endTransfer();

	/*
	* <summary>Callback for set progress</summary>
	* <param name="set">set should be [0;1.0]</param>
	*/
	void progressBarSetProgress(double set);
private:
	GtkWidget* progressBarHandler;
	GtkWidget* progressBarDialog;
	GtkWidget* progressBarCancelButton;
	GtkWidget* progressBarLabel;
	std::atomic<double> progress;

	GtkWidget* connectButton;
	GtkWidget* disconnectButton;
	
	bool downloadOrUpload;

	InnerConfig* innerConfigObject;
	ControlMainEventsInterface* controlObject;
	ViewFileListManager* fileListManagerObject;

	ContainerFileInfo* serverCurrentFileSelected;
	ContainerFileInfo* localCurrentFileSelected;
	bool lastSelectedLocal;

	bool doubleClick; //identificaction for last event on lists

	GtkWidget* mainWindowHandler;
	GtkWidget* layoutManager;

	GtkWidget* menuBar;

	GtkWidget* connectWindow;
	GtkWidget* connectWindow_inputHost;
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
	*<summary>Build interface for main window. Create menu bar, create layout manager, spawn connect window on start, create files lists</summary>
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
	*EVENTCALLBACK
	*<summary>Callback for connect button in connectWindow. Send to control object data received from connectWindow form.</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void connectWindowButtonConnectClicked(GtkWidget* button, gpointer* data);

	/*
	*EVENTCALLBACK
	*<summary>Callback for connect button in menu bar in mainWinow. Spawn connectWindow if not spawned yet.</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void mainWindowMenuBarButtonConnectClicked(GtkWidget* object, gpointer* data);

	/*
	*EVENTCALLBACK
	*<summary>Callback for OK button in exceptionWindow. Destroys window.</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void exceptionWindowOkButton(GtkDialog* dialog, gint id, gpointer* data);

	/*
	*EVENTCALLBACK
	*<summary>Callback local list double click on row. Send name of clicked row to control object.</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void localTreeRowDoubleClick(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer* data);
	
	/*
	*EVENTCALLBACK
	*<summary>Callback server list double click on row. Send name of clicked row to control object.</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void serverTreeRowDoubleClick(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer* data);

	/*
	*EVENTCALLBACK
	*<summary>Callback local list row select. Sets localCurrentFileSelected field and activate proper buttons</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static gboolean localTreeRowSelected (GtkTreeSelection *selection,GtkTreeModel *model,GtkTreePath *path,gboolean path_currently_selected,
											gpointer data);
	/*
	*EVENTCALLBACK
	*<summary>Callback server list row select. Sets serverCurrentFileSelected field and activate proper buttons</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static gboolean serverTreeRowSelected (GtkTreeSelection *selection,GtkTreeModel *model,GtkTreePath *path,gboolean path_currently_selected,
											gpointer data);

	/*
	*EVENTCALLBACK
	*<summary>Callback delete button clicked. Check last selected tree and send last selected file to control object</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void deleteButtonClicked(GtkWidget *widget, gpointer data);

	/*
	*EVENTCALLBACK
	*<summary>Callback new folder button clicked. Check last selected tree and call proper function from control object.</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void newFolderButtonClicked(GtkWidget *widget, gpointer data);

	/*
	*EVENTCALLBACK
	*<summary>Callback download button clicked. Send last server selected file to control object.</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void downloadButtonClicked(GtkWidget *widget, gpointer data);

	/*
	*EVENTCALLBACK
	*<summary>Callback upload button clicked. Send last local selected file to control object.</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void uploadButtonClicked(GtkWidget *widget, gpointer data);

	/*
	*EVENTCALLBACK
	*<summary>Callback close button in progress window. Call cancel download/upload from control object</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void progressBarWindowCloseButtonClicked(GtkWidget* widget, GdkEvent* events, gpointer data);

	/*
	*EVENTCALLBACK
	*<summary>Callback close button in progress window. Call cancel download/upload from control object</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void progressBarCancelButtonClicked(GtkWidget *widget, gpointer data);

	/*
	*EVENTCALLBACK
	*<summary>Callback close button in main window. Call end program from control object and destroy main window widget</summary>
	* Params: required by lib
	* <param name="data">ViewGuiBuilder object - this</param>
	*/
	static void mainWindowCloseButtonClicked(GtkWidget* widget, GdkEvent* events, gpointer data);
};

