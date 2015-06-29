#include "Query.h"
#include <iostream>

Query::Query(string qstr,vector<string> *m_pTexts)
{
	int pos=0;
	if(qstr.find('*',pos)!=string::npos)
		fuzzyQuery(qstr,m_pTexts);
	else
		singleQuery(qstr,m_pTexts);
}

void Query::singleQuery(string qstr,vector<string> *m_pTexts)
{
   	string caps("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	string::size_type pos = 0;
	//uptolow for qstr
	while( (pos = qstr.find_first_of(caps, pos)) != string::npos )
		qstr[pos] = tolower( qstr[pos] );

	for(int i=0;i<(int)m_pTexts->size();i++)
	{
		string findstr=(*m_pTexts)[i];
		pos = 0;
		//uptolow for findstr
		while( (pos = findstr.find_first_of(caps, pos)) != string::npos )
			findstr[pos] = tolower( findstr[pos] );

		if(findstr.find(qstr)!=string::npos)find_loc.push_back(i);
	}
}

void Query::fuzzyQuery(string qstr,vector<string> *m_pTexts)
{
   	string caps("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	string::size_type pos = 0;
	//uptolow for qstr
	while( (pos = qstr.find_first_of(caps, pos)) != string::npos )
		qstr[pos] = tolower( qstr[pos] );
	while(qstr[0]=='*')qstr.erase(qstr.begin());
	while(qstr[qstr.size()-1]=='*')qstr.erase(qstr.end()-1);
	Tokener tok;
	tok.parsing(qstr,"*");
	
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
		if(isfind)find_loc.push_back(i);
	}
}

bool Query::fuzzyQuery(string qstr,string findstr)
{
   	string caps("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	string::size_type pos = 0;
	//uptolow for qstr
	while( (pos = qstr.find_first_of(caps, pos)) != string::npos )
		qstr[pos] = tolower( qstr[pos] );
	while(qstr[0]=='*')qstr.erase(qstr.begin());
	while(qstr[qstr.size()-1]=='*')qstr.erase(qstr.end()-1);
	Tokener tok;
	tok.parsing(qstr,"*");
	
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
	if(isfind)return true;
	else return false;
}

Query::~Query()
{
}


vector<int> Query::getAns()
{
	return find_loc;
}
