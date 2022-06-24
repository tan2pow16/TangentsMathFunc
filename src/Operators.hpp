/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 */

#ifndef __TANGENT_MATH_FUNC__OPERATION_ELEM
#define __TANGENT_MATH_FUNC__OPERATION_ELEM 65536

/*
 * An interface class allowing us to put both Operators and Operands into a same linked structure.
 */
class OperationElement
{
    public:
        virtual bool isOperator() const = 0;
};

class Operand : public OperationElement
{
    public:
        bool isOperator() const;
        
        virtual bool isNumeric() const = 0;
};

class IndexingOperand : public Operand
{
    private:
        int index;
    
    public:
        IndexingOperand(int _index);
        
        int getIndex() const;
        
        bool isNumeric() const;
};

/*
 * Operand to be put into the MathFunction::postfix expression.
 */

class NumericOperand : public Operand
{
    private:
        /*
         * Value of this operand. May be nullptr if this represents a named variable.
         */
        double value;
    
    public:
        /*
         * Constand value operand
         */
        NumericOperand(double _value);
        
        double getValue() const;
        
        bool isNumeric() const;
};

/*
 * Operator base-class
 */
class OperatorUnary;
class OperatorBinary;
class OperatorLeftBracket;

class Operator : public OperationElement
{
    private:
        // Disabled
        Operator(const Operator&);
        void operator=(const Operator&);
        
    protected:
        Operator(){}
    
    public:
        static const OperatorUnary& OPERATOR_NEGATIVE;
        static const OperatorBinary& OPERATOR_ADDITION;
        static const OperatorBinary& OPERATOR_NEGATION;
        static const OperatorBinary& OPERATOR_MULTIPLICATION;
        static const OperatorBinary& OPERATOR_DIVISION;
        static const OperatorBinary& OPERATOR_MODDING;
        static const OperatorBinary& OPERATOR_POWER;
        static const OperatorLeftBracket& OPERATOR_LEFT_BRACKET;
        
        virtual bool isBracket() const;
        
        bool isOperator() const;
        
        virtual bool isUnary() const = 0;
        
        virtual bool isFunction() const;
        
        virtual int getLevel() const = 0;
};

/*
 * Unary operator base-class
 */

class OperatorUnary : public Operator
{
    private:
        OperatorUnary(const OperatorUnary&);
        void operator=(const OperatorUnary&);
        
    protected:
        OperatorUnary(){}
        
    public:
        bool isUnary() const;
        
        virtual double operate(const double& input) const = 0;
};

/*
 * Binary operator base-class
 */

class OperatorBinary : public Operator
{
    private:
        OperatorBinary(const OperatorBinary&);
        void operator=(const OperatorBinary&);
        
    protected:
        OperatorBinary(){}
    
    public:
        bool isUnary() const;
        
        virtual double operate(const double& lhs, const double& rhs) const = 0;
};

/*
 * E.g. "-" in "-a" should correspond to this.
 */

class OperatorNegative : public OperatorUnary
{
    private:
        OperatorNegative(){}
        OperatorNegative(const OperatorNegative&);
        void operator=(const OperatorNegative&);
        
    public:
        double operate(const double& input) const;
        
        int getLevel() const;
    
    friend class Operator;
};

/*
 * Corresponding to "+"
 */

class OperatorAddition : public OperatorBinary
{
    private:
        OperatorAddition(){}
        OperatorAddition(const OperatorAddition&);
        void operator=(const OperatorAddition&);
        
    public:
        double operate(const double& lhs, const double& rhs) const;
        
        int getLevel() const;
    
    friend class Operator;
};

/*
 * Corresponding to "-"
 */

class OperatorNegation : public OperatorBinary
{
    private:
        OperatorNegation(){}
        OperatorNegation(const OperatorNegation&);
        void operator=(const OperatorNegation&);
        
    public:
        double operate(const double& lhs, const double& rhs) const;
        
        int getLevel() const;
    
    friend class Operator;
};

/*
 * Corresponding to "*"
 */

class OperatorMultiplication : public OperatorBinary
{
    private:
        OperatorMultiplication(){}
        OperatorMultiplication(const OperatorMultiplication&);
        void operator=(const OperatorMultiplication&);
        
    public:
        double operate(const double& lhs, const double& rhs) const;
        
        int getLevel() const;
    
    friend class Operator;
};

/*
 * Corresponding to "/"
 */

class OperatorDivision : public OperatorBinary
{
    private:
        OperatorDivision(){}
        OperatorDivision(const OperatorDivision&);
        void operator=(const OperatorDivision&);
        
    public:
        double operate(const double& lhs, const double& rhs) const;
        
        int getLevel() const;
    
    friend class Operator;
};

/*
 * Corresponding to "%"
 */

class OperatorModding : public OperatorBinary
{
    private:
        OperatorModding(){}
        OperatorModding(const OperatorModding&);
        void operator=(const OperatorModding&);
        
    public:
        double operate(const double& lhs, const double& rhs) const;
        
        int getLevel() const;
    
    friend class Operator;
};

/*
 * Corresponding to power of x. Please note that "^" sign is default to bitwise "xor", thus it MUST be redifined for both int, long long, float, double.
 */

class OperatorPower : public OperatorBinary
{
    private:
        OperatorPower(){}
        OperatorPower(const OperatorPower&);
        void operator=(const OperatorPower&);
        
    public:
        double operate(const double& lhs, const double& rhs) const;
        
        int getLevel() const;
    
    friend class Operator;
};

class OperatorLeftBracket : public OperatorBinary
{
    private:
        OperatorLeftBracket(){}
        OperatorLeftBracket(const OperatorLeftBracket&);
        void operator=(const OperatorLeftBracket&);
    
    public:
        bool isUnary() const;
        
        bool isBracket() const;
        
        double operate(const double& lhs, const double& rhs) const;
        
        int getLevel() const;
    
    friend class Operator;
};

class MathFunction;

class OperatorInvokeFunc : public Operator
{
    public:
        const MathFunction* func;
        int varCount;
        
        OperatorInvokeFunc(MathFunction* _f);
        
        bool isFunction() const;
        
        bool isUnary() const;
        
        int getLevel() const;
};

#endif
