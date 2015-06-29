#include "GUI_DialogMaker.h"
#include <sstream>

GdkPixmap *GUI_DialogMaker::g_pixmap=NULL;
GtkWidget *GUI_DialogMaker::dialog=NULL;
GtkWidget *GUI_DialogMaker::dialog_vbox=NULL;
GtkWidget *GUI_DialogMaker::dialog_hbox=NULL;
GtkWidget *GUI_DialogMaker::label=NULL;
GtkWidget *GUI_DialogMaker::dialog_action_area=NULL;
GtkWidget *GUI_DialogMaker::cancelbutton=NULL;
GtkWidget *GUI_DialogMaker::okbutton=NULL;
GtkWidget *GUI_DialogMaker::entry_input=NULL;
GtkWidget *GUI_DialogMaker::entry_x=NULL;
GtkWidget *GUI_DialogMaker::entry_y=NULL;
GtkWidget *GUI_DialogMaker::drawingarea=NULL;
GtkWidget *GUI_DialogMaker::radiobutton1=NULL;
GtkWidget *GUI_DialogMaker::radiobutton2=NULL;
GtkWidget *GUI_DialogMaker::radiobutton3=NULL;
GtkWidget *GUI_DialogMaker::calendar=NULL;
GtkWidget *GUI_DialogMaker::scrolledwindow=NULL;
GtkWidget *GUI_DialogMaker::viewport=NULL;
GSList *GUI_DialogMaker::radiobutton1_group=NULL;
string GUI_DialogMaker::dialog_des="";
string GUI_DialogMaker::cmd="";
string GUI_DialogMaker::arg1="";
string GUI_DialogMaker::arg2="";
bool GUI_DialogMaker::action_type=true;
int GUI_DialogMaker::sele=1;

GUI_DialogMaker::GUI_DialogMaker()
{

}

GUI_DialogMaker::~GUI_DialogMaker()
{
	gtk_widget_unref(dialog);
	gtk_widget_unref(dialog_vbox);
	gtk_widget_unref(dialog_hbox);
	gtk_widget_unref(label);
	gtk_widget_unref(dialog_action_area);
	gtk_widget_unref(cancelbutton);
	gtk_widget_unref(okbutton);
	gtk_widget_unref(entry_input);
	gtk_widget_unref(entry_x);
	gtk_widget_unref(entry_y);
	gtk_widget_unref(drawingarea);
	gdk_pixmap_unref(g_pixmap);
}

GtkWidget *GUI_DialogMaker::makeDialog_with_FileChooser(string c,string des,bool type,string arg)
{
	if(type==true)
		dialog = gtk_file_chooser_dialog_new ("", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL);
	else
		dialog = gtk_file_chooser_dialog_new ("", NULL, GTK_FILE_CHOOSER_ACTION_SAVE, NULL);
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_DIALOG);

	dialog_vbox = GTK_DIALOG (dialog)->vbox;

	dialog_action_area = GTK_DIALOG (dialog)->action_area;
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	cancelbutton = gtk_button_new_from_stock ("gtk-cancel");
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), cancelbutton, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (cancelbutton, GTK_CAN_DEFAULT);

	okbutton = gtk_button_new_from_stock ("gtk-open");
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), okbutton, GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS (okbutton, GTK_CAN_DEFAULT);

	//setup even
	cmd=c;
	action_type=type;
	arg1=arg;
	g_signal_connect (G_OBJECT (okbutton), "clicked", G_CALLBACK(okbutton_OnClicked_FileChooser), (gpointer)dialog);
	g_signal_connect (G_OBJECT (cancelbutton), "clicked", G_CALLBACK(cancelbutton_OnClicked), (gpointer)dialog);
	return dialog;
}

