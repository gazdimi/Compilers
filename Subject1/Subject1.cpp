#include <iostream>
#include <queue>
#include "Automaton.h"

void PrintAllStates(state allStates[4]){
    std::cout<<"State    Symbol    nextSymbol    nextState    Symbol    ruleNumber"<<std::endl;
    for(int i=0;i<4;i++){
        std::cout<<allStates[i].GetStName()<<"       "<<
        allStates[i].GetCSymbol()<<"         "<<
        allStates[i].GetISymbol()<<"             "<<
        allStates[i].GetNtState()<<"           "<<
        allStates[i].GetNtSymbol()<<"        "<<
        allStates[i].GetRuleNumber()<<std::endl;
    }
}

int main(int argc,char *argv[])
{
    std::queue <char> inputQueue;
    //Parse User Input
    for (int i = 1; i < argc; ++i) {
        for (int j = 0; argv[i][j] != '\0'; ++j) {
        inputQueue.push(argv[i][j]);
        }
    }
    Automaton automaton = Automaton();
    for(int i=0; i<inputQueue.size();i++){
        if(!automaton.completed){
            if(!automaton.Feed(inputQueue.front())){
                std::cout<<"No valid state found"<<std::endl;
                return -1;
            }
            else{
                std::cout<<inputQueue.front()<<std::endl;
                inputQueue.pop();
            }
        }
        else{
            break;
        }
    }
    if(automaton.completed&&inputQueue.size()>0){
        std::cout<<"Automaton finished without compiling all input."<<std::endl;
    }else if(!automaton.completed&&inputQueue.size()<=0){
        std::cout<<"Operation stoped unexpectedly."<<std::endl;
    }else if (automaton.completed&&inputQueue.size()<=0){
    std::cout<<"Operation completed Successfully."<<std::endl;
    }
}