#pragma once
#include <gtk-3.0\gtk\gtk.h>
#include "InnerConfig.h"
#include "ContainerFileInfo.h"
#include <list>
#include <string>

namespace FtpClient {
    class ViewFileListManager;
}

class FtpClient::ViewFileListManager
{
public:
	ViewFileListManager(InnerConfig* config);
	virtual ~ViewFileListManager(void);

	/*
	*<summary>Create FilesList for server
	  Create 4 columns:
		*Icon: set to pixbuf or text (if error in open icons), inform user if dir or file
		*Name: name of file/dir
		*Date: date of creation
		*Size: size of file in bytes - empty if dir
	</summary>
	  <returns>FilesList widget</returns>
	*/
	GtkWidget* createFilesListServer(void);

	/*
	*<summary>Create FilesList for local
	  Create 4 columns:
		*Icon: set to pixbuf or text (if error in open icons), inform user if dir or file
		*Name: name of file/dir
		*Date: date of creation
		*Size: size of file in bytes - empty if dir
	</summary>
	  <returns>FilesList widget</returns>
	*/
	GtkWidget* createFilesListLocal(void);

	/*
	* <summary>Show filesList in local tree</summary>
	* <param name="filesList"> Pointer to list with files containers</param>
	*/
	void showListInLocalTree(std::list<ContainerFileInfo>* filesList);

	/*
	* <summary>Show filesList in server tree</summary>
	* <param name="filesList"> Pointer to list with files containers</param>
	*/
	void showListInServerTree(std::list<ContainerFileInfo>* filesList);

	/*
	* <summary>Getter</summary>
	* <returns> handler of local tree</returns>
	*/
	GtkWidget* getLocalTreeHandler();

	/*
	* <summary>Getter</summary>
	* <returns> handler of local tree</returns>
	*/
	GtkWidget* getServerTreeHandler();

	/*
	* <summary>Get path and basing on it return name of clicked cell</summary>
	* <param name="treeview"> Local or server tree</param>
	* <param name="path">Information about cell</param>
	* <param name="local">True: local; False: server</param>
	* <returns> string with name</returns>
	*/
	std::string getNameFromClickedCell(GtkTreeView *treeview, GtkTreePath *path, bool local);

	/*
	* <summary>Similar to getNameFromClickedCell but returns fileContainer connected to clicked cell</summary>
	* <param name="selection">Information about selected cell</param>
	* <param name="path">Information about cell</param>
	* <param name="model">Model of tree</param>
	* <param name="local">True: local; False: server</param>
	* <returns> string with name</returns>
	*/
	ContainerFileInfo* getFileFromSelectedCell(GtkTreeSelection *selection, GtkTreeModel * model, GtkTreePath *path, bool local);

private:
	/*
	* <summary>Get date from file and return it as string </summary>
	* <param name="file">File to get date</param>
	* <returns>date in format dd-mm-yyyy hh:mm</returns>
	*/
	std::string getDateToView(ContainerFileInfo file);

	/*
	* <summary>Get size from file and return it as string </summary>
	* <param name="file">File to get size</param>
	* <returns>size in bytes</returns>
	*/
	std::string getSizeToView(ContainerFileInfo file);
	InnerConfig* configObject;

	GdkPixbuf* dirImage;
	GdkPixbuf* fileImage;

	GtkWidget* treeLocal;
	GtkWidget* treeServer;

	GtkListStore* serverStoreList;
	GtkTreeIter serverStoreIter;

	GtkListStore* localStoreList;
	GtkTreeIter localStoreIter;

	std::list<ContainerFileInfo>* localFilesList;
	std::list<ContainerFileInfo>* serverFilesList;
};

