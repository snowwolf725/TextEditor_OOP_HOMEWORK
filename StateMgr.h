#ifndef _STATEMGR_H_
#define _STATEMGR_H_

class StateMgr
{
public:
	static StateMgr *getInstance();
	~StateMgr();
	static void setGUIState(bool isshow);
	static bool getGUIState();
	static void setModeState(bool mode);
	static bool getModeState();
private:
	static StateMgr *op;
	StateMgr();
	static bool _GUIS;
	static bool _mode;
};

#endif //_STATEMGR_H_
