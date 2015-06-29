#ifndef _GUI_COMM_WIN_H_
#define _GUI_COMM_WIN_H_

#include <gtk/gtk.h>
#include <string>
#include "Input.h"

using namespace std;

//use singleton pattern
class GUI_Comm_Win
{
public:
	~GUI_Comm_Win();
	static void showCommWin();	//Instance()
	static void delCommWin();
	static void cmd_win_exit_OnClick(GtkWidget *widget,gpointer data);
	static void button_cmd_OnClicked(GtkButton *button,gpointer user_data);
private:
	GUI_Comm_Win();
	static GtkWidget *window_cmd;
	static GtkWidget *hbox_cmd;
	static GtkWidget *vbox_cmd;
	static GtkWidget *entry_cmd;
	static GtkWidget *button_cmd;
	static GtkWidget *label_cmd;
};

#endif //_GUI_COMM_WIN_H_
