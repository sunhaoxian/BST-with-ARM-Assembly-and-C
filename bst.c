#include "bst.h"
#include <stdio.h>
#include <string.h>

/*
 * This file is to build several functions dealing with a binary search tree,
 * where we can create a new node, add the node into tree, or remove a 
 * specific node from the tree. In addition, we can also count the number of
 * nodes and the sum of the lengths of each key.
 *
 */ 

// void bst_addHelper(struct BSTNode* node, char* key);
// struct BSTNode* bst_addHelper(struct BSTNode* node, char* key);

// struct BSTNode* bst_removeHelper(struct BSTNode* node, char* key);
// void bst_removeHelper(struct BSTNode* node, char* key);

//declare a helper function
void bst_deleteTreeHelper(struct BSTNode* node);  



/**
 *  bst_max - finds the key of the largest (rightmost) node in this bst.
 *
 *  Parameters:
 *    struct BST* bst - tree whose largest node we're looking for.
 *
 *  Return value: largest key in the tree, or
 *    empty string if tree is empty.
 */
char* bst_max(struct BST* bst) {
	struct BSTNode* node = bst->root;

	//if node is not null, promote to the rightmost node
	//and return the key
	if (node) {
		while (node->right) {
			node = node->right;
		}
    		return node->key;
  	}

	//if it is null, return null 
	else {
    		return NULL;
  	}
}



/*
 * bst_makeNode - create a new node with the input parameters
 *
 * Parameters:
 * 	char* key - the key contained by the new node
 * 	struct BSTNode* left - the pointer pointing to the left node
 * 	struct BSTNode* right - the right pointer of new node
 *
 * Return value: the new node which has been created by these 3 parameters
 */ 
struct BSTNode* bst_makeNode (char* key, struct BSTNode* left,
				struct BSTNode* right) {

	//allocate the memory with size of BSTNode
	struct BSTNode* n = malloc(sizeof(struct BSTNode));

	//duplicate the input key into memory
	n -> key = strdup(key);

	//set the left pointer 
	n -> left = left;

	//set the right pointer
	n -> right = right;
	return n;
}



/*
 * bst_contains - search the tree for a node with the specific key
 *
 * Parameters:
 * 	struct BST* bst - the tree to be searched through
 * 	char* key - the key needs to be found
 *
 * Return value: Return 1 if the node was found; otherwise return 0
 */ 
int bst_contains (struct BST* bst, char* key) {

	//initialize integer for further while loop
	int compare = 0;
	int zero = 0;

	//if the tree is empty, return 0
	if (bst -> root == NULL) {
		return 0;
	}

	//if the key is null, return 0
	if (key == NULL) {
		return 0;
	}

	//set a variable same as root
	struct BSTNode* start = bst -> root;

	//a loop to keep checking
	while (start != NULL)  {

		//compare the input key with each key of node in tree
		compare = strcmp(key, start -> key);

		//if we find it
		if (compare == 0) {
			return 1;
		}

		//if it should be in the left subtree
		if (compare < 0) {

			//if left is not null, promote checking
			if (start -> left) {
				start = start -> left;
			}

			//otherwise, return 0
			else {
				return 0;
			}
		}

		//check the right subtree
		else {
			if (start -> right) {
				start = start -> right;
			}
			else {
				return 0;
			}
		}	
	}
	return zero;
}



/*
 * bst_min - This function should return the key of the smallest node in the 
 * 	     tree.
 *
 * Parameters: struct BST* bst - the tree need to be searched
 * 
 * Return value: the node with the smallest key
 */ 
char* bst_min(struct BST* bst) {

	//if the tree is empty, return null
	if (bst -> root == NULL) {
		return NULL;
	}
	
	
	struct BSTNode* start = bst -> root;
	char* min = start -> key;

	//promote to the leftmost node
	while (start -> left != NULL) {

		//store the key of that node
		min = start -> left -> key;

		//each time move left
		start = start -> left;
	}
	return min;
}



/*
 * bst_add - This function should add a BSTNode* with the specified key to 
 * 	     bst
 *
 * Parameters: struct BST* bst - the binary search tree which should be used
 * 	       char* key - the key should be set into a node and added into
 * 	       		   bst
 *
 * Return value: None
 */ 
void bst_add(struct BST* bst, char* key) {

	//if the key is null, end
	if (key == NULL) {
		return;
	}

	//if the tree does not contain key, end
	int check = bst_contains (bst, key);
	if (check == 1) {
		return;
	}

	//create a new node with key
	int compare = 0;
	struct BSTNode* node = bst_makeNode(key, NULL, NULL);

	//if the tree is empty, set root
	if (bst -> root == NULL) {
		bst -> root = node;
		return;
	}
	
	struct BSTNode* start = bst -> root;

	//loop through each node in tree
	while (start != NULL) {

		//compare the key with the key of each node
		compare = strcmp(key, start -> key);

		//if the key is less, checking left
		if (compare < 0) {

			//if the left one is empty, set the node there
			if (start -> left == NULL) {
				start -> left = node;
				return;	
			}

			//otherwise, promote left checking
			else {
				start = start -> left;
			}
		}

		//if the key is bigger, checking rightward
		else {
			if (start -> right == NULL) {
				start -> right = node;
				return;
			}
			else {
				start = start -> right;
			}
		}
	}
}



