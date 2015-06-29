#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <gtk/gtk.h>

class Command
{
public:
	static void single(GtkWidget *widget,GdkEvent *event,gpointer data);
	static void setupGUI();
	~Command();
protected:
	Command();
};

#endif //_COMMAND_H_
