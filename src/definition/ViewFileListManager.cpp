#include "../header/ViewFileListManager.h"
#include <gtk-3.0\gtk\gtk.h>
#include "../header/InnerConfig.h"
#include "../header/ContainerFileInfo.h"
#include "../header/ViewGuiBuilder.h"
#include <list>
#include <string>
#include <sstream>


using namespace FtpClient;

ViewFileListManager::ViewFileListManager(InnerConfig* config){
	this->configObject = config;
	this->dirImage = gdk_pixbuf_new_from_file("img/dirIcon.png",NULL);
	this->fileImage =gdk_pixbuf_new_from_file("img/fileIcon.png",NULL);
}


ViewFileListManager::~ViewFileListManager(void)
{
}

GtkWidget* ViewFileListManager::createFilesListServer(void) {
	this->treeServer = gtk_tree_view_new();
	this->serverColumnIcon = gtk_tree_view_column_new();
	this->serverColumnName = gtk_tree_view_column_new();
	this->serverColumnDate = gtk_tree_view_column_new();
	this->serverColumnSize = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(this->serverColumnName, this->configObject->lang_filesListServerColumnName.c_str());
	gtk_tree_view_column_set_title(this->serverColumnDate, this->configObject->lang_filesListServerColumnDate.c_str());
	gtk_tree_view_column_set_title(this->serverColumnSize, this->configObject->lang_filesListServerColumnSize.c_str());
	gtk_tree_view_column_set_sizing (this->serverColumnIcon, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (this->serverColumnName, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (this->serverColumnDate, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (this->serverColumnSize, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_resizable(this->serverColumnName, TRUE);
	gtk_tree_view_column_set_resizable(this->serverColumnDate, TRUE);
	gtk_tree_view_column_set_resizable(this->serverColumnSize, TRUE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeServer), this->serverColumnIcon);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeServer), this->serverColumnName);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeServer), this->serverColumnSize);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeServer), this->serverColumnDate);
	this->serverColumnIconNumber = 0;
	this->serverColumnNameNumber = 1;
	this->serverColumnDateNumber = 2;
	this->serverColumnSizeNumber = 3;
	gtk_widget_set_hexpand(this->treeServer, TRUE);
	gtk_widget_set_vexpand(this->treeServer, TRUE);
	if(this->dirImage == NULL || this->fileImage == NULL) {
		this->serverRenderIcon = gtk_cell_renderer_text_new();
		gtk_tree_view_column_pack_start(this->serverColumnIcon, this->serverRenderIcon, true);
		gtk_tree_view_column_add_attribute(this->serverColumnIcon, this->serverRenderIcon, "text",this->serverColumnIconNumber);
		gtk_tree_view_column_set_title(this->serverColumnIcon, this->configObject->lang_filesListServerColumnType.c_str());
	} else {
		this->serverRenderIcon = gtk_cell_renderer_pixbuf_new();
		gtk_tree_view_column_pack_start(this->serverColumnIcon, this->serverRenderIcon, true);
		gtk_tree_view_column_add_attribute(this->serverColumnIcon, this->serverRenderIcon, "pixbuf",this->serverColumnIconNumber);
	}
	this->serverRenderName = gtk_cell_renderer_text_new();
	this->serverRenderSize = gtk_cell_renderer_text_new();
	this->serverRenderDate = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(this->serverColumnName, this->serverRenderName, true);
	gtk_tree_view_column_add_attribute(this->serverColumnName, this->serverRenderName, "text",this->serverColumnNameNumber);
	gtk_tree_view_column_pack_start(this->serverColumnDate, this->serverRenderDate, true);
	gtk_tree_view_column_add_attribute(this->serverColumnDate, this->serverRenderDate, "text",this->serverColumnDateNumber);
	gtk_tree_view_column_pack_start(this->serverColumnSize, this->serverRenderSize, true);
	gtk_tree_view_column_add_attribute(this->serverColumnSize, this->serverRenderSize, "text",this->serverColumnSizeNumber);
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
	this->localColumnIcon = gtk_tree_view_column_new();
	this->localColumnName = gtk_tree_view_column_new();
	this->localColumnDate = gtk_tree_view_column_new();
	this->localColumnSize = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(this->localColumnName, this->configObject->lang_filesListLocalColumnName.c_str());
	gtk_tree_view_column_set_title(this->localColumnDate, this->configObject->lang_filesListLocalColumnDate.c_str());
	gtk_tree_view_column_set_title(this->localColumnSize, this->configObject->lang_filesListLocalColumnSize.c_str());
	gtk_tree_view_column_set_sizing (this->localColumnIcon, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (this->localColumnName, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (this->localColumnDate, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (this->localColumnSize, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_resizable(this->localColumnName, TRUE);
	gtk_tree_view_column_set_resizable(this->localColumnDate, TRUE);
	gtk_tree_view_column_set_resizable(this->localColumnSize, TRUE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), this->localColumnIcon);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), this->localColumnName);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), this->localColumnSize);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), this->localColumnDate);
	this->localColumnIconNumber = 0;
	this->localColumnNameNumber = 1;
	this->localColumnDateNumber = 2;
	this->localColumnSizeNumber = 3;
	gtk_widget_set_hexpand(this->treeLocal, TRUE);
	gtk_widget_set_vexpand(this->treeLocal, TRUE);
	if(this->dirImage == NULL || this->fileImage == NULL) {
		this->localRenderIcon = gtk_cell_renderer_text_new();
		gtk_tree_view_column_pack_start(this->localColumnIcon, this->localRenderIcon, true);
		gtk_tree_view_column_add_attribute(this->localColumnIcon, this->localRenderIcon, "text",this->localColumnIconNumber);
		gtk_tree_view_column_set_title(this->localColumnIcon, this->configObject->lang_filesListLocalColumnType.c_str());
	} else {
		this->localRenderIcon = gtk_cell_renderer_pixbuf_new();
		gtk_tree_view_column_pack_start(this->localColumnIcon, this->localRenderIcon, true);
		gtk_tree_view_column_add_attribute(this->localColumnIcon, this->localRenderIcon, "pixbuf",this->localColumnIconNumber);
	}
	this->localRenderName = gtk_cell_renderer_text_new();
	this->localRenderSize = gtk_cell_renderer_text_new();
	this->localRenderDate = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(this->localColumnName, this->localRenderName, true);
	gtk_tree_view_column_add_attribute(this->localColumnName, this->localRenderName, "text",this->localColumnNameNumber);
	gtk_tree_view_column_pack_start(this->localColumnDate, this->localRenderDate, true);
	gtk_tree_view_column_add_attribute(this->localColumnDate, this->localRenderDate, "text",this->localColumnDateNumber);
	gtk_tree_view_column_pack_start(this->localColumnSize, this->localRenderSize, true);
	gtk_tree_view_column_add_attribute(this->localColumnSize, this->localRenderSize, "text",this->localColumnSizeNumber);
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

std::string ViewFileListManager::convertSpecialSigns(std::string strToConvert) {
	std::string strToReturn = std::string();
	for(int i = 0; i < strToConvert.size(); i++) {
		if(strToConvert[i] < 0) {
			int newSign = -((254 + strToConvert[i]) + strToConvert[i+1]);
			i++;
			strToReturn.push_back((char)newSign);
		} else {
			strToReturn.push_back(strToConvert[i]);
		}
	}
	return strToReturn;
}


