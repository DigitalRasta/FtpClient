#include "../header/ViewFileListManager.h"
#include <gtk-3.0\gtk\gtk.h>
#include "../header/InnerConfig.h"
#include "../header/ContainerFileInfo.h"
#include "../header/ViewGuiBuilder.h"
#include <list>
#include <string>
#include <sstream>
#include <typeinfo>


using namespace FtpClient;

ViewFileListManager::ViewFileListManager(InnerConfig* config){
	this->configObject = config;
	this->dirImage = gdk_pixbuf_new_from_file(this->configObject->view_dirIconSrc.c_str(),NULL);
	this->fileImage = gdk_pixbuf_new_from_file(this->configObject->view_fileIconSrc.c_str(),NULL);
}


ViewFileListManager::~ViewFileListManager(void)
{
}

GtkWidget* ViewFileListManager::createFilesListServer(void) {
	this->treeServer = gtk_tree_view_new();
	GtkTreeViewColumn* serverColumnIcon = gtk_tree_view_column_new();
	GtkTreeViewColumn* serverColumnName = gtk_tree_view_column_new();
	GtkTreeViewColumn* serverColumnDate = gtk_tree_view_column_new();
	GtkTreeViewColumn* serverColumnSize = gtk_tree_view_column_new();
	GtkCellRenderer* serverRenderIcon;
	GtkCellRenderer* serverRenderName;
	GtkCellRenderer* serverRenderSize;
	GtkCellRenderer* serverRenderDate;
	gtk_tree_view_column_set_title(serverColumnName, this->configObject->lang_filesListServerColumnName.c_str());
	gtk_tree_view_column_set_title(serverColumnDate, this->configObject->lang_filesListServerColumnDate.c_str());
	gtk_tree_view_column_set_title(serverColumnSize, this->configObject->lang_filesListServerColumnSize.c_str());
	gtk_tree_view_column_set_sizing (serverColumnIcon, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (serverColumnName, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (serverColumnDate, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (serverColumnSize, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_resizable(serverColumnName, TRUE);
	gtk_tree_view_column_set_resizable(serverColumnDate, TRUE);
	gtk_tree_view_column_set_resizable(serverColumnSize, TRUE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeServer), serverColumnIcon);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeServer), serverColumnName);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeServer), serverColumnSize);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeServer), serverColumnDate);
	int serverColumnIconNumber = 0;
	int serverColumnNameNumber = 1;
	int serverColumnDateNumber = 2;
	int serverColumnSizeNumber = 3;
	gtk_widget_set_hexpand(this->treeServer, TRUE);
	gtk_widget_set_vexpand(this->treeServer, TRUE);
	if(this->dirImage == NULL || this->fileImage == NULL) {
		serverRenderIcon = gtk_cell_renderer_text_new();
		gtk_tree_view_column_pack_start(serverColumnIcon, serverRenderIcon, true);
		gtk_tree_view_column_add_attribute(serverColumnIcon, serverRenderIcon, "text",serverColumnIconNumber);
		gtk_tree_view_column_set_title(serverColumnIcon, this->configObject->lang_filesListServerColumnType.c_str());
	} else {
		serverRenderIcon = gtk_cell_renderer_pixbuf_new();
		gtk_tree_view_column_pack_start(serverColumnIcon, serverRenderIcon, true);
		gtk_tree_view_column_add_attribute(serverColumnIcon, serverRenderIcon, "pixbuf",serverColumnIconNumber);
	}
	serverRenderName = gtk_cell_renderer_text_new();
	serverRenderSize = gtk_cell_renderer_text_new();
	serverRenderDate = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(serverColumnName, serverRenderName, true);
	gtk_tree_view_column_add_attribute(serverColumnName, serverRenderName, "text",serverColumnNameNumber);
	gtk_tree_view_column_pack_start(serverColumnDate, serverRenderDate, true);
	gtk_tree_view_column_add_attribute(serverColumnDate, serverRenderDate, "text",serverColumnDateNumber);
	gtk_tree_view_column_pack_start(serverColumnSize, serverRenderSize, true);
	gtk_tree_view_column_add_attribute(serverColumnSize, serverRenderSize, "text",serverColumnSizeNumber);
	if(this->dirImage == NULL || this->fileImage == NULL) {
		this->serverStoreList = gtk_list_store_new(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
	} else {
		this->serverStoreList = gtk_list_store_new(5, GDK_TYPE_PIXBUF, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
	}
	gtk_tree_view_set_model(GTK_TREE_VIEW(this->treeServer),GTK_TREE_MODEL(this->serverStoreList));

	GtkWidget* scroll = gtk_scrolled_window_new( NULL,NULL );
    gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( scroll ),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC );
	gtk_container_add( GTK_CONTAINER( scroll ),this->treeServer );

	return scroll;
}

