#include "GUI_Menu.h"

GtkWidget *GUI_Menu::menu_bar=NULL;
GtkWidget *GUI_Menu::root_menu_file=NULL;
GtkWidget *GUI_Menu::root_menu_edit=NULL;
GtkWidget *GUI_Menu::root_menu_find=NULL;
GtkWidget *GUI_Menu::root_menu_format=NULL;
GtkWidget *GUI_Menu::root_menu_spell=NULL;
GtkWidget *GUI_Menu::root_menu_view=NULL;
GtkWidget *GUI_Menu::root_menu_option=NULL;
GtkWidget *GUI_Menu::root_menu_help=NULL;
//file menu
GtkWidget *GUI_Menu::file_menu=NULL;
GtkWidget *GUI_Menu::file_menu_sep=NULL;
GtkWidget *GUI_Menu::file_menu_new=NULL;
GtkWidget *GUI_Menu::file_menu_open=NULL;
GtkWidget *GUI_Menu::file_menu_save=NULL;
GtkWidget *GUI_Menu::file_menu_quit=NULL;
//edit menu
GtkWidget *GUI_Menu::edit_menu=NULL;
GtkWidget *GUI_Menu::edit_menu_sep1=NULL;
GtkWidget *GUI_Menu::edit_menu_sep2=NULL;
GtkWidget *GUI_Menu::edit_menu_insert=NULL;
GtkWidget *GUI_Menu::edit_menu_insertfile=NULL;
GtkWidget *GUI_Menu::edit_menu_delete=NULL;
GtkWidget *GUI_Menu::edit_menu_deleterow=NULL;
GtkWidget *GUI_Menu::edit_menu_modify=NULL;
GtkWidget *GUI_Menu::edit_menu_replace=NULL;
GtkWidget *GUI_Menu::edit_menu_copy=NULL;
GtkWidget *GUI_Menu::edit_menu_paste=NULL;
GtkWidget *GUI_Menu::edit_menu_cut=NULL;
GtkWidget *GUI_Menu::edit_menu_undo=NULL;
GtkWidget *GUI_Menu::edit_menu_redo=NULL;
//find menu
GtkWidget *GUI_Menu::find_menu=NULL;
GtkWidget *GUI_Menu::find_menu_search=NULL;
GtkWidget *GUI_Menu::find_menu_query=NULL;
//Formatting menu
GtkWidget *GUI_Menu::format_menu=NULL;
GtkWidget *GUI_Menu::format_menu_eliminate=NULL;
GtkWidget *GUI_Menu::format_menu_compact=NULL;
GtkWidget *GUI_Menu::format_menu_breaking=NULL;
//Spell menu
GtkWidget *GUI_Menu::spell_menu=NULL;
GtkWidget *GUI_Menu::spell_menu_check=NULL;
GtkWidget *GUI_Menu::spell_menu_suggestion=NULL;
//View menu
GtkWidget *GUI_Menu::view_menu=NULL;
GtkWidget *GUI_Menu::view_menu_map=NULL;
GtkWidget *GUI_Menu::view_menu_statistic=NULL;
//Option menu
GtkWidget *GUI_Menu::option_menu=NULL;
GtkWidget *GUI_Menu::option_menu_width=NULL;
GtkWidget *GUI_Menu::option_menu_mode=NULL;
GtkWidget *GUI_Menu::option_menu_exclude=NULL;
GtkWidget *GUI_Menu::option_menu_dictionary=NULL;
//Help menu
GtkWidget *GUI_Menu::help_menu=NULL;
GtkWidget *GUI_Menu::help_menu_about=NULL;

GtkWidget *GUI_Menu::root_menu_cmd=NULL;
GtkWidget *GUI_Menu::root_menu_exit=NULL;

GtkAccelGroup *GUI_Menu::accel_group=NULL;

