#ifndef _GUI_INTERFACE_H_
#define _GUI_INTERFACE_H_

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "GUI_Comm_Win.h"
#include "GUI_Menu.h"

using namespace std;

class GUI_Interface
{
public:
	GUI_Interface(int argc,char *argv[]);
	~GUI_Interface();
	static void show();
	static void exit();
	static void release();
	static void setText(string output);
	static string getText();
	static void setStateBar(string str);
private:
	static void setupGUI();
	static void window_OnDestroy(GtkWidget *widget,GdkEvent *event,gpointer data);
	static GtkWidget *window;
	static GtkWidget *scrolled_window;
	static GtkWidget *viewport;
	static GtkWidget *textview;
	static GtkWidget *vbox;
	static GtkWidget *button;
	static GtkWidget *statusbar;
	static GtkWidget *toolbar;
	static GtkWidget *toolbaritem1;
	static GtkWidget *toolbar_btn_new;
	static GtkWidget *handlebox	;
	static GtkTextBuffer *buffer;
};

#endif //_GUI_INTERFACE_H_
