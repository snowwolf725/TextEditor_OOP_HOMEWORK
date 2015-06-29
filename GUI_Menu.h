#ifndef _GUI_MENU_H_
#define _GUI_MENU_H_

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "GUI_Comm_Win.h"
#include "GUI_DialogMaker.h"

//Use Command patten
class GUI_Menu
{
public:
	~GUI_Menu();
	static GtkWidget *getMenu();
	static GtkWidget *getToolbar();
	static GtkAccelGroup *getAcce();
	static void setupMenu();
	static void setupToolbar();
	static void release();
private:
	friend class GUI_DialogMaker;
	static void addMenuItem(GtkWidget *menu,GtkWidget *menu_item,const char *desc,void (func)(GtkWidget *widget,GdkEvent *event,gpointer data),int key);
	static void addToolButton(GtkWidget *toolbar,GtkWidget *tool_button,string des,string icon_name,void (func)(GtkWidget *widget,GdkEvent *event,gpointer data));
	GUI_Menu();
	static void file_menu_new_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void file_menu_open_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void file_menu_save_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void edit_menu_insert_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void edit_menu_insertfile_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void edit_menu_delete_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void edit_menu_deleterow_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void edit_menu_modify_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void edit_menu_replace_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void edit_menu_copy_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void edit_menu_paste_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void edit_menu_cut_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void edit_menu_undo_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void edit_menu_redo_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void find_menu_search_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void find_menu_query_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void format_menu_eliminate_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void format_menu_compact_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void format_menu_breaking_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void spell_menu_check_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void spell_menu_suggestion_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void view_menu_map_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void view_menu_statistic_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void option_menu_map_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void option_menu_width_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void option_menu_mode_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void option_menu_exclude_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void option_menu_dictionary_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void help_menu_about_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void root_menu_cmd_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void root_menu_exit_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data);
	//root menu
	static GtkWidget *menu_bar;
	static GtkWidget *root_menu_file;
	static GtkWidget *root_menu_edit;
	static GtkWidget *root_menu_find;
	static GtkWidget *root_menu_format;
	static GtkWidget *root_menu_spell;
	static GtkWidget *root_menu_view;
	static GtkWidget *root_menu_option;
	static GtkWidget *root_menu_help;
	static GtkWidget *root_menu_cmd;
	static GtkWidget *root_menu_exit;
	//file menu
	static GtkWidget *file_menu;
	static GtkWidget *file_menu_sep;
	static GtkWidget *file_menu_new;
	static GtkWidget *file_menu_open;
	static GtkWidget *file_menu_save;
	static GtkWidget *file_menu_quit;
	//edit menu
	static GtkWidget *edit_menu;
	static GtkWidget *edit_menu_sep1;
	static GtkWidget *edit_menu_sep2;
	static GtkWidget *edit_menu_insert;
	static GtkWidget *edit_menu_insertfile;
	static GtkWidget *edit_menu_delete;
	static GtkWidget *edit_menu_deleterow;
	static GtkWidget *edit_menu_modify;
	static GtkWidget *edit_menu_replace;
	static GtkWidget *edit_menu_copy;
	static GtkWidget *edit_menu_paste;
	static GtkWidget *edit_menu_cut;
	static GtkWidget *edit_menu_undo;
	static GtkWidget *edit_menu_redo;
	//Find menu
	static GtkWidget *find_menu;
	static GtkWidget *find_menu_search;
	static GtkWidget *find_menu_query;
	//Formatting menu
	static GtkWidget *format_menu;
	static GtkWidget *format_menu_eliminate;
	static GtkWidget *format_menu_compact;
	static GtkWidget *format_menu_breaking;
	//Spell menu
	static GtkWidget *spell_menu;
	static GtkWidget *spell_menu_check;
	static GtkWidget *spell_menu_suggestion;
	//View menu
	static GtkWidget *view_menu;
	static GtkWidget *view_menu_map;
	static GtkWidget *view_menu_statistic;
	//Option menu
	static GtkWidget *option_menu;
	static GtkWidget *option_menu_width;
	static GtkWidget *option_menu_mode;
	static GtkWidget *option_menu_exclude;
	static GtkWidget *option_menu_dictionary;
	//Help menu
	static GtkWidget *help_menu;
	static GtkWidget *help_menu_about;
	
	//tool bar
	static GtkWidget *toolbar;
	static GtkWidget *toolbutton_new;
	static GtkWidget *toolbutton_save;
	static GtkWidget *toolbutton_open;
	static GtkWidget *toolbutton_copy;
	static GtkWidget *toolbutton_paste;
	static GtkWidget *toolbutton_cut;
	static GtkWidget *toolbutton_redo;
	static GtkWidget *toolbutton_undo;
	static GtkWidget *toolbutton_spellcheck;
	static GtkWidget *toolbutton_spellcheck_suggestion;
	static GtkWidget *toolbutton_map;
	static GtkWidget *toolbutton_about;
	static GtkWidget *toolbutton_exit;
	
	static GtkAccelGroup *accel_group;
};

#endif //_GUI_MENU_H_