//toolbar
GtkWidget *GUI_Menu::toolbar=NULL;
GtkWidget *GUI_Menu::toolbutton_new=NULL;
GtkWidget *GUI_Menu::toolbutton_save=NULL;
GtkWidget *GUI_Menu::toolbutton_open=NULL;
GtkWidget *GUI_Menu::toolbutton_copy=NULL;
GtkWidget *GUI_Menu::toolbutton_paste=NULL;
GtkWidget *GUI_Menu::toolbutton_cut=NULL;
GtkWidget *GUI_Menu::toolbutton_redo=NULL;
GtkWidget *GUI_Menu::toolbutton_undo=NULL;
GtkWidget *GUI_Menu::toolbutton_spellcheck=NULL;
GtkWidget *GUI_Menu::toolbutton_spellcheck_suggestion=NULL;
GtkWidget *GUI_Menu::toolbutton_map=NULL;
GtkWidget *GUI_Menu::toolbutton_about=NULL;
GtkWidget *GUI_Menu::toolbutton_exit=NULL;

GUI_Menu::GUI_Menu()
{

}

GUI_Menu::~GUI_Menu()
{
	release();
}

void GUI_Menu::setupMenu()
{
	accel_group = gtk_accel_group_new ();
	//setup menu
	//setup file menu
	file_menu=gtk_menu_new();
	root_menu_file=gtk_menu_item_new_with_mnemonic("_File");
	addMenuItem(file_menu,file_menu_new,"_New",file_menu_new_Onpress,GDK_N);
	addMenuItem(file_menu,file_menu_open,"_Open",file_menu_open_Onpress,GDK_O);
	addMenuItem(file_menu,file_menu_save,"_Save",file_menu_save_Onpress,GDK_S);
	file_menu_sep = gtk_separator_menu_item_new ();
	gtk_container_add (GTK_CONTAINER (file_menu), file_menu_sep);
	gtk_widget_set_sensitive (file_menu_sep, FALSE);
	addMenuItem(file_menu,file_menu_quit,"_Quit",root_menu_exit_Onpress,GDK_Q);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu_file),file_menu);
	//setup Edit menu
	edit_menu=gtk_menu_new();
	root_menu_edit=gtk_menu_item_new_with_mnemonic("_Edit");
	addMenuItem(edit_menu,edit_menu_insert,"_Insert",edit_menu_insert_Onpress,GDK_I);
	addMenuItem(edit_menu,edit_menu_insertfile,"_Insert file",edit_menu_insertfile_Onpress,0);
	addMenuItem(edit_menu,edit_menu_delete,"_Delete",edit_menu_delete_Onpress,GDK_D);
	addMenuItem(edit_menu,edit_menu_deleterow,"_Delete row",edit_menu_deleterow_Onpress,0);
	addMenuItem(edit_menu,edit_menu_modify,"_Modify",edit_menu_modify_Onpress,GDK_M);
	addMenuItem(edit_menu,edit_menu_replace,"_Replace",edit_menu_replace_Onpress,GDK_R);
	edit_menu_sep1 = gtk_separator_menu_item_new ();
	gtk_container_add (GTK_CONTAINER (edit_menu), edit_menu_sep1);
	gtk_widget_set_sensitive (edit_menu_sep1, FALSE);
	addMenuItem(edit_menu,edit_menu_copy,"_Copy",edit_menu_copy_Onpress,0);
	addMenuItem(edit_menu,edit_menu_paste,"_Paste",edit_menu_paste_Onpress,0);
	addMenuItem(edit_menu,edit_menu_cut,"_Cut",edit_menu_cut_Onpress,0);
	edit_menu_sep2 = gtk_separator_menu_item_new ();
	gtk_container_add (GTK_CONTAINER (edit_menu), edit_menu_sep2);
	gtk_widget_set_sensitive (edit_menu_sep2, FALSE);
	addMenuItem(edit_menu,edit_menu_undo,"_Undo",edit_menu_undo_Onpress,GDK_Z);
	addMenuItem(edit_menu,edit_menu_redo,"_Redo",edit_menu_redo_Onpress,GDK_Y);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu_edit),edit_menu);
	//setup Find menu
	find_menu=gtk_menu_new();
	root_menu_find=gtk_menu_item_new_with_mnemonic("_Find");
	addMenuItem(find_menu,find_menu_search,"_Search",find_menu_search_Onpress,GDK_F);
	addMenuItem(find_menu,find_menu_query,"_Query",find_menu_query_Onpress,GDK_Q);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu_find),find_menu);
	//setup Formatting menu
	format_menu=gtk_menu_new();
	root_menu_format=gtk_menu_item_new_with_mnemonic("_Formatting");
	addMenuItem(format_menu,format_menu_eliminate,"_Eliminate",format_menu_eliminate_Onpress,0);
	addMenuItem(format_menu,format_menu_compact,"_Compact",format_menu_compact_Onpress,0);
	addMenuItem(format_menu,format_menu_breaking,"_Breaking",format_menu_breaking_Onpress,0);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu_format),format_menu);
	//setup Spell menu
	spell_menu=gtk_menu_new();
	root_menu_spell=gtk_menu_item_new_with_mnemonic("_Spell");
	addMenuItem(spell_menu,spell_menu_check,"_Check",spell_menu_check_Onpress,0);
	addMenuItem(spell_menu,spell_menu_suggestion,"_Suggestion",spell_menu_suggestion_Onpress,0);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu_spell),spell_menu);
	//setup View menu
	view_menu=gtk_menu_new();
	root_menu_view=gtk_menu_item_new_with_mnemonic("_View");
	addMenuItem(view_menu,view_menu_map,"_Map",view_menu_map_Onpress,0);
	addMenuItem(view_menu,view_menu_statistic,"_Statistic",view_menu_statistic_Onpress,0);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu_view),view_menu);
	//setup Option menu
	option_menu=gtk_menu_new();
	root_menu_option=gtk_menu_item_new_with_mnemonic("_Option");
	addMenuItem(option_menu,option_menu_width,"Text width",option_menu_width_Onpress,0);
	addMenuItem(option_menu,option_menu_mode,"Editing mode",option_menu_mode_Onpress,0);
	addMenuItem(option_menu,option_menu_exclude,"Word exclude",option_menu_exclude_Onpress,0);
	addMenuItem(option_menu,option_menu_dictionary,"Word dictionary",option_menu_dictionary_Onpress,0);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu_option),option_menu);
	
	//setup Help menu
	help_menu=gtk_menu_new();
	root_menu_help=gtk_menu_item_new_with_mnemonic("_Help");
	addMenuItem(help_menu,help_menu_about,"_About",help_menu_about_Onpress,0);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu_help),help_menu);
	
	root_menu_cmd=gtk_menu_item_new_with_mnemonic("_Command");
	root_menu_exit=gtk_menu_item_new_with_mnemonic("_Exit");
	menu_bar=gtk_menu_bar_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),root_menu_file);
	gtk_widget_set_sensitive(root_menu_edit,0);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),root_menu_edit);
	gtk_widget_set_sensitive(root_menu_find,0);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),root_menu_find);
	gtk_widget_set_sensitive(root_menu_format,0);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),root_menu_format);
	gtk_widget_set_sensitive(root_menu_spell,0);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),root_menu_spell);
	gtk_widget_set_sensitive(root_menu_view,0);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),root_menu_view);
	gtk_widget_set_sensitive(root_menu_option,0);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),root_menu_option);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),root_menu_help);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),root_menu_cmd);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),root_menu_exit);
	g_signal_connect_swapped(G_OBJECT (root_menu_cmd), "activate", G_CALLBACK(root_menu_cmd_Onpress),NULL);
	g_signal_connect_swapped(G_OBJECT (root_menu_exit), "activate", G_CALLBACK(root_menu_exit_Onpress),NULL);
}

