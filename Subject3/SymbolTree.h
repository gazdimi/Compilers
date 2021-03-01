class SymbolTree{
    public:
        struct node{
            struct node *parent;
            struct node *left;
            struct node *middle;
            struct node *right;
            char data;
        };
        static node* createNode(char _data){
            node* temp = new node;
            temp -> data = _data;
            temp -> parent = NULL;
            temp -> left = NULL;
            temp -> middle = NULL;
            temp -> right = NULL;
            return temp;
        }
};

/*node* SymbolTree::createNode(char _data){
    node* temp = new node;
    temp -> data = _data;
    temp -> parent = NULL;
    temp -> left = NULL;
    temp -> middle = NULL;
    temp -> right = NULL;
    return temp;
}*/