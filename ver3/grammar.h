// Grammar.h 

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Grammar
{
public:
	string Gname;  // grammar name
	int level = 5;        // generation level
	string grammar = "FA[*+X][-/&X][/%X]B";//grammar
	string result;   // result afer generating

	Grammar() {}
	void clear();   
	void Iteration();//generation level

	void setGrammarName(const string& ref);
	void setLevel(int num);
	string getGrammarName();
	int getLevel();
	string getResult();
};

