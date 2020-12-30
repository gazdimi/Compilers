#include <string>
class state
{
private:
    int ruleNumber;
    std::string stateName;
    char currentSymbol;
    char inputSymbol;
    std::string nextState;
    char nextSymbol;
public:
    state();
    state(std::string stName,char cSymbol,char iSymbol,int rlNumber,std::string ntState,char ntSymbol);
    std::string GetStName();
    char GetCSymbol();
    char GetISymbol();
    std::string GetNtState();
    char GetNtSymbol();
    int GetRuleNumber();
    bool isValidInput(char inputSymbol);
    ~state();
};
state::state(std::string stName,char cSymbol,char iSymbol,int rlNumber,std::string ntState,char ntSymbol)
{
    stateName=stName;
    currentSymbol=cSymbol;
    inputSymbol=iSymbol;
    ruleNumber=rlNumber;
    nextState=ntState;
    nextSymbol=ntSymbol;
    
}
std::string state::GetStName(){return stateName;}
char state::GetCSymbol(){return currentSymbol;};
char state::GetISymbol(){return inputSymbol;};
std::string state::GetNtState(){return nextState;};
char state::GetNtSymbol(){return nextSymbol;};
int state::GetRuleNumber(){return ruleNumber;};
state::state()
{
}
state::~state()
{
}
bool state::isValidInput(char inputSymbol){
    if(this->inputSymbol==inputSymbol){
        return true;
    }
    return false;
}