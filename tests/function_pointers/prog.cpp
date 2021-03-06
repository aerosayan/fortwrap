#include "FortWrap.h"

// Procedure pointers are called directly without wrappers, so can't
// convert pass-by-value to pass-by-reference.  Check the generated
// header file for the correct function signature.
int add(const int *a, const int *b) 
{
  return *a + *b;
}

int add_byval(int a, int b)
{
  return a + b;
}


int main(void) 
{

  int a=1, b=2;

  // Demonstrate that function pointers can be stored in a derived type
  Container c(add, a,b);
  if (c.container_callf() != a + b)
    return 1;

  // Demonstrate direct use of a function pointer callback
  if (FortFuncs::callf(add, a, b) != a + b)
    return 2;
  if (FortFuncs::callf_value(add_byval, a, b) != a + b)
    return 3;
  if (FortFuncs::callf_bindc(add_byval, a, b) != a + b)
    return 4;

  // Optional arguments
  if (FortFuncs::callf_opt(a, b, add) != a + b)
    return 5;
  if (FortFuncs::callf_opt(a, b) != -1)
    return 6;

  return 0;
}
