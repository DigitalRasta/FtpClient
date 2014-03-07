#include "..\HEADER\ViewGuiBuilder.h"
#include "../../InnerConfig.h"
#include <gtk-3.0/gtk/gtk.h>


using namespace FtpClient;
ViewGuiBuilder::ViewGuiBuilder(InnerConfig* innerConfigObject): innerConfigObject(innerConfigObject){
}

void ViewGuiBuilder::initializeMainWindow(void) {
	this->mainWindowHandler = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);   
    gtk_window_set_title(GTK_WINDOW(this->mainWindowHandler), "GTK+ with VS2010");
	gtk_widget_show(this->mainWindowHandler);     
    gtk_main(); 
}


ViewGuiBuilder::~ViewGuiBuilder(void)
{
}
