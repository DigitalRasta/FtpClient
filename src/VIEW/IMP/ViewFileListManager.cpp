#include "..\HEADER\ViewFileListManager.h"
#include <gtk-3.0\gtk\gtk.h>
#include "../../InnerConfig.h"


using namespace FtpClient;

ViewFileListManager::ViewFileListManager(InnerConfig* config){
	this->configObject = config;
}


ViewFileListManager::~ViewFileListManager(void)
{
}

GtkWidget* ViewFileListManager::createFilesListServer(void) {
	this->filesListServer = gtk_tree_view_new();
	GtkTreeViewColumn   *col;
	GtkCellRenderer     *renderer;
	GtkTreeModel        *model;
		/* --- Column #1 --- */
 
	  col = gtk_tree_view_column_new();
 
	  gtk_tree_view_column_set_title(col, "Col1");
	  gtk_tree_view_column_set_sizing (col, GTK_TREE_VIEW_COLUMN_FIXED);
	  gtk_tree_view_column_set_fixed_width(col, 200);
 
	  /* pack tree view column into tree view */
	  gtk_tree_view_append_column(GTK_TREE_VIEW(this->filesListServer), col);
 
	  //renderer = gtk_cell_renderer_text_new();
 
	  /* pack cell renderer into tree view column */
	  //gtk_tree_view_column_pack_start(col, renderer, TRUE);
 
	  /* set 'text' property of the cell renderer */
	  //g_object_set(renderer, "text", "Boooo!", NULL);
	  gtk_widget_set_hexpand(this->filesListServer, TRUE);
	  gtk_widget_set_vexpand(this->filesListServer, TRUE);
	return this->filesListServer;
}

GtkWidget* ViewFileListManager::createFilesListLocal(void) {
	this->filesListLocal = gtk_tree_view_new();
	gtk_widget_set_hexpand(this->filesListLocal, TRUE);
	gtk_widget_set_vexpand(this->filesListServer, TRUE);
	return this->filesListLocal;
}


