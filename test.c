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
  // This is a lot of manually allocating! Once you write bst_makeNode, this
  // can get simpler
  struct BSTNode* node = (struct BSTNode*)malloc(sizeof(struct BSTNode));
  node->key = strdup("apple");
  node->left = NULL;
  node->right = NULL;
  CuAssertStrEquals(tc, "apple", node->key);

  struct BSTNode* forRight = (struct BSTNode*)malloc(sizeof(struct BSTNode));
  forRight->key = strdup("cranberry");
  forRight->left = NULL;
  forRight->right = NULL;

  struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
  bst->root = node;
  bst->root->right = forRight;

  CuAssertStrEquals(tc, "cranberry", bst_max(bst));

  // This is a lot of freeing! Once you write the delete functions this won't
  // be necessary anymore; the next five lines should really just be
  // bst_deleteTree

  bst_deleteTree(bst);
}



/*
 * This function is to test whether makeNode function is correct
 */ 
void TestMakeNode(CuTest *tc) {
	
	//call that function to create a node
	struct BSTNode* result = bst_makeNode("n", NULL, NULL);

	//test each element of it
	CuAssertPtrNotNull(tc, result);
	CuAssertPtrEquals(tc, NULL, result -> left);
	CuAssertPtrEquals(tc, NULL, result -> right);
	CuAssertStrEquals(tc, "n", result -> key);

	//free the node
	free(result -> key);
	free(result);
}



/*
 * This function is to test the add case
 */ 
void TestAdd(CuTest *tc) {
	struct BST* bst = (struct BST*)malloc(sizeof(struct BST));

	//when the tree is empty, add "a"
	bst -> root = NULL;
	bst_add(bst, "a");
	CuAssertPtrNotNull(tc, bst -> root);
	CuAssertStrEquals(tc, "a", bst -> root -> key);

	//when trying to add another "a"
	bst_add(bst, "a");
	CuAssertPtrEquals(tc, NULL, bst -> root -> left);
	CuAssertPtrEquals(tc, NULL, bst -> root -> right);
	CuAssertPtrNotNull(tc, bst -> root);

	//when adding "c" into the tree
	bst_add(bst, "c");
	CuAssertPtrEquals(tc, NULL, bst -> root -> left);
	CuAssertPtrNotNull(tc, bst -> root -> right);
	CuAssertStrEquals(tc, "c", bst -> root -> right -> key);
	CuAssertPtrEquals(tc, NULL, bst -> root -> right -> left);
	CuAssertPtrEquals(tc, NULL, bst -> root -> right -> right);

	//when adding "b"
	bst_add(bst, "b");
	CuAssertPtrNotNull(tc, bst -> root -> right -> left);
	CuAssertStrEquals(tc, "b", bst -> root -> right -> left -> key);
	CuAssertPtrEquals(tc, NULL, bst -> root -> right -> right);

	//when adding "d"
	bst_add(bst, "d");
	CuAssertPtrNotNull(tc, bst -> root -> right -> right);
	CuAssertStrEquals(tc, "d", bst -> root -> right -> right -> key);

	bst_deleteTree(bst); 
} 



/*
 * This function is to test the bst_contains function
 */ 
void TestContains(CuTest *tc) {

	struct BSTNode * node = bst_makeNode("e", NULL, NULL);

	//search "a" in an empty tree
	struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
	bst -> root = NULL;
	CuAssertPtrNotNull(tc, bst);
	int zero = bst_contains(bst, "a");
	CuAssertPtrEquals(tc, NULL, bst -> root);
	CuAssertIntEquals(tc, 0, zero);

	//set "e" as root and check its existence
	bst -> root = node;
	CuAssertPtrNotNull(tc, bst -> root);
	CuAssertStrEquals(tc, "e", bst -> root -> key);
	int number = bst_contains(bst, "e");
	CuAssertIntEquals(tc, 1, number);

	//add f into the tree and check it
	struct BSTNode * node1 = bst_makeNode("f", NULL, NULL);
	bst -> root -> right = node1;
	CuAssertPtrNotNull(tc, bst -> root -> right);
	CuAssertStrEquals(tc, "f", bst -> root -> right -> key);
	int result0 = bst_contains(bst, "f");
	CuAssertIntEquals(tc, 1, result0);

	//add b into the tree and check it
	struct BSTNode * node2 = bst_makeNode("b", NULL, NULL);
	bst -> root -> left = node2;
	CuAssertPtrNotNull(tc, bst -> root -> left);
	CuAssertStrEquals(tc, "b", bst -> root -> left -> key);
	int result1 = bst_contains(bst, "b");
	CuAssertIntEquals(tc, 1, result1);

	//check if c exists
	int result2 = bst_contains(bst, "c");
	CuAssertPtrEquals(tc, NULL, bst -> root -> left -> right);
	CuAssertIntEquals(tc, 0, result2);

	//add more nodes
	bst_add(bst, "z");
	bst_add(bst, "y");
	bst_add(bst, "u");
	bst_add(bst, "i");
	bst_add(bst, "p");
	bst_add(bst, "zzz");
	
	int num1 = bst_contains(bst, "zz");
	CuAssertIntEquals(tc, 0, num1);

	
	int result3 = bst_contains(bst, "");
	CuAssertIntEquals(tc, 0, result3);
	
	bst_deleteTree(bst);
}



