#ifndef _CLIPBOARD_H_
#define _CLIPBOARD_H_
#include <string>

using namespace std;
class Clipboard
{
public:
	Clipboard();
    
    void put(string str);    
    string get();

private :
    string mem;
    
};

#endif //_CLIPBOARD_H_
