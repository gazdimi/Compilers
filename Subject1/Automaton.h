#include <string>
#include <stack>
#include "State.h"
#include "PrettyPrint.h"
class Automaton
{
private:
    state allStates[4];
    std::string currentState;
    std::stack <char> symbolStack;
    void OperateStack(char symbol);
    bool IsValidState(state cstate,char symbol);
    std::queue<char> inputQ;
    
    
public:
    Automaton();
    ~Automaton();
    bool Feed(char input);
    bool Start(std::queue<char> inputQueue);
};

Automaton::Automaton()						//constructor
{
    //State initialization.
    allStates[0] = state("k1",'$','x',1,"k1",'P');		//initialize rules of pushdown automaton
    allStates[1] = state("k1",'P','x',2,"k1",'P');
    allStates[2] = state("k1",'P','y',3,"k1",'e');
    allStates[3] = state("k1",'$','e',4,"k2",'e');
    currentState = "k1";					//initial state of pushdown automaton
    symbolStack.push('$');					//Symbol stack initialization.
}


Automaton::~Automaton() { }					//destructor

bool Automaton::Start(std::queue<char>inputQueue){

    inputQ = inputQueue;
    inputQ.push('e');
    while(!inputQ.empty()){					//while there is an input character that needs to be checked by the automaton
        if(Feed(inputQ.front())){				//check if there is an appropriate rule to be applied by the automaton
            inputQ.pop();					//after applying the appropriate rule, remove the first character of the queue (letter that was identified by the automaton)
        }else{							//no proper rule exists
            std::cout<<"Wrong"<<std::endl;
            return false;
        }
    }
    return true;
}

bool Automaton::Feed(char input){				//check for appropriate rule and then apply it

    for(int i=0; i<4;i++){
        if(IsValidState(allStates[i], input)){
            currentState = allStates[i].GetNtState();		//move on to the next state
            PrettyPrint::print(symbolStack, currentState, inputQ, allStates[i].GetRuleNumber());
            OperateStack(allStates[i].GetNtSymbol());		//modify the stack according to the appropriate rule

            return true;
        }
    }
    return false;
}

bool Automaton::IsValidState(state cstate, char symbol){	//check if given rule can be applied

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

void Automaton::OperateStack(char symbol){
    if(symbol=='P'){
        symbolStack.push('P');
    }
    else{
        symbolStack.pop();
    }
}