void GUI_Menu::setupToolbar()
{
	toolbar = gtk_toolbar_new ();
	gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH);
//	tmp_toolbar_icon_size = gtk_toolbar_get_icon_size (GTK_TOOLBAR (toolbar));
  
	addToolButton(toolbar,toolbutton_new,"New file","gtk-new",file_menu_new_Onpress);
	addToolButton(toolbar,toolbutton_save,"Save file","gtk-save",file_menu_save_Onpress);
	addToolButton(toolbar,toolbutton_open,"Open file","gtk-open",file_menu_open_Onpress);
	addToolButton(toolbar,toolbutton_copy,"Copy","gtk-copy",edit_menu_copy_Onpress);
	addToolButton(toolbar,toolbutton_new,"Paste","gtk-paste",edit_menu_paste_Onpress);
	addToolButton(toolbar,toolbutton_copy,"Cut","gtk-cut",edit_menu_cut_Onpress);
	addToolButton(toolbar,toolbutton_copy,"Redo","gtk-redo",edit_menu_redo_Onpress);
	addToolButton(toolbar,toolbutton_copy,"Undo","gtk-undo",edit_menu_undo_Onpress);
	addToolButton(toolbar,toolbutton_new,"Spellcheck","gtk-find-and-replace",spell_menu_check_Onpress);
	addToolButton(toolbar,toolbutton_new,"Map","gtk-justify-fill",view_menu_map_Onpress);
	addToolButton(toolbar,toolbutton_new,"About","gtk-about",help_menu_about_Onpress);
	addToolButton(toolbar,toolbutton_new,"Exit","gtk-exit",root_menu_exit_Onpress);
}

