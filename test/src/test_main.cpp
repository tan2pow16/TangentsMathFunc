#include <stdio.h>

#include <TangentsMathFunc.hpp>

using namespace std;

int main(int argc, char* argv[])
{
  MathFunctionNamespace ns;

  MathFunction func0("f(a, b, c)", "(a + b) ^ c");
  double ret0 = func0.invoke({1.0, 2.0, 0.03});

  MathFunction func1("g(x, y, z)", "log(f(x, y, z) - 1)");
  double ret1 = func1.invoke({1.0, 2.0, 0.03});

  fprintf(stdout, "%.4f, %.4f", ret0, ret1);
  return 0;
}
