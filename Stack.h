/**
* Author : Ahmet Isik
* ID: 21702226
* Section : 02
* Assignment : 5
* this class declaration is taken from lecture slides of CS201 course and also text book
*/
#ifndef STACK_H
#define STACK_H
const int MAX_STACK = 10000;
// this class definitions with Stack.cpp are copied from lecture slides of CS201 course
class Stack{

public:
   Stack();

   bool isEmpty() const;
   bool push(const int newItem);
   bool pop();
   bool pop(int& stackTop);
   bool getTop(int& stackTop) const;

private:
   // array of stack items
   int items[MAX_STACK];
   // index to top of stack
   int top;
};


#endif // STACK_H
