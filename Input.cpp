#include <iostream>
#include <string>
#include "Input.h"

using namespace std;

Input::Input() : m_pText(NULL)
{
	lastCmd = "";
}

Input::~Input()
{
}

Input *Input::m_pInput=NULL;

Input *Input::getInstance()
{
	if(m_pInput==NULL)
	{
		m_pInput=new Input();
	}
	return m_pInput;
}

void Input::processInput() 
{
	if( m_pText == NULL) return;

	string line;
	getline(cin, line);

	// Remove CRLF from the tail of string
	static const int CRLF = 0x0D;
	if( line.size() > 0 && line[line.size()-1] == CRLF )
		line.erase( line.size()-1 );	

	unsigned int pos = line.find_first_of(" ");

	string cmd = line, arg = "";

	if( pos < line.size() ) {
		cmd = line.substr( 0, pos );

		pos = line.find_first_not_of(" ", pos);
		if( pos < line.size() )
			arg = line.substr(pos);
	}
		
	dispatchCommand( cmd, arg );
}

void Input::dispatchCommand(string cmd, string arg)
{
	Tokener argv;
	argv.parsing(arg);
	try{
		
	if( cmd == "exit" ) 
	{
		if(argCheck(argv.size(),0,0))
			exit(0);
	}
	else if( cmd == "!" ) 
	{
		cmd=lastCmd;arg=lastArg;dispatchCommand(cmd,arg);
	}
	else if( cmd == "new" ) 
	{
		if(argCheck(argv.size(),0,0))
			m_pText->newFile();
	}
	else if( cmd == "." ) 
	{
		if(argCheck(argv.size(),0,1))
		{
			if(!m_pText->safeCheck(true))
			{
				if(argv.size()==0)
					m_pText->display(string(""));
				else
					m_pText->display(argv[0]);
			}
		}
	}
	else if( cmd == "open" ) 
	{
		if(argCheck(argv.size(),1,1))
		{
			m_pText->readFile(argv[0]);
			LineBreak *linebreak=new LineBreak_Pre(m_pText->getTexts(),m_pText->getLineWidth());
			linebreak->setWidth(80);
		}
	}
	else if( cmd == "save" ) 
	{
		if(argCheck(argv.size(),1,1))
			m_pText->saveFile(argv[0]);
	}
	else if( cmd == "query" ) 
	{
		if(argv.size()<=0)	throw WrongNumberOfArgumentsException(argv.size(),0,0);
		else
			{
				if(m_pText->getMode()==0) m_pText->query(argv,arg);
				else if(m_pText->getMode()==1) m_pText->queryWord(argv,arg);
			}
	}
	else if( cmd == "search" || cmd =="/" ) 
	{
		if(argCheck(argv.size(),1,1))
		{
			if(m_pText->getMode()==0)
				m_pText->search_Char(argv[0]);
			else if(m_pText->getMode()==1)
				m_pText->search(argv[0]);
		}
	}
	else if( cmd == "map" ) 
	{
		if(argCheck(argv.size(),0,0))
			m_pText->map();
	}
	else if( cmd == "goto" ) 
	{
		if(argCheck(argv.size(),2,2))
			if(m_pText->getMode()==0)
				m_pText->setPos_Char(atoi(argv[0].c_str())-1,atoi(argv[1].c_str())-1);
			else if(m_pText->getMode()==1)
				m_pText->setPos(atoi(argv[0].c_str())-1,atoi(argv[1].c_str())-1);
	}
	else if( cmd == "home" ) 
	{
		if(!m_pText->safeCheck(true)&&argCheck(argv.size(),0,0))
			m_pCursor->gotoHome();
	}
	else if( cmd == "end" ) 
	{
		if(!m_pText->safeCheck(true)&&argCheck(argv.size(),0,0))
			m_pCursor->gotoEnd();
	}
	else if( cmd == "p" ) 
	{
		if(argCheck(argv.size(),0,0))
			m_pText->displayPLine();
	}
	else if( cmd == "n" ) 
	{
		if(argCheck(argv.size(),0,0))
			m_pText->displayNLine();
	}
	else if( cmd == "P" ) 
	{
		if(argCheck(argv.size(),0,0))
			m_pText->displayPPage();
	}
	else if( cmd == "N" ) 
	{
		if(argCheck(argv.size(),0,0))
			m_pText->displayNPage();
	}
	else if( cmd == "exclude")
	{
		if(argCheck(argv.size(),1,1))
			m_pText->exclude(argv[0]);
	}
	else if( cmd == "if" || cmd == "insertfile")
	{
		if(argCheck(argv.size(),1,1))
			m_pText->insertfile(argv[0]);
	}
	else if( cmd == "insert" )
	{
		if(m_pText->getMode()==0)
				m_pText->insert_Char(arg,m_pCursor->getX(),m_pCursor->getY());
		else if(m_pText->getMode()==1)
		{
			if(argv.size()==1)m_pText->insert(argv[0],m_pCursor->getX(),m_pCursor->getY());
			else if(argv.size()==3)m_pText->insert(argv[0],atoi(argv[2].c_str())-1,atoi(argv[1].c_str())-1);
			else throw WrongNumberOfArgumentsException(argv.size(),1,3);
		}
	}
	else if( cmd == "delete" )
	{
		if(argv.size()==0)
		{
			if(m_pText->getMode()==0)
				m_pText->delChar(m_pCursor->getX(),m_pCursor->getY());
			else if(m_pText->getMode()==1)
				m_pText->delWord(m_pCursor->getX(),m_pCursor->getY());
		}
		else if(argv.size()==2)
		{
			if(m_pText->getMode()==0)
				m_pText->delChar(atoi(argv[1].c_str())-1,atoi(argv[0].c_str())-1);
			else if(m_pText->getMode()==1)
				m_pText->delWord(atoi(argv[1].c_str())-1,atoi(argv[0].c_str())-1);
		}
		else throw WrongNumberOfArgumentsException(argv.size(),0,0);
	}
	else if( cmd == "copy")
	{
		if(argv.size()==0)
		{
			if(m_pText->getMode()==0)
				m_pText->copyChar(m_pCursor->getX(),m_pCursor->getY());
			else if(m_pText->getMode()==1)
				m_pText->copyWord(m_pCursor->getX(),m_pCursor->getY());
		}
		else if(argv.size()==2)
		{
			if(m_pText->getMode()==0)
				m_pText->copyChar(atoi(argv[1].c_str())-1,atoi(argv[0].c_str())-1);
			else if(m_pText->getMode()==1)
				m_pText->copyWord(atoi(argv[1].c_str())-1,atoi(argv[0].c_str())-1);
		}
		else throw WrongNumberOfArgumentsException(argv.size(),0,0);
	}
	else if( cmd == "cut")
	{
		if(argv.size()==0)
		{
			if(m_pText->getMode()==0)
				m_pText->cutChar(m_pCursor->getX(),m_pCursor->getY());
			else if(m_pText->getMode()==1)
				m_pText->cutWord(m_pCursor->getX(),m_pCursor->getY());
		}
		else if(argv.size()==2)
		{
			if(m_pText->getMode()==0)
				m_pText->cutChar(atoi(argv[1].c_str())-1,atoi(argv[0].c_str())-1);
			else if(m_pText->getMode()==1)
				m_pText->cutWord(atoi(argv[1].c_str())-1,atoi(argv[0].c_str())-1);
		}
		else throw WrongNumberOfArgumentsException(argv.size(),0,0);
	}
	else if( cmd == "paste")
	{
		if(argv.size()==0)
		{
			if(m_pText->getMode()==0)
				m_pText->pasteChar(m_pCursor->getX(),m_pCursor->getY());
			else if(m_pText->getMode()==1)
				m_pText->pasteWord(m_pCursor->getX(),m_pCursor->getY());
		}
		else if(argv.size()==2)
		{
			if(m_pText->getMode()==0)
				m_pText->pasteChar(atoi(argv[1].c_str())-1,atoi(argv[0].c_str())-1);
			else if(m_pText->getMode()==1)
				m_pText->pasteWord(atoi(argv[1].c_str())-1,atoi(argv[0].c_str())-1);
		}
		else throw WrongNumberOfArgumentsException(argv.size(),0,0);
	}
	else if( cmd == "modify")
	{
		if(m_pText->getMode()==0)
		{
			m_pText->modifyChar(arg,m_pCursor->getX(),m_pCursor->getY());
		}
		else if(m_pText->getMode()==1)
		{
			if(argv.size()==1)
				m_pText->modifyWord(argv[0],m_pCursor->getX(),m_pCursor->getY());
			if(argv.size()==3)
				m_pText->modifyWord(argv[0],atoi(argv[2].c_str())-1,atoi(argv[1].c_str())-1);
			else throw WrongNumberOfArgumentsException(argv.size(),0,0);
		}
	}
	else if( cmd == "deleterow" || cmd == "dr")
	{
		if(argv.size()==0)
			m_pText->deleteRow(m_pCursor->getY()+1);
		else if(argv.size()==1)
			m_pText->deleteRow(atoi(argv[0].c_str()));
		else throw WrongNumberOfArgumentsException(argv.size(),0,0);
	}
	else if( cmd == "replace")
	{
		if(m_pText->getMode()==0)
		{
			string::size_type pos = 0;
			if((pos=arg.find("to"))!=string::npos)
			{
				string arg1,arg2;
				arg1=arg.substr(0,pos-1);
				arg2=arg.substr(pos+3,arg.length()-pos+3);
				m_pText->replaceString(arg1,arg2);
			}
		}
		else if(m_pText->getMode()==1)
		{
			if(argCheck(argv.size(),2,2))
				m_pText->replaceWord(argv[0],argv[1]);
		}
	}
	else if( cmd == "set")
	{
		if(argCheck(argv.size(),2,2))
			if(argv[0]=="mode")
			{
				if(argv[1]=="char")
					m_pText->setMode(0);
				else if(argv[1]=="word")
					m_pText->setMode(1);
				else throw InvalidArgumentException(arg);
			}
			else if(argv[0]=="dictionary")
				m_pSpellChecker->loadDict(argv[1]);
			else if(argv[0]=="linebreak")
			{
				if(argv[1]=="division"||argv[1]=="preservation"&&!m_pText->safeCheck(true))
				{
				   m_pText->chgLineBreakState(argv[1]);
				
					LineBreak *linebreak;
					if( m_pText->getLineBreakState()=="division")
					{
						linebreak=new LineBreak_Div(m_pText->getTexts(),m_pText->getLineWidth());
						m_pText->prompt("The line breaking rule is changed to division strategy.");
					}
					else if( m_pText->getLineBreakState()=="preservation")
					{
						linebreak=new LineBreak_Pre(m_pText->getTexts(),m_pText->getLineWidth());
						m_pText->prompt("The line breaking rule is changed to preservation strategy.");
					}
					else throw InvalidArgumentException(arg);
					linebreak->revert();
					linebreak->setWidth(m_pText->getLineWidth());
					delete linebreak;
				}
			}
			else if(argv[0]=="width"&&!m_pText->safeCheck(true))
			{
				LineBreak *linebreak;
				if( m_pText->getLineBreakState()=="division")
					linebreak=new LineBreak_Div(m_pText->getTexts(),m_pText->getLineWidth());
				else if( m_pText->getLineBreakState()=="preservation")
					linebreak=new LineBreak_Pre(m_pText->getTexts(),m_pText->getLineWidth());
				linebreak->revert();
				if(linebreak->setWidth(atoi(argv[1].c_str())-1)==true)
				{
					m_pText->chgLineWidth(atoi(argv[1].c_str())-1);
					m_pText->prompt("The width is changed to "+argv[1]+" characters.");
				}
				else m_pText->alertError( string("Can't set width "+argv[1]));
				delete linebreak;
			}
			else if(argv[0]=="GUI")
			{
				if(argv[1]=="ON"&&m_pState->getGUIState()==false)m_pState->setGUIState(true);
				else if(argv[1]=="OFF"&&m_pState->getGUIState()==true)
				{
					GUI_Interface::exit();
					m_pState->setGUIState(false);
				}
				else throw InvalidArgumentException(arg);
			}
			else throw InvalidArgumentException(arg);
	}
	else if( cmd == "eliminate")
	{
		if(argCheck(argv.size(),1,1))
		{
			if(argv[0]=="empty")m_pText->eli_empty();
			else if(argv[0]=="head")m_pText->eli_head();
			else if(argv[0]=="tail")m_pText->eli_tail();
			else throw InvalidArgumentException(arg);
		}
	}
	else if( cmd == "compact")
	{
		if(argCheck(argv.size(),0,0))
			m_pText->compact();
	}
	else if( cmd == "spellcheck")
	{
		if(!m_pText->safeCheck(true)&&argCheck(argv.size(),0,1))
		{
			m_pSpellChecker->setTexts(m_pText->getTexts());
			if(argv.size()==1&&argv[0]=="suggestion")
				m_pSpellChecker->spellCheck(true);
			else if(argv.size()==0)
				m_pSpellChecker->spellCheck(false);
			else throw InvalidArgumentException(arg);
		}
	}
	else if( cmd == "renew")
	{
		if(StateMgr::getGUIState()==true)
		{
			m_pCursor->inputPrompt();
			m_pText->renewContext();
		}
	}
	else m_pText->alertError( string("Can't support command: <") + cmd + ">");

	}
	catch(WrongNumberOfArgumentsException e)
	{
		ostringstream oss;
		oss<<e.getname()<<"\n"<<"Wrong number of arguments\n argc="<<e.getargc();
		m_pText->alertError( oss.str() );
	}
	catch(InvalidArgumentException e)
	{
		ostringstream oss;
		oss<<e.getname()<<"\n arg="<<e.getarg();
		m_pText->alertError( oss.str() );
	}
	catch(InvalidLocationException e)
	{
		ostringstream oss;
		Location loc=e.getLocation();
		oss<<e.getname()<<"\n line="<<loc.getY()<<" row="<<loc.getX();
		m_pText->alertError( oss.str() );
	}

	m_pText->fixBoundary();
	
	if(StateMgr::getGUIState()==true)
	{
		m_pCursor->inputPrompt();
		m_pText->renewContext();
	}
	
	lastCmd=cmd;
	lastArg=arg;
}

void Input::setText(Text *t)
{
      m_pText = t;
}

void Input::setCursor(Cursor *c)
{
      m_pCursor = c;
}

void Input::setChecker(SpellChecker *sc)
{
      m_pSpellChecker = sc;
}

void Input::setStateMgr(StateMgr *s)
{
	m_pState=s;
}

bool Input::argCheck(int input,int ck1,int ck2)
{
	if(input<ck1||input>ck2)
	{
		throw WrongNumberOfArgumentsException(input,ck1,ck2);
//		return false;
	}
	return true;
}
