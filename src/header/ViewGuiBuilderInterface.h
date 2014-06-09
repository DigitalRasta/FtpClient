#pragma once
#include "ControlMainEventsInterface.h"
#include <string>
#include "ContainerException.h"
#include "ContainerFileInfo.h"
#include <list>
#include <functional>



namespace FtpClient {
    class ViewGuiBuilderInterface;
}

/*
* <summary>Public interface for ViewGuiBuilder</summary>
*/
class FtpClient::ViewGuiBuilderInterface
{
public:
	/*
	* <summary>Creates main window. Sets window size, title, position, background color, layout manager, based on config object.
	           Connect delete and destroy signals.</summary>
	*/
	virtual void initializeMainWindow(void) = 0;

	/*
	* <summary>Create connect dialog with fields: host,port,login,password. Block main window events.</summary>
	*/
	virtual void spawnConnectWindow(void) = 0;

	/*
	* <summary>Destroy connect dialog and set dialog widget field to null</summary>
	*/
	virtual void destroyConnectWindow(void) = 0;

	/*
	* <summary>Spawn exception window for display message to user</summary>
	* <param name="massage"> Message to display </param>
	* <param name="errorLeveL"> Error level - different window desing for different level</param>
	*/
	virtual void spawnExceptionWindow(std::string message, ExceptionLevel errorLevel) = 0;

	/*
	* <summary>Destroy exception window and set window widget field to null</summary>
	*/
	virtual void destroyExceptionWindow(void) = 0;

	/*
	* <summary>Show filesList in local files tree</summary>
	* <param name="filesList"> Pointer to list with files containers</param>
	*/
	virtual void showListInLocalTree(std::list<ContainerFileInfo>* filesList) = 0;

	/*
	* <summary>Show filesList in server files tree</summary>
	* <param name="filesList"> Pointer to list with files containers</param>
	*/
	virtual void showListInServerTree(std::list<ContainerFileInfo>* filesList) = 0;

	/*
	* <summary>Activate button</summary>
	*/
	virtual void activateDownloadButton() = 0;

	/*
	* <summary>Deactivate button</summary>
	*/
	virtual void deactivateDownloadButton() = 0;

	/*
	* <summary>Activate button</summary>
	*/
	virtual void activateUploadButton() = 0;

	/*
	* <summary>Deactivate button</summary>
	*/
	virtual void deactivateUploadButton() = 0;

	/*
	* <summary>Activate button</summary>
	*/
	virtual void activateDeleteButton() = 0;

	/*
	* <summary>Deactivate button</summary>
	*/
	virtual void deactivateDeleteButton() = 0;

	/*
	* <summary>Activate button</summary>
	*/
	virtual void activateNewFolderButton() = 0;

	/*
	* <summary>Deactivate button</summary>
	*/
	virtual void deactivateNewFolderButton() = 0;

	/*
	* <summary>Activate button</summary>
	*/
	virtual void activateConnectButton() = 0;

	/*
	* <summary>Deactivate button</summary>
	*/
	virtual void deactivateConnectButton() = 0;

	/*
	* <summary>Activate button</summary>
	*/
	virtual void activateDisconnectButton() = 0;

	/*
	* <summary>Deactivate button</summary>
	*/
	virtual void deactivateDisconnectButton() = 0;

	/*
	* <summary>Spawn dialog with 2 buttons: OK and CANCEL. Block main window events.</summary>
	* <returns> True if answer was: OK
	*			False if answer was: CANCEL </returns>
	*/
	virtual bool spawnAreYouSureWindow() = 0;

	/*
	* <summary>Spawn dialog for creating new directory. Text field for insert name of new directory and OK button.</summary>
	* <returns> String inserted in field or empty string if close button was clicked</returns>
	*/
	virtual std::string spawnInsertNameWindow() = 0;

	/*
	* <summary>Spawn window with progress bar and cancel button. Connect cancel button signals</summary>
	* <param name="download"> true - download; false - upload</param>
	*/
	virtual void spawnProgressBar(bool download) = 0;

	/*
	* <summary>Get progress callback for update progress in progress bar</summary>
	* <returns> Function callback: progressBarSetProgress, double param should be [0;1.0]</returns>
	*/
	virtual std::function<void(double)> getProgressBarCallback() = 0;
	
	/*
	* <summary>Refresh progress bar and progress precent label based on progress field.</summary>
	*/
	virtual void refreshProgressBar() = 0;

	/*
	* <summary>Destroy progress window </summary>
	*/
	virtual void endTransfer() = 0;

	/*
	* <summary>Dependency injection</summary>
	* <param name="controlObject">controlObject for events functions</param>
	*/
	virtual void bindMainWindowEvents(ControlMainEventsInterface* controlObject) = 0;

};

