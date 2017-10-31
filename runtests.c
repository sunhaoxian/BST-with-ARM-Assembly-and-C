/*
 * Do not edit this file. Feel free to read it! It just starts up the tester.
 *
 * This is derived from the CuTest documentation: https://github.com/ennorehling/cutest
 *
 */
#include "cutest/CuTest.h"
#include <stdio.h>
#include <stdlib.h>
    
CuSuite* StrUtilGetSuite();

void RunAllTests(void) {
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();
  CuSuite* ourSuite = StrUtilGetSuite();
  
  CuSuiteAddSuite(suite, ourSuite);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  CuStringDelete(output);
  CuSuiteDelete(suite);
  free(ourSuite);
}

int main(void) {
  RunAllTests();
  return 0;
}