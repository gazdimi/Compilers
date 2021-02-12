#include <cstdlib>
#include "Automaton.h"

int main()
{
	std::srand(time(0));                                             //pseudo-random number generator using time as an unpredictable seed
	Automaton automaton = Automaton();
}
//g++ -std=c++11  Subject2.cpp -o Subject2.out		needs c++ version 11 or later in order to be executed from g++ compiler (because of vector's initialization as list)
//g++ -std=c++14  Subject2.cpp -o Subject2.out
