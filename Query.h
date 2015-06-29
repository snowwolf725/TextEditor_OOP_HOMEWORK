#ifndef _QUERY_H_
#define _QUERY_H_
#include <string>
#include <vector>
#include "Tokener.h"

using namespace std;

class Query
{
public:
	Query(){};//for easy to test my code
	Query(string qstr,vector<string> *m_pTexts);
	~Query();
	bool fuzzyQuery(string qstr,string findstr);
	vector<int> getAns();
private:
	friend class Query_Test;
	void singleQuery(string qstr,vector<string> *m_pTexts);
	void fuzzyQuery(string qstr,vector<string> *m_pTexts);
	vector<int> find_loc;
};

#endif //_QUERY_H_
