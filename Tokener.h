#ifndef TOKENER_H
#define TOKENER_H

#include <vector>
#include <string>

using namespace std;	

// 將一個字串依空白拆解成多個token
class Tokener{
private:
	vector<string> _tokens;
	string _separate;
public:
	int size();
	string operator[](int index);
	void parsing(const string& origin, string sep = " \t");
	int maxTokenSize();
public:
	Tokener() { _separate = " \t"; }
	virtual ~Tokener() { }
};

#endif // TOKENER_H
