#include <math.h>

#include "misc/TFException.hpp"
#include "Operators.hpp"
#include "TangentsMathFunc.hpp"

using namespace std;

// Operators.
const OperatorUnary& Operator::OPERATOR_NEGATIVE = *(new OperatorNegative());
const OperatorBinary& Operator::OPERATOR_ADDITION = *(new OperatorAddition());
const OperatorBinary& Operator::OPERATOR_NEGATION = *(new OperatorNegation());
const OperatorBinary& Operator::OPERATOR_MULTIPLICATION = *(new OperatorMultiplication());
const OperatorBinary& Operator::OPERATOR_DIVISION = *(new OperatorDivision());
const OperatorBinary& Operator::OPERATOR_MODDING = *(new OperatorModding());
const OperatorBinary& Operator::OPERATOR_POWER = *(new OperatorPower());
const OperatorLeftBracket& Operator::OPERATOR_LEFT_BRACKET = *(new OperatorLeftBracket());

bool Operand::isOperator() const
{
    return false;
}

IndexingOperand::IndexingOperand(int _index)
{
    this->index = _index;
}

int IndexingOperand::getIndex() const
{
    return this->index;
}

bool IndexingOperand::isNumeric() const
{
    return false;
}

bool NumericOperand::isNumeric() const
{
    return true;
}

NumericOperand::NumericOperand(double _value)
{
    this->value = _value;
}

double NumericOperand::getValue() const
{
    return this->value;
}

bool Operator::isBracket() const
{
    return false;
}

bool Operator::isOperator() const
{
    return true;
}

bool Operator::isFunction() const
{
    return false;
}

bool OperatorUnary::isUnary() const
{
    return true;
}

bool OperatorBinary::isUnary() const
{
    return false;
}

double OperatorNegative::operate(const double& input) const
{
    return -input;
}

int OperatorNegative::getLevel() const
{
    return 3;
}

double OperatorAddition::operate(const double& lhs, const double& rhs) const
{
    return lhs + rhs;
}

int OperatorAddition::getLevel() const
{
    return 1;
}

double OperatorNegation::operate(const double& lhs, const double& rhs) const
{
    return lhs - rhs;
}

int OperatorNegation::getLevel() const
{
    return 1;
}

double OperatorMultiplication::operate(const double& lhs, const double& rhs) const
{
    return lhs * rhs;
}

int OperatorMultiplication::getLevel() const
{
    return 2;
}

double OperatorDivision::operate(const double& lhs, const double& rhs) const
{
    if(rhs == 0)
    {
        throw DividedByZeroException();
    }
    return lhs / rhs;
}

int OperatorDivision::getLevel() const
{
    return 2;
}

double OperatorModding::operate(const double& lhs, const double& rhs) const
{
    if(rhs == 0)
    {
        throw DividedByZeroException();
    }
    return fmod(lhs, rhs);
}

int OperatorModding::getLevel() const
{
    return 2;
}

double OperatorPower::operate(const double& lhs, const double& rhs) const
{
    return pow(lhs, rhs);
}
        
int OperatorPower::getLevel() const
{
    return 4;
}

bool OperatorLeftBracket::isUnary() const
{
    return false;
}

bool OperatorLeftBracket::isBracket() const
{
    return true;
}

double OperatorLeftBracket::operate(const double& lhs, const double& rhs) const
{
    double* __oops__ = nullptr;
    return *(__oops__);
}

int OperatorLeftBracket::getLevel() const
{
    return 0;
}

OperatorInvokeFunc::OperatorInvokeFunc(MathFunction* _f) : func(_f), varCount(_f->getIdentifier().getVariablesCount()){}

bool OperatorInvokeFunc::isFunction() const
{
    return true;
}

bool OperatorInvokeFunc::isUnary() const
{
    return true;
}

int OperatorInvokeFunc::getLevel() const
{
    return -1;
}
