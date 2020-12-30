#include <string>
#include <stack>
#include "State.h"
class Automaton
{
private:
    state allStates[4];
    std::string currentState;
    std::stack <char> symbolStack;
    bool OperateStack(char symbol);
    bool IsValidState(state cstate,char symbol);
    
public:
    Automaton();
    ~Automaton();
    bool completed;
    bool Feed(char input);
};

Automaton::Automaton()
{
    //State initialization.
    allStates[0]= state("k1",'$','(',1,"k1",'P');
    allStates[1]= state("k1",'P','(',2,"k1",'P');
    allStates[2]= state("k1",'P',')',3,"k1",'e');
    allStates[3]= state("k1",'$','e',4,"k2",'e');
    currentState=allStates[0].GetStName();
    symbolStack.push('$');
    completed=false;
}


Automaton::~Automaton()
{
}

bool Automaton::Feed(char input){
    for(int i=0; i<4;i++){
        if(IsValidState(allStates[i],input)){
            currentState=allStates[i].GetStName();
            if(currentState=="k2"){
                completed=true;
            }
            return OperateStack(allStates[i].GetNtSymbol());
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

bool Automaton::OperateStack(char symbol){
    if(symbol=='P'){
        symbolStack.push('P');
        return true;
    }
    else{
        symbolStack.pop();
        return true;
    }
}