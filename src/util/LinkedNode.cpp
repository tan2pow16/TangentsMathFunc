/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 */

#include "LinkedNode.hpp"

template <typename T>
Node<T>::Node(T* _val, bool _del)
{
    this->value = _val;
    this->del = _del;
    this->next = nullptr;
}

template <typename T>
Node<T>::Node(T* _val, Node<T>* _next, bool _del)
{
    this->value = _val;
    this->del = _del;
    this->next = _next;
}

template <typename T>
Node<T>::~Node()
{
    if(this->del)
    {
        delete this->value;
    }
}

template <typename T>
T* Node<T>::getValue() const
{
    return this->value;
}

template <typename T>
void Node<T>::setValue(T* newValue, bool _del)
{
    if(this->del)
    {
        delete this->value;
    }
    this->del = _del;
    this->value = newValue;
}

template <typename T>
Node<T>* Node<T>::getNext() const
{
    return this->next;
}

template <typename T>
void Node<T>::setNext(Node<T>* _next)
{
    this->next = _next;
}

#include "LinkedNode.inl"
