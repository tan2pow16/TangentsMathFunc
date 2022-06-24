#include "StringWrap.hpp"

String::String(const string& _val)
{
    this->value = _val;
}

const string& String::cpp_str() const
{
    return this->value;
}

/*
 * Hash function based on the content.
 */
int String::hash(int capacity) const
{
    int init = 1;
    for(int i = 0 ; i < this->value.size() ; i++)
    {
        switch(i % 3)
        {
            case 0:
                init *= this->value[i];
                init %= capacity;
                break;
            case 1:
                init += this->value[i];
                init %= capacity;
                break;
            case 2:
                init -= this->value[i];
                if(init < 0)
                {
                    init = (init % capacity) + capacity - 1;
                }
                init %= capacity;
                break;
        }
    }
    return init;
}
        
bool String::operator==(const String& str) const
{
    return this->value == str.value;
}