GtkWidget *GUI_DialogMaker::makeDialog_with_twoButton(string c,string des,string arg)
{
	dialog = gtk_dialog_new ();
	dialog_vbox = GTK_DIALOG (dialog)->vbox;
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
	
	dialog_action_area = GTK_DIALOG (dialog)->action_area;
	gtk_widget_show (dialog_action_area);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	cancelbutton = gtk_button_new_from_stock ("gtk-cancel");
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), cancelbutton, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (cancelbutton, GTK_CAN_DEFAULT);

	okbutton = gtk_button_new_from_stock ("gtk-ok");
	gtk_widget_show (okbutton);
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), okbutton, GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS (okbutton, GTK_CAN_DEFAULT);

	//setup label
	dialog_des="<span color=\"blue\">"+des+"</span>";
	label=gtk_label_new(dialog_des.c_str());
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	//add to dialog
	gtk_box_pack_start(GTK_BOX(dialog_vbox),label,TRUE,TRUE,0);
	//setup even
	cmd=c;
	arg1=arg;
	g_signal_connect (G_OBJECT (okbutton), "clicked", G_CALLBACK(okbutton_OnClicked_twoButton), NULL);
	g_signal_connect (G_OBJECT (cancelbutton), "clicked", G_CALLBACK(cancelbutton_OnClicked), NULL);
	return dialog;
}

GtkWidget *GUI_DialogMaker::makeDialog_with_oneEntry(string c,string des,string defaultvalue_input,string arg)
{
	dialog = gtk_dialog_new ();
	dialog_vbox = GTK_DIALOG (dialog)->vbox;
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
	
	dialog_action_area = GTK_DIALOG (dialog)->action_area;
	gtk_widget_show (dialog_action_area);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	cancelbutton = gtk_button_new_from_stock ("gtk-cancel");
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), cancelbutton, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (cancelbutton, GTK_CAN_DEFAULT);

	okbutton = gtk_button_new_from_stock ("gtk-ok");
	gtk_widget_show (okbutton);
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), okbutton, GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS (okbutton, GTK_CAN_DEFAULT);

	//setup label
	dialog_des="<span color=\"blue\">"+des+"</span>";
	label=gtk_label_new(dialog_des.c_str());
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	//setup entry
	entry_input=gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry_input),defaultvalue_input.c_str());
	//add to dialog
	gtk_box_pack_start(GTK_BOX(dialog_vbox),label,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_vbox),entry_input,TRUE,TRUE,0);
	//setup even
	cmd=c;
	arg1=arg;
	g_signal_connect (G_OBJECT (okbutton), "clicked", G_CALLBACK(okbutton_OnClicked_oneEntry), NULL);
	g_signal_connect (G_OBJECT (cancelbutton), "clicked", G_CALLBACK(cancelbutton_OnClicked), NULL);
	g_signal_connect (G_OBJECT (entry_input), "activate", G_CALLBACK(okbutton_OnClicked_oneEntry), NULL);
	return dialog;
}

GtkWidget *GUI_DialogMaker::makeDialog_with_twoEntry(string c,string des,bool type)
{
	ostringstream oss,oss2;
	dialog = gtk_dialog_new ();
	dialog_vbox = GTK_DIALOG (dialog)->vbox;
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
	
	dialog_action_area = GTK_DIALOG (dialog)->action_area;
	gtk_widget_show (dialog_action_area);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	cancelbutton = gtk_button_new_from_stock ("gtk-cancel");
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), cancelbutton, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (cancelbutton, GTK_CAN_DEFAULT);

	okbutton = gtk_button_new_from_stock ("gtk-ok");
	gtk_widget_show (okbutton);
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), okbutton, GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS (okbutton, GTK_CAN_DEFAULT);

	//setup label
	dialog_des="<span color=\"blue\">"+des+"</span>";
	label=gtk_label_new(dialog_des.c_str());
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	//setup entry
	entry_x=gtk_entry_new();
	entry_y=gtk_entry_new();
	if(type==true)
	{
		Cursor *m_pCursor=Cursor_Imp::getInstance();
		oss<<m_pCursor->getX()+1;
		gtk_entry_set_text(GTK_ENTRY(entry_x),oss.str().c_str());
		oss2<<m_pCursor->getY()+1;
		gtk_entry_set_text(GTK_ENTRY(entry_y),oss2.str().c_str());
	}
	//setup hbox
	dialog_hbox=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(dialog_hbox),entry_x,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_hbox),entry_y,TRUE,TRUE,0);
	//add to dialog
	gtk_box_pack_start(GTK_BOX(dialog_vbox),label,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_vbox),dialog_hbox,TRUE,TRUE,0);
	//setup even
	cmd=c;
	g_signal_connect (G_OBJECT (okbutton), "clicked", G_CALLBACK(okbutton_OnClicked_twoEntry), NULL);
	g_signal_connect (G_OBJECT (cancelbutton), "clicked", G_CALLBACK(cancelbutton_OnClicked), NULL);
	return dialog;
}

