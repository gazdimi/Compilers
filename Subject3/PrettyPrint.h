#include <stack>
#include <string>
#include <queue>
#include <iostream>
#include <vector>

class PrettyPrint
{
public:
   	static void print(std::stack<std::string> symbols,std::string stateName,std::queue<std::string> input,int rule);
	static void Print_tree(std::list <std::string> tree, int tree_depth);
	static int checkNext(int levels_size, int middle_tabs, std::string symbol);
};

void PrettyPrint::print(std::stack<std::string> symbols,std::string stateName,std::queue<std::string> input, int rule){
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

void PrettyPrint::Print_tree(std::list <std::string> tree, int tree_depth){

	//-------------------create subtrees of given tree--------------------
	std::vector <std::vector <std::string>> levels;
	std::vector <std::string> temp;

	auto it = std::find(tree.begin(), tree.end(), "Z");	// basic tree
	++it;
	auto tmp = it;
	for(it; it!=tree.end(); ++it){
		temp.push_back(*it);
		if(*it=="e"){
			tmp=it;
			++tmp;
			levels.push_back(temp);
			temp.clear();
			if(tmp==tree.end() || *tmp=="e"){	// if "e+"
				break;
			}
		}
	}
	//-------------------print syntax tree-------------------------------
	if(levels.size()<3){
		int tabs = ceil((double)tree_depth/2);

		std::cout << std::string(tabs,'\t') << "S" << std::endl << std::endl;
		std::cout << std::string(tabs-levels.size()-1,'\t') << "(";
		std::cout << std::string(levels.size()+1,'\t') << "X";
		std::cout << std::string(levels.size()+1,'\t') << ")" << std::endl << std::endl;
		std::cout << std::string(tabs-levels.size()-1,'\t') << "Y";
		std::cout << std::string((levels.size()+1)*2,'\t') << "Z" << std::endl << std::endl;

		int middle_tabs = (levels.size()+1)*2 - 1;
		int next_level_tabs = 0;
		int first_node = 0;
		
		if(levels.size()==1){							//single subtree in tree
			for(auto i : levels){
				for(auto j=i.begin(); j!=i.end();){
					first_node++;
					if(*j=="+" | *j=="*" | *j =="-"){
						std::cout << std::string(middle_tabs,'\t') << *j;
						std::cout << std::string(levels.size()+1,'\t') << "X" << std::endl << std::endl;
						j+=2;
						i.erase(i.begin(), j);
						j = i.begin();
						next_level_tabs+=middle_tabs + levels.size();
						middle_tabs--;
					
					}else if(*j=="Y"){
						std::cout << std::string(next_level_tabs,'\t') << *j;
						std::cout << std::string(levels.size()+1,'\t') << "Z" << std::endl << std::endl;
						j+=2;
						i.erase(i.begin(),j);
						j = i.begin();
					
					}else if(*j=="e" | *j=="a" | *j=="b" | *j=="S"){
						if(first_node==1){
							next_level_tabs = tabs - levels.size()-1;
						}
						if(*j=="e"){ 
							i.erase(j);
							j=i.begin();
							continue;
						}
						std::cout << std::string(next_level_tabs,'\t') << *j;
						if(*j=="S"){
							std::cout << std::endl << std::endl;
							next_level_tabs--;
							middle_tabs--;
						}else if((*j=="a" | *j=="b")&(first_node != 1 )){ middle_tabs--;}

						i.erase(j);
						j=i.begin();
					
					}else if(*j=="("){
						std::cout << std::string(next_level_tabs,'\t') << *j;
						std::cout << std::string(1,'\t') << "X" << std::string(1, '\t') << ")" << std::endl << std::endl;
						j+=3;
						i.erase(i.begin(), j);
						j=i.begin();
					}
				}
			}
		}else if(levels.size()==2){									//2 subtrees in tree
			for(auto subtree = levels.begin(); subtree!=levels.end()--; ++subtree){
				for(auto n = subtree -> begin(); n!=subtree -> end();){
					first_node++;
					if( *n =="a" | *n =="b" | *n =="S"){
						if(first_node==1){
							next_level_tabs = tabs - levels.size()-1;
						
							std::cout << std::string(next_level_tabs,'\t') << *n; 
							auto next_subtree = subtree;
							for(++next_subtree; next_subtree!=levels.end(); ++next_subtree){
								int erased_nodes = checkNext(levels.size(), middle_tabs, next_subtree[0][0]);
								next_subtree[0].erase(next_subtree -> begin(), next_subtree -> begin() + erased_nodes);
							}
							if(*n=="S"){
								next_level_tabs--;
							}else if((*n=="a" | *n=="b")&(first_node != 1 )){ middle_tabs--;}
						
							subtree[0].erase(n);												//remove printed nodes from current subtree
							n = subtree -> begin();
						}else{
							std::cout << std::string(next_level_tabs,'\t') << *n;
							subtree[0].erase(n);												//remove printed nodes from current subtree
							n = subtree -> begin();
						}
						
					}else if(*n == "("){
						std::cout << std::string(next_level_tabs,'\t') << *n;
						std::cout << std::string(levels.size()-1,'\t') << "X" << std::string(levels.size()-1, '\t') << ")";
						auto next_subtree = subtree;
						for(++next_subtree; next_subtree!=levels.end(); ++next_subtree){
							int erased_nodes = checkNext(levels.size(), middle_tabs, next_subtree[0][0]);
							next_subtree[0].erase(next_subtree -> begin(), next_subtree -> begin() + erased_nodes); 			//remove printed nodes from next subtree
						}
						n+=3;
						subtree[0].erase(subtree -> begin(), n);
						n=subtree -> begin();
					
					}else if(*n=="Y"){
						std::cout << std::string(next_level_tabs,'\t') << *n;
						std::cout << std::string(levels.size(),'\t') << "Z";
						auto next_subtree = subtree;
						for(++next_subtree; next_subtree!=levels.end(); ++next_subtree){
							int erased_nodes = checkNext(levels.size(), middle_tabs, next_subtree[0][0]);
							std::cout << std::endl << std::endl;						
							next_subtree[0].erase(next_subtree -> begin(), next_subtree -> begin() + erased_nodes); 		//will always be e (because of handling 2 subtrees)
							/*}else{															//+,-,*
							next_subtree[0].erase(next_subtree -> begin(), next_subtree -> begin() + erased_nodes + checkNext(levels.size(), middle_tabs, next_subtree[0][1])); 
							}*/
						} if(first_node==4){break;} //std::cout << "first " << first_node;//
						n+=2;
						subtree[0].erase(subtree -> begin(), n);
						n = subtree -> begin();
					}else if(*n == "*" | *n == "+" | *n == "-"){
						std::cout << std::string(levels.size()-1,'\t') << *n;
						std::cout << std::string(levels.size(),'\t') << "X";
						auto next_subtree = subtree;
						for(++next_subtree; next_subtree!=levels.end(); ++next_subtree){
							int erased_nodes = checkNext(levels.size(), middle_tabs, next_subtree[0][0]);
							next_subtree[0].erase(next_subtree -> begin(), next_subtree -> begin() + erased_nodes); 			//remove printed nodes from next subtree
						}
						n+=2;
						subtree[0].erase(subtree -> begin(), n);
						n = subtree -> begin();
					}
				}
				//first_node = 0;
				break;
			}
		}
		std::cout << std::endl << std::endl;
	}else{ std::cout << "Syntax tree constists of " << levels.size() << " subtrees and has " << tree_depth << " levels... too long to be printed!" << std::endl; }

}
int PrettyPrint::checkNext(int levels_size, int middle_tabs, std::string symbol){
	if(symbol == "*" | symbol == "+" | symbol == "-"){		
		std::cout << std::string(middle_tabs,'\t') << symbol;														//print +,-,* (operators)
		std::cout << std::string(levels_size,'\t') << "X" << std::endl << std::endl;
		return 2;
	}else if(symbol == "e"){														//remove e from next subtree
		return 1;
	}else if(symbol == "Y"){
		std::cout << std::string(middle_tabs,'\t') << symbol;														//print Y
		std::cout << std::string(levels_size,'\t') << "Z" << std::endl << std::endl;
		return 2;
	}else if(symbol == "S"){
		std::cout << std::string(middle_tabs,'\t') << symbol;
		return 1;
	}else if(symbol == "("){
		std::cout << std::string(levels_size+1,'\t') << symbol;
		std::cout << std::string(levels_size-1,'\t') << "X";
		std::cout << std::string(levels_size-1,'\t') << ")" << std::endl << std::endl;
		return 3;
	}
	/*auto next_node1 = levels.begin(); ++next_node1;
	for(auto p = next_node1 -> begin(); p!=next_node1 -> end(); ++p){ std::cout << *p;} break;	//check if next nodes have been removed*/
	return -1;
}
