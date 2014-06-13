#pragma once
#include <string>
#include "ContainerFileInfo.h"

namespace FtpClient {
    class ControlMainEventsInterface;
}
class FtpClient::ControlMainEventsInterface
{
public:
	/*
	* OVERRIDE
	* <summary>Get informations from ConnectWindow</summary>
	* <param name="host">Server host - ip or something like host.com</param>
	* <param name="port">Number of port, standard for FTP is: 21</param>
	* <param name="login">Login for authetication</param>
	* <param name="password">Password for authetication</param>
	*/
	virtual void connectWindowButtonConnectClicked(std::string host, std::string port, std::string login, std::string password) = 0;

	/*
	* OVERRIDE
	* <summary>Clear server list and server list with ContainerFileInfo</summary>
	*/
	virtual void disconnectButtonClicked() = 0;

	/*
	* OVERRIDE
	* <summary>Get name from clicked cell and if it is directory changes current dir</summary>
	* <param name="cellName">Name of clicked cell</param>
	*/
	virtual void localTreeCellDoubleClick(std::string cellName) = 0;

	/*
	* OVERRIDE
	* <summary>Get name from clicked cell and if it is directory changes current dir</summary>
	* <param name="cellName">Name of clicked cell</param>
	*/
	virtual void serverTreeCellDoubleClick(std::string cellName) = 0;

	/*
	* OVERRIDE
	* <summary>Action for deleting on server. Deletes file or directory.</summary>
	* <param name="file">Pointer to file to delete</param>
	*/
	virtual void serverDeleteButton(ContainerFileInfo* file) = 0;

	/*
	* OVERRIDE
	* <summary>Action for local deleting. Deletes file or directory.</summary>
	* <param name="file">Pointer to file to delete</param>
	*/
	virtual void localDeleteButton(ContainerFileInfo* file) = 0;

	/*
	* OVERRIDE
	* <summary>Action for local new folder. Spawn insert-name-window and creates new directory if possible</summary>
	*/
	virtual void localNewFolderButton() = 0;

	/*
	* OVERRIDE
	* <summary>Action for server new folder. Spawn insert-name-window and creates new directory if possible</summary>
	*/
	virtual void serverNewFolderButton() = 0;

	/*
	* OVERRIDE
	* <summary>Action for download file. Download it to current location.</summary>
	* <param name="file">Pointer to file to download</param>
	*/
	virtual void downloadButton(ContainerFileInfo* fileServer) = 0;

	/*
	* OVERRIDE
	* <summary>Action for upload file. Upload it to current location.</summary>
	* <param name="file">Pointer to file to upload</param>
	*/
	virtual void uploadButton(ContainerFileInfo* fileLocal) = 0;

	/*
	* OVERRIDE
	* <summary>Cancel current download. Kill transfer thread and delete already downloaded part.</summary>
	*/
	virtual void cancelDownload() = 0;

	/*
	* OVERRIDE
	* <summary>Cancel current upload. Kill transfer thread.</summary>
	*/
	virtual void cancelUpload() = 0;

	/*
	* OVERRIDE
	* <summary>End program</summary>
	*/
	virtual void endProgram() = 0;
};

