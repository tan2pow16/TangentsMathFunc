/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 */

#include "HashTable.hpp"

template<typename K, typename T>
HashEntry<K, T>::HashEntry(K* _key, T* _value, bool _del)
{
    this->key = _key;
    this->value = _value;
    this->del = _del;
}

template<typename K, typename T>
HashEntry<K, T>::~HashEntry()
{
    if(this->del)
    {
        delete this->key;
        delete this->value;
    }
}

template<typename K, typename T>
K* HashEntry<K, T>::getKey() const
{
    return this->key;
}

template<typename K, typename T>
T* HashEntry<K, T>::getValue() const
{
    return this->value;
}

template<typename K, typename T>
int HashEntry<K, T>::hash(int capacity)
{
    return this->key->hash(capacity);
}

template<typename K, typename T>
HashTable<K, T>::HashTable(int _cap)
{
    this->capacity = _cap;
    this->size = 0;
    this->entries = new Node<HashEntry<K, T>>*[this->capacity];
    memset(this->entries, 0, this->capacity * sizeof(new Node<HashEntry<K, T>>*));
}

template<typename K, typename T>
HashTable<K, T>::~HashTable()
{
    static Node<HashEntry<K, T>>* cache = nullptr;
    for(int i = 0 ; i < this->capacity ; i++)
    {
        cache = this->entries[i];
        while(cache != nullptr)
        {
            this->entries[i] = this->entries[i]->getNext();
            delete cache;
            cache = this->entries[i];
        }
    }
}

template<typename K, typename T>
int HashTable<K, T>::getSize() const
{
    return this->size;
}

template<typename K, typename T>
int HashTable<K, T>::getCapacity() const
{
    return this->capacity;
}

template<typename K, typename T>
void HashTable<K, T>::put(K* _key, T* _value, bool& replacing)
{
    replacing = false;
    int hash = _key->hash(this->capacity);
    if(hash < 0)
    {
        hash = (hash % this->capacity) + this->capacity - 1;
    }
    else
    {
        hash %= this->capacity;
    }
    
    static Node<HashEntry<K, T>>* cache = nullptr;
    
    cache = this->entries[hash];
    while(cache != nullptr)
    {
        if(*(cache->getValue()->getKey()) == *(_key))
        {
            cache->setValue(new HashEntry<K, T>(_key, _value, false), false);
            replacing = true;
            return;
        }
        cache = cache->getNext();
    }
    
    this->size++;
    this->entries[hash] = new Node<HashEntry<K, T>>(new HashEntry<K, T>(_key, _value, false), this->entries[hash], false);
}

template<typename K, typename T>
T* HashTable<K, T>::get(const K* _key)
{
    int hash = _key->hash(this->capacity);
    if(hash < 0)
    {
        hash = (hash % this->capacity) + this->capacity - 1;
    }
    else
    {
        hash %= this->capacity;
    }
    
    static Node<HashEntry<K, T>>* cache = nullptr;
    
    cache = this->entries[hash];
    while(cache != nullptr)
    {
        if(*(cache->getValue()->getKey()) == *(_key))
        {
            return cache->getValue()->getValue();
        }
        cache = cache->getNext();
    }
    
    return nullptr;
}

template<typename K, typename T>
T* HashTable<K, T>::remove(const K* _key)
{
    int hash = _key->hash(this->capacity);
    if(hash < 0)
    {
        hash = (hash % this->capacity) + this->capacity - 1;
    }
    else
    {
        hash %= this->capacity;
    }
    
    static Node<HashEntry<K, T>>* cache1 = nullptr;
    static Node<HashEntry<K, T>>* cache2 = nullptr;
    
    if(this->entries[hash] == nullptr)
    {
        return nullptr;
    }
    
    cache1 = this->entries[hash];
    if(*(cache1->getValue()->getKey()) == *_key)
    {
        this->entries[hash] = this->entries[hash]->getNext();
        T* _ret = cache1->getValue()->getValue();
        delete cache1;
        this->size--;
        return _ret;
    }
    
    cache2 = cache1->getNext();
    while(cache2 != nullptr)
    {
        if(*(cache2->getValue()->getKey()) == *(_key))
        {
            cache1->setNext(cache2->getNext());
            T* _ret = cache2->getValue()->getValue();
            delete cache2;
            this->size--;
            return _ret;
        }
        cache1 = cache2;
        cache2 = cache2->getNext();
    }
    
    return nullptr;
}

#include "HashTable.inl"
