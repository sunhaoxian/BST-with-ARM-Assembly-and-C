#include "cutest/CuTest.h"
#include "bst.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
    
/*
 * Your tests won't look like this; they will use helpers like makeNode and
 * call the actual bst_ functions. This is here to give you an example of
 * creating space for a BSTNode with malloc and using a testing function to
 * check the string.
 *
 */
void TestManualMallocAndFree(CuTest *tc) {
  struct BSTNode* bst = (struct BSTNode*)malloc(sizeof(struct BSTNode));
  bst->key = strdup("abcd");
  bst->left = NULL;
  bst->right = NULL;
  CuAssertStrEquals(tc, "abcd", bst->key);

  free(bst->key);
  free(bst);
}



/*
 * Note that as you add new testing functions, you need to add them to the list
 * below using SUITE_ADD_TEST. Otherwise they will not run.
 */
CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, TestManualMallocAndFree);
  return suite;
}
