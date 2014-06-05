#pragma once
#include <string>


namespace FtpClient {
    class InnerConfig;
}
class FtpClient::InnerConfig
{
public:

	int view_mainWindowWidth;
	int view_mainWindowHeight;
	
	std::string view_mainWindowBackground;

	std::string view_dirIconSrc;
	std::string view_fileIconSrc;
	std::string view_mainIconPath;

	std::string view_buttonDownloadActiveIconSrc;
	std::string view_buttonDownloadInactiveIconSrc;
	std::string view_buttonUploadActiveIconSrc;
	std::string view_buttonUploadInactiveIconSrc;
	std::string view_buttonDeleteActiveIconSrc;
	std::string view_buttonDeleteInactiveIconSrc;
	std::string view_buttonNewFolderActiveIconSrc;
	std::string view_buttonNewFolderInactiveIconSrc;
	

	int view_connectWindowWidth;
	int view_connectWindowHeight;

	int view_exceptionWindowWidth;
	int view_exceptionWindowHeight;

	int view_insertNameWindowWidth;
	int view_insertNameWindowHeight;

	int view_progressWindowWidth;
	int view_progressWindowHeight;

	std::string view_exceptionWindowIconSrcStandard;
	std::string view_exceptionWindowIconSrcHigh;
	std::string view_exceptionWindowIconSrcCritical;

	int model_maxNumberOfConnections;

	std::string lang_mainWindowTitle;
	std::string lang_mainWindowMenuConnectButtonText;
	std::string lang_mainWindowMenuDisconnectButtonText;
	std::string lang_connectWindowTitle;
	std::string lang_connectWindowLabelHost;
	std::string lang_connectWindowLabelPort;
	std::string lang_connectWindowLabelLogin;
	std::string lang_connectWindowLabelPassword;
	std::string lang_connectWindowButtonConnect;

	std::string lang_exceptionWindowTitle;


	std::string lang_filesListLocalColumnType;
	std::string lang_filesListLocalColumnName;
	std::string lang_filesListLocalColumnSize;
	std::string lang_filesListLocalColumnDate;
	std::string lang_filesListServerColumnType;
	std::string lang_filesListServerColumnName;
	std::string lang_filesListServerColumnSize;
	std::string lang_filesListServerColumnDate;
	std::string lang_filesListDirectory;
	std::string lang_filesListFile;

	std::string lang_areYouSureWindowTitle;

	std::string lang_progressBarCancelButton;

	std::string lang_insertNameWindowTitle;
	std::string lang_insertNameWindowLabel;

	std::string error_directoryListing;
	std::string error_connection_unknownId;

	std::string exception_directoryListing_inaccessible;
	std::string exception_connection_tooManyConnections;
	std::string exception_connection_badHostName;
	std::string exception_connection_connectFailed;
	std::string exception_connection_noResponse;
	std::string exception_connection_invalidResponse;
	std::string exception_connection_userNa;
	std::string exception_connection_passNa;
	std::string exception_connection_unknown;

	std::string exception_cannotDeleteDirectory;
	std::string exception_cannotDeleteFile;

	std::string exception_specialCharsNotSupported;
	std::string exception_cannotCreateDirectory;

	std::string exception_cannotDownloadFile;
	InnerConfig(void) {
		view_mainWindowWidth = 800;
		view_mainWindowHeight = 500;
		view_mainWindowBackground = "#FF0000";

		view_dirIconSrc = std::string("img/dirIcon.png");
		view_fileIconSrc = std::string("img/fileIcon.png");
		view_mainIconPath = std::string("img/icon.png");

		view_buttonDownloadActiveIconSrc = std::string("img/arrowright_active.png");
		view_buttonDownloadInactiveIconSrc = std::string("img/arrowright_inactive.png");
		view_buttonUploadActiveIconSrc = std::string("img/arrowleft_active.png");
		view_buttonUploadInactiveIconSrc = std::string("img/arrowleft_inactive.png");
		view_buttonDeleteActiveIconSrc = std::string("img/delete_active.png");
		view_buttonDeleteInactiveIconSrc = std::string("img/delete_inactive.png");
		view_buttonNewFolderActiveIconSrc = std::string("img/newfolder_active.png");
		view_buttonNewFolderInactiveIconSrc = std::string("img/newfolder_inactive.png");

		view_connectWindowWidth = 200;
		view_connectWindowHeight = 200;

		view_exceptionWindowWidth = 400;
		view_exceptionWindowHeight = 200;

		view_insertNameWindowWidth = 220;
		view_insertNameWindowHeight = 60;

		view_progressWindowWidth = 600;
		view_progressWindowHeight = 200;

		view_exceptionWindowIconSrcStandard = std::string("src");
		view_exceptionWindowIconSrcHigh = std::string("src");
		view_exceptionWindowIconSrcCritical = std::string("src");

		model_maxNumberOfConnections = 8;

		lang_mainWindowTitle = std::string("FtpClient - connect to your server.");
		lang_mainWindowMenuConnectButtonText = std::string("Connect");
		lang_mainWindowMenuDisconnectButtonText = std::string("Disconnect");
		lang_connectWindowTitle = std::string("Connect");
		lang_connectWindowLabelHost = std::string("Host:");
		lang_connectWindowLabelPort = std::string("Port:");
		lang_connectWindowLabelLogin = std::string("Login:");
		lang_connectWindowLabelPassword = std::string("Password:");
		lang_connectWindowButtonConnect = std::string("Connect");

		lang_exceptionWindowTitle = std::string("Error!");

		lang_filesListLocalColumnType = std::string("Type");
		lang_filesListLocalColumnName = std::string("Name");
		lang_filesListLocalColumnSize = std::string("Size");
		lang_filesListLocalColumnDate = std::string("Date");

		lang_filesListServerColumnType = std::string("Type");
		lang_filesListServerColumnName = std::string("Name");
		lang_filesListServerColumnSize = std::string("Size");
		lang_filesListServerColumnDate = std::string("Date");

		lang_filesListDirectory = std::string("Directory");
		lang_filesListFile = std::string("File");

		lang_areYouSureWindowTitle = std::string("Are you sure?");

		lang_progressBarCancelButton = std::string("Cancel");

		lang_insertNameWindowTitle = std::string("Insert name of directory");
		lang_insertNameWindowLabel = std::string("Name: ");

		error_connection_unknownId = std::string("Unknown connection ID");

		exception_directoryListing_inaccessible = std::string("Directory is inaccessible");
		exception_connection_tooManyConnections = std::string("Too many connections");
		exception_connection_badHostName = std::string("Wrong host name format");
		exception_connection_connectFailed = std::string("Something went wrong. Check your firewall");
		exception_connection_noResponse = std::string("Host not responding");
		exception_connection_invalidResponse = std::string("Host responding but wrong");
		exception_connection_userNa = std::string("User command not accepted");
		exception_connection_passNa = std::string("Pass command not accepted");
		exception_connection_unknown = std::string("Unknown connection error");

		exception_cannotDeleteDirectory = std::string("Directory inaccessible or not empty!");
		exception_cannotDeleteFile = std::string("You cannot delete this file!");

		exception_specialCharsNotSupported = std::string("Sorry! Special characters not supported!");
		exception_cannotCreateDirectory = std::string("Cannot create directory");

		exception_cannotDownloadFile = std::string("Sorry! Cannot download file.");
	};
	virtual ~InnerConfig(void){};
};