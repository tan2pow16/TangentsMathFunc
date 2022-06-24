/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 */

#include <string>

#ifndef __TANGENT_MATH_FUNC__STRING
#define __TANGENT_MATH_FUNC__STRING 65536

using namespace std;

class String
{
    private:
        string value;
    
    public:
        String(const string& _val);
        
        const string& cpp_str() const;
        
        /*
         * Hash function based on the content.
         */
        int hash(int capacity) const;
        
        bool operator==(const String& str) const;
};

#endif
