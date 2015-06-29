#ifndef _FILE_OPEN_H_
#define _FILE_OPEN_H_

#include "Command.h"
#include "../Input.h"

class File_Open : public Command
{
public:
	~File_Open();
	static void single(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void setupGUI();
protected:
	File_Open();
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

#endif //_FILE_OPEN_H_
