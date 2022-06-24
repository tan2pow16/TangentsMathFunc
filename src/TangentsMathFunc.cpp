/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 */

#include <initializer_list>
#include <math.h>
#include <string>
#include <string.h>

#include "util/LinkedStack.hpp"
#include "misc/TFException.hpp"
#include "Operators.hpp"
#include "TangentsMathFunc.hpp"

MathFunctionNamespace& MathFunction::DEFAULT_NAMESPACE = *(new MathFunctionNamespace());

class MathFunctionSine : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionSine(MathFunctionNamespace& ns);
};

class MathFunctionCosine : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionCosine(MathFunctionNamespace& ns);
};

class MathFunctionTangent : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionTangent(MathFunctionNamespace& ns);
};

class MathFunctionHyperbolicSine : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionHyperbolicSine(MathFunctionNamespace& ns);
};

class MathFunctionHyperbolicCosine : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionHyperbolicCosine(MathFunctionNamespace& ns);
};

class MathFunctionHyperbolicTangent : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionHyperbolicTangent(MathFunctionNamespace& ns);
};

class MathFunctionArcSine : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionArcSine(MathFunctionNamespace& ns);
};

class MathFunctionArcCosine : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionArcCosine(MathFunctionNamespace& ns);
};

class MathFunctionArcTangent : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionArcTangent(MathFunctionNamespace& ns);
};

class MathFunctionArcTangent2 : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionArcTangent2(MathFunctionNamespace& ns);
};

class MathFunctionExponential : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionExponential(MathFunctionNamespace& ns);
};

class MathFunctionNaturalLog : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionNaturalLog(MathFunctionNamespace& ns);
};

class MathFunctionLog10 : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionLog10(MathFunctionNamespace& ns);
};

class MathFunctionLog : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionLog(MathFunctionNamespace& ns);
};

class MathFunctionCeiling : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionCeiling(MathFunctionNamespace& ns);
};

class MathFunctionFloor : public MathFunction
{
    protected:
        double invoke(double* operands) const;
    
    public:
        MathFunctionFloor(MathFunctionNamespace& ns);
};

MathFunctionIdentifier::MathFunctionIdentifier(const string& _name, int _vCount)
{
    this->name = _name;
    this->varCount = _vCount;
}

const string& MathFunctionIdentifier::getName() const
{
    return this->name;
}

const int MathFunctionIdentifier::getVariablesCount() const
{
    return this->varCount;
}

bool MathFunctionIdentifier::operator==(const MathFunctionIdentifier& comp) const
{
    return (comp.name == this->name && comp.varCount == this->varCount);
}

int MathFunctionIdentifier::hash(int capacity) const
{
    int init = 1;
    for(int i = 0 ; i < this->name.size() ; i++)
    {
        switch(i % 3)
        {
            case 0:
                init *= this->name[i];
                init %= capacity;
                break;
            case 1:
                init += this->name[i];
                init %= capacity;
                break;
            case 2:
                init -= this->name[i];
                if(init < 0)
                {
                    init = (init % capacity) + capacity - 1;
                }
                init %= capacity;
                break;
        }
    }
    for(int i = 0 ; i < this->varCount ; i++)
    {
        init = (init * init) % capacity;
    }
    return init;
}

MathFunctionNamespace::MathFunctionNamespace()
{
    this->functions = new HashTable<const MathFunctionIdentifier, MathFunction>(MAX_FUNCTIONS_CAPACITY);
}

MathFunctionNamespace::~MathFunctionNamespace()
{
    delete this->functions;
}

void MathFunctionNamespace::replace(const MathFunctionIdentifier* ident, MathFunction* _replace)
{
    static bool dummy;
    if(this->functions->remove(ident))
    {
        this->functions->put(ident, _replace, dummy);
    }
}

bool MathFunctionNamespace::add(const MathFunctionIdentifier* ident, MathFunction* func)
{
    if(this->functions->get(ident) == nullptr)
    {
        static bool dummy;
        this->functions->put(ident, func, dummy);
        return true;
    }
    return false;
}

bool MathFunctionNamespace::del(const MathFunctionIdentifier* ident)
{
    static MathFunction* cache = nullptr;
    if((cache = this->functions->get(ident)) != nullptr)
    {
        if(!(cache->isReferencedByOthers))
        {
            this->functions->remove(ident);
            return true;
        }
    }
    return false;
}

