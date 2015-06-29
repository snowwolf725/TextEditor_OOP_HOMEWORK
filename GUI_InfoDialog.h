#ifndef _GUI_INFODIALOG_H_
#define _GUI_INFODIALOG_H_

#include <gtk/gtk.h>
#include <string>

using namespace std;

class GUI_InfoDialog
{
public:
	GUI_InfoDialog();
	~GUI_InfoDialog();
	void showGUI(string context);
private:
	static void closebutton_OnClick(GtkWidget *widget,GdkEvent *event,gpointer data);
	static GtkWidget *dialog;
	GtkWidget *label;
	GtkWidget *dialog_vbox;
	GtkWidget *dialog_action_area;
	GtkWidget *closebutton;
};

#endif //_GUI_INFODIALOG_H_
