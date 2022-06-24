#include "../Operators.hpp"

template NumericOperand const* LinkedStack<NumericOperand const>::peek() const;
template NumericOperand const* LinkedStack<NumericOperand const>::pop();
template void LinkedStack<NumericOperand const>::push(NumericOperand const*);
template bool LinkedStack<NumericOperand const>::isEmpty() const;
template LinkedStack<NumericOperand const>::~LinkedStack();

template void LinkedStack<Operator const>::push(Operator const*);
template Operator const* LinkedStack<Operator const>::pop();
template Operator const* LinkedStack<Operator const>::peek() const;
template bool LinkedStack<Operator const>::isEmpty() const;
template LinkedStack<Operator const>::~LinkedStack();
