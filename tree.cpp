/**
    @author [mst]
    @file   tree.cpp
    @brief  Binary tree implementations and utils
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
	TreeNode *parent; // the parent node is not always available
	TreeNode() : val(-1), left(nullptr), right(nullptr){}	// here invalid value is -1
	TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){}

	void printInOrder(){
		if (left) { left->printInOrder(); }
		cout << val << endl;
		if (right) { right->printInOrder(); }
	}

	// binary search tree insertion (recursive)
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

	// insertion overloaded for array-to-tree conversion
	void insert(int arr[], int size) {
		if (size == 0) return;
		for(int i = 0; i<size; i++) {
			this->insert(arr[i]);
		}
	}

	// check if a value present in the given (sub)tree
	bool find (int val) {
		TreeNode *root=this;
		if (root == nullptr){
			return false;
		}

		if (root->val == val) return true;
		if (val > root->val) {
			return right->find(val);
		} else {
			return left->find(val);
		}
	}

	// used in leetcode 226, a recursive tree inversion
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

	// [here] use https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/ to complete
	// In Binary Tree, Inorder successor of a node is the next node in Inorder traversal of the Binary Tree.
	// Inorder Successor is NULL for the last node in Inorder traversal.
	// used in leetcode 285 [here] also, consider a version with a parent pointer type of nodes
	int inOrderSuccessor (int val) {
		// reached a leaf (int not found)
		if (this == nullptr) {
			return -1;
		}

		// value found - indicate that spotted
		if (val == this->val) {
			if (this->right) return this->right->val;
			return -2;
		}
		int res;
		if (val > this->val) {
			res = right->inOrderSuccessor(val);
			if (res == -2) return this->val;
			return res;
		} else {
			res = left->inOrderSuccessor(val);
			if (res == -2) return this->val;
			return res;
		}
	}




};

// this is singled-out as a specific solution for leetcode
// time: O(n) we must visit each tree node at least once
// space: O(n) n nodes visited will populate the stack
class TreeUtils {
public:
    int treeDepth (TreeNode *root) {
        if (root == nullptr){
			return 0;
		}

        // in bst we only care about leftmost leaf for depth
        return 1 + treeDepth(root->left);
    }

    // [wip] print the bst in a sexy way. se charmap?
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
	//    4
	//   / \
	//  2   7
	// / \  / \
	//1   3 6  9

	int array[7] = { 4,2,7,1,3,6,9 };
	tree1.insert(array,7);
	cout << "inputting: [4,2,7,1,3,6,9]" << endl;
	tree1.printInOrder();	// [wip] i want a sexy tree-like print!
	//utils.fancyPrint(&tree1);


	// finding an integer in a tree
	int target1 = 6;
	string res = (tree1.find(target1))?"true":"false";
	cout << "finding " <<target1<<" in tree1: " << res << endl;


    // inverting a binary tree (used in leetcode 226)
	cout << "inverting..." << endl;
	tree1.invertTree(&tree1);
	tree1.printInOrder();
	tree1.invertTree(&tree1);	// revert state

	// in-order successor
	int target2 = 3;
	cout << "in-order successor of: " <<target2<<" in tree1: " << tree1.inOrderSuccessor(target2) << endl;




	cin.get(); // pseudo-pause the console
	return 0;
}