GtkWidget *GUI_DialogMaker::makeDialog_with_threeEntry(string c,string des)
{
	ostringstream oss,oss2;
	dialog = gtk_dialog_new ();
	dialog_vbox = GTK_DIALOG (dialog)->vbox;
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
	
	dialog_action_area = GTK_DIALOG (dialog)->action_area;
	gtk_widget_show (dialog_action_area);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	cancelbutton = gtk_button_new_from_stock ("gtk-cancel");
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), cancelbutton, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (cancelbutton, GTK_CAN_DEFAULT);

	okbutton = gtk_button_new_from_stock ("gtk-ok");
	gtk_widget_show (okbutton);
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), okbutton, GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS (okbutton, GTK_CAN_DEFAULT);

	//setup label
	dialog_des="<span color=\"blue\">"+des+"</span>";
	label=gtk_label_new(dialog_des.c_str());
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	//setup entry
	entry_input=gtk_entry_new();
	entry_x=gtk_entry_new();
	entry_y=gtk_entry_new();
	Cursor *m_pCursor=Cursor_Imp::getInstance();
	oss<<m_pCursor->getX()+1;
	gtk_entry_set_text(GTK_ENTRY(entry_x),oss.str().c_str());
	oss2<<m_pCursor->getY()+1;
	gtk_entry_set_text(GTK_ENTRY(entry_y),oss2.str().c_str());
	//setup hbox
	dialog_hbox=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(dialog_hbox),entry_x,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_hbox),entry_y,TRUE,TRUE,0);
	//add to dialog
	gtk_box_pack_start(GTK_BOX(dialog_vbox),label,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_vbox),dialog_hbox,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_vbox),entry_input,TRUE,TRUE,0);
	//setup even
	cmd=c;
	g_signal_connect (G_OBJECT (okbutton), "clicked", G_CALLBACK(okbutton_OnClicked_threeEntry), NULL);
	g_signal_connect (G_OBJECT (cancelbutton), "clicked", G_CALLBACK(cancelbutton_OnClicked), NULL);
	g_signal_connect (G_OBJECT (entry_input), "activate", G_CALLBACK(okbutton_OnClicked_threeEntry), NULL);
	return dialog;
}

