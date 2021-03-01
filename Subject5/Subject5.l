%{
#include <stdio.h>
#include <string.h>
int parsed;
void isValid(char *input);
%}

ALPHABET [A-H]

%%
"point"[" "\t]+({ALPHABET}{1})$ {isValid(yytext);}
"line"[" "\t]+({ALPHABET}{2})$ {isValid(yytext);}
"triangle"[" "\t]+({ALPHABET}{3})$ {isValid(yytext);}
"angle"[" "\t]+({ALPHABET}{3})$ {isValid(yytext);}
"square"[" "\t]+({ALPHABET}{4})$ {isValid(yytext);}
"pentagon"[" "\t]+({ALPHABET}{5})$ {isValid(yytext);}
"hexagon"[" "\t]+({ALPHABET}{6})$ {isValid(yytext);}
"heptagon"[" "\t]+({ALPHABET}{7})$ {isValid(yytext);}
"octagon"[" "\t]+({ALPHABET}{8})$ {isValid(yytext);}
%%

void isValid(char *input){

	int dups[8]={0,0,0,0,0,0,0,0};
	


	char *token = strtok(input, " ");	
	while (token != NULL){
        	token = strtok(NULL, " ");
		printf("\naa",token);
        }
	

	char *i;
	for(i=token;*i;i++){
		printf(i);
		printf("\n");
		if(*i==(char) 'A'){
			dups[0]++;
		}else if(*i==(char) 'B'){
			dups[1]++;
		}else if(*i==(char) 'C'){
			dups[2]++;
		}else if(*i==(char) 'D'){
			dups[3]++;
		}else if(*i==(char) 'E'){
			dups[4]++;
		}else if(*i==(char) 'F'){
			dups[5]++;
		}else if(*i==(char) 'G'){
			dups[6]++;
		}else if(*i==(char) 'H'){
			dups[7]++;
		}
	}
	
	for(int i=0;i<8;i++){
		if(dups[i]>1){
			parsed=0;
			break;
		}else{
			parsed=1;
		}
	}
	
}

int main(){
	printf("Enter your sentence: ");
	yylex();

	if(parsed==1){
		printf("Recognized!\n");
	}else if(parsed==0){
		printf("Error!\n");
	}
	return 0;
}
