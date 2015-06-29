#include <fstream>
#include <sstream>
#include <algorithm>
#include "Text_Imp.h"
#include <iostream>

using namespace std;

Text_Imp::Text_Imp() : m_pDisplay(NULL), m_pTexts(NULL), m_exWords(NULL),_linestate("preservation")
{
	m_pCursor=NULL;
	fileload=false;
	mode=0;
}

Text_Imp::~Text_Imp()
{
	release();
	releaseOther();
}

void Text_Imp::setMode(int newmode)
{
	//if(mode!=newmode)
	if(StateMgr::getModeState()!=newmode)
	{
		//mode=newmode;
		StateMgr::setModeState(newmode);
		if(newmode==0)
		{
			m_pCursor->setX(toPhyLoc( m_pCursor->getX(),m_pCursor->getY()) );
			prompt("set mode to char mode");
		}
		else if(newmode==1)
		{
			m_pCursor->setX(toLogLoc(m_pCursor->getX(),m_pCursor->getY()) );
			prompt("set mode to word mode");
		}
	}
}

int Text_Imp::getMode()
{
	return StateMgr::getModeState();
//	return mode;
}

int Text_Imp::safeCheck(bool showmsg)
{
	if(!fileload)
	{
		if(showmsg)
			prompt("No file is specified");
		return 1;
	}
	else return 0;
}

void Text_Imp::release()
{
	if( m_pTexts != NULL ) {
		delete m_pTexts;
		m_pTexts = NULL;
	}
	fileload=false;
}

void Text_Imp::releaseOther()
{
	if( m_exWords != NULL ) {
		delete m_exWords;
		m_exWords = NULL;
	}
}

void Text_Imp::setDisplay(Display *d)
{
	m_pDisplay = d;
}

void Text_Imp::setCursor(Cursor *c)
{
	m_pCursor = c;
}

void Text_Imp::alertError(string msg)
{
	const static string ERROR_PREFIX = "[ERROR]";
	prompt( ERROR_PREFIX + msg );
}

void Text_Imp::prompt(string msg)
{
	m_pDisplay->drawText( msg );
}

void Text_Imp::updateContext(string context)
{
	m_pDisplay->drawContext( context );
}

void Text_Imp::newFile()
{
	release();	// release older resources
	m_pTexts = new vector<string>;
	
	m_pCursor->setX(0);
	m_pCursor->setY(0);
	m_pCursor->setPage(0);
	m_pCursor->setTotolLine(m_pTexts->size()-1);
	m_pCursor->setTotolPage(m_pTexts->size()/20);

	fileload=true;
}

void Text_Imp::readFile(string filename)
{
	ifstream fin;
	fin.open( filename.c_str() );
	if( !fin ) {
		alertError("Can't open this file.");
		return;
	}
	
	release();	// release older resources

	m_pTexts = new vector<string>;
	string temp;
	while(!fin.eof() )  {
		getline(fin, temp);
       static const int CRLF = 0x0D;
       if( temp.size() > 0 && temp[temp.size()-1] == CRLF )
        	temp.erase( temp.size()-1 );
		m_pTexts->push_back(temp);
	}

	m_pCursor->setX(0);
	m_pCursor->setY(0);
	m_pCursor->setPage(0);
	m_pCursor->setTotolLine(m_pTexts->size()-1);
	m_pCursor->setTotolPage(m_pTexts->size()/20);

	prompt("Read ok.");
	fin.close();
	fileload=true;
}

void Text_Imp::saveFile(string filename)
{
	if(safeCheck(true))return;
	ofstream fout;
	fout.open( filename.c_str() );
	if( !fout ) {
		alertError("Can't open this file.");
		return;
	}

	for(unsigned int i = 0 ; i<m_pTexts->size() ; i++) {
		if(i!=m_pTexts->size()-1)
			fout << (*m_pTexts)[i] << endl;
		else
			fout << (*m_pTexts)[i];
	}
	
	fout.close();
	prompt( "saveFile..." );
}

