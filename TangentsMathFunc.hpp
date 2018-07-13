#include<initializer_list>
#include<math.h>
#include<string>
#include<string.h>
#include<stdexcept>

/*
 * Tangent's Math Function V1.01
 *  Copyright (c) 2018, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 *
 * Usage:
 *    MathFunction("f(x, y, ...)", "<operations>");
 */

using namespace std;

template <typename T>
class Node
{
    private:
        /*
         * Value, or the content of this node. Late-binding compatible.
         */
        T* value;
        
        /*
         * Whether the value should be deleted when being replaced/removed.
         */
        bool del;
        
        /*
         * Next node.
         */
        Node<T>* next;
        
        /*
         * :P (Banned constructor.)
         */
        Node(const Node<T>&);
        
        /*
         * Nah. (Banned operator.)
         */
        void operator=(const Node<T>&);
        
    public:
        /*
         * Creates a node with its content only.
         *
         * Param(s):
         *    _val    -> Content of the new node which WILL NOT be copied.
         */
        Node(T* _val, bool _del);
        
        /*
         * Creates a node with both its content and the next node it links to.
         *
         * Param(s):
         *    _val     -> Content of the new node which WILL NOT be copied.
         *    _next    -> The next node this node should link to.
         */
        Node(T* _val, Node<T>* _next, bool _del);
        
        ~Node();
        
        /*
         * Get the content of this node as a pointer.
         *
         * Return:
         *    _ret    -> The content of this node as a pointer.
         */
        T* getValue() const;
        
        /*
         * Replace the content with a new one.
         *
         * Param(s):
         *    newValue    -> New content of the new node which WILL NOT be copied.
         *    del         -> Whether the old content should be deleted.
         */
        void setValue(T* newValue, bool del);
        
        /*
         * Get the next node this node links to.
         *
         * Return:
         *    _ret    -> The next node as a pointer.
         */
        Node<T>* getNext() const;
        
        /*
         * Set the next node of this node.
         *
         * Param(s):
         *    _next    -> Next node.
         */
        void setNext(Node<T>* _next);
};

template<typename K, typename T>
class HashEntry
{
	private:
		K* key;
		T* value;
		
		bool del;
		
		HashEntry(const HashEntry<K, T>&);
		void operator=(const HashEntry<K, T>&);
	
	public:
		HashEntry(K* _key, T* _value, bool _del);
		~HashEntry();
		
		K* getKey() const;
		T* getValue() const;
	
		int hash(int capacity);
};

template<typename K, typename T>
class HashTable
{
	private:
		int capacity;
		
		int size;
		Node<HashEntry<K, T>>** entries;
		
		HashTable(const HashTable<K, T>&);
		void operator=(const HashTable<K, T>&);
		
	public:
		HashTable(int _cap);
		~HashTable();
		
		int getSize() const;
		int getCapacity() const;
		
		void put(K* _key, T* _value, bool& replacing);
		T* get(const K* _key);
		
		T* remove(const K* _key);
};

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

const char* DividedByZeroException::CANNED_MESSAGE = "Divided by 0!";

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

const char* InvalidArgumentException::CANNED_MESSAGE = "Invalid argument!";

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

const char* InvalidFormulaException::CANNED_MESSAGE = "Invalid formulation!";

template <typename T>
class LinkedStack
{
	private:
		Node<T>* head = nullptr;
		int size = 0;
		
		// Forbidden
		LinkedStack(const LinkedStack<T>&);
		void operator=(const LinkedStack<T>&);
	
	public:
		LinkedStack(){}
		~LinkedStack();
		
		bool isEmpty() const;
		T* peek() const;
		T* pop();
		void push(T* _entry);
		
		int getSize() const;
};

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

// Operators.
const OperatorUnary& Operator::OPERATOR_NEGATIVE = *(new OperatorNegative());
const OperatorBinary& Operator::OPERATOR_ADDITION = *(new OperatorAddition());
const OperatorBinary& Operator::OPERATOR_NEGATION = *(new OperatorNegation());
const OperatorBinary& Operator::OPERATOR_MULTIPLICATION = *(new OperatorMultiplication());
const OperatorBinary& Operator::OPERATOR_DIVISION = *(new OperatorDivision());
const OperatorBinary& Operator::OPERATOR_MODDING = *(new OperatorModding());
const OperatorBinary& Operator::OPERATOR_POWER = *(new OperatorPower());
const OperatorLeftBracket& Operator::OPERATOR_LEFT_BRACKET = *(new OperatorLeftBracket());

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

