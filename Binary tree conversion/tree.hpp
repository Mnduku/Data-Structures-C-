#include <sstream>

BET::BET(){
   root = nullptr;
}

BET::BET(const string& postfix){
   buildFromPostfix(postfix);
}

      
BET::BET(const BET& X){
    root = clone(X.root);
}


BET::~BET(){
   makeEmpty(root);
   if(root != nullptr) delete [] root;
}

const BET & BET::operator= (const BET & copy){
   if ( &copy != this )
    {
        BET temp(copy);
        swap(temp.root, root);
    }
    return *this;
}

size_t BET::size(){
   return size(root);
}

size_t BET::leaf_nodes(){
   return leaf_nodes(root);
}

bool BET::empty(){
   return(root == nullptr);
}

      
void BET::makeEmpty(Data* &t){
   if(t != nullptr){
      makeEmpty(t->lchild);
      makeEmpty(t->rchild);
      delete t;
   }
   t = nullptr;

}      

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
 

size_t BET::leaf_nodes(Data *t){
   size_t total = 0;

   if(t->rchild == nullptr && t->lchild == nullptr){
      total++;
   }  
   if(t->rchild != nullptr){
      leaf_nodes(t->rchild);
   }
   if(t->lchild != nullptr){
      leaf_nodes(t->lchild);
   }
   return total;  

}

BET::Data* BET::clone(Data *t){
   if(t == nullptr){
      return NULL;
   }

   Data *copy = new Data(t->data, clone(t->lchild), clone(t->rchild));
   return copy;
}


bool BET::errorcheck(const string x){

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


bool BET::isoperator(string x){
   return (x == "+" || x == "-" || x == "*" || x == "/");
}


bool BET::buildFromPostfix(const string& postfix){

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
      //   delete [] temp;                                     //PTR OR NO PTR???
      }
   }
   swap(root, billy.top());   
   return true;
}

void BET::printPostfixExpression(){
    printPostfixExpression(root);
    cout << endl;
}


void BET::printPostfixExpression(Data *n){
   if (n  == nullptr) {
        return;
    }
   printPostfixExpression(n->lchild);
   printPostfixExpression(n->rchild);
   cout << n->data  << " ";

}


void BET::printInfixExpression(){
   printInfixExpression(root);   
   cout << "\n";
}


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
