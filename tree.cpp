/**
    @author [mst]
    @file   tree.cpp
    @brief  Linked list implementations
    Binary search tree implementation and best practices doodle

    features, changelog:
    -2022.11: -initial draft

    @author [mst]
    @version 0.1 2022.04
*/

////////////////// LIBS
#include <iostream>         // usage of console prints
using namespace std;


////////////////// DECL_IMPL

class TreeNode {
private:
	
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	// [demo][wip] various constructor syntaxes?
	//TreeNode(){
	//	val = 0;
	//	left = nullptr;
	//	right = nullptr;
	//}
	TreeNode() : val(-1), left(nullptr), right(nullptr){}	// here invalid value is -1
	TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){}

	void printInOrder(){
		if (left) { left->printInOrder(); }
		cout << val << endl;
		if (right) { right->printInOrder(); }
	}

	// binary search tree insertion
	void insert(int x) {
		// empty tree case
		if (val == -1) {
			val = x;
			return;
		}
		
		if (x <= val) {	// value lesser than the root will be routed left
			if (left == nullptr){ left = new TreeNode(x); }	// empty left node
			else {
				left->insert(x);	// non empty left node
			}
		}
		else {	// value higherr than the root will be routed right
			if (right == nullptr){ right = new TreeNode(x); }	// empty right node
			else {
				right->insert(x);	// non empty right node
			}			
		}
	}

};

// this is singled-out as a specific solution for leetcode
// time: O(n) we must visit each tree node at least once
// space: O(n) n nodes visited will populate the stack
class TreeUtils {
public:
	TreeNode* invertTree(TreeNode* root){
		// stopping condition: we are at the leaf
		if (root == nullptr){
			return root;
		}

		TreeNode* left = invertTree(root->left);	// this will traverse down to the leaves and keep nodes in the stack for inversion
		TreeNode* right = invertTree(root->right);

		root->left = right;	// the actual re-routing of the nodes
		root->right = left;

		return root;
	}

    int treeDepth (TreeNode *root) {
        if (root == nullptr){
			return 0;
		}

        // in bst we only care about leftmost leaf for depth
        return 1 + treeDepth(root->left);
    }

    // [wip][here] print the bst in a sexy way
    // [bp] use charmap?
    void fancyPrint (TreeNode *root) {
        if (root == nullptr){
			return;
		}        

        int depth = treeDepth(root);
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << root->val << endl;
        for (int j = 0; j < depth-1; j++) cout << "  ";
        cout << '/' << "  " << '\\' << endl;

        fancyPrint(root->left);        
        fancyPrint(root->right);

    }

};




////////////////// DRIVER
int main()
{
	cout << "[mst] binary tree doodle" << endl << endl;

	TreeNode tree1;

	// inserting values as the example shows: [4,2,7,1,3,6,9]
	tree1.insert(4);
	tree1.insert(2);
	tree1.insert(7);
	tree1.insert(1);
	tree1.insert(3);
	tree1.insert(6);
	tree1.insert(9);
	cout << "inputting: [4,2,7,1,3,6,9]" << endl;
	tree1.printInOrder();	// [wip] i want a sexy tree-like print!


    // inverting a binary tree (used in leetcode 226)
	cout << "inverting..." << endl;
	TreeUtils utils;
	TreeNode* tree2 = utils.invertTree(&tree1);
	tree2->printInOrder();

    //utils.fancyPrint(&tree1);

	

	cin.get(); // pseudo-pause the console
	return 0;
}