template <typename T>
Node<T>::Node(T* _val, bool _del)
{
    this->value = _val;
    this->del = _del;
    this->next = nullptr;
}

template <typename T>
Node<T>::Node(T* _val, Node<T>* _next, bool _del)
{
    this->value = _val;
    this->del = _del;
    this->next = _next;
}

template <typename T>
Node<T>::~Node()
{
    if(this->del)
    {
    	delete this->value;
	}
}

template <typename T>
T* Node<T>::getValue() const
{
    return this->value;
}

template <typename T>
void Node<T>::setValue(T* newValue, bool _del)
{
    if(this->del)
    {
    	delete this->value;
	}
	this->del = _del;
    this->value = newValue;
}

template <typename T>
Node<T>* Node<T>::getNext() const
{
    return this->next;
}

template <typename T>
void Node<T>::setNext(Node<T>* _next)
{
    this->next = _next;
}

template<typename K, typename T>
HashEntry<K, T>::HashEntry(K* _key, T* _value, bool _del)
{
	this->key = _key;
	this->value = _value;
	this->del = _del;
}

template<typename K, typename T>
HashEntry<K, T>::~HashEntry()
{
	if(this->del)
	{
		delete this->key;
		delete this->value;
	}
}

template<typename K, typename T>
K* HashEntry<K, T>::getKey() const
{
	return this->key;
}

template<typename K, typename T>
T* HashEntry<K, T>::getValue() const
{
	return this->value;
}

template<typename K, typename T>
int HashEntry<K, T>::hash(int capacity)
{
	return this->key->hash(capacity);
}

template<typename K, typename T>
HashTable<K, T>::HashTable(int _cap)
{
	this->capacity = _cap;
	this->size = 0;
	this->entries = new Node<HashEntry<K, T>>*[this->capacity];
	memset(this->entries, 0, this->capacity * sizeof(new Node<HashEntry<K, T>>*));
}

template<typename K, typename T>
HashTable<K, T>::~HashTable()
{
	static Node<HashEntry<K, T>>* cache = nullptr;
	for(int i = 0 ; i < this->capacity ; i++)
	{
		cache = this->entries[i];
		while(cache != nullptr)
		{
			this->entries[i] = this->entries[i]->getNext();
			delete cache;
			cache = this->entries[i];
		}
	}
}

template<typename K, typename T>
int HashTable<K, T>::getSize() const
{
	return this->size;
}

template<typename K, typename T>
int HashTable<K, T>::getCapacity() const
{
	return this->capacity;
}

template<typename K, typename T>
void HashTable<K, T>::put(K* _key, T* _value, bool& replacing)
{
	replacing = false;
	int hash = _key->hash(this->capacity);
	if(hash < 0)
	{
		hash = (hash % this->capacity) + this->capacity - 1;
	}
	else
	{
		hash %= this->capacity;
	}
	
	static Node<HashEntry<K, T>>* cache = nullptr;
	
	cache = this->entries[hash];
	while(cache != nullptr)
	{
		if(*(cache->getValue()->getKey()) == *(_key))
		{
			cache->setValue(new HashEntry<K, T>(_key, _value, false), false);
			replacing = true;
			return;
		}
		cache = cache->getNext();
	}
	
	this->size++;
	this->entries[hash] = new Node<HashEntry<K, T>>(new HashEntry<K, T>(_key, _value, false), this->entries[hash], false);
}

template<typename K, typename T>
T* HashTable<K, T>::get(const K* _key)
{
	int hash = _key->hash(this->capacity);
	if(hash < 0)
	{
		hash = (hash % this->capacity) + this->capacity - 1;
	}
	else
	{
		hash %= this->capacity;
	}
	
	static Node<HashEntry<K, T>>* cache = nullptr;
	
	cache = this->entries[hash];
	while(cache != nullptr)
	{
		if(*(cache->getValue()->getKey()) == *(_key))
		{
			return cache->getValue()->getValue();
		}
		cache = cache->getNext();
	}
	
	return nullptr;
}

