# TangentsMathFunc
A primitive math expression evaluation library made for a course I was taking back in 2018.

Everything you'll need is in the header file: `#include <TangentsMathFunc.hpp>`

# Usage
## Math Function

Declaring a new math function `f(x, y) = 9x^2 + 6xy + y^2 - 3x - y - 1`, and get `f(1, 1)`:  
```C++
MathFunction func_f("f(x, y)", "9*x^2 + 6*x*y + y^2 - 3*x - y - 1");
double val1 = func_f.invoke({1, 1});
```

Nested function calls referencing previously declared custom functions are supported, e.g. `g(x) = f(x + 1, x - 1) / f(1 - x, 1 + x)`:
```C++
MathFunction func_g("g(x)", "f(x + 1, x - 1) / f(1 - x, 1 + x)");
double val2 = func_g.invoke({1, 1});
```

The following built-in functions are supported:
 * `sin(x)`: trigonometry sine
 * `cos(x)`: trigonometry cosine
 * `tan(x)`: trigonometry tangent
 * `sinh(x)`: hyperbolic sine
 * `cosh(x)`: hyperbolic cosine
 * `tanh(x)`: hyperbolic tangent
 * `asin(x)`: trigonometry arcsine, or sin<sup>-1</sup>(x)
 * `acos(x)`: trigonometry arccosine, or cos<sup>-1</sup>(x)
 * `atan(x)`: trigonometry arctangent, or tan<sup>-1</sup>(x)
 * `atan2(y, x)`: trigonometry cartesian arctangent
 * `exp(x)`: exponential function
 * `ln(x)`: natural logarithm
 * `log10(x)`: base 10 logarithm
 * `log(b, x)`: base `b` logarithm
 * `floor(x)`: floor function (nearest integer less than or equal to `x`)
 * `ceil(x)`: ceiling function (nearest integer greater than or equal to `x`)

## Custom namespace
All `MathFunction` objects are bound to a namespace. If not specified, the default namespace is used. Currently built-in functions are only supported in default namespace.  

An example of custom namespace:
```C++
MathFunctionNamespace ns;
MathFunction func(ns, "f(a, b, c)", "(a + b) / c");
double val = func.invoke({1.0, 2.0, 0.03});
```

Namespaces are independent to each other, meaning that you can declare functions with same names in different namespaces, and they cannot reference other functions in different namespaces.

E.g. the following code will NOT throw an exception due to conflicting function name:
```C++
MathFunctionNamespace ns1;
MathFunction func1(ns1, "f(a, b, c)", "(a + b) * c");
double val1 = func1.invoke({1.0, 2.0, 0.03});

MathFunctionNamespace ns2;
MathFunction func2(ns2, "f(x, y)", "x * y");
double val2 = func2.invoke({-1.0, 1.0});
```

E.g. the following code WILL throw an exception due to undefined reference, since `f(a, b, c)` is defined within another namespace independent to where `g(x, y)` is declared:
```C++
MathFunctionNamespace ns1;
MathFunction func1(ns1, "f(a, b, c)", "(a + b) * c");
double val1 = func1.invoke({1.0, 2.0, 0.03});

MathFunctionNamespace ns2;
MathFunction func2(ns2, "g(x, y)", "f(x, 1, y)");
double val2 = func2.invoke({-1.0, 1.0});
```

## Example snippet 
```C++
#include <stdio.h>
#include <math.h>

#include <TangentsMathFunc.hpp>

using namespace std;

int main(int argc, char* argv[])
{
  // Example using default namespace and declare a function 'f(a, b, c) = (a + b) ^ c',
  //  where the operator '^' means power.
  MathFunction func0("f(a, b, c)", "(a + b) ^ c");
  double ret0 = func0.invoke({1.0, 2.0, 0.03});

  // Another example using default namespace with reference to the previously declared function
  //  and a built-in function 'log()'.
  MathFunction func1("g(x, y, z)", "log(f(x, y, z) - 1)");
  double ret1 = func1.invoke({1.0, 2.0, 0.03});

  // Print out the results.
  fprintf(stdout, "%.4f, %.4f\n", ret0, ret1);

  // Example using custom namespace.
  MathFunctionNamespace ns;

  // Declare a function in another namespace, independent to the default one.
  MathFunction func2(ns, "f(a, b, c)", "(a + b) / c");
  double ret2 = func2.invoke({1.0, 2.0, 0.03});

  double ret3 = nan("");
  try
  {
    // Custom namespace does not support built-in functions.
    MathFunction func3(ns, "g(x, y, z)", "log(f(x, y, z))");
    ret3 = func3.invoke({1.0, 2.0, 0.03});
  }
  catch(const InvalidFormulaException& ex)
  {
    fprintf(stderr, "%s\n", ex.what());
  }

  // Print out the results.
  fprintf(stdout, "%.4f, %.5f\n", ret2, ret3);

  return 0;
}
```
# Changelog
## 1.0.2
Restructure codes and populate readme. No implementation change was made.

## 1.0.1
Initial commit.
