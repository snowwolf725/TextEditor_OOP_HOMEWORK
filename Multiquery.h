#ifndef _MULTIQUERY_H_
#define _MULTIQUERY_H_
#include <string>
#include "Tokener.h"
#include "Display.h"
#include "Query.h"
#include "QueryWord.h"
#include <stack>
#undef  DEBUG
#ifdef DEBUG
#include <iostream>
#endif

class Multiquery
{
public:
	Multiquery(){};//for easy to test my code
	Multiquery(vector<string> *m_pTexts,Tokener &argv,int type=0);
	~Multiquery();
	vector<int> getAns();
	int check();
private:
	friend class Multiquery_Test;
	bool parsering(Tokener &qtok);
	int checkop(string &op);
	int checkstack();
	void conexp(int op_in_hand);
	vector<int> notQuery(vector<int> &ans);
	vector<int> andQuery(vector<int> &ans1,vector<int> &ans2);
	vector<int> orQuery(vector<int> &ans1,vector<int> &ans2);
	vector<int> final_ans;
	int illegal;
	vector<string> *m_pTexts;
	stack<string> m_operator;
	stack<vector<int> > m_operand;
	int querytype;
};

#endif //_MULTIQUERY_H_
