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
	int Tree_Depth();
	SymbolTree::node* root;
	SymbolTree::node* currentNode;
	std::stack<int> backtracking;
	int currentRank = 0;
	void goBack();
	std::list <std::string> tree;
    
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
	symbolStack.push("S");					//Symbol stack initialization.
	root = SymbolTree::createNode('S');
	currentNode = root;					//Syntax tree initialization					
	currentRank++;
	tree.push_back("S");				
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
		std::cout<< "Recognized"<<std::endl << std::endl;
		tree.pop_back();				// remove last "e"	
								
		std::cout << "Tree depth is " << Tree_Depth() << std::endl;
		PrettyPrint::DisplayTree(root,true,true,ceil((double)Tree_Depth()/2));	//print syntax tree of recognized sequence
		break;
	    }
        }
    }
    return true;
}

bool Automaton::Feed(std::string input){						//check for appropriate rule and then apply it
    right = false;
    for(int i=0; i<19;i++){
        if(IsValidState(allStates[i], input)){
            right = true;
	    currentState = allStates[i].GetNtState();					//move on to the next state
	    ruleNum = allStates[i].GetRuleNumber();					//modify the stack according to the appropriate rule
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

bool Automaton::IsValidState(state cstate,std::string symbol){				//check if given rule can be applied

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

void Automaton::OperateStack(int symbol){						//apply rule and construct syntax tree
    	
	if (symbol==1){
		symbolStack.pop();
		symbolStack.push(")");
		symbolStack.push("X");
		symbolStack.push("(");
		done = true;
		
		currentNode -> left = SymbolTree::createNode('(');
		currentNode -> left -> parent = currentNode;

		currentNode -> middle = SymbolTree::createNode('X');
		currentNode -> middle -> parent = currentNode;

		currentNode -> right = SymbolTree::createNode(')');
		currentNode -> right -> parent = currentNode;
		currentNode = currentNode -> middle;
		currentRank++;
	
		tree.push_back("(");
		tree.push_back("X");
		tree.push_back(")");

	}else if(symbol>=2 && symbol<=4){
		symbolStack.pop();
		symbolStack.push("Z");
		symbolStack.push("Y");
		done = true;

		backtracking.push(currentRank);
		currentNode -> left = SymbolTree::createNode('Y');
		currentNode -> left -> parent = currentNode;

		currentNode -> right = SymbolTree::createNode('Z');
		currentNode -> right -> parent = currentNode;
		currentNode = currentNode -> left;
		currentRank++;

		tree.push_back("Y");
		tree.push_back("Z");
		
	}else if(symbol==5){
		symbolStack.pop();
		symbolStack.push("a");
		done = true;

		currentNode -> left = SymbolTree::createNode('a');
		currentNode -> left -> parent = currentNode;
		goBack();
		
		tree.push_back("a");

	}else if(symbol==6){
		symbolStack.pop();
		symbolStack.push("b");
		done = true;

		currentNode -> left = SymbolTree::createNode('b');
		currentNode -> left -> parent = currentNode;
		goBack();
		
		tree.push_back("b");
		
	}else if(symbol==7){
		symbolStack.pop();
		symbolStack.push("S");
		done = true;

		currentNode -> left = SymbolTree::createNode('S');
		currentNode -> left -> parent = currentNode;

		currentNode = currentNode -> left;
		currentRank++;

		tree.push_back("S");

	}else if(symbol==8){
		symbolStack.pop();
		symbolStack.push("X");
		symbolStack.push("*");
		done = true;

		currentNode -> left = SymbolTree::createNode('*');
		currentNode -> left -> parent = currentNode;

		currentNode -> right = SymbolTree::createNode('X');
		currentNode -> right -> parent = currentNode;

		currentNode = currentNode -> right;
		currentRank++;

		tree.push_back("*");
		tree.push_back("X");
		
	}else if(symbol==9){
		symbolStack.pop();
		symbolStack.push("X");
		symbolStack.push("-");
		done = true;

		currentNode -> left = SymbolTree::createNode('-');
		currentNode -> left -> parent = currentNode;

		currentNode -> right = SymbolTree::createNode('X');
		currentNode -> right -> parent = currentNode;

		currentNode = currentNode -> right;
		currentRank++;

		tree.push_back("-");
		tree.push_back("X");

	}else if(symbol==10){
		symbolStack.pop();
		symbolStack.push("X");
		symbolStack.push("+");
		done = true;

		currentNode -> left = SymbolTree::createNode('+');
		currentNode -> left -> parent = currentNode;

		currentNode -> right = SymbolTree::createNode('X');
		currentNode -> right -> parent = currentNode;

		currentNode = currentNode -> right;
		currentRank++;

		tree.push_back("+");
		tree.push_back("X");
		
	}else{
		goBack();
		tree.push_back("e");
		symbolStack.pop();
		done = true;
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

void Automaton::goBack(){					//tree backtracking in order to place the node in the right position
	if(!backtracking.empty()){
	for(int i=0; i < (currentRank-backtracking.top()); i++){
		currentNode = currentNode -> parent;
		
	}
	currentRank = currentRank-(currentRank - backtracking.top());
	backtracking.pop();
	currentNode = currentNode -> right;
	currentRank++;
	}
}