/*
 * This function tests the bst_min function
 */ 
void TestMin(CuTest *tc) {

	//test an empty tree
	struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
	bst -> root = NULL;
	char* result = bst_min(bst);
	CuAssertPtrEquals(tc, NULL, bst -> root);
	CuAssertStrEquals(tc, NULL, result);

	//add e and check the min
	struct BSTNode * node1 = bst_makeNode("e", NULL, NULL);
	bst -> root = node1;
	char* result1 = bst_min(bst);
	CuAssertPtrNotNull(tc, bst -> root);
	CuAssertStrEquals(tc, "e", result1);

	//add two more nodes and test the min
	struct BSTNode * node2 = bst_makeNode("c", NULL, NULL);
	struct BSTNode * node3 = bst_makeNode("a", NULL, NULL);
	
	bst -> root -> left = node2;
	bst -> root -> left -> left = node3;
	char* result2 = bst_min(bst);
	CuAssertPtrNotNull(tc, bst -> root -> left);
	CuAssertPtrNotNull(tc, bst -> root -> left -> left);
	CuAssertStrEquals(tc, "a", result2);

	bst_deleteTree(bst);
}


//This function is to test bst_Max function
void TestMax(CuTest *tc) {

	//test the empty gree
	struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
	bst -> root = NULL;
	char* result = bst_max(bst);
	CuAssertPtrEquals(tc, NULL, bst -> root);
	CuAssertPtrEquals(tc, NULL, result);

	//create different nodes
	struct BSTNode* node1 = bst_makeNode("c", NULL, NULL);
	struct BSTNode* node2 = bst_makeNode("b", NULL, NULL);
	struct BSTNode* node3 = bst_makeNode("f", NULL, NULL);
	struct BSTNode* node4 = bst_makeNode("zoo", NULL, NULL);
	struct BSTNode* node5 = bst_makeNode("g", NULL, NULL);	

	//add different nodes and check the max value
	bst -> root = node1;
	bst -> root -> left = node2;
	CuAssertPtrNotNull(tc, bst -> root);
	CuAssertPtrNotNull(tc, bst -> root -> left);
	char* result0 = bst_max(bst);
	CuAssertStrEquals(tc, "c", result0);

	bst -> root -> right = node3;
	bst -> root -> right -> right = node4;
	CuAssertPtrNotNull(tc, bst -> root -> right);
	CuAssertPtrNotNull(tc, bst -> root -> right -> right);
	char* result1 = bst_max(bst);
	CuAssertStrEquals(tc, "zoo", result1);

	bst -> root -> right -> right -> left = node5;
	CuAssertPtrNotNull(tc, bst -> root -> right -> right -> left);
	char* result2 = bst_max(bst);
	CuAssertStrEquals(tc, "zoo", result2);

	bst_deleteTree(bst);
}


//This function is to check bst_remove function 
void TestRemove(CuTest *tc) {

	//check empty tree
	struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
	bst -> root = NULL;
	bst_remove(bst, "a");
	CuAssertPtrEquals(tc, NULL, bst -> root);

	//add 4 nodes	
	bst_add(bst, "e");
	bst_add(bst, "d");
	bst_add(bst, "c");
	bst_add(bst, "a");

	CuAssertPtrNotNull(tc, bst -> root);
	CuAssertPtrNotNull(tc, bst -> root -> left);
	CuAssertStrEquals(tc, "e", bst -> root -> key);
	CuAssertStrEquals(tc, "d", bst -> root -> left -> key);
	CuAssertPtrNotNull(tc, bst -> root -> left -> left);
	CuAssertStrEquals(tc, "c", bst -> root -> left -> left -> key);

	bst_remove(bst, "e");
	CuAssertPtrNotNull(tc, bst -> root);
	CuAssertStrEquals(tc, "d", bst -> root -> key);
	CuAssertPtrNotNull(tc, bst -> root -> left);
	CuAssertPtrNotNull(tc, bst -> root -> left -> left);
	CuAssertStrEquals(tc, "c", bst -> root -> left -> key);
	CuAssertStrEquals(tc, "a", bst -> root -> left -> left -> key);

	bst_remove(bst, "c");
	CuAssertPtrNotNull(tc, bst -> root -> left);
	CuAssertStrEquals(tc, "a", bst -> root -> left -> key);

	bst_add(bst, "j");
	CuAssertPtrNotNull(tc, bst -> root -> right);

	bst_add(bst, "h");
	bst_add(bst, "f");
	bst_add(bst, "i");
	bst_add(bst, "x");
	CuAssertPtrNotNull(tc, bst -> root -> right -> right);

	bst_add(bst, "y");
	CuAssertPtrNotNull(tc, bst -> root -> right -> right -> right);

	CuAssertStrEquals(tc, "f", bst->root->right->left->left->key);
	bst_remove(bst, "d");
	CuAssertPtrNotNull(tc, bst -> root);
	CuAssertStrEquals(tc, "f", bst -> root -> key);
	CuAssertPtrEquals(tc, NULL, bst -> root -> right -> left -> left);

	bst_remove(bst, "f");
	CuAssertPtrNotNull(tc, bst -> root);
	CuAssertStrEquals(tc, "h", bst -> root -> key);
	CuAssertPtrNotNull(tc, bst -> root -> right -> left);
	CuAssertStrEquals(tc, "i", bst -> root -> right -> left -> key);
	
	bst_remove(bst, "19");
	bst_remove(bst, "j");
	CuAssertPtrNotNull(tc, bst -> root -> right);
	CuAssertStrEquals(tc, "x", bst -> root -> right -> key);
	CuAssertPtrNotNull(tc, bst -> root -> right -> right);
	CuAssertStrEquals(tc, "y", bst -> root -> right -> right -> key);
	
	bst_remove(bst, "y");
	CuAssertPtrEquals(tc, NULL, bst -> root -> right -> right);
	
	bst_deleteTree(bst);
}



