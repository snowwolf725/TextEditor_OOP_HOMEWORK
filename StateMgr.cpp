#include "StateMgr.h"

StateMgr *StateMgr::op=0;
bool StateMgr::_GUIS=true;
bool StateMgr::_mode=false;

StateMgr::StateMgr()
{

}

StateMgr::~StateMgr()
{

}

StateMgr *StateMgr::getInstance()
{
	if(op==0)
	{
		op=new StateMgr();
	}
	return op;
}

void StateMgr::setGUIState(bool isshow)
{
	_GUIS=isshow;
}

bool StateMgr::getGUIState()
{
	return _GUIS;
}

void StateMgr::setModeState(bool mode)
{
	_mode=mode;
}

bool StateMgr::getModeState()
{
	return _mode;
}
