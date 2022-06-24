/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 */

#include "LinkedStack.hpp"

template <typename T>
LinkedStack<T>::~LinkedStack()
{
    Node<T>* cache = nullptr;
    while((cache = this->head) != nullptr)
    {
        this->head = cache->getNext();
        delete cache;
    }
}

template <typename T>
bool LinkedStack<T>::isEmpty() const
{
    return this->head == nullptr;
}

template <typename T>
T* LinkedStack<T>::peek() const
{
    return (this->head == nullptr ? nullptr : this->head->getValue());
}

template <typename T>
T* LinkedStack<T>::pop()
{
    if(head == nullptr)
    {
        return nullptr;
    }
    else
    {
        Node<T>* cache = this->head;
        T* ret = cache->getValue();
        cache->setValue(nullptr, false);
        this->head = cache->getNext();
        delete cache;
        this->size--;
        return ret;
    }
}

template <typename T>
void LinkedStack<T>::push(T* _entry)
{
    this->head = new Node<T>(_entry, this->head, false);
    this->size++;
}

template <typename T>
int LinkedStack<T>::getSize() const
{
    return this->size;
}

#include "LinkedStack.inl"