void GUI_Menu::root_menu_exit_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	//hide main winodow
	GtkWidget *w;
	w = (GtkWidget *)gtk_window_list_toplevels ()->data;
	gtk_widget_hide_all(w);
//	gtk_widget_hide_all(window);

//	GUI_Comm_Win::delCommWin();
	StateMgr::setGUIState(false);
	gtk_main_quit();

	Input *m_pInput=Input::getInstance();
	string cmd = "exit", arg = "";
	m_pInput->dispatchCommand( cmd, arg );
}

void GUI_Menu::root_menu_cmd_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	GUI_Comm_Win::showCommWin();
}

void GUI_Menu::addMenuItem(GtkWidget *menu,GtkWidget *menu_item,const char *desc,void (func)(GtkWidget *widget,GdkEvent *event,gpointer data),int key)
{
	menu_item=gtk_image_menu_item_new_with_mnemonic(desc);

	if(key!=0)
		gtk_widget_add_accelerator (menu_item, "activate", accel_group,
                              key, (GdkModifierType) GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

	GtkWidget *image1;
	image1 = gtk_image_new_from_stock ("gtk-media-forward", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menu_item), image1);
	
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),menu_item);
	g_signal_connect_swapped(G_OBJECT (menu_item), "activate", G_CALLBACK(func),NULL);
}

void GUI_Menu::addToolButton(GtkWidget *toolbar,GtkWidget *tool_button,string des,string icon_name,void (func)(GtkWidget *widget,GdkEvent *event,gpointer data))
{
	GtkWidget *label;
	GtkWidget *tmp_image;
	string toolbar_des;
	GtkIconSize tmp_toolbar_icon_size;
	//setup label
	toolbar_des="<span color=\"red\">"+des+"</span>";
	label=gtk_label_new(toolbar_des.c_str());
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	
	tmp_toolbar_icon_size = gtk_toolbar_get_icon_size (GTK_TOOLBAR (toolbar));
	tmp_image = gtk_image_new_from_stock ((char *)icon_name.c_str(), tmp_toolbar_icon_size);
	tool_button = (GtkWidget*) gtk_tool_button_new (tmp_image, "");
//	tool_button = (GtkWidget*) gtk_tool_button_new (NULL, "");
	gtk_tool_button_set_label_widget ((GtkToolButton *)tool_button, label);
	
	g_signal_connect_swapped(G_OBJECT (tool_button), "clicked", G_CALLBACK(func),NULL);
	gtk_container_add (GTK_CONTAINER (toolbar), tool_button);
}

