#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <list>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "PrettyPrint.h"

class Automaton
{
private:
	std::map< std::string, std::map<int, std::vector<std::string> > > rules;
	std::list<std::string> generated_output;
	std::vector<std::string> terminals;
	std::vector<std::string> non_terminals;
	int randomChoice(const int begin, const int end);
	void Start();
	void applyRulePart(std::string non_terminal, int rule_part);
	bool checkToStop();
	int randomWithWeights();
	int weight = 4;
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
	
	int number = 1;
	for (auto rule : rules)
	{
		std::cout << number << ". " << rule.first << " ::= ";
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
		++number;
	}
	int spaces = 12;
    	std::cout << std::endl <<"Generated Output" << std::string(spaces,' ') << "Non-terminal" << std::string(spaces,' ') << "Production" << std::string(spaces,' ') << "Rule" << std::endl;

	std::cout << "<E>" << std::endl;
	for(auto i = rules["<E>"][0].begin(); i<rules["<E>"][0].end(); i++){ generated_output.push_back(*i); 	}
	PrettyPrint::print(generated_output, "<E>", rules["<E>"][0], 1);
	Start();
}

Automaton::~Automaton(){ }

void Automaton::Start()												//start generating
{
	int rule_part; int rule;
	std::vector<std::string> temp_non_terminals;
	for(auto i = generated_output.begin(); i != generated_output.end(); ++i)
	{
		if(std::find(non_terminals.begin(), non_terminals.end(), *i) != non_terminals.end()) {
			temp_non_terminals.push_back(*i);							/* generated output contains a non terminal symbol */
		}
	}

	if(temp_non_terminals.size() ==  1){								//only one rule can be applied
		
		if(temp_non_terminals[0]=="<E>" | temp_non_terminals[0]=="<Y>"){				//the single rule has only one production part
			applyRulePart(temp_non_terminals[0], 0);

		}else{												//the single rule has 2 or more production parts, we need to choose a random part among them
			if(temp_non_terminals[0] == "<A>"){ 
				rule_part = randomWithWeights(); 
			}else{			
				rule_part = randomChoice(0, rules[temp_non_terminals[0]].size()-1);
			}
			applyRulePart(temp_non_terminals[0], rule_part);		
		}
	}else{													//2 or more rules can be applied, we need to choose a random rule among them and then apply it
		rule = randomChoice(0,  temp_non_terminals.size()-1);

		if(temp_non_terminals[rule]=="<E>" | temp_non_terminals[rule]=="<Y>"){				//the choosen rule has only one production part
			applyRulePart(temp_non_terminals[rule], 0);
		}else{												//the single rule has 2 or more production parts, we need to choose a random part among them
			
			if(temp_non_terminals[rule] == "<A>"){
				rule_part = randomWithWeights();
			}else{ 
				rule_part = randomChoice(0, rules[temp_non_terminals[rule]].size()-1);
			}
			applyRulePart(temp_non_terminals[rule], rule_part);		
		}
	}
	
	temp_non_terminals.erase(temp_non_terminals.begin() + rule);						//remove non terminal that was replaced
	bool stop = checkToStop();
	if(stop)												//no more rules can be applied, only terminals included in generated output 
	{
		std::cout << std::endl << "Generated Output: ";
		for (auto it=generated_output.begin(); it!=generated_output.end(); ++it)
			std::cout << *it;
		std::cout << std::endl;
	}else{
		Start();
	}
}

void Automaton::applyRulePart(std::string non_terminal, int rule_part)						//apply right-side of the rule to the generayed output
{
	auto it = std::find(generated_output.begin(), generated_output.end(), non_terminal);			//find the position in the generated output, where the rule_part should be applied
	if (it != generated_output.end()) {
		it = generated_output.erase(it);								//remove the symbol from generated ouput, that will be replaced with rule's production part
		for (int j=0; j<rules[non_terminal][rule_part].size(); ++j)
		{
			if(rules[non_terminal][rule_part][j] != "e"){
				it = generated_output.insert(it, rules[non_terminal][rule_part][j]);
				++it;
			}
		}
	}
	int rule;
	if(non_terminal == "<E>"){
		rule = 1;
	}else if(non_terminal == "<Y>"){
		rule = 2;
	}else if(non_terminal == "<A>"){
		rule = 3;
	}else{ rule = 4;}
	PrettyPrint::print(generated_output, non_terminal, rules[non_terminal][rule_part], rule);
}

bool Automaton::checkToStop()											//check if generated output's symbols are terminals
{
	int check = 0;
	for (auto i = generated_output.begin(); i!=generated_output.end(); ++i)
	{
		if(std::find(terminals.begin(), terminals.end(), *i) != terminals.end()) {
    			check++;
		}	
	}
	if(check == generated_output.size()) { return true; } else { return false;}
}

int Automaton::randomChoice(const int begin, const int end)
{
	std::random_device random_dev;
	std::mt19937 generator(random_dev());
	std::uniform_int_distribution<int>  distr(begin, end);
	return distr(generator);
}

int Automaton::randomWithWeights()
{
	srand(time(0));
	int prob = rand() % 10;
	if(prob > 0 & prob <= weight )
	{
		return 0;
	}else{	
		if(weight < 10) { weight++; }
		return 1;
	}

}
