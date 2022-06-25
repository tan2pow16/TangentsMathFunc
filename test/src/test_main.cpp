/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 */

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
