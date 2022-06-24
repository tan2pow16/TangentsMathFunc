/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 */

#include "LinkedNode.hpp"

#ifndef __TANGENT_MATH_FUNC__LINKED_STACK
#define __TANGENT_MATH_FUNC__LINKED_STACK 65536

template <typename T>
class LinkedStack
{
    private:
        Node<T>* head = nullptr;
        int size = 0;
        
        // Forbidden
        LinkedStack(const LinkedStack<T>&);
        void operator=(const LinkedStack<T>&);
    
    public:
        LinkedStack(){}
        ~LinkedStack();
        
        bool isEmpty() const;
        T* peek() const;
        T* pop();
        void push(T* _entry);
        
        int getSize() const;
};

#endif