//Test the bst_count function
void TestCount(CuTest* tc) {

	//test an empty tree
	struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
	bst -> root = NULL;
	int number = bst_count(bst);
	CuAssertIntEquals(tc, 0, number);
	
	//add and remove several nodes and compare the number of nodes
	bst_add(bst, "a");
	CuAssertPtrNotNull(tc, bst -> root);
	int number1 = bst_count(bst);
	CuAssertIntEquals(tc, 1, number1);

	bst_remove(bst, "a");
	CuAssertPtrEquals(tc, NULL, bst -> root);
	int number0 = bst_count(bst);
	CuAssertIntEquals(tc, 0, number0);

	bst_add(bst, "e");
	bst_add(bst, "c");
	bst_add(bst, "a");
	bst_add(bst, "j");
	bst_add(bst, "f");
	
	int number2 = bst_count(bst);
	CuAssertIntEquals(tc, 5, number2);
	
	bst_add(bst, "b");
	bst_add(bst, "d");
	bst_add(bst, "l");

	int number3 = bst_count(bst);
	CuAssertIntEquals(tc, 8, number3);
	
	bst_remove(bst, "e");
	int number4 = bst_count(bst);
	CuAssertIntEquals(tc, 7, number4);	
	
	bst_deleteTree(bst);
}



//Test the bst_totalLength function
void TestTotalLength(CuTest* tc) {

	//when the tree is empty
	struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
	bst -> root = NULL;
	int number = bst_totalLength(bst);
	CuAssertIntEquals(tc, 0, number);

	//add different strings and check the return
	bst_add(bst, "abcd");
	CuAssertPtrNotNull(tc, bst -> root);
	int number1 = bst_totalLength(bst);
	CuAssertIntEquals(tc, 4, number1);

	bst_add(bst, "efg");
	bst_add(bst, "hijk");
	bst_add(bst, "b");
	
	int number2 = bst_totalLength(bst);
	CuAssertIntEquals(tc, 12, number2);

	bst_remove(bst, "efg");
	int number3 = bst_totalLength(bst);
	CuAssertIntEquals(tc, 9, number3);
	
	bst_remove(bst, "b");
	int number4 = bst_totalLength(bst);
	CuAssertIntEquals(tc, 8, number4);

	bst_add(bst, "zzzza");
	int number5 = bst_totalLength(bst);
	CuAssertIntEquals(tc, 13, number5);

	bst_add(bst, "c");
	int number6 = bst_totalLength(bst);
	CuAssertIntEquals(tc, 14, number6);	
	
	bst_deleteTree(bst);
}



/*
 * Note that as you add new testing functions, you need to add them to the list
 * below using SUITE_ADD_TEST. Otherwise they will not run.
 */
CuSuite* StrUtilGetSuite() {
	CuSuite* suite = CuSuiteNew();
 	SUITE_ADD_TEST(suite, TestManualMallocAndFree);
  	SUITE_ADD_TEST(suite, TestMakeNode);
  	SUITE_ADD_TEST(suite, TestContains);
  	SUITE_ADD_TEST(suite, TestMin);
  	SUITE_ADD_TEST(suite, TestMax);
  	SUITE_ADD_TEST(suite, TestAdd);
 	SUITE_ADD_TEST(suite, TestRemove);
  	SUITE_ADD_TEST(suite, TestCount);
  	SUITE_ADD_TEST(suite, TestTotalLength);
 	return suite;
}
