#ifndef _GUI_DIALOGMAKER_H_
#define _GUI_DIALOGMAKER_H_

#include <gtk/gtk.h>
#include "Input.h"
#include "Cursor_Imp.h"
#include "GUI_Menu.h"
#include "StepHandler.h"
#include <vector>
#include <sstream>
#include <iostream>

class GUI_DialogMaker
{
public:
	~GUI_DialogMaker();
	static GtkWidget *makeDialog_with_FileChooser(string c,string des,bool type,string arg="");
	static GtkWidget *makeDialog_with_twoButton(string c,string des,string arg);
	static GtkWidget *makeDialog_with_oneEntry(string c,string des,string defaultvalue_input,string arg="");
	static GtkWidget *makeDialog_with_twoEntry(string c,string des,bool type);
	static GtkWidget *makeDialog_with_threeEntry(string c,string des);
	static GtkWidget *makeDialog_with_drawingArea(string c,string des);
	static GtkWidget *makeDialog_with_twoSele(string c,string des,string sel1_des,string sel2_des,string arg);
	static GtkWidget *makeDialog_with_threeSele(string c,string des,string sel1_des,string sel2_des,string sel3_des,string arg);
	static GtkWidget *makeDialog_with_about();
private:
	GUI_DialogMaker();
	static void inputCommand(char *cmd,char *arg);
	static void okbutton_OnClicked_FileChooser(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void okbutton_OnClicked_twoButton(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void okbutton_OnClicked_oneEntry(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void okbutton_OnClicked_twoEntry(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void okbutton_OnClicked_threeEntry(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void okbutton_OnClicked_drawingArea(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void okbutton_OnClicked_twoSele(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void okbutton_OnClicked_threeSele(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void radiobutton_OnToggled(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void cancelbutton_OnClicked(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void okbutton_OnClicked_Statistic(GtkWidget *widget,GdkEvent *event,gpointer data);
	
	static gint configure_event(GtkWidget *widget, GdkEventConfigure *event,gpointer data);
	static gint expose_event(GtkWidget *widget, GdkEventExpose *event);
	static void drawString(int x,int y,string str);
	static void charStatistic();
	static void wordStatistic();
	static GdkPixmap *g_pixmap;
	static GtkWidget *dialog;
	static GtkWidget *dialog_action_area;
	static GtkWidget *cancelbutton;
	static GtkWidget *okbutton;
	static GtkWidget *dialog_vbox;
	static GtkWidget *dialog_hbox;
	static GtkWidget *label;
	static GtkWidget *entry_input;
	static GtkWidget *entry_x;
	static GtkWidget *entry_y;
	static GtkWidget *drawingarea;
	static GtkWidget *radiobutton1;
	static GtkWidget *radiobutton2;
	static GtkWidget *radiobutton3;
	static GtkWidget *scrolledwindow;
	static GtkWidget *viewport;
	static GSList *radiobutton1_group;
	static GtkWidget *calendar;
	static string cmd;
	static string x;
	static string y;
	static string arg1;
	static string arg2;
	static string dialog_des;
	static int sele;
	static bool action_type;
};

#endif //_GUI_DIALOGMAKER_H_
