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
	

	int view_connectWindowWidth;
	int view_connectWindowHeight;

	int view_exceptionWindowWidth;
	int view_exceptionWindowHeight;
	std::string view_exceptionWindowIconSrcStandard;
	std::string view_exceptionWindowIconSrcHigh;
	std::string view_exceptionWindowIconSrcCritical;

	std::string lang_mainWindowTitle;
	std::string lang_mainWindowMenuConnectButtonText;
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
	std::string lang_filesListServerColumnName;
	std::string lang_filesListServerColumnSize;
	std::string lang_filesListServerColumnDate;


	std::string error_directoryListing;

	InnerConfig(void) {
		view_mainWindowWidth = 800;
		view_mainWindowHeight = 500;
		view_mainWindowBackground = "#FF0000";

		view_connectWindowWidth = 200;
		view_connectWindowHeight = 200;

		view_exceptionWindowWidth = 400;
		view_exceptionWindowHeight = 200;
		view_exceptionWindowIconSrcStandard = std::string("src");
		view_exceptionWindowIconSrcHigh = std::string("src");
		view_exceptionWindowIconSrcCritical = std::string("src");

		lang_mainWindowTitle = std::string("FtpClient - connect to your server.");
		lang_mainWindowMenuConnectButtonText = std::string("Connect...");
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

		lang_filesListServerColumnName = std::string("Name");
		lang_filesListServerColumnSize = std::string("Size");
		lang_filesListServerColumnDate = std::string("Date");


		error_directoryListing = std::string("Problem with directory listing");
	};
	virtual ~InnerConfig(void){};
};