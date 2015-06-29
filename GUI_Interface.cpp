#include "GUI_Interface.h"

GtkWidget *GUI_Interface::window=NULL;
GtkWidget *GUI_Interface::scrolled_window=NULL;
GtkWidget *GUI_Interface::viewport=NULL;
GtkWidget *GUI_Interface::vbox=NULL;
GtkWidget *GUI_Interface::button=NULL;
GtkWidget *GUI_Interface::statusbar=NULL;
GtkWidget *GUI_Interface::toolbar=NULL;
GtkWidget *GUI_Interface::toolbaritem1=NULL;
GtkWidget *GUI_Interface::toolbar_btn_new=NULL;
GtkWidget *GUI_Interface::handlebox=NULL;
GtkWidget *GUI_Interface::textview=NULL;
GtkTextBuffer *GUI_Interface::buffer=NULL;

GUI_Interface::GUI_Interface(int argc,char *argv[])
{
	//init gtk main window
	gtk_init(&argc,&argv);
	setupGUI();
}

GUI_Interface::~GUI_Interface()
{
	release();
	GUI_Menu::release();
}

void GUI_Interface::release()
{
	gtk_widget_unref(window);
	gtk_widget_unref(vbox);
	gtk_widget_unref(button);
	gtk_widget_unref(statusbar);
	gtk_widget_unref(toolbar);
	gtk_widget_unref(toolbaritem1);
	gtk_widget_unref(toolbar_btn_new);
	gtk_widget_unref(handlebox);
	gtk_widget_unref(textview);
}

void GUI_Interface::setupGUI()
{
//	accel_group = gtk_accel_group_new ();
	//setup main window
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK(window_OnDestroy), NULL);
	gtk_window_set_title(GTK_WINDOW(window),"Text Editor - 2005 OOP");
	gtk_window_set_default_size(GTK_WINDOW(window),500,500);
	//setup TextView
	textview = gtk_text_view_new ();
	//setup scrolled_window
	scrolled_window=gtk_scrolled_window_new(NULL,NULL);
	gtk_container_border_width (GTK_CONTAINER (scrolled_window), 10);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
								  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	viewport = gtk_viewport_new (NULL, NULL);
	gtk_container_add (GTK_CONTAINER (viewport),textview);
	gtk_container_add (GTK_CONTAINER (scrolled_window),viewport);
	//setup menu
	GUI_Menu::setupMenu();
	//setup toolbar
	GUI_Menu::setupToolbar();
	handlebox = gtk_handle_box_new ();
	gtk_container_add (GTK_CONTAINER (handlebox),GUI_Menu::getToolbar());
	//setup statebar
	statusbar = gtk_statusbar_new ();
	setStateBar("(0, 0)  Character-based mode");
	//add menu and label to window
	vbox=gtk_vbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),GUI_Menu::getMenu(),FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),handlebox,FALSE,FALSE,2);
	gtk_box_pack_start(GTK_BOX(vbox),scrolled_window,TRUE,TRUE,2);
	gtk_box_pack_end(GTK_BOX(vbox),statusbar,FALSE,FALSE,2);
	gtk_container_add (GTK_CONTAINER (window),vbox);
	gtk_window_add_accel_group (GTK_WINDOW (window), GUI_Menu::getAcce());
}

void GUI_Interface::show()
{
	if(window==NULL)setupGUI();
	gtk_widget_show_all (window);
	gtk_main();
}

void GUI_Interface::exit()
{
	//hide main winodow
	GtkWidget *w;
	w = (GtkWidget *)gtk_window_list_toplevels ()->data;
	gtk_widget_hide_all(w);

	GUI_Comm_Win::delCommWin();
	// *((GtkWidget **)data) = NULL;
	StateMgr::setGUIState(false);
	
	gtk_main_quit();
}

void GUI_Interface::setText(string output)
{
	const char *str=output.c_str();
	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview)), str, strlen(str));
}

string GUI_Interface::getText()
{
	GtkTextIter start, end;

	gchar *str1;
	buffer=gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
	gtk_text_buffer_get_start_iter (buffer, &start);
	gtk_text_buffer_get_end_iter (buffer, &end);
	str1 = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
	
	string str(str1);
	return str;
}


void GUI_Interface::window_OnDestroy(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_hide_all(window);

	GUI_Comm_Win::delCommWin();
	StateMgr::setGUIState(false);
	gtk_main_quit();

	window=NULL;

	Input *m_pInput=Input::getInstance();
	string cmd = "exit", arg = "";
	m_pInput->dispatchCommand( cmd, arg );
}

void GUI_Interface::setStateBar(string str)
{
	gint context_id;
	context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR (statusbar), "");
	gtk_statusbar_push (GTK_STATUSBAR (statusbar), context_id, str.c_str());
}
