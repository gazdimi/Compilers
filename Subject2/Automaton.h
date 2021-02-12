#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <random>

class Automaton
{
private:
	std::map< std::string, std::map<int, std::vector<std::string> > > rules;
	std::vector<std::string> generated_output;
	int randomChoice(const int begin, const int end);
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
	
	for(auto i = rules["<E>"][0].begin(); i<rules["<E>"][0].end(); i++){ generated_output.push_back(*i); 	}	//rules["<E>"][0][0]
	//for(auto i = generated_output.begin(); i != generated_output.end(); ++i){ std::cout << *i << std::endl;}
	
	std::cout << randomChoice(1, 5) << std::endl;	

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

int Automaton::randomChoice(const int begin, const int end)
{
	std::random_device random_dev;
	std::mt19937 generator(random_dev());
	std::uniform_int_distribution<int>  distr(begin, end);
	return distr(generator);
	
	//std::srand(time(0));                                             //pseudo-random number generator using time as an unpredictable seed
	//return rand();


}
