%{
#include <stdio.h>
int line=1;
int error=0;
void isValid(){
    if(error>0){
        printf("Error in line: %d\n",line);
    }
    else{
        printf("Line %d: Valid Variable Assignment!\n",line);
    }
    error=0;
}
%}
VARIABLE [A-Za-z_][A-Za-z0-9_]*
EQUAL "="
NUMBER [0-9][0-9]*
OPERATION "+"|"-"|"%"|"*"|"/"
QUESTIONMARK ";"
%%
{VARIABLE}{EQUAL}({VARIABLE}|{NUMBER})({QUESTIONMARK}|({OPERATION}({VARIABLE}|{NUMBER}))+{QUESTIONMARK})
. {error++;}
\n { isValid(); line++; }
%%

int main(){
    yylex();
    return 0;
}