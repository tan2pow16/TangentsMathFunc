/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 */

#include <stdexcept>

#ifndef __TANGENT_MATH_FUNC__TANGENT_FUNC_EXCPET
#define __TANGENT_MATH_FUNC__TANGENT_FUNC_EXCPET 65536

using namespace std;

/*
 * Thrown when dividing something by 0.
 */
class DividedByZeroException : public exception
{
    private:
        static const char* CANNED_MESSAGE;
    
    public:
        const char* what() const noexcept;
};

/*
 * Thrown when invalid arguments are passed into the function MathFunction<T>::invoke();
 */
class InvalidArgumentException : public exception
{
    private:
        char* message;
        
        static const char* CANNED_MESSAGE;
    
    public:
        InvalidArgumentException(const char* _msg);
        InvalidArgumentException(const InvalidArgumentException& copy);
        ~InvalidArgumentException();
        const InvalidArgumentException& operator=(const InvalidArgumentException& copy);
        const char* what() const noexcept;
};

/*
 * Thrown when an invalid formulation is passed into the constructor MathFunction<T>();
 */
class InvalidFormulaException : public exception
{
    private:
        char* message;
        
        static const char* CANNED_MESSAGE;
        
    public:
        InvalidFormulaException(const char* sub_msg);
        InvalidFormulaException(const InvalidFormulaException& _copy);
        ~InvalidFormulaException();
        const InvalidFormulaException& operator=(const InvalidFormulaException& _copy);
        const char* what() const noexcept;
};

#endif
