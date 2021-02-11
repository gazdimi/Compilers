#include <queue>
#include "Automaton.h"

int main(int argc,char *argv[])
{
    std::queue <char> inputQueue;
    //Parse User Input
    for (int i = 1; i < argc; ++i) {
        for (int j = 0; argv[i][j] != '\0'; ++j) {
        inputQueue.push(argv[i][j]);
        }
    }
    int spaces=20;
    std::cout << "Stack" << std::string(spaces,' ') << "State" << std::string(spaces,' ') << "Input" << std::string(spaces,' ') << "Rule" << std::endl;
    Automaton automaton = Automaton();			//initialization of pushdown automaton
    automaton.Start(inputQueue);			//pass user input to check whether it can be identified
}
