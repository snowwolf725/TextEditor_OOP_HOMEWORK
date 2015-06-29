#include "QueryWord.h"

QueryWord::QueryWord(string qstr,vector<string> *m_pTexts)
{
	int pos=0;
	if(qstr.find('*',pos)!=string::npos)
		fuzzyQuery(qstr,m_pTexts);
	else
		singleQuery(qstr,m_pTexts);
}

void QueryWord::singleQuery(string qstr,vector<string> *m_pTexts)
{
	TextLocationMapBuilder *builder=new TextLocationMapBuilder_Imp();
	TextLocationMap *m_pLocationMap;
//	builder->loadExclude(m_exWords);
	m_pLocationMap = builder->build( m_pTexts );
	
	vector<TextLocationMap::LocationSet>* locs;
	locs=m_pLocationMap->getLocations();
	vector<string>* words=m_pLocationMap->getWord();

	vector<string> query_text[m_pTexts->size()];	
	for(int j=0;j<(int)m_pTexts->size();j++)
	{
		//collect someline's words
		for(int i=0;i<(int)words->size();i++)
		{
			vector<Location> w_loc;
			w_loc=(*locs)[i];
			for(int a=0;a<(int)w_loc.size();a++)
			{
				if(w_loc[a].getY()==j)query_text[j].push_back((*words)[i]);
			}
		}
		
		//fuzzyquery to words
		for(int i=0;i<(int)query_text[j].size();i++)
		{
			if( qstr==query_text[j][i] )
			{
				find_loc.push_back(j);
				break;
			}
		}
	}
}

void QueryWord::fuzzyQuery(string qstr,vector<string> *m_pTexts)
{
	TextLocationMapBuilder *builder=new TextLocationMapBuilder_Imp();
	TextLocationMap *m_pLocationMap;
//	builder->loadExclude(m_exWords);
	m_pLocationMap = builder->build( m_pTexts );
	
	vector<TextLocationMap::LocationSet>* locs;
	locs=m_pLocationMap->getLocations();
	vector<string>* words=m_pLocationMap->getWord();

	vector<string> query_text[m_pTexts->size()];	
	for(int j=0;j<(int)m_pTexts->size();j++)
	{
		//collect someline's words
		for(int i=0;i<(int)words->size();i++)
		{
			vector<Location> w_loc;
			w_loc=(*locs)[i];
			for(int a=0;a<(int)w_loc.size();a++)
			{
				if(w_loc[a].getY()==j)query_text[j].push_back((*words)[i]);
			}
		}
		
		//fuzzyquery to words
		for(int i=0;i<(int)query_text[j].size();i++)
		{
			if( fuzzyQuery(qstr,query_text[j][i]) )
			{
				find_loc.push_back(j);
				break;
			}
		}
	}
}

bool QueryWord::fuzzyQuery(string qstr,string findstr)
{
   	string caps("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	string::size_type pos = 0;
	bool fuzzyinhead=false;
	//uptolow for qstr
	while( (pos = qstr.find_first_of(caps, pos)) != string::npos )
		qstr[pos] = tolower( qstr[pos] );
	if(qstr[0]=='*')fuzzyinhead=true;
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
	if(isfind && fuzzyinhead)
		return true;
	else if(isfind && !fuzzyinhead)
	{
		if((pos = findstr.find_first_of(caps, pos)) != 0)
			return false;
		return true;
	}
	else return false;
}

QueryWord::~QueryWord()
{
}


vector<int> QueryWord::getAns()
{
	return find_loc;
}
