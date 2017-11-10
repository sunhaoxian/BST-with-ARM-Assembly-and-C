cs30fand

1. G, C, E, A, D, F, J, I, H, B

2. For the mistake when testing "make testbst2", after setting a as a root 
and c as its right child. When I try to add "b", it fails since bst -> root
-> right -> left is null, which means that b has not been added successfully.
To fix this problem, we can build to loop a compare the key of input with
the key of each node in tree. If it is less than the node in tree, and if
the left pointer is null, then set the input node there.

   For the mistake when test "make tebst9", it shows that the char* which 
has been returned when testing TestMax is "b". However, I've already built
a tree with root = "c" and root -> left = "b". In this case, the correct
answer is "c", also the rightmost node. Hence, if we tend to fix it, we 
can create a loop to arrive the rightmost node of trees, and then return
the key of that node.


