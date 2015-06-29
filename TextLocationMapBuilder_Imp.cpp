#include "TextLocationMapBuilder_Imp.h" // class's header file
#include <iostream>
#include <algorithm>
using namespace std;

const string TextLocationMapBuilder_Imp::filt_elems( "\",.;:!?)(\\/\0x0D\n" );

// class constructor
TextLocationMapBuilder_Imp::TextLocationMapBuilder_Imp()
{
}

// class destructor
TextLocationMapBuilder_Imp::~TextLocationMapBuilder_Imp()
{
}

TextLocationMap*
TextLocationMapBuilder_Imp::
build(vector<string>* lines_of_text,bool suffix)
{
    vector<string> words;
    vector<Location> locs;
    
    // step 1
    separate_words(lines_of_text, &words, &locs);
    // step 2
    filter_text( &words );
    // step 3
    if(suffix) suffix_text( &words );
    // step 4
    strip_cap( &words );
    // step 5
    exclude_text( &words );
    // step 6
    sort_text( &words, &locs);

    // step 7 , build the entire product
	return build_location_map( &words, &locs );
}

void
TextLocationMapBuilder_Imp::
separate_words(vector<string>* lines_of_text, vector<string>* words, vector<Location>* locs )
{
    /* 以空白分隔開每一個 word */ 
	int pos_f=0;
	for(unsigned int line_pos = 0; line_pos < lines_of_text->size(); line_pos++ )
	{
		int word_pos = 0;
		string textline = (*lines_of_text)[ line_pos ];
		
		string::size_type pos = 0, prev_pos = 0;
		
		//fix for linebreak
		//if about line is linebreak
		if(pos_f!=0)
		{
			textline.erase(textline.begin(),textline.begin()+pos_f);
			pos_f=0;
		}
		//if this line is linebreak
		if(textline[textline.size()-1]=='-'&&line_pos!=lines_of_text->size()-1)
		{
			string nextline = (*lines_of_text)[ line_pos+1 ];
			textline.erase(textline.size()-1);
			pos_f = nextline.find_first_of( ' ', 0 );
			textline=textline+nextline.substr(0,pos_f);
		}
		
		while( ( pos = textline.find_first_of( ' ', pos )) != string::npos )
		{
			words->push_back( textline.substr( prev_pos, pos - prev_pos ));
			locs->push_back( Location(word_pos, line_pos) );

			word_pos++; pos++; prev_pos = pos;
		}

		words->push_back( textline.substr( prev_pos, pos - prev_pos ));
		locs->push_back( Location( word_pos, line_pos ));
	}    
}

void TextLocationMapBuilder_Imp::filter_text(vector<string>* words)
{
    /* 去掉符號 */
    vector<string>::iterator iter = words->begin();
	vector<string>::iterator iter_end = words->end();

    while ( iter != iter_end )
    {
        string::size_type pos = 0;
        while (( pos = (*iter).find_first_of( filt_elems, pos )) != string::npos )
            (*iter).erase(pos,1);
        iter++;
    }
}

void TextLocationMapBuilder_Imp::suffix_text(vector<string>* words)
{
    /* 單複數的處理 */
	vector<string>::iterator iter = words->begin();
	vector<string>::iterator iter_end = words->end();
	
	while ( iter != iter_end )
	{
		int pos=(*iter).size();
		if(pos<=3)
		{
			iter++;
			continue;
		}
		else if((*iter)[pos-1]=='s')(*iter).erase(pos-1);
		else if((*iter)[pos-2]=='e'&&(*iter)[pos-1]=='d')(*iter).erase(pos-2);
		else if((*iter)[pos-3]=='i'&&(*iter)[pos-2]=='n'&&(*iter)[pos-1]=='g')(*iter).erase(pos-3);
		iter++;
	}
    /* none */
}

void TextLocationMapBuilder_Imp::strip_cap(vector<string>* words)
{
    /* 全轉為小寫字 */
    vector<string>::iterator iter = words->begin();
    vector<string>::iterator iter_end = words->end();

	string caps( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );

    while ( iter != iter_end ) {
        string::size_type pos = 0;
        while (( pos = (*iter).find_first_of( caps, pos )) != string::npos )
            (*iter)[ pos ] = tolower( (*iter)[pos] );
        ++iter;
    }
}

void TextLocationMapBuilder_Imp::exclude_text(vector<string>* words )
{
	if(exclude_words.size()!=0)
	{
		/* exclude words */
		vector<string>::iterator iter = words->begin();
		vector<string>::iterator ex_iter = (&exclude_words)->begin();
		vector<string>::iterator iter_end = words->end();
		vector<string>::iterator ex_iter_end = (&exclude_words)->end();
		
		vector<string> tmp;
		
		while ( iter != iter_end ) {
			while( ex_iter != ex_iter_end )
			{
				if((*iter)==(*ex_iter))
					(*iter)="";
				else ++ex_iter;
			}
			ex_iter = (&exclude_words)->begin();
			++iter;
		}
	}
}

void
TextLocationMapBuilder_Imp::
sort_text(vector<string>* words, vector<Location>* locs)
{
    /* 排序 - 使用較簡單的 bubble sort*/
    unsigned int i,j;
    for(i=0;i<words->size()-1;i++) {
        for(j=i+1;j<words->size();j++) {
          	// sorting by word
            if( (*words)[i] > (*words)[j] ) {
                string s = (*words)[i];
                (*words)[i] = (*words)[j];
                (*words)[j] = s;
                
                Location c = (*locs)[i];
                (*locs)[i] = (*locs)[j];
                (*locs)[j] = c;
                continue;
            }
            if( (*words)[i] != (*words)[j] ) continue;

			// sorting by location X
          	if( (*locs)[i].getX() > (*locs)[j].getX() ) {
                Location c = (*locs)[i];
                (*locs)[i] = (*locs)[j];
                (*locs)[j] = c;
				continue;
           	}
           	
          	if( (*locs)[i].getX() != (*locs)[j].getX() ) continue;

			// sorting by location Y
          	if( (*locs)[i].getY() > (*locs)[j].getY() ) {
                Location c = (*locs)[i];
                (*locs)[i] = (*locs)[j];
                (*locs)[j] = c;
				continue;
           	}
        }
    }
}

TextLocationMap*
TextLocationMapBuilder_Imp::
build_location_map(vector<string>* words, vector<Location>* locs)
{
    /* 建立 TextLocationMap */
    TextLocationMap *map = new TextLocationMap_Imp();

    TextLocationMap::LocationSet word_locs;
    string previous = "";
    for(unsigned int i=0; i<words->size();i++) {
        if( (*words)[i] == previous ) {
            word_locs.push_back( (*locs)[i] );
        } else {
            if( previous != "" )
                map->add( previous, word_locs );
            previous = (*words)[i];
            word_locs.clear();
            word_locs.push_back( (*locs)[i] );
        }
    }

    if( previous != "" )
        map->add( previous, word_locs );

    return map;
}

void TextLocationMapBuilder_Imp::loadExclude(vector<string>* lines_of_text)
{
	if(lines_of_text!=NULL)
	{
		vector<Location> locs;
	    
		// step 1
		separate_words(lines_of_text, &exclude_words, &locs);
		// step 2
		filter_text( &exclude_words );
		// step 3
		suffix_text( &exclude_words );
		// step 4
		strip_cap( &exclude_words );
	}
}
