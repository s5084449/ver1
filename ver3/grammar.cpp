#include "grammar.h"

void Grammar::clear()
{
	grammar.clear();
}

void Grammar::Iteration()
{
	string temprule = grammar;
	for (int i = 1; i <= level; i++)
	{
		int curleng = temprule.length();
		int j = 0;
		while (j < curleng)
		{
			if (temprule[j] == 'X') //generating and replacing
			{
				result += grammar;
				j++;
			}
			else //remain angle
			{
				result += temprule[j];
				j++;
			}
		}
		temprule = result;
		result.clear();
	}
	result = temprule;
}

void Grammar::setGrammarName(const string& ref)
{
	Gname = ref;
}

void Grammar::setLevel(int num)
{
	level = num;
}

string Grammar::getGrammarName()
{
	return Gname;
}

int Grammar::getLevel()
{
	return level;
}

string Grammar::getResult()
{
	return result;
}