GtkWidget *GUI_DialogMaker::makeDialog_with_drawingArea(string c,string des)
{
	dialog = gtk_dialog_new ();
	gtk_widget_set_size_request (dialog, 500, 500);
	dialog_vbox = GTK_DIALOG (dialog)->vbox;
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
	
	dialog_action_area = GTK_DIALOG (dialog)->action_area;
	gtk_widget_show (dialog_action_area);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	cancelbutton = gtk_button_new_from_stock ("gtk-cancel");
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), cancelbutton, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (cancelbutton, GTK_CAN_DEFAULT);

	okbutton = gtk_button_new_from_stock ("gtk-ok");
	gtk_widget_show (okbutton);
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), okbutton, GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS (okbutton, GTK_CAN_DEFAULT);
	//setup scrolled window
	scrolledwindow = gtk_scrolled_window_new (NULL, NULL);
	viewport = gtk_viewport_new (NULL, NULL);
	gtk_container_add (GTK_CONTAINER (scrolledwindow), viewport);

	//setup drawingarea
	drawingarea = gtk_drawing_area_new ();
	gtk_container_add (GTK_CONTAINER (viewport), drawingarea);
	gtk_widget_set_events(drawingarea,GDK_EXPOSURE_MASK|GDK_BUTTON_PRESS_MASK|GDK_BUTTON_MOTION_MASK|GDK_SUBSTRUCTURE_MASK);
	gtk_signal_connect(GTK_OBJECT(drawingarea),"configure_event",GTK_SIGNAL_FUNC(configure_event),NULL);
	gtk_signal_connect(GTK_OBJECT(drawingarea),"expose_event",GTK_SIGNAL_FUNC(expose_event),NULL); 
	//add to dialog
	gtk_box_pack_start(GTK_BOX(dialog_vbox),scrolledwindow,TRUE,TRUE,0);
	//setup even
	cmd=c;
	g_signal_connect (G_OBJECT (cancelbutton), "clicked", G_CALLBACK(cancelbutton_OnClicked), NULL);
	g_signal_connect (G_OBJECT (okbutton), "clicked", G_CALLBACK(okbutton_OnClicked_Statistic), NULL);
	return dialog;
}

GtkWidget *GUI_DialogMaker::makeDialog_with_twoSele(string c,string des,string sel1_des,string sel2_des,string arg)
{
	dialog = gtk_dialog_new ();
	dialog_vbox = GTK_DIALOG (dialog)->vbox;
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
	
	dialog_action_area = GTK_DIALOG (dialog)->action_area;
	gtk_widget_show (dialog_action_area);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	cancelbutton = gtk_button_new_from_stock ("gtk-cancel");
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), cancelbutton, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (cancelbutton, GTK_CAN_DEFAULT);

	okbutton = gtk_button_new_from_stock ("gtk-ok");
	gtk_widget_show (okbutton);
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), okbutton, GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS (okbutton, GTK_CAN_DEFAULT);
	//setup hbox
	dialog_hbox=gtk_hbox_new(FALSE,0);
	//setup radioButton
	radiobutton1 = gtk_radio_button_new_with_mnemonic (NULL,sel1_des.c_str());
	gtk_toggle_button_toggled ((GtkToggleButton *)radiobutton1);
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton1), radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton1));

	radiobutton2 = gtk_radio_button_new_with_mnemonic (NULL, sel2_des.c_str());
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton2), radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton2));
	//add to dialog
	gtk_box_pack_start(GTK_BOX(dialog_hbox),radiobutton1,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_hbox),radiobutton2,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_vbox),dialog_hbox,TRUE,TRUE,0);
	//setup even
	cmd=c;
	arg1=arg;
	g_signal_connect (G_OBJECT (okbutton), "clicked", G_CALLBACK(okbutton_OnClicked_twoSele), NULL);
	g_signal_connect (G_OBJECT (cancelbutton), "clicked", G_CALLBACK(cancelbutton_OnClicked), NULL);
	g_signal_connect_swapped ((gpointer) radiobutton1, "toggled",G_CALLBACK (radiobutton_OnToggled),GTK_OBJECT (radiobutton1));
	g_signal_connect_swapped ((gpointer) radiobutton2, "toggled",G_CALLBACK (radiobutton_OnToggled),GTK_OBJECT (radiobutton2));
	return dialog;
}

