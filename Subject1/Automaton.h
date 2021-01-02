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

Automaton::Automaton()
{
    //State initialization.
    allStates[0]= state("k1",'$','(',1,"k1",'P');
    allStates[1]= state("k1",'P','(',2,"k1",'P');
    allStates[2]= state("k1",'P',')',3,"k1",'e');
    allStates[3]= state("k1",'$','e',4,"k2",'e');
    currentState="k1";
    symbolStack.push('$');//Symbol stack initialization.
}


Automaton::~Automaton()
{
}
bool Automaton::Start(std::queue<char>inputQueue){
    inputQ=inputQueue;
    inputQ.push('e');
    while(!inputQ.empty()){
        if(Feed(inputQ.front())){
            inputQ.pop();
        }else{
            std::cout<<"Wrong"<<std::endl;
            return false;
        }
    }
    return true;
}

bool Automaton::Feed(char input){
    for(int i=0; i<4;i++){
        if(IsValidState(allStates[i],input)){
            PrettyPrint::print(symbolStack,currentState,inputQ,allStates[i].GetRuleNumber());
            currentState=allStates[i].GetNtState();
            OperateStack(allStates[i].GetNtSymbol());
            return true;
        }
    }
    return false;
}

bool Automaton::IsValidState(state cstate,char symbol){
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
