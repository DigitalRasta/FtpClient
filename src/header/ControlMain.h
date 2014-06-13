#pragma once
#include "ControlMainEventsInterface.h"
#include "ModelDAOInterface.h"
#include "ViewGuiBuilderInterface.h"
#include "InnerConfig.h"
#include "ControlExceptionManager.h"
#include <string>
#include <functional>


namespace FtpClient {
    class ControlMain;
}
/*
* <summary> Class which organize actions in program </summary>
*/
class FtpClient::ControlMain :
	public FtpClient::ControlMainEventsInterface
{
public:
	/*
	* <summary>Standard constructor with dependency injection.</summary>
	*/
	ControlMain(ViewGuiBuilderInterface* viewGuiBuilderObject, ModelDAOInterface* modelDAOObject, InnerConfig* innerConfigObject);
	virtual ~ControlMain(void);

	/*
	* <summary>Build interface and init local browser</summary>
	*/
	void startFtpClient(void);

	/*
	* <summary>Init local browser in startPath</summary>
	* <param name="startPath">path to start</param>
	*/
	void initLocalBrowser(std::string startPath);

	/*
	* OVERRIDE
	* <summary>Get informations from ConnectWindow</summary>
	* <param name="host">Server host - ip or something like host.com</param>
	* <param name="port">Number of port, standard for FTP is: 21</param>
	* <param name="login">Login for authetication</param>
	* <param name="password">Password for authetication</param>
	*/
	void connectWindowButtonConnectClicked(std::string host, std::string port, std::string login, std::string password);

	/*
	* OVERRIDE
	* <summary>Clear server list and server list with ContainerFileInfo</summary>
	*/
	void disconnectButtonClicked();

	/*
	* OVERRIDE
	* <summary>Get name from clicked cell and if it is directory changes current dir</summary>
	* <param name="cellName">Name of clicked cell</param>
	*/
	void localTreeCellDoubleClick(std::string cellName);

	/*
	* OVERRIDE
	* <summary>Get name from clicked cell and if it is directory changes current dir</summary>
	* <param name="cellName">Name of clicked cell</param>
	*/
	void serverTreeCellDoubleClick(std::string cellName);

	/*
	* OVERRIDE
	* <summary>Action for deleting on server. Deletes file or directory.</summary>
	* <param name="file">Pointer to file to delete</param>
	*/
	void serverDeleteButton(ContainerFileInfo* file);

	/*
	* OVERRIDE
	* <summary>Action for local deleting. Deletes file or directory.</summary>
	* <param name="file">Pointer to file to delete</param>
	*/
	void localDeleteButton(ContainerFileInfo* file);

	/*
	* OVERRIDE
	* <summary>Action for local new folder. Spawn insert-name-window and creates new directory if possible</summary>
	*/
	void localNewFolderButton();

	/*
	* OVERRIDE
	* <summary>Action for server new folder. Spawn insert-name-window and creates new directory if possible</summary>
	*/
	void serverNewFolderButton();

	/*
	* OVERRIDE
	* <summary>Action for download file. Download it to current location.</summary>
	* <param name="fileServer">Pointer to file to download</param>
	*/
	void downloadButton(ContainerFileInfo* fileServer);

	/*
	* OVERRIDE
	* <summary>Action for upload file. Upload it to current location.</summary>
	* <param name="fileLocal">Pointer to file to upload</param>
	*/
	void uploadButton(ContainerFileInfo* fileLocal);

	/*
	* OVERRIDE
	* <summary>Cancel current download. Kill transfer thread and delete already downloaded part.</summary>
	*/
	void cancelDownload();

	/*
	* OVERRIDE
	* <summary>Cancel current upload. Kill transfer thread.</summary>
	*/
	void cancelUpload();

	/*
	* OVERRIDE
	* <summary>End program</summary>
	*/
	void endProgram();

	/*
	* <summary>Callback for end transfer</summary>
	* <param name="param">transfer code, if 0: ok</param>
	*/
	void endTransferCallback(int param);

	/*
	* <summary>Used in main loop</summary>
	*/
	void checkTransferEnd();

	/*
	* <summary>Used in main loop</summary>
	*/
	bool checkProgramEnd();

	
private:
	/*
	* <summary>Refresh local tree in path</summary>
	*/
	void refreshLocalTree(std::string path);

	/*
	* <summary>Refresh server tree in path</summary>
	*/
	void refreshServerTree(std::string path);

	/*
	* <summary>Refresh progress bar</summary>
	*/
	void refreshProgressBar();

	ViewGuiBuilderInterface* viewGuiBuilderObject;
	ModelDAOInterface* modelDAOObject;
	InnerConfig* innerConfigObject;
	ControlExceptionManager* exceptionManagerObject;

	bool connected;

	std::list<ContainerFileInfo>* localFilesList;
	std::list<ContainerFileInfo>* serverFilesList;

	bool transferEnd;
	bool programEnd;

	bool downloadOrUpload;

	int lastTransferCode;

	ContainerFileInfo* lastFileTransfer;


};

