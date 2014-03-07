#pragma once


namespace FtpClient {
    class InnerConfig;
}
class FtpClient::InnerConfig
{
public:

	int view_mainWindowWidth;
	int view_mainWindowHeight;




	InnerConfig(void) {
		view_mainWindowWidth = 600;
		view_mainWindowHeight = 600;
	};
	virtual ~InnerConfig(void){};
};