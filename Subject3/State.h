#include <string>
class state
{
private:
    int ruleNumber;
    std::string stateName;
    std::string currentSymbol;
    std::string inputSymbol;
    std::string nextState;
    std::string nextSymbol;
public:
    state();
    state(std::string stName,std::string cSymbol,std::string iSymbol,int rlNumber,std::string ntState,std::string ntSymbol);
    std::string GetStName();
    std::string GetCSymbol();
    std::string GetISymbol();
    std::string GetNtState();
    std::string GetNtSymbol();
    int GetRuleNumber();
    bool isValidInput(std::string inputSymbol);
    ~state();
};

state::state(std::string stName,std::string cSymbol,std::string iSymbol,int rlNumber,std::string ntState,std::string ntSymbol)	//constructor
{
    stateName = stName;
    currentSymbol = cSymbol;
    inputSymbol = iSymbol;
    ruleNumber = rlNumber;
    nextState = ntState;
    nextSymbol = ntSymbol;
    
}

std::string state::GetStName(){return stateName;}

std::string state::GetCSymbol(){return currentSymbol;};

std::string state::GetISymbol(){return inputSymbol;};

std::string state::GetNtState(){return nextState;};

std::string state::GetNtSymbol(){return nextSymbol;};

int state::GetRuleNumber(){return ruleNumber;};

state::state(){	}

state::~state(){ }

bool state::isValidInput(std::string inputSymbol){
    if(this->inputSymbol==inputSymbol){
        return true;
    }
    return false;
}
