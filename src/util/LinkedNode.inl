#include "../Operators.hpp"
#include "../TangentsMathFunc.hpp"

template Node<OperationElement const>::Node(OperationElement const*, bool);
template Node<OperationElement const>* Node<OperationElement const>::getNext() const;
template OperationElement const* Node<OperationElement const>::getValue() const;
template void Node<OperationElement const>::setNext(Node<OperationElement const>*);

template Node<NumericOperand const>::Node(NumericOperand const*, Node<NumericOperand const>*, bool);
template NumericOperand const* Node<NumericOperand const>::getValue() const;
template void Node<NumericOperand const>::setValue(NumericOperand const*, bool);
template Node<NumericOperand const>* Node<NumericOperand const>::getNext() const;
template Node<NumericOperand const>::~Node();

template Node<Operator const>::Node(Operator const*, Node<Operator const>*, bool);
template Operator const* Node<Operator const>::getValue() const;
template void Node<Operator const>::setValue(Operator const*, bool);
template Node<Operator const>* Node<Operator const>::getNext() const;
template Node<Operator const>::~Node();

template Node<HashEntry<MathFunctionIdentifier const, MathFunction>>::Node(HashEntry<MathFunctionIdentifier const, MathFunction>*, Node<HashEntry<MathFunctionIdentifier const, MathFunction>>*, bool);
template HashEntry<MathFunctionIdentifier const, MathFunction>* Node<HashEntry<MathFunctionIdentifier const, MathFunction>>::getValue() const;
template void Node<HashEntry<MathFunctionIdentifier const, MathFunction>>::setValue(HashEntry<MathFunctionIdentifier const, MathFunction>*, bool);
template Node<HashEntry<MathFunctionIdentifier const, MathFunction>>* Node<HashEntry<MathFunctionIdentifier const, MathFunction>>::getNext() const;
template void Node<HashEntry<MathFunctionIdentifier const, MathFunction>>::setNext(Node<HashEntry<MathFunctionIdentifier const, MathFunction>>*);
template Node<HashEntry<MathFunctionIdentifier const, MathFunction>>::~Node();

template Node<HashEntry<String, int>>::Node(HashEntry<String, int>*, Node<HashEntry<String, int> >*, bool);
template Node<HashEntry<String, int>>* Node<HashEntry<String, int>>::getNext() const;
template HashEntry<String, int>* Node<HashEntry<String, int>>::getValue() const;
template void Node<HashEntry<String, int>>::setValue(HashEntry<String, int>*, bool);
template Node<HashEntry<String, int>>::~Node();
