#ifndef _FILE_SAVE_H_
#define _FILE_SAVE_H_

#include "Command.h"
#include "../Input.h"

class File_Save : public Command
{
public:
	~File_Save();
	static void single(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void setupGUI();
protected:
	File_Save();
private:
	static GtkWidget *filechooserdialog1;
	static GtkWidget *dialog_vbox1;
	static GtkWidget *dialog_action_area1;
	static GtkWidget *button1;
	static GtkWidget *button2;
	static void inputCommand(char *cmd,char *arg);
	static void okbutton_OnClicked(GtkWidget *w,GtkFileSelection *fs);
	static void cancelbutton_OnClicked(GtkWidget *widget,GdkEvent *event,gpointer data);
};

#endif //_FILE_SAVE_H_
