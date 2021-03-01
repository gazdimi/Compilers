#include <string>
#include <list>
#include <iostream>
#include <vector>

class PrettyPrint
{
public:
	static void print(std::list<std::string> generated_output, std::string non_terminal, std::vector<std::string> rule_part,int rule);
	static void printRules();
};

void PrettyPrint::print(std::list<std::string> generated_output, std::string non_terminal, std::vector<std::string> rule_part,int rule)
{
	const int spaces = 20;
	int o = 0;
	for (auto it=generated_output.begin(); it!=generated_output.end(); ++it){
		if(*it == "<E>" | *it == "<Y>" | *it == "<A>" | *it == "<B>" ){
			o+=3;
		}else{ ++o; }
	}
	
 	const int outputSize = o;
	int r = 0;
	for (auto it=rule_part.begin(); it!=rule_part.end(); ++it){
		if(*it == "<E>" | *it == "<Y>" | *it == "<A>" | *it == "<B>" ){
			r+=3;
		}else{ ++r; }
	}
	const int rulePartSize = r;
	int too_long = 0;
	if(outputSize < 30){
		for (auto it=generated_output.begin(); it!=generated_output.end(); ++it)
			std::cout << *it;
	}else{
		int start = 0;
		int end = generated_output.size() - 3;
		for (auto it=generated_output.begin(); it!=generated_output.end(); ++it){
			if(start < 3 | start >= end){
				std::cout << *it;
				if(*it == "<E>" | *it == "<Y>" | *it == "<A>" | *it == "<B>" ){
					too_long += 3;
				}else{ too_long++; }
			}else if(start == 4){
				std::cout << "...";
				too_long += 3;
			}
			start++;
		}
	}
	if(outputSize < 30){
		std::cout << std::string((spaces-outputSize) + 11,' ') << non_terminal << std::string(spaces,' '); 
	}else{
		std::cout << std::string((spaces- too_long) + 11,' ') << non_terminal << std::string(spaces,' ');
	}
	
	for (auto it=rule_part.begin(); it!=rule_part.end(); ++it)
		std::cout << *it;
	
	std::cout << std::string((spaces - rulePartSize) + 2,' ');
	std::cout << rule << std::endl;
}
void PrettyPrint::printRules()
{
	std::cout << "1. <E> ::= (<Y>)" << std::endl;
	std::cout << "2. <Y> ::= <A><B>" << std::endl;
	std::cout << "3. <A> ::= v | <E>" << std::endl;
	std::cout << "4. <B> ::= -<Y> | +<Y> | e" << std::endl;

}
