#include "SpellChecker.h"

SpellChecker::SpellChecker(Display *d):m_pDict(NULL),m_pDisplay(d)
{
	
}

SpellChecker::~SpellChecker()
{
	release();
}

void SpellChecker::setTexts(vector<string> *t)
{
	m_pTexts=t;
}

void SpellChecker::release()
{
	if( m_pDict != NULL ) {
		delete m_pDict;
		m_pDict = NULL;
	}
	_dictload=false;
}

void SpellChecker::prompt(string msg)
{
	m_pDisplay->drawText( msg );
}

void SpellChecker::alertError(string msg)
{
	const static string ERROR_PREFIX = "[ERROR]";
	prompt( ERROR_PREFIX + msg );
}

bool SpellChecker::loadDict(string dictname)
{
	ifstream fin;
	fin.open( dictname.c_str() );
	if( !fin ) {
		alertError("Can't open this file.");
		return false;
	}
	
	release();	// release older resources

	m_pDict = new vector<string>;
	string temp;
	while(!fin.eof() )  {
		getline(fin, temp);
		
		// case insensitive
	   	string caps("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		string::size_type pos = 0;
		while( (pos = temp.find_first_of(caps, pos)) != string::npos )
			temp[pos] = tolower( temp[pos] );
		
       static const int CRLF = 0x0D;
       if( temp.size() > 0 && temp[temp.size()-1] == CRLF )
        	temp.erase( temp.size()-1 );
		m_pDict->push_back(temp);
	}

	fin.close();
	_dictload=true;
	return true;
}

bool SpellChecker::spellCheck(bool sugges)
{
	if(!_dictload)loadDict("dictionary.txt");
	
	ostringstream oss;
	TextLocationMapBuilder *builder=new TextLocationMapBuilder_Imp();
	TextLocationMap *m_pLocationMap;
	//builder->loadExclude(m_exWords);
	m_pLocationMap = builder->build( m_pTexts ,false);
	TextLocationMap::ErrorSet *result 
        = m_pLocationMap->getErrorSet( m_pDict );
	
	//count misspell words
	int count=0;
	for(int i=0;i<(int)result->size();i++)
	{
		pair<string,LocationSet> errorword;
		errorword=errorword=(*result)[i];;
		TextLocationMap::LocationSet result_loc=errorword.second;
		count += result_loc.size();
	}
	oss<<"Find "<< count << " misspell words!!"<<endl;
	
	for(int i=0;i<(int)result->size();i++)
	{
		string msg;
		TextLocationMap::LocationSet result_loc;

		pair<string,LocationSet> errorword;
		errorword=(*result)[i];
		string word=errorword.first;
		
		//print locations
		result_loc=errorword.second;
	    for(unsigned int j=0; j<result_loc.size()-1;j++)
			msg += result_loc[j].toString() + ", ";

		msg += result_loc[ result_loc.size()-1 ].toString();
		msg += word.c_str();
		if(sugges)
		{
			string sug=findsugges(word);
			if(sug!="")msg = msg + " => " + findsugges(word);
		}
		oss<< msg.c_str() <<endl;
	}
	prompt(oss.str().c_str());
	if(count==0)return false;
	else return true;
}

string SpellChecker::findsugges(string word)
{
	string result;
	for(int i=0;i<(int)m_pDict->size();i++)
	{
		if((*m_pDict)[i].size()==word.size())
		{
			int diff=0;
			for(int j=0;j<(int)word.size();j++)
				if(diff>=2)break;
				else if(word[j]!=(*m_pDict)[i][j])diff++;
			if(diff==1)
				result += (*m_pDict)[i]+",";
		}
		else
		{
			bool diff=false;
			for(int j=0;j<(int)word.size();j++)
				if(word[j]!=(*m_pDict)[i][j])
				{
					diff=true;
					break;
				}
			if(diff==false)
			{
				if((*m_pDict)[i].size()<=word.size()+4)
					result += (*m_pDict)[i]+",";
			}
		}
	}
	
	//remove last ','
	if(result!="")result.erase(result.end()-1);
	return result;
}

vector<string> *SpellChecker::getDict()
{
	return m_pDict;
}

void SpellChecker::setDict(vector<string> *dict)
{
	(*m_pDict)=*dict;
}