template<typename K, typename T>
T* HashTable<K, T>::remove(const K* _key)
{
	int hash = _key->hash(this->capacity);
	if(hash < 0)
	{
		hash = (hash % this->capacity) + this->capacity - 1;
	}
	else
	{
		hash %= this->capacity;
	}
	
	static Node<HashEntry<K, T>>* cache1 = nullptr;
	static Node<HashEntry<K, T>>* cache2 = nullptr;
	
	if(this->entries[hash] == nullptr)
	{
		return nullptr;
	}
	
	cache1 = this->entries[hash];
	if(*(cache1->getValue()->getKey()) == *_key)
	{
		this->entries[hash] = this->entries[hash]->getNext();
		T* _ret = cache1->getValue()->getValue();
		delete cache1;
		this->size--;
		return _ret;
	}
	
	cache2 = cache1->getNext();
	while(cache2 != nullptr)
	{
		if(*(cache2->getValue()->getKey()) == *(_key))
		{
			cache1->setNext(cache2->getNext());
			T* _ret = cache2->getValue()->getValue();
			delete cache2;
			this->size--;
			return _ret;
		}
		cache1 = cache2;
		cache2 = cache2->getNext();
	}
	
	return nullptr;
}

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

const char* DividedByZeroException::what() const noexcept
{
	return CANNED_MESSAGE;
}

InvalidArgumentException::InvalidArgumentException(const char* _msg)
{
	static int len1 = strlen(CANNED_MESSAGE);
	int len2 = strlen(_msg);
	
	this->message = new char[len1 + len2 + 2];
	strcpy(this->message, CANNED_MESSAGE);
	strcpy(this->message + len1 + 1, _msg);
	this->message[len1] = ' ';
}

InvalidArgumentException::InvalidArgumentException(const InvalidArgumentException& copy)
{
	this->message = new char[strlen(copy.message) + 1];
	strcpy(this->message, copy.message);
}

InvalidArgumentException::~InvalidArgumentException()
{
	delete this->message;
}

const InvalidArgumentException& InvalidArgumentException::operator=(const InvalidArgumentException& copy)
{
	if(this == &copy)
	{
		return copy;
	}
	
	int lenC = strlen(copy.message);
	if(strlen(this->message) != lenC)
	{
		delete this->message;
		this->message = new char[lenC + 1];
	}
	strcpy(this->message, copy.message);
	
	return *this;
}

const char* InvalidArgumentException::what() const noexcept
{
	return this->message;
}

InvalidFormulaException::InvalidFormulaException(const char* _msg)
{
	static int len1 = strlen(CANNED_MESSAGE);
	int len2 = strlen(_msg);
	
	this->message = new char[len1 + len2 + 2];
	strcpy(this->message, CANNED_MESSAGE);
	strcpy(this->message + len1 + 1, _msg);
	this->message[len1] = ' ';
}

InvalidFormulaException::InvalidFormulaException(const InvalidFormulaException& copy)
{
	this->message = new char[strlen(copy.message) + 1];
	strcpy(this->message, copy.message);
}

InvalidFormulaException::~InvalidFormulaException()
{
	delete this->message;
}

const InvalidFormulaException& InvalidFormulaException::operator=(const InvalidFormulaException& copy)
{
	if(this == &copy)
	{
		return copy;
	}
	
	int lenC = strlen(copy.message);
	if(strlen(this->message) != lenC)
	{
		delete this->message;
		this->message = new char[lenC + 1];
	}
	strcpy(this->message, copy.message);
	
	return *this;
}

const char* InvalidFormulaException::what() const noexcept
{
	return this->message;
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
	Node<T>* cache = nullptr;
	while((cache = this->head) != nullptr)
	{
		this->head = cache->getNext();
		delete cache;
	}
}

template <typename T>
bool LinkedStack<T>::isEmpty() const
{
	return this->head == nullptr;
}

template <typename T>
T* LinkedStack<T>::peek() const
{
	return (this->head == nullptr ? nullptr : this->head->getValue());
}

template <typename T>
T* LinkedStack<T>::pop()
{
	if(head == nullptr)
	{
		return nullptr;
	}
	else
	{
		Node<T>* cache = this->head;
		T* ret = cache->getValue();
		cache->setValue(nullptr, false);
		this->head = cache->getNext();
		delete cache;
		this->size--;
		return ret;
	}
}

template <typename T>
void LinkedStack<T>::push(T* _entry)
{
	this->head = new Node<T>(_entry, this->head, false);
	this->size++;
}

template <typename T>
int LinkedStack<T>::getSize() const
{
	return this->size;
}

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
