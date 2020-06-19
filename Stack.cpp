/**
* Author : Ahmet Isik
* ID: 21702226
* Section : 02
* Assignment : 5
* this class declaration is taken from lecture slides of CS201 course and also textbook
*/
#include "Stack.h"

Stack::Stack(): top(-1){

}

bool Stack::isEmpty() const{

   return top < 0;

}

bool Stack::push(int newItem){

   // if stack has no more room for
   // another item
   if (top >= MAX_STACK-1)
      return false;

   else{
      ++top;
      items[top] = newItem;
      return true;
   }

}

bool Stack::pop(){

   if (isEmpty())
      return false;

   // stack is not empty; pop top
   else {
      --top;
      return true;
   }

}

bool Stack::pop(int& stackTop){

   if (isEmpty())
      return false;

   // stack is not empty; retrieve top
   else {
      stackTop = items[top];
      --top;
      return true;
   }

}

bool Stack::getTop(int& stackTop)
             const{

   if (isEmpty())
      return false;

   // stack is not empty; retrieve top
   else {
      stackTop = items[top];
      return true;
   }

}

