#include <map>
#include <vector>
#include <string>
#include <iostream>

class Automaton
{
private:
	std::map< std::string, std::map<int, std::vector<std::string> > > rules;
public:
	Automaton();
	~Automaton();
};

Automaton::Automaton()
{
	std::vector<std::string> labels = {"<E>", "<Y>", "<A>", "<B>"};	//non-terminals, left-side of rules
	std::map<int, std::vector<std::string> > production;		//right-side of rules
	for(int i=0; i<labels.size(); ++i)
	{
		if(i==0){						//E
			production[0] = {"(","<Y>",")"};
		}else if(i==1){						//Y
			production[0] = {"<A>","<B>"};
		}else if(i==2){						//A
			production[0] = {"v"};
			production[1] = {"<E>"};
		}else{							//B
			production[0] = {"-","<Y>"};
			production[1] = {"+","<Y>"};
			production[2] = {"e"};		
		}
		rules[labels[i]] = production;
	}
	
	for (auto rule : rules)
	{
		std::cout << rule.first << " ::= ";
		for( auto right_side : rule.second)
		{ 
			for(int j=0; j<right_side.second.size(); ++j)
			{
				if(right_side.first != 0 & (j+1 == right_side.second[j].size() | right_side.second.size()==1)){ std::cout << " | ";}
				std::cout << right_side.second[j];
			}
		}
		std::cout << std::endl;
	}
}

Automaton::~Automaton(){ }
