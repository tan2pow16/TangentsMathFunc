#include <string.h>

#include "../TangentsMathFunc.hpp"

template HashEntry<MathFunctionIdentifier const, MathFunction>::~HashEntry();

template HashTable<MathFunctionIdentifier const, MathFunction>::HashTable(int);
template MathFunction* HashTable<MathFunctionIdentifier const, MathFunction>::remove(MathFunctionIdentifier const*);
template MathFunction* HashTable<MathFunctionIdentifier const, MathFunction>::get(MathFunctionIdentifier const*);
template void HashTable<MathFunctionIdentifier const, MathFunction>::put(MathFunctionIdentifier const*, MathFunction*, bool&);
template HashTable<MathFunctionIdentifier const, MathFunction>::~HashTable();

template HashEntry<String, int>::~HashEntry();

template HashTable<String, int>::HashTable(int);
template int* HashTable<String, int>::get(String const*);
template void HashTable<String, int>::put(String*, int*, bool&);
template HashTable<String, int>::~HashTable();