GtkAccelGroup *GUI_Menu::getAcce()
{
	return accel_group;
}

GtkWidget *GUI_Menu::getMenu()
{
	return menu_bar;
}

GtkWidget *GUI_Menu::getToolbar()
{
	return toolbar;
}

void GUI_Menu::release()
{
	gtk_widget_unref(menu_bar);
	gtk_widget_unref(root_menu_file);
	gtk_widget_unref(root_menu_edit);
	gtk_widget_unref(root_menu_find);
	gtk_widget_unref(root_menu_format);
	gtk_widget_unref(root_menu_spell);
	gtk_widget_unref(root_menu_cmd);
	gtk_widget_unref(root_menu_exit);
	//file menu
	gtk_widget_unref(file_menu);
	gtk_widget_unref(file_menu_sep);
	gtk_widget_unref(file_menu_new);
	gtk_widget_unref(file_menu_open);
	gtk_widget_unref(file_menu_save);
	gtk_widget_unref(file_menu_quit);
	//edit menu
	gtk_widget_unref(edit_menu);
	gtk_widget_unref(edit_menu_sep1);
	gtk_widget_unref(edit_menu_sep2);
	gtk_widget_unref(edit_menu_insert);
	gtk_widget_unref(edit_menu_insertfile);
	gtk_widget_unref(edit_menu_delete);
	gtk_widget_unref(edit_menu_deleterow);
	gtk_widget_unref(edit_menu_modify);
	gtk_widget_unref(edit_menu_replace);
	gtk_widget_unref(edit_menu_copy);
	gtk_widget_unref(edit_menu_paste);
	gtk_widget_unref(edit_menu_cut);
	gtk_widget_unref(edit_menu_undo);
	gtk_widget_unref(edit_menu_redo);
	//find menu
	gtk_widget_unref(find_menu);
	gtk_widget_unref(find_menu_search);
	gtk_widget_unref(find_menu_query);
	//Format menu
	gtk_widget_unref(format_menu);
	gtk_widget_unref(format_menu_eliminate);
	gtk_widget_unref(format_menu_compact);
	gtk_widget_unref(format_menu_breaking);
	//Spell menu
	gtk_widget_unref(spell_menu);
	gtk_widget_unref(spell_menu_check);
	gtk_widget_unref(spell_menu_suggestion);
	//View menu
	gtk_widget_unref(view_menu);
	gtk_widget_unref(view_menu_map);
	gtk_widget_unref(view_menu_statistic);
	//Option menu
	gtk_widget_unref(option_menu);
	gtk_widget_unref(option_menu_width);
	gtk_widget_unref(option_menu_mode);
	gtk_widget_unref(option_menu_exclude);
	gtk_widget_unref(option_menu_dictionary);
	//Help menu
	gtk_widget_unref(help_menu);
	gtk_widget_unref(help_menu_about);
	//toolbar
	gtk_widget_unref(toolbar);
	gtk_widget_unref(toolbutton_new);
	gtk_widget_unref(toolbutton_open);
	gtk_widget_unref(toolbutton_save);
	gtk_widget_unref(toolbutton_copy);
	gtk_widget_unref(toolbutton_paste);
	gtk_widget_unref(toolbutton_cut);
	gtk_widget_unref(toolbutton_redo);
	gtk_widget_unref(toolbutton_undo);
	gtk_widget_unref(toolbutton_spellcheck);
	gtk_widget_unref(toolbutton_spellcheck_suggestion);
	gtk_widget_unref(toolbutton_map);
	gtk_widget_unref(toolbutton_about);
	gtk_widget_unref(toolbutton_exit);
}

void GUI_Menu::file_menu_new_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_twoButton("new","Create new file?",""));
}

void GUI_Menu::file_menu_save_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_FileChooser("save","Save file?",false));
}

