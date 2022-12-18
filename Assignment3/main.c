// string to use is “FLOCCINAUCINIHILIPILIFICATION”
#include "bst_skeleton.c"

int main(){
    char data[] = "FLOCCINAUCINIHILIPILIFICATION";
    Tree_Node * BSTPointer = create_bst(data);
    Tree_Node * ptr = tree_search(BSTPointer, 'N');
    tree_print_sorted(BSTPointer);
}