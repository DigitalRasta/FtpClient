#pragma once
#include <gtk-3.0\gtk\gtk.h>
#include "InnerConfig.h"
#include "ContainerFileInfo.h"
#include <list>

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
	* Create 4 columns:
	*	*Icon: set to pixbuf or text (if error in open icons), inform user if dir or file
	*	*Name: name of file/dir
	*	*Date: date of creation
	*	*Size: size of file in bytes
	* return: FilesList widget
	*/
	GtkWidget* createFilesListLocal(void);

	/*
	* Show files list in local tree
	*/
	void showListInLocalTree(std::list<ContainerFileInfo> filesList);

private:
	std::string getDateToView(ContainerFileInfo file);
	std::string getSizeToView(ContainerFileInfo file);



	InnerConfig* configObject;

	GdkPixbuf* dirImage;
	GdkPixbuf* fileImage;

	GtkWidget* filesListServer;
	GtkWidget* treeLocal;

	GtkTreeViewColumn* serverColumnName;
	GtkTreeViewColumn* serverColumnDate;
	GtkTreeViewColumn* serverColumnSize;

	GtkTreeViewColumn* localColumnIcon;
	GtkTreeViewColumn* localColumnName;
	GtkTreeViewColumn* localColumnDate;
	GtkTreeViewColumn* localColumnSize;

	GtkCellRenderer* localRenderIcon;
	GtkCellRenderer* localRenderName;
	GtkCellRenderer* localRenderSize;
	GtkCellRenderer* localRenderDate;

	GtkListStore* localStoreList;
	GtkTreeIter localStoreIter;
};

