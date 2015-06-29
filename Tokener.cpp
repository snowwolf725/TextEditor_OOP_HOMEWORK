#include "Tokener.h"
#include <iostream>
using namespace std;

void Tokener::parsing(const string& origin, string sep)
{
	_separate = sep;
	_tokens.clear()	; // 清空舊元素

	string::size_type beginIdx, endIdx;
	beginIdx = origin.find_first_not_of( _separate );
	// 拆解string
	while( beginIdx != string::npos )
	{
		endIdx = origin.find_first_of(_separate, beginIdx);
		if( endIdx == string::npos)
			endIdx = origin.length();

		_tokens.push_back( origin.substr( beginIdx, endIdx-beginIdx) );
		beginIdx = origin.find_first_not_of(_separate, endIdx);	
	}
}

// token 個數
int Tokener::size()
{
	return _tokens.size();
}

// 取得第index 個token
string Tokener::operator[](int index)
{
	return _tokens[index];
}

int Tokener::maxTokenSize()
{
	int maxsize=-1;
	for(int i=0;i<(int)_tokens.size();i++)
	{
		if(maxsize==-1)maxsize=_tokens[i].size();
		else if(maxsize<(int)_tokens[i].size()) maxsize=_tokens[i].size();
	}
	return maxsize;
}
