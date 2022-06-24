/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 *
 * Usage:
 *    MathFunction("f(x, y, ...)", "<operations>");
 */

#include <string>

#include "util/LinkedNode.hpp"
#include "util/HashTable.hpp"
#include "misc/StringWrap.hpp"
#include "Operators.hpp"

#ifndef __TANGENT_MATH_FUNC__
#define __TANGENT_MATH_FUNC__ 65536

using namespace std;

/*
 * The identifier for a MathFunction in a MathFunctionNamespace.
 *  The identifier is NOT templated since MathFunction's with differend operand types will NEVER be put into same MathFunctionNamespace.
 */
class MathFunctionIdentifier
{
    private:
        /*
         * Name
         */
        string name;
        
        /*
         * Variable count
         */
        int varCount;
        
        // Disabled
        MathFunctionIdentifier(const MathFunctionIdentifier&);
        void operator=(const MathFunctionIdentifier&);
    
    public:
        MathFunctionIdentifier(const string& _name, int _vCount);
        
        const string& getName() const;
        
        const int getVariablesCount() const;
        
        bool operator==(const MathFunctionIdentifier& comp) const;
        
        /*
         * Hash function that should give out a reasonable hash value base on the name, varCount and the passed-in capacity.
         */
        int hash(int capacity) const;
};

/*
 * Namespace of the MathFunctions
 */
class MathFunctionNamespace
{
    private:
        /*
         * All mathfunctions in this namespace
         */
        HashTable<const MathFunctionIdentifier, MathFunction>* functions;
        
        // Disabled.
        MathFunctionNamespace(const MathFunctionNamespace&);
        void operator=(const MathFunctionNamespace&);
        
        /*
         * If a MathFunction is spawned as a local variable, and later being referenced by other math function(s),
         *  the function should spawn a copy to replace itself in the namespace before being destroyed.
         */
        void replace(const MathFunctionIdentifier* ident, MathFunction* _replace);
        
                
        /*
         * Add a function into this namespace.
         *  If the function has a same identifier with a function already in this namespace,
         *  then the operation should be rejected and return false.
         */
        bool add(const MathFunctionIdentifier* ident, MathFunction* func);
        
        /*
         * Remove a MathFunction from this object. If the function is referenced by other functions in this namespace,
         *  it WILL NOT be remove and the operation returns false.
         */
        bool del(const MathFunctionIdentifier* ident);
    
    public:
        MathFunctionNamespace();
        ~MathFunctionNamespace();
        
        static const int MAX_FUNCTIONS_CAPACITY = 65537;
        
    friend class MathFunction;
};

/*
 * Math function object.
 */
class MathFunction
{
    private:
        static MathFunctionNamespace& DEFAULT_NAMESPACE;
        
        /*
         * Identifier of a function, including a string as its name and an integer representing the number of arguments.
         */
        MathFunctionIdentifier* identifier;
        
        /*
         * The original expression.
         */
        string expression;
        
        /*
         * The namespace containing this MathFuncton
         */
        MathFunctionNamespace& NAME_SPACE;
        
        /*
         * The linked postfix expression which is easy to access by calling Node::next() to acquire the next operation.
         */
        Node<const OperationElement>* postfixOperations = nullptr; // circular tail
        
        // Disabled
        MathFunction(const MathFunction&);
        void operator=(const MathFunction&);
        
        /*
         * Whether this object is once referenced by other functions. If YES, then the function will copy itself in its namespace before being destroyed.
         */
        bool isReferencedByOthers = false;
        
        /*
         * If true, all the spaces WILL be removed. c:
         */
        static bool isStringSpacedValid(string& _str, int brackets_pair_limit, bool isIdent);
        
        static bool isAlphabetOrNumber(char c);
        
        int parseInnerFunctionInput(string& _expressions, int& endIndex, HashTable<String, int>& availableVariables);
        
        void addToNode(const OperationElement* elem);
    
    protected:
        MathFunction(MathFunctionNamespace& _name_space, MathFunctionIdentifier* _identifier, bool _replace = false);
        
        virtual double invoke(double* operands) const;
        
    public:
        static const int MAX_VARIABLE_COUNT = 257;
        
        static const MathFunction& SIN; // Sine
        static const MathFunction& COS; // Cosine
        static const MathFunction& TAN; // Tangent
        static const MathFunction& SINH; // Hyperbolic sine
        static const MathFunction& COSH; // Hyperbolic cosine
        static const MathFunction& TANH; // Hyperbolic tangent
        static const MathFunction& ASIN; // Arc sine
        static const MathFunction& ACOS; // Arc cosine
        static const MathFunction& ATAN; // Arc tangent
        static const MathFunction& ATAN2; // Arc tangent(x, y)
        static const MathFunction& EXP; // Exponential
        static const MathFunction& LN; // Natural log
        static const MathFunction& LOG10; // Log_10()
        static const MathFunction& LOG; // Log(base, x)
        static const MathFunction& CEIL; // Ceiling
        static const MathFunction& FLOOR; // Floor
        
        /* 
         * e.g. MathFunction(ns, "F(a, B, x, alpha)", "(a + B * (2 - x)) ^ alpha");
         *  The created function MUST be added into the "namespace" passed into the constructor for future usage.
         */
        MathFunction(const string& _identifier, const string& formula);
        
        /* 
         * e.g. MathFunction(ns, "F(a, B, x, alpha)", "(a + B * (2 - x)) ^ alpha");
         *  The created function MUST be added into the "namespace" passed into the constructor for future usage.
         */
        MathFunction(MathFunctionNamespace& _name_space, const string& _identifier, const string& formula);
        
        ~MathFunction();
        
        /*
         * Invoke the function. e.g. 
         *  MathFunction* mf = new MathFunction(ns, "f(a, b, c)", "(a + b) ^ c");
         *  mf.invoke({1.0, 2.0, 0.03});                  
         */
        virtual double invoke(initializer_list<double> var_list) const;
        
        const MathFunctionIdentifier& getIdentifier() const;
    
    friend class MathFunctionNamespace;
};

#endif
