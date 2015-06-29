#include "LineBreak_Div.h"
#include <iostream>

LineBreak_Div::LineBreak_Div(vector<string> *t,int width):_width(width)
{
	m_pTexts=t;
}

LineBreak_Div::~LineBreak_Div()
{

}

bool LineBreak_Div::check(int width)
{
	int maxwidth=-1;
	for(int i=0;i<(int)m_pTexts->size();i++)
	{
		string line=(*m_pTexts)[i];
		Tokener tok;
		tok.parsing(line);
		if(maxwidth==-1)maxwidth=tok.maxTokenSize();
		else if(maxwidth<tok.maxTokenSize())maxwidth=tok.maxTokenSize();
	}
	if(width<=maxwidth-1)return false;
	else return true;
}

bool LineBreak_Div::setWidth(int width)
{
	if(check(width)==false)return false;
	vector<string>	texts;
	texts=*m_pTexts;
	m_pTexts->clear();
	for(int i=0;i<(int)texts.size();i++)
	{
		if((int)texts[i].size()==0)
			m_pTexts->push_back(texts[i]);
		
		while(texts[i].size()!=0)
		{
			if((int)texts[i].size()<=width)
			{
				m_pTexts->push_back(texts[i]);
				texts[i]="";
			}
			else if(texts[i][width]==' '||texts[i][width+1]==' ')
			{
				m_pTexts->push_back( texts[i].substr(0,width+1) );
				texts[i]=texts[i].substr(width+1,texts[i].size()-width);
			}
			else
			{
				string newline;
				if(texts[i][width-1]!=' ')
					newline=texts[i].substr(0,width)+"-";
				else newline=texts[i].substr(0,width);
				m_pTexts->push_back( newline );
				texts[i]=texts[i].substr(width,texts[i].size()-width);
			}
		}
	}
	return true;
}

void LineBreak_Div::revert()
{
	vector<string>	texts;
	texts=*m_pTexts;
	m_pTexts->clear();
	string newline;
	for(int i=0;i<(int)texts.size();i++)
	{
		if(texts[i][texts[i].size()-1]=='-')
		{
			texts[i].erase(texts[i].size()-1);
			newline+=texts[i];
		}
		else if((int)texts[i].size()==0)
		{
			m_pTexts->push_back(newline);
			newline="";
			m_pTexts->push_back(texts[i]);			
		}
		else newline+=texts[i];
	}
	m_pTexts->push_back(newline);
}