GtkWidget *GUI_DialogMaker::makeDialog_with_threeSele(string c,string des,string sel1_des,string sel2_des,string sel3_des,string arg)
{
	dialog = gtk_dialog_new ();
	dialog_vbox = GTK_DIALOG (dialog)->vbox;
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
	
	dialog_action_area = GTK_DIALOG (dialog)->action_area;
	gtk_widget_show (dialog_action_area);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	cancelbutton = gtk_button_new_from_stock ("gtk-cancel");
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), cancelbutton, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (cancelbutton, GTK_CAN_DEFAULT);

	okbutton = gtk_button_new_from_stock ("gtk-ok");
	gtk_widget_show (okbutton);
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), okbutton, GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS (okbutton, GTK_CAN_DEFAULT);
	//setup hbox
	dialog_hbox=gtk_hbox_new(FALSE,0);
	//setup radioButton
	radiobutton1 = gtk_radio_button_new_with_mnemonic (NULL,sel1_des.c_str());
	gtk_toggle_button_toggled ((GtkToggleButton *)radiobutton1);
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton1), radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton1));

	radiobutton2 = gtk_radio_button_new_with_mnemonic (NULL, sel2_des.c_str());
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton2), radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton2));
	
	radiobutton3 = gtk_radio_button_new_with_mnemonic (NULL, sel3_des.c_str());
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (radiobutton3), radiobutton1_group);
	radiobutton1_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton3));
	//add to dialog
	gtk_box_pack_start(GTK_BOX(dialog_hbox),radiobutton1,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_hbox),radiobutton2,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_hbox),radiobutton3,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_vbox),dialog_hbox,TRUE,TRUE,0);
	//setup even
	cmd=c;
	arg1=arg;
	g_signal_connect (G_OBJECT (okbutton), "clicked", G_CALLBACK(okbutton_OnClicked_threeSele), NULL);
	g_signal_connect (G_OBJECT (cancelbutton), "clicked", G_CALLBACK(cancelbutton_OnClicked), NULL);
	g_signal_connect_swapped ((gpointer) radiobutton1, "toggled",G_CALLBACK (radiobutton_OnToggled),GTK_OBJECT (radiobutton1));
	g_signal_connect_swapped ((gpointer) radiobutton2, "toggled",G_CALLBACK (radiobutton_OnToggled),GTK_OBJECT (radiobutton2));
	g_signal_connect_swapped ((gpointer) radiobutton3, "toggled",G_CALLBACK (radiobutton_OnToggled),GTK_OBJECT (radiobutton3));
	return dialog;
}

GtkWidget *GUI_DialogMaker::makeDialog_with_about()
{
	dialog = gtk_dialog_new ();
	dialog_vbox = GTK_DIALOG (dialog)->vbox;
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
	
	dialog_action_area = GTK_DIALOG (dialog)->action_area;
	gtk_widget_show (dialog_action_area);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	cancelbutton = gtk_button_new_from_stock ("gtk-cancel");
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), cancelbutton, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (cancelbutton, GTK_CAN_DEFAULT);
	//setup label
	dialog_des="student id:94598031\n"
	           "author name:Jung-Chi Wang\n"
	           "release date:2006/1/9\n"
	           "software version:HW5";
	label=gtk_label_new(dialog_des.c_str());
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	//setup calendar
	calendar = gtk_calendar_new ();
	gtk_widget_show (calendar);
	//add to dialog
	gtk_box_pack_start(GTK_BOX(dialog_vbox),label,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(dialog_vbox),calendar,TRUE,TRUE,0);
	//setup even
	g_signal_connect (G_OBJECT (cancelbutton), "clicked", G_CALLBACK(cancelbutton_OnClicked), NULL);
	return dialog;
}

void GUI_DialogMaker::okbutton_OnClicked_FileChooser(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	const gchar *filename=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
	if(cmd=="open")
	{
		StepHandler *handler=StepHandler::getInstance();
		handler->clearRedoStack();
		handler->clearUndoStack();
		
		gtk_widget_set_sensitive(GUI_Menu::root_menu_edit,1);
		gtk_widget_set_sensitive(GUI_Menu::root_menu_find,1);
		gtk_widget_set_sensitive(GUI_Menu::root_menu_format,1);
		gtk_widget_set_sensitive(GUI_Menu::root_menu_spell,1);
		gtk_widget_set_sensitive(GUI_Menu::root_menu_view,1);
		gtk_widget_set_sensitive(GUI_Menu::root_menu_option,1);
	}
	else
	{
		StepHandler *handler=StepHandler::getInstance();
		handler->clearRedoStack();
		handler->saveStep();
	}

	string args=arg1+filename;
	inputCommand((char *)cmd.c_str(),(char *)args.c_str());
	gtk_widget_hide_all(dialog);
}

