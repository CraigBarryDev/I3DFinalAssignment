#include "tree.h"

tree* create_tree(void* data) {
	//Create the tree object
	tree* t = (tree*)malloc(sizeof(tree));

	//Create the root node of the tree
	treeNode* root = (treeNode*)malloc(sizeof(treeNode));
	//Initialize tree root node
	root->data = data;
	root->nChildren = 0;
	root->children = NULL;

	//Set the tree root
	t->root = root;

	//Return tree object
	return t;
}

treeNode* tree_add(treeNode* parent, void* data) {
	//Create new node
	treeNode node;
	node.data = data;
	node.nChildren = 0;
	node.children = NULL;

	//If the parent already has children
	if(parent->children) {
		parent->children = (treeNode*)realloc(parent->children, sizeof(treeNode) * (parent->nChildren + 1));
	}
	else {
		parent->children = (treeNode*)malloc(sizeof(treeNode));
	}
	//Set the created node as the last child of the parent
	parent->children[parent->nChildren] = node;
	
	//Increment number of children in root node
	parent->nChildren++;

	//Return pointer to newest parent
	return &parent->children[parent->nChildren - 1];
}

void destroy_node_recursive(treeNode* node) {
	for(int i = 0; i < node->nChildren; i++) {
		destroy_node_recursive(&node->children[i]);
	}
	if(node->nChildren) free(node->children);
}

void destroy_tree(tree* t) {
	destroy_node_recursive(t->root);
	free(t->root);
	free(t);
}