GtkWidget* ViewFileListManager::createFilesListLocal(void) {
	this->treeLocal = gtk_tree_view_new();
	GtkTreeViewColumn* localColumnIcon = gtk_tree_view_column_new();
	GtkTreeViewColumn* localColumnName = gtk_tree_view_column_new();
	GtkTreeViewColumn* localColumnDate = gtk_tree_view_column_new();
	GtkTreeViewColumn* localColumnSize = gtk_tree_view_column_new();
	GtkCellRenderer* localRenderIcon;
	GtkCellRenderer* localRenderName;
	GtkCellRenderer* localRenderSize;
	GtkCellRenderer* localRenderDate;
	gtk_tree_view_column_set_title(localColumnName, this->configObject->lang_filesListLocalColumnName.c_str());
	gtk_tree_view_column_set_title(localColumnDate, this->configObject->lang_filesListLocalColumnDate.c_str());
	gtk_tree_view_column_set_title(localColumnSize, this->configObject->lang_filesListLocalColumnSize.c_str());
	gtk_tree_view_column_set_sizing (localColumnIcon, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (localColumnName, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (localColumnDate, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (localColumnSize, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_resizable(localColumnName, TRUE);
	gtk_tree_view_column_set_resizable(localColumnDate, TRUE);
	gtk_tree_view_column_set_resizable(localColumnSize, TRUE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), localColumnIcon);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), localColumnName);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), localColumnSize);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), localColumnDate);
	int localColumnIconNumber = 0;
	int localColumnNameNumber = 1;
	int localColumnDateNumber = 2;
	int localColumnSizeNumber = 3;
	gtk_widget_set_hexpand(this->treeLocal, TRUE);
	gtk_widget_set_vexpand(this->treeLocal, TRUE);
	//Show text if icons not found
	if(this->dirImage == NULL || this->fileImage == NULL) {
		localRenderIcon = gtk_cell_renderer_text_new();
		gtk_tree_view_column_pack_start(localColumnIcon, localRenderIcon, true);
		gtk_tree_view_column_add_attribute(localColumnIcon, localRenderIcon, "text",localColumnIconNumber);
		gtk_tree_view_column_set_title(localColumnIcon, this->configObject->lang_filesListLocalColumnType.c_str());
	} else {
		localRenderIcon = gtk_cell_renderer_pixbuf_new();
		gtk_tree_view_column_pack_start(localColumnIcon, localRenderIcon, true);
		gtk_tree_view_column_add_attribute(localColumnIcon, localRenderIcon, "pixbuf",localColumnIconNumber);
	}
	localRenderName = gtk_cell_renderer_text_new();
	localRenderSize = gtk_cell_renderer_text_new();
	localRenderDate = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(localColumnName, localRenderName, true);
	gtk_tree_view_column_add_attribute(localColumnName, localRenderName, "text",localColumnNameNumber);
	gtk_tree_view_column_pack_start(localColumnDate, localRenderDate, true);
	gtk_tree_view_column_add_attribute(localColumnDate, localRenderDate, "text",localColumnDateNumber);
	gtk_tree_view_column_pack_start(localColumnSize, localRenderSize, true);
	gtk_tree_view_column_add_attribute(localColumnSize, localRenderSize, "text",localColumnSizeNumber);
	if(this->dirImage == NULL || this->fileImage == NULL) {
		this->localStoreList = gtk_list_store_new(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
	} else {
		this->localStoreList = gtk_list_store_new(5, GDK_TYPE_PIXBUF, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
	}
	gtk_tree_view_set_model(GTK_TREE_VIEW(this->treeLocal),GTK_TREE_MODEL(this->localStoreList));
	GtkWidget* scroll = gtk_scrolled_window_new( NULL,NULL );
    gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( scroll ),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC );
	gtk_container_add( GTK_CONTAINER( scroll ),this->treeLocal );

	return scroll;
}

void ViewFileListManager::showListInLocalTree(std::list<ContainerFileInfo>* filesList) {
	this->localFilesList = filesList;
	gtk_list_store_clear(this->localStoreList);
	//For each file in filesList add cell in stroeList for local Tree
	for(std::list<ContainerFileInfo>::const_iterator i = (*filesList).begin(); i != (*filesList).end(); i++) {
			gtk_list_store_append(this->localStoreList, &this->localStoreIter);
			std::string fileDate = this->getDateToView((*i));
			std::string fileSize = this->getSizeToView((*i));
			gchar* fileName = g_locale_to_utf8((*i).fileName.c_str(), (*i).fileName.size(), NULL, NULL, NULL);
			if(this->fileImage != NULL && this->dirImage != NULL) {
				if((*i).isDir) {
					gtk_list_store_set(this->localStoreList, &this->localStoreIter,0, this->dirImage,  1, fileName, 2, fileDate.c_str(), 3, fileSize.c_str(), 4, (*i).ID);
				} else {
					gtk_list_store_set(this->localStoreList, &this->localStoreIter,0, this->fileImage,  1, fileName, 2, fileDate.c_str(), 3, fileSize.c_str(), 4, (*i).ID);
				}
			} else {
				if((*i).isDir) {
					gtk_list_store_set(this->localStoreList, &this->localStoreIter,0, this->configObject->lang_filesListDirectory.c_str(),  1, fileName, 2, fileDate.c_str(), 3, fileSize.c_str(), 4, (*i).ID);
				} else {
					gtk_list_store_set(this->localStoreList, &this->localStoreIter,0, this->configObject->lang_filesListFile.c_str(),  1, fileName, 2, fileDate.c_str(), 3, fileSize.c_str(), 4, (*i).ID);
				}
			}
	}
}