void Text_Imp::exclude(string filename)
{
	ifstream fin;
	fin.open( filename.c_str() );
	if( !fin ) {
		alertError("Can't open this file.");
		return;
	}
	
	// release older resources
	if(m_exWords!=NULL)delete m_exWords;

	m_exWords = new vector<string>;
	string temp;
	while(!fin.eof() )  {
		getline(fin, temp);
		
       static const int CRLF = 0x0D;
       if( temp.size() > 0 && temp[temp.size()-1] == CRLF )
        	temp.erase( temp.size()-1 );
		
		m_exWords->push_back(temp);
	}

	prompt("Read ok.");
	fin.close();
}

void Text_Imp::insertfile(string filename)
{
	ifstream fin;
	fin.open( filename.c_str() );
	if( !fin ) {
		alertError("Can't open this file.");
		return;
	}
	
	string temp;
	while(!fin.eof() )  {
		getline(fin, temp);
		
       static const int CRLF = 0x0D;
       if( temp.size() > 0 && temp[temp.size()-1] == CRLF )
        	temp.erase( temp.size()-1 );
		
		m_pTexts->push_back(temp);
	}

	m_pCursor->setTotolLine(m_pTexts->size()-1);
	m_pCursor->setTotolPage(m_pTexts->size()/20);

	prompt("Read ok.");
	fin.close();
}

void Text_Imp::query(Tokener tok,string m_query)
{
	if(safeCheck(true))return;
	
	Multiquery myquery(this->m_pTexts,tok);
	if(myquery.check()!=-1)
	{
		ostringstream oss;
		vector<int> ans=myquery.getAns();
		oss<<"Requested query: "<<m_query<<endl;
		oss<<m_query<<" ( "<<ans.size()<<" )"<< " lines match"<<endl;
		for(int i=0;i<(int)ans.size();i++)
			oss<<displayLine(ans[i],1).c_str();
		prompt(oss.str());
	}
	else alertError("query string illegal~!!");
}

void Text_Imp::queryWord(Tokener tok,string m_query)
{
	if(safeCheck(true))return;

	Multiquery myquery(this->m_pTexts,tok,1);
	if(myquery.check()!=-1)
	{
		ostringstream oss;
		vector<int> ans=myquery.getAns();
		prompt("Requested query: "+m_query);
		oss<<m_query<<" ( "<<ans.size()<<" )"<< " lines match"<<endl;
		for(int i=0;i<(int)ans.size();i++)
			oss<<displayLine(ans[i],1).c_str();
		prompt(oss.str());
	}
	else alertError("query string illegal~!!");
}

void Text_Imp::search(string target)
{
	if(safeCheck(true))return;

	TextLocationMapBuilder *builder=new TextLocationMapBuilder_Imp();
	TextLocationMap *m_pLocationMap;
	builder->loadExclude(m_exWords);
	m_pLocationMap = builder->build( m_pTexts );
	
	TextLocationMap::LocationSet *result 
        = m_pLocationMap->getLocationSet( target );

    string msg = "The result of \"search " + target + "\": ";
    if( result == NULL ) {
        prompt( msg + "none" );
        return;
    }
    
    for(unsigned int i=0; i<result->size()-1;i++)
		msg += (*result)[i].toString() + ", ";

	msg += (*result)[ result->size()-1 ].toString();
    prompt( msg );
}