void GUI_DialogMaker::okbutton_OnClicked_twoButton(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	if(cmd=="new")
	{
		StepHandler *handler=StepHandler::getInstance();
		handler->clearRedoStack();
		handler->clearUndoStack();
		
		gtk_widget_set_sensitive(GUI_Menu::root_menu_edit,1);
		gtk_widget_set_sensitive(GUI_Menu::root_menu_find,1);
		gtk_widget_set_sensitive(GUI_Menu::root_menu_format,1);
		gtk_widget_set_sensitive(GUI_Menu::root_menu_spell,1);
		gtk_widget_set_sensitive(GUI_Menu::root_menu_view,1);
		gtk_widget_set_sensitive(GUI_Menu::root_menu_option,1);
	}

	inputCommand((char *)cmd.c_str(),(char *)arg1.c_str());
	gtk_widget_hide_all(dialog);
}

void GUI_DialogMaker::okbutton_OnClicked_oneEntry(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	StepHandler *handler=StepHandler::getInstance();
	handler->clearRedoStack();
	handler->saveStep();

	const gchar *input_string=gtk_entry_get_text(GTK_ENTRY(entry_input));
	string args=arg1+input_string;
	inputCommand((char *)cmd.c_str(),(char *)args.c_str());
	gtk_widget_hide_all(dialog);
}

void GUI_DialogMaker::okbutton_OnClicked_twoEntry(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	StepHandler *handler=StepHandler::getInstance();
	handler->clearRedoStack();
	handler->saveStep();

	const gchar *input_x=gtk_entry_get_text(GTK_ENTRY(entry_x));
	const gchar *input_y=gtk_entry_get_text(GTK_ENTRY(entry_y));
	char args[50];
	sprintf(args,"%s %s",input_x,input_y);
	inputCommand((char *)cmd.c_str(),args);
	gtk_widget_hide_all(dialog);
}

void GUI_DialogMaker::okbutton_OnClicked_threeEntry(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	StepHandler *handler=StepHandler::getInstance();
	handler->clearRedoStack();
	handler->saveStep();

	const gchar *input_string=gtk_entry_get_text(GTK_ENTRY(entry_input));
	const gchar *input_x=gtk_entry_get_text(GTK_ENTRY(entry_x));
	const gchar *input_y=gtk_entry_get_text(GTK_ENTRY(entry_y));
	char args[50];
	sprintf(args,"%s %s %s",input_string,input_x,input_y);
	inputCommand((char *)cmd.c_str(),args);
	gtk_widget_hide_all(dialog);
}

void GUI_DialogMaker::okbutton_OnClicked_twoSele(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	StepHandler *handler=StepHandler::getInstance();
	handler->clearRedoStack();
	handler->saveStep();

	char args[50];
	if(arg1=="linebreak ")
	{
		if(sele==1)sprintf(args,"%s division",arg1.c_str());
		else if(sele==2)sprintf(args,"%s preservation",arg1.c_str());
		else sprintf(args,"linebreak preservation");
	}
	else if(arg1=="mode ")
	{
		if(sele==1)sprintf(args,"%s char",arg1.c_str());
		else if(sele==2)sprintf(args,"%s word",arg1.c_str());
		else sprintf(args,"linebreak char");
	}
	inputCommand((char *)cmd.c_str(),args);
	gtk_widget_hide_all(dialog);
}

void GUI_DialogMaker::okbutton_OnClicked_threeSele(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	StepHandler *handler=StepHandler::getInstance();
	handler->clearRedoStack();
	handler->saveStep();

	char args[50];
	if(cmd=="eliminate")
	{
		if(sele==1)sprintf(args,"empty");
		else if(sele==2)sprintf(args,"head");
		else if(sele==3)sprintf(args,"tail");
		else sprintf(args,"empty");
	}
	inputCommand((char *)cmd.c_str(),args);
	gtk_widget_hide_all(dialog);
}

