#ifndef TOKENER_H
#define TOKENER_H

#include <vector>
#include <string>

using namespace std;	

// �N�@�Ӧr��̪ťթ�Ѧ��h��token
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