void Text_Imp::search_SingleChar(string target)
{
	ostringstream msg;
	msg << "The result of \"search " << target << "\": ";
	
   	string caps("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	string::size_type pos = 0;
	//uptolow for target
	while( (pos = target.find_first_of(caps, pos)) != string::npos )
		target[pos] = tolower( target[pos] );
	
	bool isfind=false;
	for(unsigned int i = 0 ; i<m_pTexts->size(); i++) 
	{
		string line=(*m_pTexts)[i];
		//uptolow for target
		pos=0;
		while( (pos = line.find_first_of(caps, pos)) != string::npos )
			line[pos] = tolower( line[pos] );

		pos=0;
		while((pos = line.find(target,pos)) != string::npos)
		{
			msg<< "(" << i+1 << "," << pos+1 << ")";
			pos++;
			isfind=true;
		}
	}
	if(!isfind)
	{
		msg<<"none";
		prompt( msg.str() );
	}
	else prompt( msg.str() );

}

void Text_Imp::search_FuzzyChar(string target)
{
	ostringstream msg;
	msg << "The result of \"search " << target << "\": ";
	
   	string caps("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	string::size_type pos = 0;
	//uptolow for target
	while( (pos = target.find_first_of(caps, pos)) != string::npos )
		target[pos] = tolower( target[pos] );

	bool isfind_t=false;
	bool fuzzyinhead=false;
	if(target[0]=='*')fuzzyinhead=true;
	while(target[0]=='*')target.erase(target.begin());
	while(target[target.size()-1]=='*')target.erase(target.end()-1);
	Tokener tok;
	tok.parsing(target,"*");
		
	for(int i=0;i<(int)m_pTexts->size();i++)
	{
		string findstr=(*m_pTexts)[i];
		bool isfind=true;
		pos = 0;
		//uptolow for findstr
		while( (pos = findstr.find_first_of(caps, pos)) != string::npos )
			findstr[pos] = tolower( findstr[pos] );
	
		pos=0;
		for(int j=0;j<(int)tok.size();j++)
		{
			if(findstr.find(tok[j],pos)!=string::npos)
				pos=tok[j].length()+pos;
			else
			{
				isfind=false;
				break;
			}
		}
			
		if(isfind)
		{
			isfind_t=true;
			pos=findstr.find(tok[0],pos);
			if(fuzzyinhead)
				msg<< "(" << i+1 << "," << 1 << ")";
			else
				msg<< "(" << i+1 << "," << pos+1 << ")";
		}
	}
	if(!isfind_t)
	{
		msg<<"none";
		prompt( msg.str() );
	}
	else prompt(msg.str());
}

void Text_Imp::search_Char(string target)
{
	if(safeCheck(true))return;

	if(target.find('*',0)!=string::npos)
		search_FuzzyChar(target);
	else
		search_SingleChar(target);
}

void Text_Imp::display(string arg)
{
	if(safeCheck(true))return;
	if(arg=="")
	{
		ostringstream oss;
		for(unsigned int i = 0 ; i<m_pTexts->size() -1 ; i++) {
			oss.width(3);
			oss << i+1 << ": " << (*m_pTexts)[i] << endl;
		}

		//for the last line
		oss.width(3);
		oss << m_pTexts->size() << ": " << (*m_pTexts)[m_pTexts->size()-1];
		
		if(StateMgr::getGUIState()==true)
			updateContext(oss.str());
		else
			prompt( oss.str() );
	}
	else if(arg=="line")
	{
		prompt( displayLine(m_pCursor->getY()).c_str() );
	}
	else if(arg=="page")
	{
		//need to modify
		displayPage();
	}
	else throw InvalidArgumentException(arg);
}

int Text_Imp::setPos(int newYpos,int newXpos)
{
	if(safeCheck(true))return 1;
	//need to modify for Ypos
	try{
		
	if(newXpos<-1||newYpos<=-1||newYpos>m_pCursor->GetTotolLine()||
		newXpos>colOfLine(newYpos))
	{
		Location loc(newXpos,newYpos);
		throw InvalidLocationException(loc);
//		prompt("The location can't be reached");
//		return 1;
	}
	else 
	{
		m_pCursor->setPos(newYpos,newXpos);
		return 0;
	}
	
	}
	catch(InvalidLocationException e)
	{
		ostringstream oss;
		Location loc=e.getLocation();
		oss<<e.getname()<<"\n line="<<loc.getY()<<" row="<<loc.getX();
		alertError( oss.str() );
		return 1;
	}
}

int Text_Imp::setPos_Char(int newYpos,int newXpos)
{
	if(safeCheck(true))return 1;
	//need to modify for Ypos
	if(newXpos<-1||newYpos<=-1||newYpos>m_pCursor->GetTotolLine()||
		newXpos>colOfLine_Char(newYpos))
	{
		Location loc(newXpos,newYpos);
		throw InvalidLocationException(loc);
//		prompt("The location can't be reached");
//		return 1;
	}
	else
	{
		m_pCursor->setPos(newYpos,newXpos);
		return 0;
	}
}

string Text_Imp::displayLine(int lineno,int type)
{
	ostringstream oss;
	if(type==0)
	{
		oss.width(3);
		oss << lineno+1 << ": " << (*m_pTexts)[lineno]<<endl;
	}
	else if(type==1)
		oss<< "(" <<  lineno+1 << ") " << (*m_pTexts)[lineno]<<endl;
	return oss.str();
}

void Text_Imp::displayPage()
{
	ostringstream oss;
//	for(int i = 20 * pageno ;i<(int)m_pTexts->size() && i<(int)20*(pageno+1); i++) {
//		oss.width(3);
//		oss << i << ": " << (*m_pTexts)[i];
//	}
	if(m_pCursor->getY()+20>m_pCursor->GetTotolLine())
	{
		int i;
		if((m_pCursor->GetTotolLine()-19)<0) i=0;
		else i=m_pCursor->GetTotolLine()-19;
		
		for(;i<=m_pCursor->GetTotolLine()-1;i++)
		{
			oss.width(3);
			oss << i+1 << ": " << (*m_pTexts)[i] << endl;
		}
		oss.width(3);
		oss << i+1 << ": " << (*m_pTexts)[i];
	}
	else if(m_pCursor->getY()<0)
	{
		int i;
		for(i=0;i<=18&&i<=m_pCursor->GetTotolLine()-1;i++)
		{
			oss.width(3);
			oss << i+1 << ": " << (*m_pTexts)[i] << endl;
		}
		oss.width(3);
		oss << i+1 << ": " << (*m_pTexts)[i];
		m_pCursor->setY(0);
	}
	else
	{
		int i;
		for(i=m_pCursor->getY();i<=m_pCursor->GetTotolLine()-1 && i<m_pCursor->getY()+19;i++)
		{
			oss.width(3);
			oss << i+1 << ": " << (*m_pTexts)[i] << endl;
		}
		oss.width(3);
		oss << i+1 << ": " << (*m_pTexts)[i] << endl;
	}
	prompt( oss.str() );
}

void Text_Imp::displayPLine()
{
	if(safeCheck(true))return;
	if(m_pCursor->getY()>=1)
	{
		//display and set ypos
		prompt( displayLine(m_pCursor->getY()-1).c_str() );
		m_pCursor->setY(m_pCursor->getY()-1);
		//set xpos
		int wordofline=colOfLine(m_pCursor->getY());
		if(m_pCursor->getX()>wordofline)
			m_pCursor->setX(wordofline);
	}
	else	prompt( displayLine(m_pCursor->getY()).c_str() );
}

void Text_Imp::displayPPage()
{
	if(safeCheck(true))return;
	//m_pDisplay->subPageno();
	m_pCursor->setY(m_pCursor->getY()-20);
	displayPage();
	//set xpos
	int wordofline=colOfLine(m_pCursor->getY());
	if(m_pCursor->getX()>wordofline)
		m_pCursor->setX(wordofline);
}

void Text_Imp::displayNLine()
{
	if(safeCheck(true))return;
	if(m_pCursor->getY()!=m_pCursor->GetTotolLine())
	{
		prompt( displayLine(m_pCursor->getY()+1).c_str() );
		m_pCursor->setY(m_pCursor->getY()+1);
		//set xpos
		int wordofline=colOfLine(m_pCursor->getY());
		if(m_pCursor->getX()>wordofline)
			m_pCursor->setX(wordofline);
	}
	else	prompt( displayLine(m_pCursor->getY()).c_str() );
}

void Text_Imp::displayNPage()
{
	if(safeCheck(true))return;
	m_pCursor->addPageno();
	//m_pDisplay->setYpos(m_pDisplay->GetYpos()+20);
	displayPage();
	//set xpos
	int wordofline=colOfLine(m_pCursor->getY());
	if(m_pCursor->getX()>wordofline)
		m_pCursor->setX(wordofline);
}

int Text_Imp::colOfLine(int lineno)
{
	if(lineno<=-1)return -1;
	else
	{
		Tokener slit;
		slit.parsing((*m_pTexts)[lineno]);
		return slit.size()-1;
//		return wordsOfCline->size()-1;
	}
}

int Text_Imp::colOfLine_Char(int lineno)
{
	if(lineno<=-1)
		return -1;
	else
	{
		string tmp=(*m_pTexts)[lineno];
		return tmp.length()-1;
	}
}

void Text_Imp::map()
{
	if(safeCheck(true))return;
    // build text location map
	TextLocationMapBuilder *builder=new TextLocationMapBuilder_Imp();
	TextLocationMap *m_pLocationMap;
	builder->loadExclude(m_exWords);
	m_pLocationMap = builder->build( m_pTexts );
    
	OutputToDisplay out(m_pDisplay);
	prompt(m_pLocationMap->dump());
}

int Text_Imp::toPhyLoc(int xpos,int ypos)
{
	int i,pos;
	string line=(*m_pTexts)[ypos];
	const string filt_elems( "\",.;:!?)(\\/\0x0D\n" );
	if(xpos==-1)return -1;
	else if(xpos==0)return 0;
	
	for(i=0;i<(int)line.length()-1&&xpos>=0;i++)
	{
		if(line[i]!=' '&&line[i]!='\t')
			{
				pos=i;
				xpos--;
				while(line[i]!=' '&&line[i]!='\t'&&(i<(int)line.length()-1))
					i++;
			}
	}
	return pos;
}

int Text_Imp::toLogLoc(int xpos,int ypos)
{
	int i,Ppos=-1;
	const string filt_elems( "\",.;:!?)(\\/\0x0D\n" );
	if(xpos==-1)return -1;
	else if(xpos==0)return 0;
	string line=(*m_pTexts)[ypos];
	
	for(i=0;i<=xpos;i++)
	{
		if(line[i]!=' '||line[i]!='\t')
		{
			while(i<=xpos&&(line[i]!=' '||line[i]!='\t'))
				i++;
			Ppos++;
		}
		else
		{
			while(i<=xpos&&(line[i]==' '||line[i]=='\t'))
				i++;
		}
	}
	return Ppos;
}

void Text_Imp::insert_Char(string insert_string,int x,int y)
{
	if(safeCheck(true))return;
	if(x<-1||y<-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine_Char(y))
	{
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't insert this word.");
//		return;
	}
	
	if(y==-1)
	{
		if(m_pTexts->size()==0)
		{
			string newline;
			m_pTexts->push_back(newline);
		}
		string &line=(*m_pTexts)[0];
		if(x==0||x==-1)
			line=insert_string+line;
		else line=line.substr(0,x)+insert_string+line.substr(x,line.length());
	}
	else
	{
		string &line=(*m_pTexts)[y];
		if(x==0||x==-1)
			line=insert_string+line;
		else line=line.substr(0,x)+insert_string+line.substr(x,line.length());
	}
}

void Text_Imp::insert(string arg,int x,int y)
{
	if(safeCheck(true))return;
	if(x<=-1||y<=-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine(y))
	{
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't insert this word.");
//		return;
	}
	int insert_pos=toPhyLoc(x,y);
	string &line=(*m_pTexts)[y];
	if(insert_pos==0)
		line=arg+" "+line;
	else line=line.substr(0,insert_pos-1)+" " +arg+" "+line.substr(insert_pos,line.length());
}

void Text_Imp::delWord(int x,int y)
{
	if(safeCheck(true))return;
	if(x<=-1||y<=-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine(y))
	{
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't del this word.");
//		return;
	}	
	string &line=(*m_pTexts)[y];
	Tokener count;
	count.parsing((*m_pTexts)[y]);
	if(count.size()==0)
		string("Can't del the word.");
	else if(count.size()-1==0)
		line="";
	else
	{
		string &line=(*m_pTexts)[y];
		int del_pos_begin=toPhyLoc(x,y);
		int del_pos_end=toPhyLoc(x+1,y);
		if(x==colOfLine(y))del_pos_end=toPhyLoc(x,y);
		if(del_pos_begin==0) line=line.substr(del_pos_end,line.length());
		else if(del_pos_begin==del_pos_end)line=line.substr(0,del_pos_begin);
		else line=line.substr(0,del_pos_begin)+line.substr(del_pos_end,line.length());
	}
}

void Text_Imp::delChar(int x,int y)
{
	if(safeCheck(true))return;
	if(x<=-1||y<=-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine_Char(y))
	{
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't del this char.");
//		return;
	}
	
	string &line=(*m_pTexts)[y];
	line.erase(line.begin()+x);
	
	//check bounder
	if(x>colOfLine_Char(y))
		m_pCursor->setX(colOfLine_Char(y));
}

Location Text_Imp::tagWord(int xpos,int ypos)
{
	Location tag(-1,-1);
	int i;
	string line=(*m_pTexts)[ypos];
	if(xpos==-1)return tag;
	
	for(i=0;i<(int)line.length()&&xpos>=0;i++)
	{
		if(line[i]!=' '&&line[i]!='\t')
			{
				tag.setX(i);
				xpos--;
				while(line[i]!=' '&&line[i]!='\t'&&(i<(int)line.length()))
					i++;
				tag.setY(i);
			}
	}
	return tag;
}

bool Text_Imp::copyWord(int x,int y)
{
	if(safeCheck(true))return false;
	if(x<=-1||y<=-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine(y))
	{
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't copy this word.");
//		return false;
	}
	Location tag=tagWord(x,y);
	if(tag.getX()!=-1&&tag.getY()!=-1)
	{
		copy_word=(*m_pTexts)[y].substr(tag.getX(),tag.getY()-tag.getX());
		prompt("copy '" + copy_word + "'");
		return true;
	}
	else return false;
}

bool Text_Imp::copyChar(int x,int y)
{
	if(safeCheck(true))return false;
	if(x<=-1||y<=-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine_Char(y))
	{//check bound
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't copy this Char.");
//		return false;
	}
	string &line=(*m_pTexts)[y];
	copy_word=line[x];
	prompt("copy '" + copy_word + "'");
	return true;
}

bool Text_Imp::cutWord(int x,int y)
{
	if(safeCheck(true))return false;
	if(x<=-1||y<=-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine(y))
	{
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't copy this word.");
//		return false;
	}
	Location tag=tagWord(x,y);
	if(tag.getX()!=-1&&tag.getY()!=-1)
	{
		//copy word
		copy_word=(*m_pTexts)[y].substr(tag.getX(),tag.getY()-tag.getX());
		
		//del word
		string &line=(*m_pTexts)[y];
		int del_pos_begin=toPhyLoc(x,y);
		int del_pos_end=toPhyLoc(x+1,y);
		if(x==colOfLine(y))del_pos_end=toPhyLoc(x,y);
		if(del_pos_begin==0) line=line.substr(del_pos_end,line.length());
		else if(del_pos_begin==del_pos_end)line=line.substr(0,del_pos_begin);
		else line=line.substr(0,del_pos_begin)+line.substr(del_pos_end,line.length());
				
		prompt("cut '" + copy_word + "'");
		return true;
	}
	else return false;
}

bool Text_Imp::cutChar(int x,int y)
{
	if(safeCheck(true))return false;
	if(x<=-1||y<=-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine_Char(y))
	{//check bound
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't copy this Char.");
//		return false;
	}
	string &line=(*m_pTexts)[y];
	copy_word=line[x];
	line.erase(line.begin()+x);
	prompt("cut '" + copy_word + "'");
	return true;
}

bool Text_Imp::pasteWord(int x,int y)
{
	if(safeCheck(true))return false;
	if(x<=-1||y<=-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine(y))
	{
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't paste this word.");
//		return false;
	}
	Location pasteloc(x,y);
	prompt("paste '" + copy_word + "' at "+pasteloc.toString());
	return modifyWord(copy_word,x,y);
}

bool Text_Imp::pasteChar(int x,int y)
{
	if(safeCheck(true))return false;
	if(x<=-1||y<=-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine_Char(y))
	{//check bound
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't paste this Char.");
//		return false;
	}
	
	string& tmp=(*m_pTexts)[y];
	tmp[x]=copy_word[0];
	Location pasteloc(x,y);
	prompt("paste '" + copy_word + "' at "+pasteloc.toString());
	return true;
}

bool Text_Imp::modifyChar(string arg,int x,int y)
{
	if(safeCheck(true))return false;
	if(x<=-1||y<=-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine_Char(y))
	{
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't modify this word.");
//		return false;
	}
	
	string &line=(*m_pTexts)[y];
	line=line.substr(0,x)+arg+line.substr(x+1,line.length()-x+1);
	return true;
}

bool Text_Imp::modifyWord(string arg,int x,int y)
{
	if(safeCheck(true))return false;
	if(x<=-1||y<=-1||y>m_pCursor->GetTotolLine()+1||x>colOfLine(y))
	{
		Location loc(x,y);
		throw InvalidLocationException(loc);
//		alertError("Can't modify this word.");
//		return false;
	}
	Location tag=tagWord(x,y);
	if(tag.getX()!=-1&&tag.getY()!=-1)
	{
		string &tmp=(*m_pTexts)[y];
		tmp=tmp.substr(0,tag.getX())+arg+tmp.substr(tag.getY(),tmp.length()-tag.getY());
		return true;
	}
	else return false;
}

bool Text_Imp::replaceString(string arg1,string arg2)
{
	if(safeCheck(true))return false;
	
	for(int i=0;i<(int)m_pTexts->size();i++)
	{
		string::size_type pos = 0;
		string &line=(*m_pTexts)[i];
		while((pos=line.find(arg1,pos+arg2.size()))!=string::npos)
			line=line.substr(0,pos)+arg2+
			     line.substr(pos+arg1.size(),line.length()-pos+arg1.size());
	}
	return true;
}

bool Text_Imp::replaceWord(string arg1,string arg2)
{
	if(safeCheck(true))return false;

	TextLocationMapBuilder *builder=new TextLocationMapBuilder_Imp();
	TextLocationMap *m_pLocationMap;
	builder->loadExclude(m_exWords);
	m_pLocationMap = builder->build( m_pTexts );
	
	TextLocationMap_Imp::LocationSet *result 
		= m_pLocationMap->getLocationSet( arg1 );
	
	for(unsigned int i=0; i<result->size();i++)
		modifyWord(arg2,(*result)[i].getX(),(*result)[i].getY());
	return true;
}

void Text_Imp::deleteRow(int row)
{
	if (m_pTexts->size()==1)
	{
		m_pTexts->erase(m_pTexts->begin()+row-1);
		m_pTexts->push_back(string(""));
	}
	else if(row <= (int)m_pTexts->size()&& row >0)
	{
		m_pTexts->erase(m_pTexts->begin()+row-1);
		m_pCursor->setTotolLine(m_pTexts->size()-1);
	}
	else alertError("Can't delete this row.");
}

void Text_Imp::eli_empty()
{
	for(int i=0;i<(int)m_pTexts->size();i++)
		if((*m_pTexts)[i].size()==0)m_pTexts->erase(m_pTexts->begin()+i);
	prompt("Empty lines elimination success!!");
}

void Text_Imp::eli_head()
{
	for(int i=0;i<(int)m_pTexts->size();i++)
	{
		string &line=(*m_pTexts)[i];
		while(line[0]==' ')
			line.erase(line.begin());
	}
	prompt("Heading spaces elimination success!!");
}

void Text_Imp::eli_tail()
{
	for(int i=0;i<(int)m_pTexts->size();i++)
	{
		string &line=(*m_pTexts)[i];
		while(line[line.size()-1]==' ')
			line.erase(line.end()-1);
	}
	prompt("Tailing spaces elimination success!!");
}

void Text_Imp::compact()
{
	for(int i=0;i<(int)m_pTexts->size();i++)
	{
		string &line=(*m_pTexts)[i];
/*		string::size_type pos=0;
		while((pos=line.find_first_of(' '))!=string::npos&&line[pos+1]==' ')
			line.erase(line.begin()+pos);*/
		for(int j=0;j<(int)line.size();j++)
			while(line[j]==' '&&line[j+1]==' ')
			{
				line.erase(line.begin()+j+1);
			}
	}

	prompt("Redundant spaces compaction success!!");
}

vector<string> *Text_Imp::getTexts()
{
	return m_pTexts;
}

void Text_Imp::chgLineBreakState(string newstate)
{
	_linestate=newstate;
}

string Text_Imp::getLineBreakState()
{
	return _linestate;
}

void Text_Imp::chgLineWidth(int width)
{
	_width=width;
}

int Text_Imp::getLineWidth()
{
	return _width;
}

void Text_Imp::fixBoundary()
{
	if(safeCheck(false))return;
	//update TotolLine
	m_pCursor->setTotolLine(m_pTexts->size()-1);
	
	//fix boundary
	int Xpos=m_pCursor->getX();
	int Ypos=m_pCursor->getY();
	
	if(getMode()==0)
	{
		//fix ypos
		int ybound=m_pCursor->GetTotolLine();
		if(Ypos<=-1)m_pCursor->setY(-1);
		if(Ypos>ybound)m_pCursor->setY(ybound);
		
		//fix xpos
		Ypos=m_pCursor->getY();
		if(Ypos>=0)
		{
			int xbound=colOfLine_Char(Ypos);
			if(Xpos<-1)m_pCursor->setX(-1);
			if(Xpos>xbound)m_pCursor->setX(xbound);
		}
		else m_pCursor->setX(-1);
	}
	else if(getMode()==1)
	{
		//fix ypos
		int ybound=m_pCursor->GetTotolLine();
		if(Ypos<=-1)if(Ypos<=-1)m_pCursor->setY(-1);
		if(Ypos>ybound)m_pCursor->setY(ybound);
		
		//fix xpos
		Ypos=m_pCursor->getY();
		if(Ypos>=0)
		{
			int xbound=colOfLine(Ypos);		
			if(Xpos<-1)m_pCursor->setX(-1);
			if(Xpos>xbound)m_pCursor->setX(xbound);
		}
		else m_pCursor->setX(-1);
	}
}

void Text_Imp::setTexts(vector<string> *Texts)
{
	(*m_pTexts)=*Texts;
}

vector<string> *Text_Imp::getExWords()
{
	return m_exWords;
}

void Text_Imp::setExWords(vector<string> *exWords)
{
	(*m_exWords)=*exWords;
}

int Text_Imp::getWidth()
{
	return _width;
}

void Text_Imp::setWidth(int width)
{
	_width=width;
}


int Text_Imp::getFileState()
{
	return fileload;
}

void Text_Imp::setFileState(int fload)
{
	fileload=fload;
}

void Text_Imp::renewContext()
{
	ostringstream oss;
	if(m_pTexts!=NULL&&m_pTexts->size()>0)
	{
		for(unsigned int i = 0 ; i<m_pTexts->size() -1 ; i++) {
			oss << (*m_pTexts)[i] << endl;
		}
	
		//for the last line
		oss << (*m_pTexts)[m_pTexts->size()-1];
	}
	updateContext(oss.str());
}