void GUI_DialogMaker::cancelbutton_OnClicked(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_hide_all(dialog);
}

void GUI_DialogMaker::radiobutton_OnToggled(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton1)))
	{
		sele=1;
	}
	else if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton2)))
	{
		sele=2;
	}
	else if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton3)))
	{
		sele=3;
	}
}

gint GUI_DialogMaker::configure_event(GtkWidget *widget, GdkEventConfigure *event,gpointer data)
{
  if(g_pixmap==NULL)
  {
	g_pixmap = gdk_pixmap_new(widget->window,widget->allocation.width,
				  widget->allocation.height,-1);
	gdk_draw_rectangle (g_pixmap,widget->style->white_gc,
		      TRUE,0, 0,widget->allocation.width,widget->allocation.height);
  }
  
	gdk_draw_rectangle (widget->window,widget->style->white_gc,
		      TRUE,0, 0,widget->allocation.width,widget->allocation.height);
	expose_event(widget, (GdkEventExpose *)event);
	return TRUE;
}

gint GUI_DialogMaker::expose_event(GtkWidget *widget, GdkEventExpose *event)
{
	gdk_draw_pixmap(widget->window,widget->style->fg_gc[GTK_WIDGET_STATE (widget)],g_pixmap,
	event->area.x, event->area.y,event->area.x, event->area.y,event->area.width, event->area.height);
    /* 將整個pixmap垂貼在drawing_area */
    gdk_draw_drawable(widget->window,
                      widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                      g_pixmap,
                      event->area.x, event->area.y,
                      event->area.x, event->area.y,
                      event->area.width, event->area.height);
                      
	return FALSE;
}

void GUI_DialogMaker::okbutton_OnClicked_Statistic(GtkWidget *widget,GdkEvent *event,gpointer data)
{	
	if(StateMgr::getModeState()==0) charStatistic();
	else if(StateMgr::getModeState()==1) wordStatistic();
}

void GUI_DialogMaker::drawString(int x,int y,string str)
{
  PangoLayout *layout = gtk_widget_create_pango_layout(drawingarea, str.c_str());
  gdk_draw_layout(g_pixmap, drawingarea->style->black_gc,x,y, layout);
}

void GUI_DialogMaker::inputCommand(char *cmd,char *arg)
{
	Input *m_pInput=Input::getInstance();
	m_pInput->dispatchCommand( cmd, arg );
}

