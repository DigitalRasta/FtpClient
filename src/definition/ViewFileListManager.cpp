#include "../header/ViewFileListManager.h"
#include <gtk-3.0\gtk\gtk.h>
#include "../header/InnerConfig.h"
#include "../header/ContainerFileInfo.h"
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
	this->filesListServer = gtk_tree_view_new();
	this->serverColumnName = gtk_tree_view_column_new();
	this->serverColumnDate = gtk_tree_view_column_new();
	this->serverColumnSize = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(this->serverColumnName, this->configObject->lang_filesListServerColumnName.c_str());
	gtk_tree_view_column_set_title(this->serverColumnDate, this->configObject->lang_filesListServerColumnDate.c_str());
	gtk_tree_view_column_set_title(this->serverColumnSize, this->configObject->lang_filesListServerColumnSize.c_str());
	 
	gtk_tree_view_column_set_sizing (this->serverColumnName, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (this->serverColumnDate, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (this->serverColumnSize, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	//gtk_tree_view_column_set_fixed_width(col, 200);
	gtk_tree_view_column_set_resizable(this->serverColumnName, TRUE);
	gtk_tree_view_column_set_resizable(this->serverColumnDate, TRUE);
	gtk_tree_view_column_set_resizable(this->serverColumnSize, TRUE);


	gtk_tree_view_append_column(GTK_TREE_VIEW(this->filesListServer), this->serverColumnName);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->filesListServer), this->serverColumnSize);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->filesListServer), this->serverColumnDate);
	
	gtk_widget_set_hexpand(this->filesListServer, TRUE);
	gtk_widget_set_vexpand(this->filesListServer, TRUE);

	return this->filesListServer;
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
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), this->localColumnIcon);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), this->localColumnName);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), this->localColumnSize);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->treeLocal), this->localColumnDate);
	gtk_widget_set_hexpand(this->treeLocal, TRUE);
	if(this->dirImage == NULL || this->fileImage == NULL) {
		this->localRenderIcon = gtk_cell_renderer_text_new();
		gtk_tree_view_column_pack_start(this->localColumnIcon, this->localRenderIcon, true);
		gtk_tree_view_column_add_attribute(this->localColumnIcon, this->localRenderIcon, "text",0);
		gtk_tree_view_column_set_title(this->localColumnIcon, this->configObject->lang_filesListLocalColumnType.c_str());
	} else {
		this->localRenderIcon = gtk_cell_renderer_pixbuf_new();
		gtk_tree_view_column_pack_start(this->localColumnIcon, this->localRenderIcon, true);
		gtk_tree_view_column_add_attribute(this->localColumnIcon, this->localRenderIcon, "pixbuf",0);
	}
	this->localRenderName = gtk_cell_renderer_text_new();
	this->localRenderSize = gtk_cell_renderer_text_new();
	this->localRenderDate = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(this->localColumnName, this->localRenderName, true);
	gtk_tree_view_column_add_attribute(this->localColumnName, this->localRenderName, "text",1);
	gtk_tree_view_column_pack_start(this->localColumnDate, this->localRenderDate, true);
	gtk_tree_view_column_add_attribute(this->localColumnDate, this->localRenderDate, "text",2);
	gtk_tree_view_column_pack_start(this->localColumnSize, this->localRenderSize, true);
	gtk_tree_view_column_add_attribute(this->localColumnSize, this->localRenderSize, "text",3);
	if(this->dirImage == NULL || this->fileImage == NULL) {
		this->localStoreList = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	} else {
		this->localStoreList = gtk_list_store_new(4, GDK_TYPE_PIXBUF, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	}
	gtk_tree_view_set_model(GTK_TREE_VIEW(this->treeLocal),GTK_TREE_MODEL(this->localStoreList));

	return this->treeLocal;
}

void ViewFileListManager::showListInLocalTree(std::list<ContainerFileInfo> filesList) {
	gtk_list_store_clear(this->localStoreList);
	for(std::list<ContainerFileInfo>::const_iterator i = filesList.begin(); i != filesList.end(); i++) {
			gtk_list_store_append(this->localStoreList, &this->localStoreIter);
			std::string fileDate = this->getDateToView((*i));
			std::string fileSize = this->getSizeToView((*i));
			if(this->fileImage != NULL && this->dirImage != NULL) {
				if((*i).isDir) {
					gtk_list_store_set(this->localStoreList, &this->localStoreIter,0, this->dirImage,  1, (*i).fileName.c_str(), 2, fileDate.c_str(), 3, fileSize.c_str());
				} else {
					gtk_list_store_set(this->localStoreList, &this->localStoreIter,0, this->fileImage,  1, (*i).fileName.c_str(), 2, fileDate.c_str(), 3, fileSize.c_str());
				}
			} else {
				if((*i).isDir) {
					gtk_list_store_set(this->localStoreList, &this->localStoreIter,0, "Directory",  1, (*i).fileName.c_str(), 2, fileDate.c_str(), 3, fileSize.c_str());
				} else {
					gtk_list_store_set(this->localStoreList, &this->localStoreIter,0, "File",  1, (*i).fileName.c_str(), 2, fileDate.c_str(), 3, fileSize.c_str());
				}
			}
	}
}

std::string ViewFileListManager::getDateToView(ContainerFileInfo file) {
	std::stringstream convert;
	std::string toReturn;
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
	convert >> toReturn;
	return toReturn;
}

std::string ViewFileListManager::getSizeToView(ContainerFileInfo file) {
	std::stringstream convert;
	std::string toReturn;
	if(file.fileSize == 0) {
		convert << "-";
	} else {
		convert << file.fileSize;
	}
	
	convert >> toReturn;
	return toReturn;
}


