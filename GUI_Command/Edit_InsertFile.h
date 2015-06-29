#ifndef _EDIT_INSERTFILE_H_
#define _EDIT_INSERTFILE_H_


#include "Command.h"
#include "../Input.h"

class Edit_InsertFile : public Command
{
public:
	~Edit_InsertFile();
	static void single(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void setupGUI();
protected:
	Edit_InsertFile();
private:
	static void release();
	static GtkWidget *filechooserdialog1;
	static GtkWidget *dialog_vbox1;
	static GtkWidget *dialog_action_area1;
	static GtkWidget *button1;
	static GtkWidget *button2;
	static void inputCommand(char *cmd,char *arg);
	static void okbutton_OnClicked(GtkWidget *w,GtkFileSelection *fs);
	static void cancelbutton_OnClicked(GtkWidget *widget,GdkEvent *event,gpointer data);
};

#endif //_EDIT_INSERTFILE_H_
