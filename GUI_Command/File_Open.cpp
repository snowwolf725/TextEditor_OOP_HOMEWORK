#include "File_Open.h"

GtkWidget *File_Open::filechooserdialog1=NULL;
GtkWidget *File_Open::dialog_vbox1=NULL;
GtkWidget *File_Open::dialog_action_area1=NULL;
GtkWidget *File_Open::button1=NULL;
GtkWidget *File_Open::button2=NULL;

File_Open::File_Open()
{

}

File_Open::~File_Open()
{
	gtk_widget_unref(filechooserdialog1);
	gtk_widget_unref(dialog_vbox1);
	gtk_widget_unref(dialog_action_area1);
	gtk_widget_unref(button1);
	gtk_widget_unref(button2);
}

void File_Open::single(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	setupGUI();
	gtk_widget_show_all(filechooserdialog1);
}

void File_Open::setupGUI()
{
	filechooserdialog1 = gtk_file_chooser_dialog_new ("", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL);
	gtk_window_set_type_hint (GTK_WINDOW (filechooserdialog1), GDK_WINDOW_TYPE_HINT_DIALOG);

	dialog_vbox1 = GTK_DIALOG (filechooserdialog1)->vbox;
	gtk_widget_show (dialog_vbox1);

	dialog_action_area1 = GTK_DIALOG (filechooserdialog1)->action_area;
	gtk_widget_show (dialog_action_area1);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);

	button1 = gtk_button_new_from_stock ("gtk-cancel");
	gtk_widget_show (button1);
	gtk_dialog_add_action_widget (GTK_DIALOG (filechooserdialog1), button1, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (button1, GTK_CAN_DEFAULT);

	button2 = gtk_button_new_from_stock ("gtk-open");
	gtk_widget_show (button2);
	gtk_dialog_add_action_widget (GTK_DIALOG (filechooserdialog1), button2, GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS (button2, GTK_CAN_DEFAULT);

	//setup even
	g_signal_connect (G_OBJECT (button2), "clicked", G_CALLBACK(okbutton_OnClicked), (gpointer)filechooserdialog1);
	g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK(cancelbutton_OnClicked), (gpointer)filechooserdialog1);
}

void File_Open::okbutton_OnClicked(GtkWidget *w,GtkFileSelection *fs)
{
	const gchar *filename=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (filechooserdialog1));
	inputCommand("open",(char *)filename);
	inputCommand(".","");
	gtk_widget_hide_all(filechooserdialog1);
}

void File_Open::cancelbutton_OnClicked(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_hide_all(filechooserdialog1);
}


void File_Open::inputCommand(char *cmd,char *arg)
{
	Input *m_pInput=Input::getInstance();
	m_pInput->dispatchCommand( cmd, arg );
}
