#include <math.h>
#include <string>
#include <stack>
#include <list>
#include <algorithm>
#include "State.h"
#include "PrettyPrint.h"
class Automaton
{
private:
    state allStates[19];
    std::string currentState;
    int ruleNum;
    std::stack <std::string> symbolStack;
    void OperateStack(int symbol);
    bool IsValidState(state cstate,std::string symbol);
    std::queue<std::string> inputQ;
    bool done = false;
    bool right = false;
    void Print_tree();
    std::list <std::string> tree;
    int Tree_Depth();
    
public:
    Automaton();
    ~Automaton();
    bool Feed(std::string input);
    bool Start(std::queue<std::string> inputQueue);
    
    
};

Automaton::Automaton()						//constructor
{
    //State initialization.					//initialize rules of pushdown automaton
	allStates[0] = state("k1","S","(",1,"k1",")X(");
    	allStates[1] = state("k1","X","(",2,"k1","ZY");
	allStates[2] = state("k1","X","a",3,"k1","ZY");
	allStates[3] = state("k1","X","b",4,"k1","ZY");
	allStates[4] = state("k1","Y","a",5,"k1","a");
	allStates[5] = state("k1","Y","b",6,"k1","b");
	allStates[6] = state("k1","Y","(",7,"k1","S");
	allStates[7] = state("k1","Z","*",8,"k1","X*");
	allStates[8] = state("k1","Z","-",9,"k1","X-");
	allStates[9] = state("k1","Z","+",10,"k1","X+");
	allStates[10] = state("k1","Z",")",11,"k1","e");
	allStates[11] = state("k1","a","a",12,"k1","e");
	allStates[12] = state("k1","b","b",13,"k1","e");
	allStates[13] = state("k1","*","*",14,"k1","e");
	allStates[14] = state("k1","-","-",15,"k1","e");
	allStates[15] = state("k1","+","+",16,"k1","e");
	allStates[16] = state("k1","(","(",17,"k1","e");
	allStates[17] = state("k1",")",")",18,"k1","e");
    	allStates[18] = state("k1","$","e",19,"k2","e");
    	currentState = "k1";					//initial state of pushdown automaton
   	symbolStack.push("$");
	symbolStack.push("S");	
	tree.push_back("S");				//Symbol stack initialization.					
}


Automaton::~Automaton() { }					//destructor

bool Automaton::Start(std::queue<std::string>inputQueue){

    inputQ = inputQueue;
    inputQ.push("e");
    
    while(!inputQ.empty()){					//while there is an input character that needs to be checked by the automaton
	if(Feed(inputQ.front())){				//check if there is an appropriate rule to be applied by the automaton
		if(inputQ.front() == symbolStack.top()){
			PrettyPrint::print(symbolStack, currentState, inputQ, ruleNum);
			symbolStack.pop();
			inputQ.pop();
		}
		done = false;					//after applying the appropriate rule, remove the first character of the queue (letter that was identified by the automaton)
        }else{							//no proper rule exists
            if (!right){
		std::cout<< "Sequence not identified"<<std::endl;
		return false;
	    }
	    if (currentState=="k2"){
		std::cout<< "Recognized"<<std::endl;
		tree.pop_back();				// remove last "e"	
								
		for(auto i=tree.begin();i!=tree.end();++i){
			std::cout << *i << " ";
		}
		std::cout << Tree_Depth() << std::endl;
		Print_tree();
		break;
	    }
        }
    }
    return true;
}

bool Automaton::Feed(std::string input){				//check for appropriate rule and then apply it
    right = false;
    for(int i=0; i<19;i++){
        if(IsValidState(allStates[i], input)){
            right = true;
	    currentState = allStates[i].GetNtState();		//move on to the next state
	    ruleNum = allStates[i].GetRuleNumber();						//modify the stack according to the appropriate rule
	    if (!done){
		PrettyPrint::print(symbolStack, currentState, inputQ, allStates[i].GetRuleNumber());
		OperateStack(allStates[i].GetRuleNumber());
		
		break;
	    }
	    return true;
        }
    }
    return false;
}

bool Automaton::IsValidState(state cstate,std::string symbol){	//check if given rule can be applied

    if(cstate.isValidInput(symbol)&&
    cstate.GetStName()==currentState&&
    cstate.GetCSymbol()==symbolStack.top()){
        return true;
    }
    else
    {
        return false;
    }
    
}

