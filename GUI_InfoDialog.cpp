#include "GUI_InfoDialog.h"

GtkWidget *GUI_InfoDialog::dialog=NULL;

GUI_InfoDialog::GUI_InfoDialog()
{
	
}

GUI_InfoDialog::~GUI_InfoDialog()
{
/*	gtk_widget_unref(dialog);
	gtk_widget_unref(dialog_vbox);
	gtk_widget_unref(dialog_action_area);
	gtk_widget_unref(closebutton);*/
}

void GUI_InfoDialog::showGUI(string context)
{
	dialog = gtk_dialog_new ();
	gtk_window_set_title (GTK_WINDOW (dialog), "Info Dialog");
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_DIALOG);

	dialog_vbox = GTK_DIALOG (dialog)->vbox;
	label = gtk_label_new (context.c_str());
	gtk_box_pack_start (GTK_BOX (dialog_vbox), label, FALSE, FALSE, 0);


	dialog_action_area = GTK_DIALOG (dialog)->action_area;
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	closebutton = gtk_button_new_from_stock ("gtk-close");
	gtk_dialog_add_action_widget (GTK_DIALOG (dialog), closebutton, GTK_RESPONSE_CLOSE);
	GTK_WIDGET_SET_FLAGS (closebutton, GTK_CAN_DEFAULT);
	g_signal_connect (G_OBJECT (closebutton), "clicked", G_CALLBACK(closebutton_OnClick), this);
	gtk_widget_show_all(dialog);
}

void GUI_InfoDialog::closebutton_OnClick(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	//hide Dialog
	gtk_widget_hide_all(dialog);
}
