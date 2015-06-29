#include "GUI_Comm_Win.h"
#include <iostream>

GtkWidget *GUI_Comm_Win::window_cmd=NULL;
GtkWidget *GUI_Comm_Win::hbox_cmd=NULL;
GtkWidget *GUI_Comm_Win::vbox_cmd=NULL;
GtkWidget *GUI_Comm_Win::entry_cmd=NULL;
GtkWidget *GUI_Comm_Win::button_cmd=NULL;
GtkWidget *GUI_Comm_Win::label_cmd=NULL;

GUI_Comm_Win::GUI_Comm_Win()
{

}

GUI_Comm_Win::~GUI_Comm_Win()
{
	gtk_widget_unref(window_cmd);
	gtk_widget_unref(vbox_cmd);
	gtk_widget_unref(hbox_cmd);
	gtk_widget_unref(label_cmd);
	gtk_widget_unref(entry_cmd);
	gtk_widget_unref(button_cmd);
}

void GUI_Comm_Win::showCommWin()
{
	//setup window
	window_cmd=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window_cmd), "destroy", (GtkSignalFunc)cmd_win_exit_OnClick, NULL);
	gtk_window_set_title(GTK_WINDOW(window_cmd),"Command");
	gtk_widget_set_size_request(GTK_WIDGET(window_cmd),300,70);
	//setup Edit
	entry_cmd=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_cmd),50);
	gtk_entry_set_text(GTK_ENTRY(entry_cmd),"open test.txt");
	g_signal_connect (G_OBJECT (entry_cmd), "activate", G_CALLBACK(button_cmd_OnClicked), NULL);
	//seetup Button
	button_cmd=gtk_button_new_from_stock(GTK_STOCK_OK);
	g_signal_connect (G_OBJECT (button_cmd), "clicked", G_CALLBACK(button_cmd_OnClicked), NULL);
	//setup label
	label_cmd=gtk_label_new("<span color=\"blue\">Input your command:</span>");
	gtk_label_set_use_markup (GTK_LABEL (label_cmd), TRUE);
	//add to window
	vbox_cmd=gtk_vbox_new(FALSE,0);
	hbox_cmd=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox_cmd),entry_cmd,TRUE,TRUE,0);
	gtk_box_pack_end(GTK_BOX(hbox_cmd),button_cmd,TRUE,TRUE,2);
	gtk_box_pack_start(GTK_BOX(vbox_cmd),label_cmd,TRUE,TRUE,0);
	gtk_box_pack_end(GTK_BOX(vbox_cmd),hbox_cmd,TRUE,TRUE,2);
	gtk_container_add (GTK_CONTAINER (window_cmd),vbox_cmd);
	//show
	gtk_widget_show_all(window_cmd);
}

void GUI_Comm_Win::cmd_win_exit_OnClick(GtkWidget *widget,gpointer data)
{
	gtk_widget_hide_all(window_cmd);
//	*((GtkWidget **)data) = NULL;
}


void GUI_Comm_Win::delCommWin()
{
	if(window_cmd!=NULL)gtk_widget_hide_all(window_cmd);
}

void GUI_Comm_Win::button_cmd_OnClicked(GtkButton *button,gpointer user_data)
{
	const gchar *cmd_c=gtk_entry_get_text(GTK_ENTRY(entry_cmd));
	gtk_widget_hide_all(window_cmd);
	Input *m_pInput=Input::getInstance();
	
	string line(cmd_c);
	// Remove CRLF from the tail of string
	static const int CRLF = 0x0D;
	if( line.size() > 0 && line[line.size()-1] == CRLF )
		line.erase( line.size()-1 );	

	unsigned int pos = line.find_first_of(" ");

	string cmd = line, arg = "";

	if( pos < line.size() ) {
		cmd = line.substr( 0, pos );

		pos = line.find_first_not_of(" ", pos);
		if( pos < line.size() )
			arg = line.substr(pos);
	}
		
	m_pInput->dispatchCommand( cmd, arg );
}
