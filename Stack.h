//
//  Stack.h
//  Stack
//
//  Created by Hayden Crabb on 10/15/18.
//  Copyright © 2018 Coconut Productions. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include <iostream>
using namespace std;

template <class type>
class Stack {
private:
    type * stackPointer;
    int count;
    
public:
    Stack();
    ~Stack();
    void push(type *);
    type * getTop();
    void pop();
    int size();
};


template <class type>
Stack<type>::Stack() {
    stackPointer = nullptr;
    count = 0;
}

template <class type>
Stack<type>::~Stack() {
    //delete all;
}
template <class type>
int Stack<type>::size() {
    return count;
}

template <class type>
void Stack<type>::push(type * newElement) {
    newElement->previous = stackPointer;
    newElement->next = nullptr;
    if (stackPointer != nullptr)
    {
        stackPointer->next = newElement;
    }
    
    stackPointer = newElement;
    
    count++;
}
template <class type>
type * Stack<type>::getTop() {
    return stackPointer;
}
template <class type>
void Stack<type>::pop()
{
    if (count > 0)
    {
        type * temp = stackPointer;
        stackPointer = stackPointer->previous;
        delete temp;
        count--;
    }
}


#endif /* Stack_h */
