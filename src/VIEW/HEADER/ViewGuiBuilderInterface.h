#pragma once

namespace FtpClient {
    class ViewGuiBuilderInterface;
}
class FtpClient::ViewGuiBuilderInterface
{
public:
	virtual void initializeMainWindow(void) = 0;
};

