
#ifndef DL_TREE_H
#define DL_TREE_H
#include <stack>
#include <string>
#include <iostream>
using namespace std;
class BET{

//renamed BinaryNode to data for convenience

   public:
      BET();
      BET(const string& postfix);
      BET(const BET& X);
      ~BET();

      void add();
      void remove();
      bool errorcheck(const string x);          //funcs i added
      bool isoperator(string x);              
      
      bool buildFromPostfix(const string& postfix);
      const BET & operator= (const BET & copy);
      void printPostfixExpression();
      void printInfixExpression();
      size_t size();
      size_t leaf_nodes();
      bool empty();
     
   struct Data{

         Data* rchild;
         Data* lchild;
         string data;
      
      Data(){
         this->lchild = this->rchild = nullptr;
      };
   
      Data(string d){
         this->data = d;
         this->lchild = this->rchild = nullptr;
      };

      Data(string d, Data *l, Data *r){
         this->data = d;
         this->lchild = l;
         this->rchild = r;
      };
   };
 
   private:

      Data* root;

      void printInfixExpression(Data *n);
      void makeEmpty(Data* &t);
      Data * clone(Data *t);
      void printPostfixExpression(Data *n);
      size_t size(Data *t);
      size_t leaf_nodes(Data *t);
};

#include "tree.hpp"
#endif
