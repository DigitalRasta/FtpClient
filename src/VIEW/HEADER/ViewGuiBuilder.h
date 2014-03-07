#pragma once
#include "ViewGuiBuilderInterface.h"
#include "../../InnerConfig.h"
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

	/*
	* Override from interface
	*/
	virtual void initializeMainWindow(void);
private:
	InnerConfig* innerConfigObject;

	GtkWidget* mainWindowHandler;
};