/*
 * bst_remove - This function should remove the BSTNode* with the specified
 * 		key from bst.
 *
 * Parameters:  struct BST* bst - the tree needs to be searched
 * 		char* key - the key contained by a node which should be 
 * 			    removed
 *
 * Return Value: None
 */
void bst_remove(struct BST* bst, char* key) {
	int compare = 0;
	int compare1 = 0;
	int compare2 = 0;

	//if the key is null, end
	if (key == NULL) {
		return;
	}
	
	//if the root is null, return
	if (bst -> root == NULL) {
		return;
	}

	//see if the key is inside the tree
	int check = bst_contains(bst, key);
	if (check == 0) {
		return;
	}
	
	//set checking and parent variables
	struct BSTNode* start = bst -> root;
	struct BSTNode* parent = NULL;
	struct BSTNode* find = NULL;

	//keep checking the existence of specific node
	while (start != NULL) {

		//initialize the parent pointer
		parent = start;

		//compare input key with every key of tree
		compare = strcmp(key, start -> key);

		//promoting according to the comparison
		if (compare < 0) {
			
			start = start -> left;
		}
		
		if (compare > 0) {
			
			start = start -> right;
		}

		//after promotion, compare again to separate the parent 
		//pointer from the start pointer
		compare1 = strcmp(key, start -> key);

		//if this time we find the node
		if (compare1 == 0) {

			//check which side the parent pointer is at
			compare2 = strcmp(start -> key, parent -> key);

			//if that node has 2 children
			if (start -> right != NULL && start -> left != NULL) {

				//promote to the right subtree and reset 
				//parent pointer
				parent = start;
				find = start -> right;

				//find the leftmost node in the right subtree
				while (find -> left != NULL) {
					parent = find;
					find = find -> left;
				}

				//compare the key of parent and leftmost node
				compare = strcmp(parent -> key, find -> key);

				//build a new connection by changing the 
				//pointer
				if (compare < 0) {
					parent -> right = find -> right;
				}
				else {
					parent -> left = find -> right;
				}

				//reset the new key and free the leftmost key
				free(start -> key);
				start -> key = strdup(find-> key);		
				free (find -> key);
				free (find);
				return;
			}

			//if it only has left child
			else if (start -> left != NULL) {

				//reset the pointer according to the position
				//of parent node
				if (compare2 == 0) {
					bst -> root = start -> left;
				}
				if (compare2 < 0) {
					parent -> left = start -> left;
				}
				if (compare2 > 0) {
					parent -> right = start -> left;
				}

				//free the replaced node
				free (start -> key);
				free (start);
				return;
			}
			
			//if it only has right child
			else if (start -> right != NULL) {
				if (compare2 == 0) {
					bst -> root = start -> right;
				}
				if (compare2 < 0) { 
					parent -> left = start -> right;
				}
				if (compare2 > 0) {
					parent -> right = start -> right;
				}
				free (start -> key);
				free (start);
				return;
			}
			
			//if it doesn't have any children
			else {	
				if (compare2 < 0) {
					parent -> left = start -> left;
				}
				if (compare2 > 0) {
					parent -> right = start -> right;
				}
				if (compare2 == 0) {
					bst -> root = start -> right;
				}
				
				free (start -> key);
				free (start);
				return;
			}
		}	
		
	}
}



/*
 * bst_count - count the number of nodes in a tree
 *
 * Parameter: struct BST* bst - the tree needs to be searched
 *
 * Return Value: If the tree is empty, return 0. Otherwise, return
 * 		 the number of nodes
 */ 
int bst_count(struct BST* bst) {
	if (bst -> root == NULL) {
		return 0;
	}
	return count(bst -> root);
} 



/*
 * bst_totalLength - It sums the lengths of all the keys in bst, and 
 * 		     return the value.
 *
 * Parameter: struct BST* bst - the tree needs to be searched
 *
 * Return Value: If the tree is empty, return 0. Otherwise, return the 
 * 		 total result from helper method
 */ 
int bst_totalLength(struct BST* bst) {
	if (bst -> root == NULL) {
		return 0;
	}
	return totalLength(bst -> root);
}



/*
 * bst_deleteTree - This function deletes the whole bst tree.
 *
 * Parameter: struct BST* bst - the tree needs to be searched
 *
 * Return Value: None
 */ 
void bst_deleteTree(struct BST* bst) {

	//if the tree is empty
	if (bst -> root == NULL) {
		free(bst);
		return;
	}

	//otherwise, call helper method
	bst_deleteTreeHelper(bst -> root);
	free(bst);
	return;
}



/*
 * bst_deleteTreeHelper - This function deletes each node in the tree
 *
 * Parameter: struct BSTNode* node - the starting node
 *
 * Return Value: None
 */ 
void bst_deleteTreeHelper(struct BSTNode* node) {

	//if the node is null, end
	if (node == NULL) {
		return;
	}

	//call recursively if it still has right or left node
	bst_deleteTreeHelper(node -> right);
	bst_deleteTreeHelper(node -> left);

	//free its key and itself
	free(node -> key);
	free(node);
}