void GUI_DialogMaker::charStatistic()
{
	GdkRectangle update_rect;
	string caps("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	ostringstream oss,oss2;
	update_rect.x = 0;
	update_rect.y = 0;
	update_rect.width = 500;
	update_rect.height = 500;

	gtk_drawing_area_size( GTK_DRAWING_AREA(drawingarea),500,500);
	if (g_pixmap)
		gdk_pixmap_unref(g_pixmap);
	g_pixmap = gdk_pixmap_new(drawingarea->window,drawingarea->allocation.width,
			  drawingarea->allocation.height,-1);
	gdk_draw_rectangle (g_pixmap,drawingarea->style->white_gc,
		      TRUE,0, 0,drawingarea->allocation.width,drawingarea->allocation.height);

	
	StepHandler *handler=StepHandler::getInstance();
	vector<string> m_pTexts=handler->getCurrentStep().getContext();
	int alphabet[26],total=0;
	for(int i=0;i<26;i++)alphabet[i]=0;
	for(int i=0;i<(int)m_pTexts.size();i++)
	{
		string &line=m_pTexts[i];
		for(int a=0;a<(int)line.size();a++)
			for(int b=0;b<(int)caps.size();b++)
			{
				if(line[a]==caps[b])
				{
					if(b>=26)alphabet[b-26]++;
					else alphabet[b]++;
				}
			}
	}
	int pos=5;
	for(int i=0;i<26;i++)total+=alphabet[i];
	for(int i=0;i<26;i++,pos+=10)
	{
		int width=alphabet[i]*100/total;
		ostringstream oss2,oss3;
		oss2<<caps[i];
		drawString(0,5+pos,oss2.str());
		gdk_draw_rectangle(g_pixmap,drawingarea->style->black_gc,true,10,10+pos,width,10);
		oss3<<alphabet[i]<<","<<width<<"%";
		drawString(15+width,5+pos,oss3.str());
		pos+=5;
	}
	gdk_draw_line(g_pixmap,drawingarea->style->black_gc,10,10,10,pos+10);
	gdk_draw_line(g_pixmap,drawingarea->style->black_gc,10,pos+10,110,pos+10);
	oss2<<"0%     50%     100%"<<endl;
	drawString(10,pos+10,oss2.str());

	oss<<"Total letters:"<<total<<endl;
	drawString(100,0,oss.str());
	gtk_widget_draw (drawingarea ,&update_rect);
}

void GUI_DialogMaker::wordStatistic()
{
	StepHandler *handler=StepHandler::getInstance();
	vector<string> m_pTexts=handler->getCurrentStep().getContext();
	ostringstream oss2,oss;
	vector<string> words;
	vector<int> wordcount;
	vector<Location> *locset;
	int maxwordwidth=0;
	int total=0;
	int pos=5;

	TextLocationMapBuilder *builder=new TextLocationMapBuilder_Imp();
	TextLocationMap *m_pLocationMap;
	m_pLocationMap = builder->build( &m_pTexts );
	words=*(m_pLocationMap->getWord());
	for(int i=0;i<(int)words.size();i++)
	{
		locset=m_pLocationMap->getLocationSet(words[i]);
		wordcount.push_back(locset->size());
	}
	
	for(int i=0;i<(int)wordcount.size();i++)
	{
		if(maxwordwidth<(int)words[i].size()*7)maxwordwidth=words[i].size()*7;
		total+=wordcount[i];
	}
	
	//update drawingarea
	GdkRectangle update_rect;
	update_rect.x = 0;
	update_rect.y = 0;
	update_rect.width = maxwordwidth+150;
	update_rect.height = total*10;
	gtk_drawing_area_size( GTK_DRAWING_AREA(drawingarea),update_rect.width,update_rect.height);
	if (g_pixmap)
		gdk_pixmap_unref(g_pixmap);
	g_pixmap = gdk_pixmap_new(drawingarea->window,drawingarea->allocation.width,
			  drawingarea->allocation.height,-1);
	gdk_draw_rectangle (g_pixmap,drawingarea->style->white_gc,
		      TRUE,0, 0,drawingarea->allocation.width,drawingarea->allocation.height);

	for(int i=0;i<(int)words.size();i++,pos+=10)
	{
		ostringstream oss2,oss3;
		oss2<<words[i];
		drawString(0,5+pos,oss2.str());
		int width=wordcount[i]*100/total;
		gdk_draw_rectangle(g_pixmap,drawingarea->style->black_gc,true,10+maxwordwidth,10+pos,width,10);
		oss3<<wordcount[i]<<","<<width<<"%";
		drawString(15+width+maxwordwidth,5+pos,oss3.str());
		pos+=15;
	}
	gdk_draw_line(g_pixmap,drawingarea->style->black_gc,10+maxwordwidth,10,10+maxwordwidth,pos+10);
	gdk_draw_line(g_pixmap,drawingarea->style->black_gc,10+maxwordwidth,pos+10,110+maxwordwidth,pos+10);
	oss2<<"0%     50%     100%"<<endl;
	drawString(10+maxwordwidth,pos+10,oss2.str());

	oss<<"Total letters:"<<total<<endl;
	drawString(100+maxwordwidth,0,oss.str());
	gtk_widget_draw (drawingarea ,&update_rect);
}
