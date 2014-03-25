#include "../header/ViewFileListManager.h"
#include <gtk-3.0\gtk\gtk.h>
#include "../header/InnerConfig.h"


using namespace FtpClient;

ViewFileListManager::ViewFileListManager(InnerConfig* config){
	this->configObject = config;
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
	this->filesListLocal = gtk_tree_view_new();
	this->localColumnName = gtk_tree_view_column_new();
	this->localColumnDate = gtk_tree_view_column_new();
	this->localColumnSize = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(this->localColumnName, this->configObject->lang_filesListLocalColumnName.c_str());
	gtk_tree_view_column_set_title(this->localColumnDate, this->configObject->lang_filesListLocalColumnDate.c_str());
	gtk_tree_view_column_set_title(this->localColumnSize, this->configObject->lang_filesListLocalColumnSize.c_str());
	 
	gtk_tree_view_column_set_sizing (this->localColumnName, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (this->localColumnDate, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sizing (this->localColumnSize, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	//gtk_tree_view_column_set_fixed_width(col, 200);
	gtk_tree_view_column_set_resizable(this->localColumnName, TRUE);
	gtk_tree_view_column_set_resizable(this->localColumnDate, TRUE);
	gtk_tree_view_column_set_resizable(this->localColumnSize, TRUE);

	gtk_tree_view_append_column(GTK_TREE_VIEW(this->filesListLocal), this->localColumnName);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->filesListLocal), this->localColumnSize);
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->filesListLocal), this->localColumnDate);
	
	gtk_widget_set_hexpand(this->filesListLocal, TRUE);
	gtk_widget_set_vexpand(this->filesListLocal, TRUE);
	return this->filesListLocal;
}


