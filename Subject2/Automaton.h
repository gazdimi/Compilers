#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <list>

class Automaton
{
private:
	std::map< std::string, std::map<int, std::vector<std::string> > > rules;
	std::list<std::string> generated_output;
	std::vector<std::string> terminals;
	std::vector<std::string> non_terminals;
	int randomChoice(const int begin, const int end);
	void Start();
public:
	Automaton();
	~Automaton();
};

Automaton::Automaton()
{
	terminals = {"(", ")", "v", "-", "+"};
	non_terminals = {"<E>", "<Y>", "<A>", "<B>"};			//non-terminals, left-side of rules
	std::map<int, std::vector<std::string> > production;		//right-side of rules
	for(int i=0; i<non_terminals.size(); ++i)
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
		rules[non_terminals[i]] = production;
	}
	
	for(auto i = rules["<E>"][0].begin(); i<rules["<E>"][0].end(); i++){ generated_output.push_back(*i); 	}	//rules["<E>"][0][0]
	//for(auto i = generated_output.begin(); i != generated_output.end(); ++i){ std::cout << *i << std::endl;}
	
	Start();

	/*for (auto rule : rules)
	{
		std::cout << rule.first << " ::= ";
		for( auto right_side : rule.second)
		{ 
			for(int j=0; j<right_side.second.size(); ++j)
			{
				if(right_side.first != 0 & (j+1 == right_side.second[j].size() | right_side.second.size()==1)){ 
					std::cout << " | ";
				}
				std::cout << right_side.second[j];
			}
		}
		std::cout << std::endl;
	}*/
}

Automaton::~Automaton(){ }

void Automaton::Start()												//start generating
{
	std::vector<std::string> temp_non_terminals;
	for(auto i = generated_output.begin(); i != generated_output.end(); ++i)
	{
		if(std::find(non_terminals.begin(), non_terminals.end(), *i) != non_terminals.end()) {
			temp_non_terminals.push_back(*i);							/* generated output contains a non terminal symbol */
		}
	}

	if(temp_non_terminals.size() ==  0)									//no more rules can be applied, only terminals included in generated output 
	{
		std::cout << "My job here is done!" << std::endl;	
	}else if(temp_non_terminals.size() ==  1){								//only one rule can be applied
		
		if(temp_non_terminals[0]=="<E>" | temp_non_terminals[0]=="<Y>"){				//rule has only one production part
			auto it = std::find(generated_output.begin(), generated_output.end(), temp_non_terminals[0]);
		    	if (it != generated_output.end()) {
				it = generated_output.erase(it);
				for (int j=0; j<rules[temp_non_terminals[0]][0].size(); ++j)
				{
					it = generated_output.insert(it, rules[temp_non_terminals[0]][0][j]);
					++it;
				}
				for (auto it2=generated_output.begin(); it2!=generated_output.end(); ++it2)
					std::cout << ' ' << *it2;
					
				std::cout << std::endl;
			}
		}else{												//rule has 2 or more production parts, we need to choose a random part among them
		}
	}else{}
}

int Automaton::randomChoice(const int begin, const int end)
{
	std::random_device random_dev;
	std::mt19937 generator(random_dev());
	std::uniform_int_distribution<int>  distr(begin, end);
	return distr(generator);
}
