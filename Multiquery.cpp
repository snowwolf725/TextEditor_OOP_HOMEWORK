#include "Multiquery.h"

Multiquery::Multiquery(vector<string> *Texts,Tokener &argv,int type)
{
	m_pTexts=Texts;
	querytype=type;
	if(argv.size()==1)
	{
		if(querytype==0)
		{
			Query	myquery(argv[0],m_pTexts);
			final_ans=myquery.getAns();
		}
		else if(querytype==1)
		{
			QueryWord	myquery(argv[0],m_pTexts);
			final_ans=myquery.getAns();		
		}
	}
	else if(argv.size()==2&&argv[0]=="!")
	{
		if(querytype==0)
		{
			Query	myquery(argv[1],m_pTexts);
			final_ans=myquery.getAns();
			final_ans=notQuery(final_ans);
		}
		else if(querytype==1)
		{
			QueryWord	myquery(argv[1],m_pTexts);
			final_ans=myquery.getAns();
			final_ans=notQuery(final_ans);
		}
	}
	else if(argv.size()>=3)
		parsering(argv);
	else illegal=1;
}

Multiquery::~Multiquery()
{
}

int Multiquery::check()
{
	if(illegal==1)return -1;
	else return 0;
}

vector<int> Multiquery::getAns()
{
	return final_ans;
}

vector<int> Multiquery::notQuery(vector<int> &ans)
{
	vector<int> notans;
	int bound=m_pTexts->size();
	if(ans.size()==0)
	{
		for(int i=0;i<bound;i++)
			notans.push_back(i);
	}
	else
	{
		int j=0;
		for(int i=0;i<bound;i++)
		{
			while(j<(int)ans.size()&&ans[j]<i)j++;
			if(i!=ans[j])notans.push_back(i);
		}
	}
	return notans;
}

vector<int> Multiquery::andQuery(vector<int> &ans1,vector<int> &ans2)
{
	vector<int> andans;
	if(ans1.size()==0||ans2.size()==0)
		return andans;
	else
	{
		for(int i=0;i<(int)ans1.size();i++)
		{
			bool find=false;
			for(int j=0;j<(int)ans2.size()&&find!=true;j++)
				if(ans1[i]==ans2[j])
				{
					find=true;
					andans.push_back(ans1[i]);
				}
		}
		return andans;
	}
}

vector<int> Multiquery::orQuery(vector<int> &ans1,vector<int> &ans2)
{
	vector<int> orans;
	if(ans1.size()==0)orans=ans2;
	else if(ans2.size()==0)orans=ans1;
	else
	{
		int i=0,j=0;
		while(i<(int)ans1.size()||j<(int)ans2.size())
		{
			if((int)ans1.size()==i)
			{
				orans.push_back(ans2[j]);
				j++;
			}
			else if((int)ans2.size()==j)
			{
				orans.push_back(ans1[i]);
				i++;
			}
			else if(ans1[i]<ans2[j])
			{
				orans.push_back(ans1[i]);
				i++;
			}
			else if(ans2[j]<ans1[i])
			{
				orans.push_back(ans2[j]);
				j++;
			}
			else if(ans2[j]==ans1[i])
			{
				orans.push_back(ans1[i]);
				i++;j++;
			}
		}
	}
	return orans;
}

bool Multiquery::parsering(Tokener &qtok)
{
	for(int i=0;i<qtok.size();i++)
	{
		string qstr=qtok[i];
		if(checkop(qstr)==0)
		{
			if(querytype==0)
			{
				Query myquery(qstr,m_pTexts);
				m_operand.push( myquery.getAns() );
			}
			else if(querytype==1)
			{
				Query myquery(qstr,m_pTexts);
				m_operand.push( myquery.getAns() );			
			}
#ifdef DEBUG
			cout<<m_operator.size()<<","<<m_operand.size()<<qstr<<endl;
#endif
		}
		else if(checkop(qstr)>checkstack()||qstr=="!")
			m_operator.push(qstr);
		else if(checkop(qstr)<=checkstack())
		{
			conexp(checkop(qstr));
#ifdef DEBUG
			cout<<m_operator.size()<<","<<m_operand.size()<<qstr<<endl;
#endif
			if(qstr!=")")
				m_operator.push(qstr);
#ifdef DEBUG
			cout<<m_operator.size()<<","<<m_operand.size()<<endl;
#endif
		}
	}
#ifdef DEBUG
	cout<<m_operator.size()<<","<<m_operand.size()<<endl;
#endif
	conexp(-1);
#ifdef DEBUG
	cout<<m_operator.size()<<","<<m_operand.size()<<endl;
#endif
	if(m_operand.size()>=2)
	{
		illegal=1;
		return false;
	}
	else
	{
		final_ans=m_operand.top();
		return true;
	}
}

int Multiquery::checkop(string &op)
{
	if(op.size()==1)
	{
		if(op[0]=='(') return 4;
		else if(op[0]==')') return 1;
		else if(op[0]=='!') return 3;
		else return 0;
	}
	else if(op.size()==2)
	{
		if(op=="&&") return 2;
		else if(op=="||") return 2;
		else return 0;
	}
	else return 0;
}

int Multiquery::checkstack()
{
	if(m_operator.empty())return 0;
	else if(m_operator.top()=="!")return 3;
	else if(m_operator.top()=="||"||m_operator.top()=="&&")return 2;
	else if(m_operator.top()=="(")return 1;
	else return 0;
}

void Multiquery::conexp(int op_in_hand)
{
	if(illegal==1)return;
	else if(m_operator.size()==0)return;
	else if(m_operator.top()=="("&&op_in_hand==1)m_operator.pop();
	else if(op_in_hand<=checkstack())
	{
		if(m_operator.top()=="!"&&m_operand.size()>=1)
		{
			vector<int> newoperand=notQuery(m_operand.top());
			m_operand.pop();
			m_operator.pop();
			m_operand.push(newoperand);
		}
		else if(m_operator.top()=="&&" && m_operand.size()>=2)
		{
			vector<int> op1=m_operand.top();
			m_operand.pop();
			vector<int> op2=m_operand.top();
			m_operand.pop();
			m_operator.pop();
			vector<int> newoperand=andQuery(op1,op2);
			m_operand.push(newoperand);
		}
		else if(m_operator.top()=="||" && m_operand.size()>=2)
		{
			vector<int> op1=m_operand.top();
			m_operand.pop();
			vector<int> op2=m_operand.top();
			m_operand.pop();
			m_operator.pop();
			vector<int> newoperand=orQuery(op1,op2);
			m_operand.push(newoperand);
		}
		else illegal=1;
		conexp(op_in_hand);
	}
	else if(op_in_hand>checkstack())return;
}