bool MathFunction::isAlphabetOrNumber(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void MathFunction::addToNode(const OperationElement* elem)
{
    if(this->postfixOperations == nullptr)
    {
        this->postfixOperations = new Node<const OperationElement>(elem, false);
        this->postfixOperations->setNext(this->postfixOperations);
    }
    else
    {
        Node<const OperationElement>* _node = new Node<const OperationElement>(elem, false);
        _node->setNext(this->postfixOperations->getNext());
        this->postfixOperations->setNext(_node);
        this->postfixOperations = this->postfixOperations->getNext();
    }
}

MathFunction::MathFunction(MathFunctionNamespace& _name_space, MathFunctionIdentifier* _identifier, bool _replace) : NAME_SPACE(_name_space)
{
    this->identifier = _identifier;
    if(_replace)
    {
        this->NAME_SPACE.replace(this->identifier, this);
    }
    else
    {
        this->NAME_SPACE.add(this->identifier, this);
    }
}

bool MathFunction::isStringSpacedValid(string& _str, int brackets_pair_limit, bool isIdent)
{
    int _len = _str.size();
    char* copy = new char[_len + 1];
    memset(copy, 0, _len + 1);
    int index = 0;
    int brackets = 0;
    for(int i = 0 ; i < _len ; i++)
    {
        if(_str[i] == ' ')
        {
            if((i > 0 && isAlphabetOrNumber(_str[i - 1])) && (i < (_len - 1) && isAlphabetOrNumber(_str[i + 1])))
            {
                delete copy;
                return false;
            }
        }
        else
        {
            if(_str[i] == '(')
            {
                brackets++;
            }
            else if(_str[i] == ')')
            {
                brackets--;
                if(brackets_pair_limit >= 0)
                {
                    brackets_pair_limit--;
                    if(brackets_pair_limit < 0)
                    {
                        delete copy;
                        return false;
                    }
                }
                if(brackets < 0)
                {
                    delete copy;
                    return false;
                }
            }
            else if(isIdent)
            {
                if(strchr("+-*/%^", _str[i]) != nullptr)
                {
                    delete copy;
                    return false;
                }
            }
            copy[index++] = _str[i];
        }
    }
    _str = copy;
    return (brackets_pair_limit <= 0);
}

MathFunction::MathFunction(const string& _identifier, const string& formula) : MathFunction::MathFunction(DEFAULT_NAMESPACE, _identifier, formula) {}

MathFunction::MathFunction(MathFunctionNamespace& _name_space, const string& _identifier, const string& formula) : NAME_SPACE(_name_space)
{
    string __ident = _identifier;
    string __formu = formula;
    
    if(isStringSpacedValid(__ident, 1, true) && isStringSpacedValid(__formu, -1, false))
    {
        this->expression = __ident + '=' + __formu;
        string __name = __ident.substr(0, __ident.find_first_of('('));
        int _cache0 = __ident.find_first_of('(') + 1;
        string __vars = __ident.substr(_cache0, __ident.find_first_of(')') - _cache0);
        int varCount = 0;
        HashTable<String, int> varTable(MAX_VARIABLE_COUNT);
        int strIndexStart = 0;
        int strIndexEnd = -1;
        static bool error = false;
        while((strIndexEnd = __vars.find_first_of(',', strIndexStart)) != string::npos)
        {
            varTable.put(new String(__vars.substr(strIndexStart, strIndexEnd - strIndexStart)), new int(varCount++), error);
            if(error)
            {
                throw InvalidFormulaException("Conflicting variable names!");
            }
            strIndexStart = strIndexEnd + 1;
        }
        varTable.put(new String(__vars.substr(strIndexStart, __vars.size() - strIndexStart)), new int(varCount++), error);
        if(error)
        {
            throw InvalidFormulaException("Conflicting variable names!");
        }
        
        this->identifier = new MathFunctionIdentifier(__name, varCount);
        if(!(this->NAME_SPACE.add(this->identifier, this)))
        {
            throw InvalidArgumentException("Conflicting function name!");
        }
        
        bool previouslyOperator = true;
        
        LinkedStack<const Operator> operators;
        
        strIndexStart = 0;
        strIndexEnd = -1;
        while(strIndexStart < __formu.size() && ((strIndexEnd = __formu.find_first_of("+-*/%^(),", strIndexStart)) != string::npos) || (strIndexEnd = __formu.size()) > strIndexStart)
        {
            if(strIndexEnd == __formu.size() || __formu[strIndexEnd] != '(')
            {
                if(strIndexEnd > strIndexStart)
                {
                    bool numericOperand = false;
                    string _operandStr_ = __formu.substr(strIndexStart, strIndexEnd - strIndexStart);
                    try
                    {
                        static size_t _offset_;
                        double val = stod(_operandStr_, &_offset_);
                        if(_offset_ == _operandStr_.size())
                        {
                            numericOperand = true;
                            this->addToNode(new NumericOperand(val));
                        }
                    }
                    catch(invalid_argument& ia){}
                
                    if(!numericOperand)
                    {
                        String _str_(_operandStr_);
                        int* index = varTable.get(&_str_);
                        if(index == nullptr)
                        {
                            throw InvalidFormulaException(("Undefined variable: " + _operandStr_).c_str());
                        }
                        this->addToNode(new IndexingOperand(*index));
                    }
                    previouslyOperator = false;
                }
                
                if(strIndexEnd == __formu.size())
                {
                    break;
                }
            }
            else if(strIndexEnd > strIndexStart)
            {
                string __f_name = __formu.substr(strIndexStart, strIndexEnd - strIndexStart);
                int _vCountInner = this->parseInnerFunctionInput(__formu, strIndexEnd, varTable);
                MathFunctionIdentifier mfi(__f_name, _vCountInner);
                MathFunction* _func = this->NAME_SPACE.functions->get(&mfi);
                if(_func == nullptr)
                {
                    throw InvalidFormulaException(("Undefined function: " + __f_name + " which should accept " + to_string(_vCountInner) + " arguments.").c_str());
                }
                _func->isReferencedByOthers = true;
                this->addToNode(new OperatorInvokeFunc(_func));
                strIndexStart = strIndexEnd;
                previouslyOperator = false;
                continue;
            }
            
            if(__formu[strIndexEnd] != '(' && __formu[strIndexEnd] != '-' && previouslyOperator)
            {
                throw InvalidFormulaException("Invalid operator sequence!");
            }
            
            const Operator* op = nullptr;
            static const Operator* op2 = nullptr;
            
            switch(__formu[strIndexEnd])
            {
                case '-':
                    if(previouslyOperator)
                    {
                        op = &(Operator::OPERATOR_NEGATIVE);
                        if((op2 = operators.peek()) != nullptr && op2->isUnary())
                        {
                            throw InvalidFormulaException("Invalid conjunction of multiple unary operator \'-\'.");
                        }
                    }
                    else
                    {
                        op = &(Operator::OPERATOR_NEGATION);
                    }
                    break;
                case '+':
                    op = &(Operator::OPERATOR_ADDITION);
                    break;
                case '*':
                    op = &(Operator::OPERATOR_MULTIPLICATION);
                    break;
                case '/':
                    op = &(Operator::OPERATOR_DIVISION);
                    break;
                case '%':
                    op = &(Operator::OPERATOR_MODDING);
                    break;
                case '^':
                    op = &(Operator::OPERATOR_POWER);
                    break;
                case '(':
                    op = &(Operator::OPERATOR_LEFT_BRACKET);
                    break;
                case ')':
                {
                    while((op2 = operators.peek()) != nullptr && !(op2->isBracket()))
                    {
                        this->addToNode(operators.pop());
                    }
                    operators.pop();
                    previouslyOperator = false;
                    strIndexStart = strIndexEnd + 1;
                    continue;
                }
                case ',':
                    throw InvalidFormulaException("Invalid seperation character \',\' outside of a function input.");
                default:
                    break;
            }
            
            if(op != nullptr)
            {
                if(!(op->isBracket()))
                {
                    while((op2 = operators.peek()) != nullptr && op2->getLevel() >= op->getLevel())
                    {
                        this->addToNode(operators.pop());
                    }
                }
                operators.push(op);
            }
            
            previouslyOperator = true;
            
            strIndexStart = strIndexEnd + 1;
        }
        
        while(operators.peek() != nullptr)
        {
            this->addToNode(operators.pop());
        }
    }
    else
    {
        throw InvalidFormulaException("Either the spacing is invalid or the brackets are not paired.");
    }
}

MathFunction::~MathFunction()
{
    if(this->isReferencedByOthers)
    {
        MathFunction* replace = new MathFunction(this->NAME_SPACE, this->identifier);
        replace->expression = this->expression;
        replace->isReferencedByOthers = true;
        replace->postfixOperations = this->postfixOperations;
    }
    else
    {
        delete this->identifier;
    }
}

int MathFunction::parseInnerFunctionInput(string& _expressions, int& endIndex, HashTable<String, int>& varTable)
{
    endIndex++;
    int _varCountInner = 0;
    bool endFuncInput = false;
    
    int argumentStartIndex = endIndex;

    while(!endFuncInput)
    {
        int argumentExpectedEndIndex = _expressions.find_first_of(",)", argumentStartIndex);
        
        int strIndexStart = argumentStartIndex;
        int strIndexEnd = -1;
        bool previouslyOperator = true;
        LinkedStack<const Operator> operators;
        int innerBrackets = 0;
        while((strIndexEnd = _expressions.find_first_of("+-*/%^(),", strIndexStart)) != string::npos && strIndexEnd <= argumentExpectedEndIndex)
        {
            if(_expressions[strIndexEnd] != '(')
            {
                if(strIndexEnd > strIndexStart)
                {
                    bool numericOperand = false;
                    string _operandStr_ = _expressions.substr(strIndexStart, strIndexEnd - strIndexStart);
                    try
                    {
                        size_t _offset_;
                        double val = stod(_operandStr_, &_offset_);
                        if(_offset_ == _operandStr_.size())
                        {
                            numericOperand = true;
                            this->addToNode(new NumericOperand(val));
                        }
                    }
                    catch(invalid_argument& ia){}
                
                    if(!numericOperand)
                    {
                        String _str_(_operandStr_);
                        int* index = varTable.get(&_str_);
                        if(index == nullptr)
                        {
                            throw InvalidFormulaException(("Undefined variable: " + _operandStr_).c_str());
                        }
                        this->addToNode(new IndexingOperand(*index));
                    }
                    previouslyOperator = false;
                }
                
                if(strIndexEnd == _expressions.size())
                {
                    break;
                }
            }
            else if(strIndexEnd > strIndexStart)
            {
                string __f_name = _expressions.substr(strIndexStart, strIndexEnd - strIndexStart);
                int _vCountInner = this->parseInnerFunctionInput(_expressions, strIndexEnd, varTable);
                MathFunctionIdentifier mfi(__f_name, _vCountInner);
                MathFunction* _func = this->NAME_SPACE.functions->get(&mfi);
                if(_func == nullptr)
                {
                    throw InvalidFormulaException(("Undefined function: " + __f_name + " which should accept " + to_string(_vCountInner) + " arguments.").c_str());
                }
                _func->isReferencedByOthers = true;
                this->addToNode(new OperatorInvokeFunc(_func));
                strIndexStart = strIndexEnd;
                argumentExpectedEndIndex = _expressions.find_first_of(",)", strIndexStart);
                previouslyOperator = false;
                continue;
            }
            
            if(_expressions[strIndexEnd] != '(' && _expressions[strIndexEnd] != '-' && previouslyOperator)
            {
                throw InvalidFormulaException("Invalid operator sequence!");
            }
            
            const Operator* op = nullptr;
            const Operator* op2 = nullptr;
            
            switch(_expressions[strIndexEnd])
            {
                case '-':
                    if(previouslyOperator)
                    {
                        op = &(Operator::OPERATOR_NEGATIVE);
                        if((op2 = operators.peek()) != nullptr && op2->isUnary())
                        {
                            throw InvalidFormulaException("Invalid conjunction of multiple unary operator \'-\'.");
                        }
                    }
                    else
                    {
                        op = &(Operator::OPERATOR_NEGATION);
                    }
                    break;
                case '+':
                    op = &(Operator::OPERATOR_ADDITION);
                    break;
                case '*':
                    op = &(Operator::OPERATOR_MULTIPLICATION);
                    break;
                case '/':
                    op = &(Operator::OPERATOR_DIVISION);
                    break;
                case '%':
                    op = &(Operator::OPERATOR_MODDING);
                    break;
                case '^':
                    op = &(Operator::OPERATOR_POWER);
                    break;
                case '(':
                    op = &(Operator::OPERATOR_LEFT_BRACKET);
                    innerBrackets++;
                    break;
                case ')':
                    if(argumentExpectedEndIndex == strIndexEnd && innerBrackets == 0)
                    {
                        endFuncInput = true;
                        endIndex = strIndexEnd + 1;
                        // Do same stuff as , if the function ends input.
                    }
                    else
                    {
                        innerBrackets--;
                        argumentExpectedEndIndex = _expressions.find_first_of(",)", strIndexEnd + 1);
                        while((op2 = operators.peek()) != nullptr && !(op2->isBracket()))
                        {
                            this->addToNode(operators.pop());
                        }
                        operators.pop();
                        previouslyOperator = false;
                        strIndexStart = strIndexEnd + 1;
                        continue;
                    }
                case ',':
                    _varCountInner++;
                    if(innerBrackets != 0)
                    {
                        throw InvalidFormulaException("Unpaired brackets.");
                    }
                    while(!operators.isEmpty())
                    {
                        this->addToNode(operators.pop());
                    }
                    previouslyOperator = true;
                    strIndexStart = strIndexEnd + 1;
                    continue;
                default:
                    break;
            }
            
            if(op != nullptr)
            {
                if(!(op->isBracket()))
                {
                    while((op2 = operators.peek()) != nullptr && op2->getLevel() >= op->getLevel())
                    {
                        this->addToNode(operators.pop());
                    }
                }
                operators.push(op);
            }

            previouslyOperator = true;
            
            strIndexStart = strIndexEnd + 1;
        }
        
        argumentStartIndex = argumentExpectedEndIndex + 1;
    }
    return _varCountInner;
}

double MathFunction::invoke(double* operands) const
{
    Node<const OperationElement>* __node = nullptr;
    Node<const OperationElement>* __cache = nullptr;
    
    __node = this->postfixOperations->getNext();
    __cache = __node;
    
    if(this->postfixOperations == nullptr)
    {
        return nan("");
    }
    
    if(__node == nullptr)
    {
        return nan("");
    }
    LinkedStack<const NumericOperand> stackedOperands;
    do
    {
        if(__cache->getValue()->isOperator())
        {
            const Operator* op = dynamic_cast<const Operator*>(__cache->getValue());
            if(op->isFunction())
            {
                const OperatorInvokeFunc* oif = dynamic_cast<const OperatorInvokeFunc*>(op);
                const MathFunction* _func = oif->func;
                double* _operands = new double[oif->varCount];
                for(int i = oif->varCount - 1 ; i >= 0 ; i--)
                {
                    _operands[i] = stackedOperands.peek()->getValue();
                    stackedOperands.pop();
                }
                NumericOperand* _fVal = new NumericOperand(_func->invoke(_operands));
                stackedOperands.push(_fVal);
                delete _operands;
            }
            else if(op->isUnary())
            {
                const OperatorUnary* ou = dynamic_cast<const OperatorUnary*>(op);
                NumericOperand* _opVal = new NumericOperand(ou->operate(stackedOperands.peek()->getValue()));
                stackedOperands.pop();
                stackedOperands.push(_opVal);
            }
            else
            {
                const OperatorBinary* ob = dynamic_cast<const OperatorBinary*>(op);
                if(stackedOperands.isEmpty())
                {
                    return nan("");
                }
                double rhs = stackedOperands.peek()->getValue();
                stackedOperands.pop();
                if(stackedOperands.isEmpty())
                {
                    return nan("");
                }
                double lhs = stackedOperands.peek()->getValue();
                
                stackedOperands.pop();
                stackedOperands.push(new NumericOperand(ob->operate(lhs, rhs)));
            }
        }
        else
        {
            const Operand* operand = dynamic_cast<const Operand*>(__cache->getValue());
            if(operand->isNumeric())
            {
                stackedOperands.push(dynamic_cast<const NumericOperand*>(operand));
            }
            else
            {
                const IndexingOperand* ioperand = dynamic_cast<const IndexingOperand*>(operand);
                stackedOperands.push(new NumericOperand(operands[ioperand->getIndex()]));
            }
        }
        __cache = __cache->getNext();
    }
    while(__cache != __node);
    
    if(stackedOperands.isEmpty())
    {
        return nan("");
    }
    return stackedOperands.peek()->getValue();
}

double MathFunction::invoke(initializer_list<double> var_list) const
{
    int _size = var_list.size();
    if(_size != this->identifier->getVariablesCount())
    {
        throw InvalidArgumentException(("The function accepts " + to_string(this->identifier->getVariablesCount()) + " arguments, but received " + to_string(_size) + ".").c_str());
    }
    double* operands = new double[_size];
    int i = 0;
    for(double d : var_list)
    {
        operands[i] = d;
        i++;
    }
    return this->invoke(operands);
}

const MathFunctionIdentifier& MathFunction::getIdentifier() const
{
    return *(this->identifier);
}

MathFunctionSine::MathFunctionSine(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("sin", 1), false) {}

double MathFunctionSine::invoke(double* operands) const
{
    return sin(operands[0]);
}

MathFunctionCosine::MathFunctionCosine(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("cos", 1), false) {}

double MathFunctionCosine::invoke(double* operands) const
{
    return cos(operands[0]);
}

MathFunctionTangent::MathFunctionTangent(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("tan", 1), false) {}

double MathFunctionTangent::invoke(double* operands) const
{
    return tan(operands[0]);
}

MathFunctionHyperbolicSine::MathFunctionHyperbolicSine(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("sinh", 1), false) {}

double MathFunctionHyperbolicSine::invoke(double* operands) const
{
    return sinh(operands[0]);
}

MathFunctionHyperbolicCosine::MathFunctionHyperbolicCosine(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("cosh", 1), false) {}

double MathFunctionHyperbolicCosine::invoke(double* operands) const
{
    return cosh(operands[0]);
}

MathFunctionHyperbolicTangent::MathFunctionHyperbolicTangent(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("tanh", 1), false) {}

double MathFunctionHyperbolicTangent::invoke(double* operands) const
{
    return tanh(operands[0]);
}

MathFunctionArcSine::MathFunctionArcSine(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("asin", 1), false) {}

double MathFunctionArcSine::invoke(double* operands) const
{
    return asin(operands[0]);
}

MathFunctionArcCosine::MathFunctionArcCosine(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("acos", 1), false) {}

double MathFunctionArcCosine::invoke(double* operands) const
{
    return acos(operands[0]);
}

MathFunctionArcTangent::MathFunctionArcTangent(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("atan", 1), false) {}

double MathFunctionArcTangent::invoke(double* operands) const
{
    return atan(operands[0]);
}

MathFunctionArcTangent2::MathFunctionArcTangent2(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("atan2", 2), false) {}

double MathFunctionArcTangent2::invoke(double* operands) const
{
    return atan2(operands[0], operands[1]);
}

MathFunctionExponential::MathFunctionExponential(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("exp", 1), false) {}

double MathFunctionExponential::invoke(double* operands) const
{
    return exp(operands[0]);
}

MathFunctionNaturalLog::MathFunctionNaturalLog(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("ln", 1), false) {}

double MathFunctionNaturalLog::invoke(double* operands) const
{
    return log(operands[0]);
}

MathFunctionLog10::MathFunctionLog10(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("log", 1), false) {}

double MathFunctionLog10::invoke(double* operands) const
{
    return log10(operands[0]);
}

MathFunctionLog::MathFunctionLog(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("log", 2), false) {}

double MathFunctionLog::invoke(double* operands) const
{
    return log(operands[1]) / log(operands[0]);
}

MathFunctionCeiling::MathFunctionCeiling(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("ceil", 1), false) {}

double MathFunctionCeiling::invoke(double* operands) const
{
    return ceil(operands[0]);
}

MathFunctionFloor::MathFunctionFloor(MathFunctionNamespace& ns) : MathFunction::MathFunction(ns, new MathFunctionIdentifier("ceil", 1), false) {}

double MathFunctionFloor::invoke(double* operands) const
{
    return floor(operands[0]);
}

const MathFunction& MathFunction::SIN = *(new MathFunctionSine(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::COS = *(new MathFunctionCosine(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::TAN = *(new MathFunctionTangent(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::SINH = *(new MathFunctionHyperbolicSine(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::COSH = *(new MathFunctionHyperbolicCosine(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::TANH = *(new MathFunctionHyperbolicTangent(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::ASIN = *(new MathFunctionArcSine(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::ACOS = *(new MathFunctionArcCosine(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::ATAN = *(new MathFunctionArcTangent(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::ATAN2 = *(new MathFunctionArcTangent2(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::EXP = *(new MathFunctionExponential(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::LN = *(new MathFunctionNaturalLog(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::LOG10 = *(new MathFunctionLog10(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::LOG = *(new MathFunctionLog(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::CEIL = *(new MathFunctionCeiling(MathFunction::DEFAULT_NAMESPACE));
const MathFunction& MathFunction::FLOOR = *(new MathFunctionFloor(MathFunction::DEFAULT_NAMESPACE));