void ViewFileListManager::showListInServerTree(std::list<ContainerFileInfo>* filesList) {
	this->serverFilesList = filesList;
	gtk_list_store_clear(this->serverStoreList);
	if(filesList == NULL) {
		return;
	}
	//For each file in filesList add cell in stroeList for server Tree
	for(std::list<ContainerFileInfo>::const_iterator i = (*filesList).begin(); i != (*filesList).end(); i++) {
			gtk_list_store_append(this->serverStoreList, &this->serverStoreIter);
			std::string fileDate = this->getDateToView((*i));
			std::string fileSize = this->getSizeToView((*i));
			gchar* fileName = g_locale_to_utf8((*i).fileName.c_str(), (*i).fileName.size(), NULL, NULL, NULL);
			if(this->fileImage != NULL && this->dirImage != NULL) {
				if((*i).isDir) {
					gtk_list_store_set(this->serverStoreList, &this->serverStoreIter,0, this->dirImage,  1, fileName, 2, fileDate.c_str(), 3, fileSize.c_str(), 4, (*i).ID);
				} else {
					gtk_list_store_set(this->serverStoreList, &this->serverStoreIter,0, this->fileImage,  1, fileName, 2, fileDate.c_str(), 3, fileSize.c_str(), 4, (*i).ID);
				}
			} else {
				if((*i).isDir) {
					gtk_list_store_set(this->serverStoreList, &this->serverStoreIter,0, this->configObject->lang_filesListDirectory.c_str(),  1, fileName, 2, fileDate.c_str(), 3, fileSize.c_str(), 4, (*i).ID);
				} else {
					gtk_list_store_set(this->serverStoreList, &this->serverStoreIter,0, this->configObject->lang_filesListFile.c_str(),  1, fileName, 2, fileDate.c_str(), 3, fileSize.c_str(), 4, (*i).ID);
				}
			}
	}
}

std::string ViewFileListManager::getDateToView(ContainerFileInfo file) {
	std::stringstream convert;
	std::string toReturn;
	if(file.day == -1 || file.fileName.compare("..") == 0) {
		convert << "-";
		convert >> toReturn;
		return toReturn;
	}
	convert << file.year << "-";
	if(file.month < 10) {
		convert << "0" << file.month;
	} else {
		convert << file.month;
	}
	convert << "-";
	if(file.day < 10) {
		convert << "0" << file.day;
	} else {
		convert << file.day;
	}
	convert << " ";
	if(file.hour < 10) {
		convert << "0" << file.hour;
	} else {
		convert << file.hour;
	}
	convert << ":";
	if(file.minute < 10) {
		convert << "0" << file.minute;
	} else {
		convert << file.minute;
	}
	return convert.str();
}

std::string ViewFileListManager::getSizeToView(ContainerFileInfo file) {
	std::stringstream convert;
	std::string toReturn;
	if(file.fileSize <= 0) {
		convert << "-";
	} else {
		convert << file.fileSize;
	}
	
	convert >> toReturn;
	return toReturn;
}

GtkWidget* ViewFileListManager::getLocalTreeHandler(void) {
	return this->treeLocal;
}

GtkWidget* ViewFileListManager::getServerTreeHandler(void) {
	return this->treeServer;
}

std::string ViewFileListManager::getNameFromClickedCell(GtkTreeView *treeview, GtkTreePath *path, bool local) {
	GtkTreeModel * model = gtk_tree_view_get_model(treeview);
	GtkTreeIter   iter;
    
	int id = 0;

    if (gtk_tree_model_get_iter(model, &iter, path)){
	   gtk_tree_model_get(model, &iter, 4, &id, -1);
    }
	if(local) {
		for (std::list<ContainerFileInfo>::iterator it=this->localFilesList->begin(); it != this->localFilesList->end(); ++it) {
			if((*it).ID == id) {
				return (*it).fileName;
			}
		}
	} else {
		for (std::list<ContainerFileInfo>::iterator it=this->serverFilesList->begin(); it != this->serverFilesList->end(); ++it) {
			if((*it).ID == id) {
				return (*it).fileName;
			}
		}
	}
}


ContainerFileInfo* ViewFileListManager::getFileFromSelectedCell(GtkTreeSelection *selection, GtkTreeModel * model, GtkTreePath *path, bool local) {
	GtkTreeIter   iter;
	gtk_tree_model_get_iter(model, &iter, path);
    
	int id = 0;
	gtk_tree_model_get(model, &iter, 4, &id, -1);
	if(local) {
		for (std::list<ContainerFileInfo>::iterator it=this->localFilesList->begin(); it != this->localFilesList->end(); ++it) {
			if((*it).ID == id) {
				return &(*it);
			}
		}
	} else {
		for (std::list<ContainerFileInfo>::iterator it=this->serverFilesList->begin(); it != this->serverFilesList->end(); ++it) {
			if((*it).ID == id) {
				return &(*it);
			}
		}
	}
}

