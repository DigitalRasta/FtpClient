#pragma once
#include <gtk-3.0\gtk\gtk.h>
#include "../../InnerConfig.h"

namespace FtpClient {
    class ViewFileListManager;
}

class FtpClient::ViewFileListManager
{
public:
	ViewFileListManager(InnerConfig* config);
	virtual ~ViewFileListManager(void);

	/*
	* Create FilesList for server
	* return: FilesList widget
	*/
	GtkWidget* createFilesListServer(void);

	/*
	* Create FilesList for local
	* return: FilesList widget
	*/
	GtkWidget* createFilesListLocal(void);
private:
	InnerConfig* configObject;

	GtkWidget* filesListServer;
	GtkWidget* filesListLocal;
};

