#include <stack>
#include <string>
#include <queue>
#include <iostream>
#include <vector>
#include "SymbolTree.h"
#include <iomanip> 

class PrettyPrint
{
public:
	static std::queue<int>backTracking;
   	static void print(std::stack<std::string> symbols,std::string stateName,std::queue<std::string> input,int rule);
	static void DisplayTree(SymbolTree::node* root,bool firstTime,bool rightfirstSub,int depth);
};

void PrettyPrint::print(std::stack<std::string> symbols,std::string stateName,std::queue<std::string> input, int rule){	//print stack
    const int spaces=20;
    const int symbolsSize=symbols.size();
    const int inputSize=input.size();
    std::deque <std::string> copysymbols;
    std::queue <std::string> copyinput=input;
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
void PrettyPrint::DisplayTree(SymbolTree::node* root,bool firstTime,bool isfirstX,int tabs){				//print syntax tree
	if(firstTime){
		std::cout<<std::string(tabs,'	')<<root->data<<std::endl;
		firstTime=!firstTime;
	}
	bool hasPrint=false;

	if(root->data=='Y'){
		if (root->parent != NULL) {
			if (root->parent->data == 'X') {
				if (root->parent->parent != NULL) {
					if (root->parent->parent->data == 'S') {
						if (root->parent->parent->parent == NULL) {
							std::cout << "---------------------------------------------------- Left Sub-Tree" << std::endl;
						}
					}
				}
			}
		}
	}
	
	bool left= root->left!=NULL;
	bool middle=root->middle!=NULL;
	bool right=root->right!=NULL;
	if(root->left!=NULL){
		std::cout<<std::string(tabs-1,'	')<<root->left->data<<'	';
		if(!middle){
			std::cout<<' '<<'	';
		}
	}
	if(root->middle!=NULL){
		std::cout<<root->middle->data<<'	';
	}
	if(root->right!=NULL){
		std::cout<<root->right->data;
	}

	if(isfirstX&&root->data=='X'){
		isfirstX=!isfirstX;
		hasPrint=true;
	}
		
	std::cout<<std::endl;
	if(left){	
		DisplayTree(root->left,false,isfirstX,tabs-1);
	}

	if(middle){
		DisplayTree(root->middle,false,isfirstX,tabs);
	}
	
	if(right){
		if (root->data == 'X'&&root->parent->data == 'S'&&root->parent->parent == NULL)
		{
			std::cout << "---------------------------------------------------- Right Sub-Tree" << std::endl;
		}
		DisplayTree(root->right,false,isfirstX,tabs+1);
	}
}