void Automaton::OperateStack(int symbol){
    	
	if (symbol==1){
		symbolStack.pop();
		symbolStack.push(")");
		symbolStack.push("X");
		symbolStack.push("(");

		tree.push_back("(");
		tree.push_back("X");
		tree.push_back(")");
		done = true;
	
	}else if(symbol>=2 && symbol<=4){
		symbolStack.pop();
		symbolStack.push("Z");
		symbolStack.push("Y");

		tree.push_back("Y");
		tree.push_back("Z");
		done = true;
	}else if(symbol==5){
		symbolStack.pop();
		symbolStack.push("a");

		tree.push_back("a");
		done = true;
	}else if(symbol==6){
		symbolStack.pop();
		symbolStack.push("b");

		tree.push_back("b");
		done = true;
	}else if(symbol==7){
		symbolStack.pop();
		symbolStack.push("S");

		tree.push_back("S");
		done = true;
	}else if(symbol==8){
		symbolStack.pop();
		symbolStack.push("X");
		symbolStack.push("*");

		tree.push_back("*");
		tree.push_back("X");
		done = true;
	}else if(symbol==9){
		symbolStack.pop();
		symbolStack.push("X");
		symbolStack.push("-");

		tree.push_back("-");
		tree.push_back("X");
		done = true;
	}else if(symbol==10){
		symbolStack.pop();
		symbolStack.push("X");
		symbolStack.push("+");

		tree.push_back("+");
		tree.push_back("X");
		done = true;
	}else{
		tree.push_back("e");
		symbolStack.pop();
		done = true;
	}
}

void Automaton::Print_tree(){
	
	
	bool chLevel=false;
	int tabs = (int) round(Tree_Depth()/2);

	std::cout << std::string(tabs,'\t') << "S" << std::endl << std::endl;
	std::cout << std::string(tabs-1,'\t') << "(";
	std::cout << std::string(1,'\t') << "X";
	std::cout << std::string(1,'\t') << ")" << std::endl << std::endl;
	std::cout << std::string(tabs-1,'\t') << "Y";
	std::cout << std::string(2,'\t') << "Z" << std::endl << std::endl;
	
	std::list <std::vector <std::string>> levels;
	std::vector <std::string> temp;

	auto it = std::find(tree.begin(), tree.end(), "Z");	// basic tree
	++it;
	auto tmp = it;
	for(it;it!=tree.end();++it){
		
		temp.push_back(*it);
		
		if(*it=="e"){
			tmp=it;
			++tmp;
			
			levels.push_back(temp);
			temp.clear();
			if(tmp==tree.end() || *tmp=="e"){	// if "e+"
				break;
			}
		}
	}


	for(auto i : levels){
		auto pt = i.begin();
		for(int j=0;j<i.size();++j){
			if(levels.size()==1){
				
				//std::cout << "Before" << i[j];
				if(i[j]=="+" || i[j]=="*" || i[j]=="-"){
					std::cout << std::string(1,'\t') << i[j];
					std::cout << std::string(1,'\t') << "X" << std::endl << std::endl;
					i.erase(i.begin(),++pt);
					j=0;
					pt = i.begin();
					
				}else if(i[j]=="Y"){
					std::cout << std::string(tabs,'\t') << i[j];
					std::cout << std::string(1,'\t') << "Z" << std::endl << std::endl;
					i.erase(i.begin(),++pt);
					j=0;
					pt = i.begin();
					
				}else{
					std::cout << std::string(tabs-1,'\t') << i[j];
					i.erase(pt);
					j=0;
					pt = i.begin();
				//gamw to spiti sou	
				}
				
				//std::cout << "After" << i[j];
				
			}
			++pt;
		}
		std::cout << std::endl;
	}
}		      
		     
		

		

int Automaton::Tree_Depth(){
	int depth=0;
	std::list <int> max;
	for(auto i=tree.begin();i!=tree.end();++i){
		if (*i == "e"){
			max.push_back(depth);
			depth=3;				// the basic tree before subtrees occur
		}
		if(*i == "S" || *i=="X" || *i == "Y"){		// count the tree bonds
			depth++;
		}
	}
	return *max_element(max.begin(), max.end())+1;		// tree depth is the bond number plus 1
}




