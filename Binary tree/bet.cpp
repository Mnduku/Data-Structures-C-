#include <sstream>

BET::BET(){
   root = nullptr;
}


//builds tree from postfix  expression. sets root to nullptr to avoid stack dump
//if the first expression is invalid
BET::BET(const string& postfix){
   bool check = errorcheck(postfix);
   if (check == true){
      root = nullptr;
      return;
   }
   else buildFromPostfix(postfix);

}

//builds tree with  an  already existing tree
BET::BET(const BET& X){
    root = clone(X.root);
}


BET::~BET(){
   makeEmpty(root);
   if(root != nullptr) delete [] root;
}

// = assignmeny operator
const BET & BET::operator= (const BET & copy){
   if ( &copy != this )
    {
        BET temp(copy);
        swap(temp.root, root);
    }
    return *this;
}

//calls helper size function to return sizee
size_t BET::size(){
   return size(root);
}

// calls helper root function to return root
size_t BET::leaf_nodes(){
   return leaf_nodes(root);
}

//checks if root points to a node
bool BET::empty(){
   return(root == nullptr);
}

//recursively calls  delete for each child on each side of the tree
void BET::makeEmpty(Data* &t){
   if(t != nullptr){
      makeEmpty(t->lchild);
      makeEmpty(t->rchild);
      delete t;
   }
   t = nullptr;

}      

//recursively goes through the left and right side of tree and calculates size
size_t BET::size(Data *t){ 
   size_t total = 0;
   if(root != nullptr){
      total++; 
   }
   if(t->rchild != nullptr){
      total += size(t->rchild);
   }
   if(t->lchild != nullptr){
      total += size(t->lchild);
   }
   return total;
}
 

//recursiely travels through tree in incrememts for each node with no children
size_t BET::leaf_nodes(Data *t){
   size_t total = 0;

   if(t->rchild == nullptr && t->lchild == nullptr){
      total++;
   }
   if(t->lchild != nullptr){
      total += leaf_nodes(t->lchild);
   }
   if(t->rchild != nullptr){
      total += leaf_nodes(t->rchild);
   }
   return total;

}

//clones a node
BET::Data* BET::clone(Data *t){
   if(t == nullptr){
      return NULL;
   }

   Data *copy = new Data(t->data, clone(t->lchild), clone(t->rchild));
   return copy;
}


bool BET::errorcheck(const string x){

/* This function is used to prevent errors by checking if the post fix expression is
acceptable. It does this by keeping track of the amount of operands. There should be 2 operands
before any operator and no more then one operator in a row. If either of these rules are broken
the expression will be deemed invalid and the program will stop. Also checks for invalid characters
*/

  istringstream zzz(x);
  string c;
  int operandcount = 0;
  int operatorcount = 0;
  int totalopercount = 0;

  while(zzz >> c){
//     cout  <<  "Error checking current: "  <<  c << endl;

     if(c == "!" ||  c  == "?" || c == "@" || c == "#" || c == "\"" ||  c == "$"  || 
     c == "%" ||  c == "^" || c == ">" || c == "<" || c == "," || c == "!" ||  c == "}" 
     || c == "|" || c == "{" || c == "~" || c == "`" || c == ")" || c == "("){     

     cout << "CONVERSION ERROR: INVALID  CHARACTERS ! " << endl;
     return true; 
     }

     else if(isoperator(c) == true){

        operatorcount++;
        if(operandcount <= 1){
           cout << "CONVERSION ERROR: OPERATOR WITH NO PREVIOUS OPERATORS ! " << endl;
           return true;               
        }
        else operandcount --;
     }

     else{
        operandcount++;
        totalopercount ++;
     }
    }

    if(operatorcount >= totalopercount){
        cout << "CONVERSION ERROR: EXTRA OPERATORS ! " << endl;
        return true;
    }
    if(operandcount > 1){
        cout << "CONVERSION ERROR: EXTRA OPERANDS ! " << endl;
        return true;
    }
    if( totalopercount > operatorcount + 1){
        cout << "CONVERSION ERROR: EXTRA OPERANDS ! " << endl;
        return true;
    }

    return false;   
}

//simple function to check if a string is a valid operator
bool BET::isoperator(string x){
   return (x == "+" || x == "-" || x == "*" || x == "/");
}


bool BET::buildFromPostfix(const string& postfix){
/*
This function builds the tree with a stack implemented. It does this by reading in the first 2 operands
and pushing them into the stack. When the operator is read, Both previous operators are popped from the
stack and the operator is pushed into it, with pointer connections to both previous operands, Thus creating
the tree. Errors are prevented by the error checking function beforehand*/


   if(errorcheck(postfix) == true){
      cout << "ERROR: Invalid postfix expresion" << endl;
      return false;
   }
   if (postfix.length() == 0){
      return false;
   }

   stack<Data*> billy;                          // STACK   
   string current;
   int i = 0;
   istringstream iss(postfix);


   while(iss >> current){
  //    cout <<  current << endl;

      if(isoperator(current) == true){
         Data* p1 = billy.top();
         billy.pop();
         Data* p2 = billy.top();
         billy.pop();
         Data* p3 = new Data(current, p2, p1);
         billy.push(p3);
      }
      else {
         Data* temp = new Data(current);
         billy.push(temp);
      }
   }
   swap(root, billy.top());   
   return true;
}

//calls helper function to print postfix
void BET::printPostfixExpression(){
    printPostfixExpression(root);
    cout << endl;
}


//recursiely prints postfix expression
void BET::printPostfixExpression(Data *n){
   if (n  == nullptr) {
        return;
    }
   printPostfixExpression(n->lchild);
   printPostfixExpression(n->rchild);
   cout << n->data  << " ";

}

//calls helper function
void BET::printInfixExpression(){
   printInfixExpression(root);   
   cout << "\n";
}


//Prints the infix of the postfix expression.It is called recursively and will extend to each of the children and
//makes sure to add paranthesis in between operators for legibility
void BET::printInfixExpression(Data *n){
    if (n == nullptr) {
        return;
    }
    if (isoperator(n->data)) {
        cout << "(";
    }
    printInfixExpression(n->lchild);
    cout << n->data;
    cout << " " ;
    printInfixExpression(n->rchild);
    if (isoperator(n->data)) {
        cout << ")";
    }
}
