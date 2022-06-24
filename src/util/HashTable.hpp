/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 */

#include "LinkedNode.hpp"

#ifndef __TANGENT_MATH_FUNC__HASH_TABLE
#define __TANGENT_MATH_FUNC__HASH_TABLE 65536

template<typename K, typename T>
class HashEntry
{
    private:
        K* key;
        T* value;
        
        bool del;
        
        HashEntry(const HashEntry<K, T>&);
        void operator=(const HashEntry<K, T>&);
    
    public:
        HashEntry(K* _key, T* _value, bool _del);
        ~HashEntry();
        
        K* getKey() const;
        T* getValue() const;
    
        int hash(int capacity);
};

template<typename K, typename T>
class HashTable
{
    private:
        int capacity;
        
        int size;
        Node<HashEntry<K, T>>** entries;
        
        HashTable(const HashTable<K, T>&);
        void operator=(const HashTable<K, T>&);
        
    public:
        HashTable(int _cap);
        ~HashTable();
        
        int getSize() const;
        int getCapacity() const;
        
        void put(K* _key, T* _value, bool& replacing);
        T* get(const K* _key);
        
        T* remove(const K* _key);
};

#endif