void GUI_Menu::file_menu_open_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_FileChooser("open","Open new file?",true));
}

void GUI_Menu::edit_menu_insert_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	if(StateMgr::getModeState()==false)
		gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_oneEntry("insert","Insert string.",""));
	else
		gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_threeEntry("insert","Insert string."));
}

void GUI_Menu::edit_menu_insertfile_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_FileChooser("insertfile","Select insertfile.",true));
}

void GUI_Menu::edit_menu_delete_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_twoEntry("delete","Delete string.",true));
}

void GUI_Menu::edit_menu_deleterow_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	ostringstream oss;
	Cursor *m_pCursor=Cursor_Imp::getInstance();
	oss<<m_pCursor->getY()+1;
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_oneEntry("deleterow","Delete row.",oss.str()));
}

void GUI_Menu::edit_menu_modify_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	if(StateMgr::getModeState()==false)
		gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_oneEntry("modify","Modify string.",""));
	else
		gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_threeEntry("modify","Modify string."));
}

void GUI_Menu::edit_menu_replace_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_twoEntry("replace","Replace string.",false));
}

void GUI_Menu::edit_menu_copy_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_twoEntry("copy","Copy string.",true));
}

void GUI_Menu::edit_menu_paste_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_twoEntry("paste","Paste string.",true));
}

void GUI_Menu::edit_menu_cut_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_twoEntry("cut","Cut string.",true));
}

void GUI_Menu::edit_menu_undo_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	StepHandler *handler=StepHandler::getInstance();
	handler->loadUndoStack();
	
	Input *m_pInput=Input::getInstance();
	m_pInput->dispatchCommand( "renew", "" );
}

void GUI_Menu::edit_menu_redo_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	StepHandler *handler=StepHandler::getInstance();
	handler->loadRedoStack();

	Input *m_pInput=Input::getInstance();
	m_pInput->dispatchCommand( "renew", "" );
}

void GUI_Menu::find_menu_search_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_oneEntry("search","Key-in search word.",""));
}

void GUI_Menu::find_menu_query_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_oneEntry("query","Key-in query string.",""));
}

void GUI_Menu::format_menu_eliminate_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	StepHandler *handler=StepHandler::getInstance();
	handler->clearRedoStack();
	handler->saveStep();

	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_threeSele("eliminate","Eliminate string.","empty","head","tail",""));	
}

void GUI_Menu::format_menu_compact_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	StepHandler *handler=StepHandler::getInstance();
	handler->clearRedoStack();
	handler->saveStep();

	Input *m_pInput=Input::getInstance();
	m_pInput->dispatchCommand( "compact", "" );
}

void GUI_Menu::format_menu_breaking_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_twoSele("set","Set Breaking strategy.","division","preservation","linebreak "));
}

void GUI_Menu::spell_menu_check_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	Input *m_pInput=Input::getInstance();
	m_pInput->dispatchCommand( "spellcheck", "suggestion" );
}

void GUI_Menu::spell_menu_suggestion_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	Input *m_pInput=Input::getInstance();
	m_pInput->dispatchCommand( "spellcheck", "suggestion" );
}

void GUI_Menu::view_menu_map_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	Input *m_pInput=Input::getInstance();
	m_pInput->dispatchCommand( "map", "" );
}

void GUI_Menu::view_menu_statistic_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_drawingArea("statistic","Statistic word."));
}

void GUI_Menu::option_menu_width_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_oneEntry("set","Set line width.","","width "));
}

void GUI_Menu::option_menu_mode_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_twoSele("set","Set edit mode.","char","word","mode "));
}

void GUI_Menu::option_menu_exclude_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_FileChooser("exclude","Select exclude file.",true));
}

void GUI_Menu::option_menu_dictionary_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_FileChooser("set","Select spellcheck dictionary.",true,"dictionary "));
}

void GUI_Menu::help_menu_about_Onpress(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_widget_show_all(GUI_DialogMaker::makeDialog_with_about());
}
