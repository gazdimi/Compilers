#include <stack>
#include <string>
#include <queue>
#include <iostream>
class PrettyPrint
{
public:
    static void print(std::stack<char> symbols,std::string stateName,std::queue<char> input,int rule);
};

void PrettyPrint::print(std::stack<char> symbols,std::string stateName,std::queue<char> input, int rule){
    const int spaces=20;
    const int symbolsSize=symbols.size();
    const int inputSize=input.size();
    std::deque <char> copysymbols;
    std::queue <char> copyinput=input;
    while(!symbols.empty()){
        copysymbols.push_back(symbols.top());
        symbols.pop();
    }
    while(!copysymbols.empty()){
        std::cout<<copysymbols.back();
        copysymbols.pop_back();
    }
    if(symbolsSize<5){
        std::cout<<std::string(spaces+(5-symbolsSize),' ')<<stateName<<std::string(spaces+3,' ');
    }
    else{
        std::cout<<std::string(spaces+(5-symbolsSize),' ')<<stateName<<std::string(spaces+3,' ');
    }
    for(int i=0;i<inputSize-1;i++){
        std::cout<<copyinput.front();
        copyinput.pop();
    }
    if(inputSize<5){
        std::cout<<std::string(5-inputSize+1+spaces,' ');
    }
    else{
        std::cout<<std::string(spaces+(5-inputSize+1),' ');
    }
    std::cout<<rule<<std::endl;
}
